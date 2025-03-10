/******************************************************************************
 *
 *  Copyright (C) 2009-2012 Broadcom Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at:
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 ******************************************************************************/


/*****************************************************************************
 *
 *  Filename:      btif_rc.c
 *
 *  Description:   Bluetooth AVRC implementation
 *
 *****************************************************************************/
#include <hardware/bluetooth.h>
#include <fcntl.h>
#include "bta_api.h"
#include "bta_av_api.h"
#include "avrc_defs.h"
#include "bd.h"
#include "gki.h"

#define LOG_TAG "BTIF_RC"
#include "btif_common.h"

/*****************************************************************************
**  Constants & Macros
******************************************************************************/
#define BTIF_RC_USE_UINPUT TRUE
#include "uinput.h"

/* cod value for Headsets */
#define COD_AV_HEADSETS        0x0404


/*****************************************************************************
**  Local type definitions
******************************************************************************/
typedef struct {
    BOOLEAN                     rc_connected;
    UINT8                       rc_handle;
    BD_ADDR                     rc_addr;
    UINT16                      rc_pending_play;
} btif_rc_cb_t;

#ifdef BTIF_RC_USE_UINPUT
#define MAX_UINPUT_PATHS 3
static const char* uinput_dev_path[] =
                       {"/dev/uinput", "/dev/input/uinput", "/dev/misc/uinput" };
static int uinput_fd = -1;

static int  send_event (int fd, uint16_t type, uint16_t code, int32_t value);
static void send_key (int fd, uint16_t key, int pressed);
static int  uinput_driver_check();
static int  uinput_create(char *name);
static int  init_uinput (void);
static void close_uinput (void);

static struct {
    const char *name;
    uint8_t avrcp;
    uint16_t mapped_id;
    uint8_t release_quirk;
} key_map[] = {
    { "PLAY",         AVRC_ID_PLAY,     KEY_PLAYCD,       1 },
    { "STOP",         AVRC_ID_STOP,     KEY_STOPCD,       0 },
    { "PAUSE",        AVRC_ID_PAUSE,    KEY_PAUSECD,      1 },
    { "FORWARD",      AVRC_ID_FORWARD,  KEY_NEXTSONG,     0 },
    { "BACKWARD",     AVRC_ID_BACKWARD, KEY_PREVIOUSSONG, 0 },
    { "REWIND",       AVRC_ID_REWIND,   KEY_REWIND,       0 },
    { "FAST FORWARD", AVRC_ID_FAST_FOR, KEY_FORWARD,      0 },
    { NULL,           0,                0,                0 }
};
#endif /* BTIF_RC_USE_UINPUT */


/*****************************************************************************
**  Static variables
******************************************************************************/
static btif_rc_cb_t btif_rc_cb;

/*****************************************************************************
**  Static functions
******************************************************************************/

/*****************************************************************************
**  Externs
******************************************************************************/
extern BOOLEAN btif_hf_call_terminated_recently();
extern BOOLEAN check_cod(const bt_bdaddr_t *remote_bdaddr, uint32_t cod);
extern BOOLEAN btif_av_is_connected(void);

/*****************************************************************************
**  Functions
******************************************************************************/


#ifdef BTIF_RC_USE_UINPUT
/*****************************************************************************
**   Local uinput helper functions
******************************************************************************/
int send_event (int fd, uint16_t type, uint16_t code, int32_t value)
{
    struct uinput_event event;

    memset(&event, 0, sizeof(event));
    event.type  = type;
    event.code  = code;
    event.value = value;

    return write(fd, &event, sizeof(event));
}

void send_key (int fd, uint16_t key, int pressed)
{
    if (fd < 0) {
        return;
    }

    BTIF_TRACE_DEBUG3("AVRCP: Send key %d (%d) fd=%d", key, pressed, fd);
    send_event(fd, EV_KEY, key, pressed);
    send_event(fd, EV_SYN, SYN_REPORT, 0);
}

/************** uinput related functions **************/
int uinput_driver_check()
{
    uint32_t i;
    for (i=0; i < MAX_UINPUT_PATHS; i++)
    {
        if (access(uinput_dev_path[i], O_RDWR) == 0) {
           return 0;
        }
    }
    BTIF_TRACE_ERROR1("%s ERROR: uinput device is not in the system", __FUNCTION__);
    return -1;
}

int uinput_create(char *name)
{
    struct uinput_dev dev;
    int fd, err, x = 0;

    for(x=0; x < MAX_UINPUT_PATHS; x++)
    {
        fd = open(uinput_dev_path[x], O_RDWR);
        if (fd < 0)
            continue;
        break;
    }
    if (x == MAX_UINPUT_PATHS) {
        BTIF_TRACE_ERROR1("%s ERROR: uinput device open failed", __FUNCTION__);
        return -1;
    }
    memset(&dev, 0, sizeof(dev));
    if (name)
        strncpy(dev.name, name, UINPUT_MAX_NAME_SIZE);

    dev.id.bustype = BUS_BLUETOOTH;
    dev.id.vendor  = 0x0000;
    dev.id.product = 0x0000;
    dev.id.version = 0x0000;

    if (write(fd, &dev, sizeof(dev)) < 0) {
        BTIF_TRACE_ERROR1("%s Unable to write device information", __FUNCTION__);
        close(fd);
        return -1;
    }

    ioctl(fd, UI_SET_EVBIT, EV_KEY);
    ioctl(fd, UI_SET_EVBIT, EV_REL);
    ioctl(fd, UI_SET_EVBIT, EV_SYN);

    for (x = 0; key_map[x].name != NULL; x++)
        ioctl(fd, UI_SET_KEYBIT, key_map[x].mapped_id);

    for(x = 0; x < KEY_MAX; x++)
        ioctl(fd, UI_SET_KEYBIT, x);

    if (ioctl(fd, UI_DEV_CREATE, NULL) < 0) {
        BTIF_TRACE_ERROR1("%s Unable to create uinput device", __FUNCTION__);
        close(fd);
        return -1;
    }
    return fd;
}

int init_uinput (void)
{
    char *name = "AVRCP";

    BTIF_TRACE_DEBUG1("%s", __FUNCTION__);
    uinput_fd = uinput_create(name);
    if (uinput_fd < 0) {
        BTIF_TRACE_ERROR3("%s AVRCP: Failed to initialize uinput for %s (%d)",
                          __FUNCTION__, name, uinput_fd);
    } else {
        BTIF_TRACE_DEBUG3("%s AVRCP: Initialized uinput for %s (fd=%d)",
                          __FUNCTION__, name, uinput_fd);
    }
    return uinput_fd;
}

void close_uinput (void)
{
    BTIF_TRACE_DEBUG1("%s", __FUNCTION__);
    if (uinput_fd > 0) {
        ioctl(uinput_fd, UI_DEV_DESTROY);

        close(uinput_fd);
        uinput_fd = -1;
    }
}
#endif // BTA_AVRCP_FORCE_USE_UINPUT

const char *dump_rc_event_name(tBTA_AV_EVT event)
{
   switch(event) {
        case BTA_AV_RC_OPEN_EVT: return "BTA_AV_RC_OPEN_EVT";
        case BTA_AV_RC_CLOSE_EVT: return "BTA_AV_RC_CLOSE_EVT";
        case BTA_AV_REMOTE_CMD_EVT: return "BTA_AV_REMOTE_CMD_EVT";
        case BTA_AV_REMOTE_RSP_EVT: return "BTA_AV_REMOTE_RSP_EVT";
        case BTA_AV_VENDOR_CMD_EVT: return "BTA_AV_VENDOR_CMD_EVT";
        case BTA_AV_VENDOR_RSP_EVT: return "BTA_AV_VENDOR_RSP_EVT";
        default: return "UNKNOWN_EVENT";
   }
}

/***************************************************************************
 *  Function       handle_rc_connect
 *
 *  - Argument:    tBTA_AV_RC_OPEN 	RC open data structure
 *
 *  - Description: RC connection event handler
 *
 ***************************************************************************/
void handle_rc_connect (tBTA_AV_RC_OPEN *p_rc_open)
{
    BTIF_TRACE_DEBUG2("%s: rc_handle: %d", __FUNCTION__, p_rc_open->rc_handle);

#ifdef BTIF_RC_USE_UINPUT
    init_uinput();
#endif

    memcpy(btif_rc_cb.rc_addr, p_rc_open->peer_addr, sizeof(BD_ADDR));
    btif_rc_cb.rc_connected = TRUE;
    btif_rc_cb.rc_handle = p_rc_open->rc_handle;
}

/***************************************************************************
 *  Function       handle_rc_disconnect
 *
 *  - Argument:    tBTA_AV_RC_CLOSE 	RC close data structure
 *
 *  - Description: RC disconnection event handler
 *
 ***************************************************************************/
void handle_rc_disconnect (tBTA_AV_RC_CLOSE *p_rc_close)
{
    BTIF_TRACE_DEBUG2("%s: rc_handle: %d", __FUNCTION__, p_rc_close->rc_handle);

    btif_rc_cb.rc_handle = 0;
    btif_rc_cb.rc_connected = FALSE;
    memset(btif_rc_cb.rc_addr, 0, sizeof(BD_ADDR));
#ifdef BTIF_RC_USE_UINPUT
    close_uinput();
#endif /* BTIF_RC_USE_UINPUT */
}

/***************************************************************************
 *  Function       handle_rc_passthrough_cmd
 *
 *  - Argument:    tBTA_AV_RC rc_id   remote control command ID
 *                 tBTA_AV_STATE key_state status of key press
 *
 *  - Description: Remote control command handler
 *
 ***************************************************************************/
void handle_rc_passthrough_cmd ( tBTA_AV_REMOTE_CMD *p_remote_cmd)
{
    const char *status;
    int pressed, i;

    btif_rc_cb.rc_handle = p_remote_cmd->rc_handle;

    /* If AVRC is open and peer sends PLAY but there is no AVDT, then we queue-up this PLAY */
    if (p_remote_cmd)
    {
        /* queue AVRC PLAY if GAVDTP Open notification to app is pending (2 second timer) */
        if ((p_remote_cmd->rc_id == BTA_AV_RC_PLAY) && (!btif_av_is_connected()))
        {
            if (p_remote_cmd->key_state == AVRC_STATE_PRESS)
            {
                APPL_TRACE_WARNING1("%s: AVDT not open, queuing the PLAY command", __FUNCTION__);
                btif_rc_cb.rc_pending_play = TRUE;
            }
            return;
        }

        if ((p_remote_cmd->rc_id == BTA_AV_RC_PAUSE) && (btif_rc_cb.rc_pending_play))
        {
            APPL_TRACE_WARNING1("%s: Clear the pending PLAY on PAUSE received", __FUNCTION__);
            btif_rc_cb.rc_pending_play = FALSE;
            return;
        }
    }
    if (p_remote_cmd->key_state == AVRC_STATE_RELEASE) {
        status = "released";
        pressed = 0;
    } else {
        status = "pressed";
        pressed = 1;
    }

    /* If this is Play/Pause command (press or release)  before processing, check the following
     * a voice call has ended recently
     * the remote device is not of type headset
     * If the above conditions meet, drop the Play/Pause command
     * This fix is to interop with certain carkits which sends an automatic  PLAY  or PAUSE
     * commands right after call ends
     */
    if((p_remote_cmd->rc_id == BTA_AV_RC_PLAY || p_remote_cmd->rc_id == BTA_AV_RC_PAUSE)&&
       (btif_hf_call_terminated_recently() == TRUE) &&
       (check_cod( (const bt_bdaddr_t*)&(btif_rc_cb.rc_addr), COD_AV_HEADSETS) != TRUE))
    {
        BTIF_TRACE_DEBUG2("%s:Dropping the play/Pause command received right after call end cmd:%d",
                           __FUNCTION__,p_remote_cmd->rc_id);
        return;
    }

    for (i = 0; key_map[i].name != NULL; i++) {
        if (p_remote_cmd->rc_id == key_map[i].avrcp) {
            BTIF_TRACE_DEBUG3("%s: %s %s", __FUNCTION__, key_map[i].name, status);

           /* MusicPlayer uses a long_press_timeout of 1 second for PLAYPAUSE button
            * and maps that to autoshuffle. So if for some reason release for PLAY/PAUSE
            * comes 1 second after the press, the MediaPlayer UI goes into a bad state.
            * The reason for the delay could be sniff mode exit or some AVDTP procedure etc.
            * The fix is to generate a release right after the press and drown the 'actual'
            * release.
            */
            if ((key_map[i].release_quirk == 1) && (pressed == 0))
            {
                BTIF_TRACE_DEBUG2("%s: AVRC %s Release Faked earlier, drowned now",
                                  __FUNCTION__, key_map[i].name);
                return;
            }
#ifdef BTIF_RC_USE_UINPUT
            send_key(uinput_fd, key_map[i].mapped_id, pressed);
#endif
            if ((key_map[i].release_quirk == 1) && (pressed == 1))
            {
                GKI_delay(30); // 30ms
                BTIF_TRACE_DEBUG2("%s: AVRC %s Release quirk enabled, send release now",
                                  __FUNCTION__, key_map[i].name);
#ifdef BTIF_RC_USE_UINPUT
                send_key(uinput_fd, key_map[i].mapped_id, 0);
#endif
            }
            break;
        }
    }

    if (key_map[i].name == NULL)
        BTIF_TRACE_ERROR3("%s AVRCP: unknown button 0x%02X %s", __FUNCTION__,
                        p_remote_cmd->rc_id, status);
}

/*****************************************************************************
**
** Function        btif_rc_init
**
** Description     Initialize RC
**
** Returns         Returns 0 on success, -1 otherwise
**
*******************************************************************************/
int btif_rc_init()
{
    BTIF_TRACE_DEBUG1("%s", __FUNCTION__);
    memset (&btif_rc_cb, 0, sizeof(btif_rc_cb));

#ifdef BTIF_RC_USE_UINPUT
    return uinput_driver_check();
#endif /* BTIF_RC_USE_UINPUT */
}

/***************************************************************************
 **
 ** Function       btif_rc_handler
 **
 ** Description    RC event handler
 **
 ***************************************************************************/
void btif_rc_handler(tBTA_AV_EVT event, tBTA_AV *p_data)
{
    BTIF_TRACE_DEBUG2 ("%s event:%s", __FUNCTION__, dump_rc_event_name(event));
    switch (event)
    {
        case BTA_AV_RC_OPEN_EVT:
        {
            BTIF_TRACE_DEBUG1("Peer_features:%x", p_data->rc_open.peer_features);
            handle_rc_connect( &(p_data->rc_open) );
        }break;

        case BTA_AV_RC_CLOSE_EVT:
        {
            handle_rc_disconnect( &(p_data->rc_close) );
        }break;

        case BTA_AV_REMOTE_CMD_EVT:
        {
            BTIF_TRACE_DEBUG2("rc_id:0x%x key_state:%d", p_data->remote_cmd.rc_id,
                               p_data->remote_cmd.key_state);
            handle_rc_passthrough_cmd( (&p_data->remote_cmd) );
        }break;
        default:
            BTIF_TRACE_DEBUG0("Unhandled RC event");
    }
}

/***************************************************************************
 **
 ** Function       btif_rc_get_connected_peer
 **
 ** Description    Fetches the connected headset's BD_ADDR if any
 **
 ***************************************************************************/
BOOLEAN btif_rc_get_connected_peer(BD_ADDR peer_addr)
{
    if (btif_rc_cb.rc_connected == TRUE) {
        bdcpy(peer_addr, btif_rc_cb.rc_addr);
        return TRUE;
    }
    return FALSE;
}

/***************************************************************************
 **
 ** Function       btif_rc_check_handle_pending_play
 **
 ** Description    Clears the queued PLAY command. if bSend is TRUE, forwards to app
 **
 ***************************************************************************/

/* clear the queued PLAY command. if bSend is TRUE, forward to app */
void btif_rc_check_handle_pending_play (BD_ADDR peer_addr, BOOLEAN bSendToApp)
{
    ALOGV("btapp_rc_check_handle_pending_play: bSendToApp=%d", bSendToApp);
    if (btif_rc_cb.rc_pending_play)
    {
        if (bSendToApp)
        {
            tBTA_AV_REMOTE_CMD remote_cmd;
            APPL_TRACE_DEBUG1("%s: Sending queued PLAYED event to app", __FUNCTION__);

            memset (&remote_cmd, 0, sizeof(tBTA_AV_REMOTE_CMD));
            remote_cmd.rc_handle  = btif_rc_cb.rc_handle;
            remote_cmd.rc_id      = AVRC_ID_PLAY;
            remote_cmd.hdr.ctype  = AVRC_CMD_CTRL;
            remote_cmd.hdr.opcode = AVRC_OP_PASS_THRU;

            /* delay sending to app, else there is a timing issue in the framework,
             ** which causes the audio to be on th device's speaker. Delay between
             ** OPEN & RC_PLAYs
            */
            GKI_delay (200);
            /* send to app - both PRESSED & RELEASED */
            remote_cmd.key_state  = AVRC_STATE_PRESS;
            handle_rc_passthrough_cmd( &remote_cmd );

            GKI_delay (100);

            remote_cmd.key_state  = AVRC_STATE_RELEASE;
            handle_rc_passthrough_cmd( &remote_cmd );
        }
        btif_rc_cb.rc_pending_play = FALSE;
    }
}

