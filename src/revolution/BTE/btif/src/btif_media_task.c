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

/******************************************************************************
 **
 **  Name:          btif_media_task.c
 **
 **  Description:   This is the multimedia module for the BTIF system.  It
 **                 contains task implementations AV, HS and HF profiles
 **                 audio & video processing
 **
 ******************************************************************************/

#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <stdint.h>
#include <sys/time.h>

#include "bt_target.h"
#include "gki.h"
#include "bta_api.h"
#include "btu.h"
#include "bta_sys.h"
#include "bta_sys_int.h"

#include "bta_av_api.h"
#include "a2d_api.h"
#include "a2d_sbc.h"
#include "a2d_int.h"
#include "bta_av_sbc.h"
#include "bta_av_ci.h"
#include "l2c_api.h"


#include "btif_av_co.h"
#include "btif_media.h"


#if (BTA_AV_INCLUDED == TRUE)
#include "sbc_encoder.h"
#endif

#define LOG_TAG "BTIF-MEDIA"

#include <hardware/bluetooth.h>
#include "audio_a2dp_hw.h"
#include "btif_av.h"
#include "btif_sm.h"
#include "btif_util.h"
#include "bt_utils.h"

/*****************************************************************************
 **  Constants
 *****************************************************************************/

//#define DEBUG_MEDIA_AV_FLOW TRUE

/* BTIF media task gki event definition */
#define BTIF_MEDIA_TASK_CMD TASK_MBOX_0_EVT_MASK
#define BTIF_MEDIA_TASK_DATA TASK_MBOX_1_EVT_MASK

#define BTIF_MEDIA_TASK_KILL EVENT_MASK(GKI_SHUTDOWN_EVT)

#define BTIF_MEDIA_AA_TASK_TIMER_ID TIMER_0
#define BTIF_MEDIA_AV_TASK_TIMER_ID TIMER_1
#define BTIF_MEDIA_AA_TASK_TIMER TIMER_0_EVT_MASK
#define BTIF_MEDIA_AV_TASK_TIMER TIMER_1_EVT_MASK

#define BTIF_MEDIA_TASK_CMD_MBOX        TASK_MBOX_0     /* cmd mailbox  */
#define BTIF_MEDIA_TASK_DATA_MBOX       TASK_MBOX_1     /* data mailbox  */

/* BTIF media cmd event definition : BTIF_MEDIA_TASK_CMD */
enum
{
    BTIF_MEDIA_START_AA_TX = 1,
    BTIF_MEDIA_STOP_AA_TX,
    BTIF_MEDIA_AA_RX_RDY,
    BTIF_MEDIA_UIPC_RX_RDY,
    BTIF_MEDIA_SBC_ENC_INIT,
    BTIF_MEDIA_SBC_ENC_UPDATE,
    BTIF_MEDIA_SBC_DEC_INIT,
    BTIF_MEDIA_VIDEO_DEC_INIT,
    BTIF_MEDIA_FLUSH_AA_TX,
    BTIF_MEDIA_FLUSH_AA_RX,
    BTIF_MEDIA_AUDIO_FEEDING_INIT,
    BTIF_MEDIA_AUDIO_RECEIVING_INIT
};

enum {
    MEDIA_TASK_STATE_OFF = 0,
    MEDIA_TASK_STATE_ON = 1,
    MEDIA_TASK_STATE_SHUTTING_DOWN = 2
};

/* Macro to multiply the media task tick */
#ifndef BTIF_MEDIA_NUM_TICK
#define BTIF_MEDIA_NUM_TICK      1
#endif

/* Media task tick in milliseconds */
#define BTIF_MEDIA_TIME_TICK                     (20 * BTIF_MEDIA_NUM_TICK)

/* Number of frames per media task tick.
   Configure value rounded up to closest integer and
   adjust any deltas in btif_get_num_aa_frame */

/* 7.5 frames/tick @ 20 ms tick (every 2nd frame send one less) */
#define BTIF_MEDIA_FR_PER_TICKS_48               (8 * BTIF_MEDIA_NUM_TICK)

/* 6.89 frames/tick  @ 20 ms tick (7 out of 64 frames send one less */
#define BTIF_MEDIA_FR_PER_TICKS_44_1             (7 * BTIF_MEDIA_NUM_TICK)

/* 5.0 frames/tick  @ 20 ms tick */
#define BTIF_MEDIA_FR_PER_TICKS_32               (5 * BTIF_MEDIA_NUM_TICK)

/* 2.5 frames/tick  @ 20 ms tick (every 2nd frame send one less) */
#define BTIF_MEDIA_FR_PER_TICKS_16               (3 * BTIF_MEDIA_NUM_TICK)


/* buffer pool */
#define BTIF_MEDIA_AA_POOL_ID GKI_POOL_ID_3
#define BTIF_MEDIA_AA_BUF_SIZE GKI_BUF3_SIZE

/* offset */
#if (BTA_AV_CO_CP_SCMS_T == TRUE)
#define BTIF_MEDIA_AA_SBC_OFFSET (AVDT_MEDIA_OFFSET + BTA_AV_SBC_HDR_SIZE + 1)
#else
#define BTIF_MEDIA_AA_SBC_OFFSET (AVDT_MEDIA_OFFSET + BTA_AV_SBC_HDR_SIZE)
#endif

/* Define the bitrate step when trying to match bitpool value */
#ifndef BTIF_MEDIA_BITRATE_STEP
#define BTIF_MEDIA_BITRATE_STEP 5
#endif

/* Middle quality quality setting @ 44.1 khz */
#define DEFAULT_SBC_BITRATE 229

#ifndef A2DP_MEDIA_TASK_STACK_SIZE
#define A2DP_MEDIA_TASK_STACK_SIZE       0x2000         /* In bytes */
#endif

#define A2DP_MEDIA_TASK_TASK_STR        ((INT8 *) "A2DP-MEDIA")
static UINT32 a2dp_media_task_stack[(A2DP_MEDIA_TASK_STACK_SIZE + 3) / 4];

#define BT_MEDIA_TASK A2DP_MEDIA_TASK

#define USEC_PER_SEC 1000000L
#define TPUT_STATS_INTERVAL_US (1000*1000)

/*
 * CONGESTION COMPENSATION CTRL ::
 *
 * Thus setting controls how many buffers we will hold in media task
 * during temp link congestion. Together with the stack buffer queues
 * it controls much temporary a2dp link congestion we can
 * compensate for. It however also depends on the default run level of sinks
 * jitterbuffers. Depending on type of sink this would vary.
 * Ideally the (SRC) max tx buffer capacity should equal the sinks
 * jitterbuffer runlevel including any intermediate buffers on the way
 * towards the sinks codec.
 */

/* fixme -- define this in pcm time instead of buffer count */
/* fixme -- tune optimal value. For now set a large buffer capacity */
#define MAX_OUTPUT_BUFFER_QUEUE_SZ 24

//#define BTIF_MEDIA_VERBOSE_ENABLED

#ifdef BTIF_MEDIA_VERBOSE_ENABLED
#define VERBOSE(fmt, ...) \
      LogMsg( TRACE_CTRL_GENERAL | TRACE_LAYER_NONE | TRACE_ORG_APPL | \
              TRACE_TYPE_ERROR, fmt, ## __VA_ARGS__)
#else
#define VERBOSE(fmt, ...)
#endif

/*****************************************************************************
 **  Data types
 *****************************************************************************/

typedef struct
{
    UINT32 aa_frame_counter;
    INT32  aa_feed_counter;
    INT32  aa_feed_residue;
} tBTIF_AV_MEDIA_FEEDINGS_PCM_STATE;


typedef union
{
    tBTIF_AV_MEDIA_FEEDINGS_PCM_STATE pcm;
} tBTIF_AV_MEDIA_FEEDINGS_STATE;

typedef struct
{
#if (BTA_AV_INCLUDED == TRUE)
    BUFFER_Q TxAaQ;
    BOOLEAN is_tx_timer;
    UINT16 TxAaMtuSize;
    UINT32 timestamp;
    UINT8 TxTranscoding;
    tBTIF_AV_FEEDING_MODE feeding_mode;
    tBTIF_AV_MEDIA_FEEDINGS media_feeding;
    tBTIF_AV_MEDIA_FEEDINGS_STATE media_feeding_state;
    SBC_ENC_PARAMS encoder;
    UINT8 busy_level;
    void* av_sm_hdl;
    UINT8 a2dp_cmd_pending; /* we can have max one command pending */
    BOOLEAN tx_flush; /* discards any outgoing data when true */
    BOOLEAN scaling_disabled;
#endif

} tBTIF_MEDIA_CB;

typedef struct {
    int rx;
    int rx_tot;
    int tx;
    int tx_tot;
    int ts_prev_us;
} t_stat;

/*****************************************************************************
 **  Local data
 *****************************************************************************/

static tBTIF_MEDIA_CB btif_media_cb;
static int media_task_running = MEDIA_TASK_STATE_OFF;


/*****************************************************************************
 **  Local functions
 *****************************************************************************/

static void btif_a2dp_data_cb(tUIPC_CH_ID ch_id, tUIPC_EVENT event);
static void btif_a2dp_ctrl_cb(tUIPC_CH_ID ch_id, tUIPC_EVENT event);
static void btif_a2dp_encoder_update(void);

/*****************************************************************************
 **  Externs
 *****************************************************************************/

static void btif_media_task_handle_cmd(BT_HDR *p_msg);
static void btif_media_task_handle_media(BT_HDR *p_msg);

#if (BTA_AV_INCLUDED == TRUE)
static void btif_media_send_aa_frame(void);
static void btif_media_task_feeding_state_reset(void);
static void btif_media_task_aa_start_tx(void);
static void btif_media_task_aa_stop_tx(void);
static void btif_media_task_enc_init(BT_HDR *p_msg);
static void btif_media_task_enc_update(BT_HDR *p_msg);
static void btif_media_task_audio_feeding_init(BT_HDR *p_msg);
static void btif_media_task_aa_tx_flush(BT_HDR *p_msg);
static void btif_media_aa_prep_2_send(UINT8 nb_frame);
#endif


/*****************************************************************************
 **  Misc helper functions
 *****************************************************************************/

static void tput_mon(int is_rx, int len, int reset)
{
    /* only monitor one connection at a time for now */
    static t_stat cur_stat;
    struct timespec now;
    unsigned int prev_us;
    unsigned int now_us;

    if (reset == TRUE)
    {
        memset(&cur_stat, 0, sizeof(t_stat));
        return;
    }

    if (is_rx)
    {
        cur_stat.rx+=len;
        cur_stat.rx_tot+=len;
    }
    else
    {
        cur_stat.tx+=len;
        cur_stat.tx_tot+=len;
    }
    clock_gettime(CLOCK_MONOTONIC, &now);

    now_us = now.tv_sec*USEC_PER_SEC + now.tv_nsec/1000;

    //APPL_TRACE_DEBUG1("%d us", now_us - cur_stat.ts_prev_us);

    if ((now_us - cur_stat.ts_prev_us) < TPUT_STATS_INTERVAL_US)
        return;

    APPL_TRACE_WARNING4("tput rx:%d, tx:%d (kB/s)  (tot : rx %d, tx %d bytes)",
          (cur_stat.rx)/((now_us - cur_stat.ts_prev_us)/1000),
          (cur_stat.tx)/((now_us - cur_stat.ts_prev_us)/1000),
           cur_stat.rx_tot, cur_stat.tx_tot);

    /* stats dumped. now reset stats for next interval */
    cur_stat.rx = 0;
    cur_stat.tx = 0;
    cur_stat.ts_prev_us = now_us;
}


static void log_tstamps_us(char *comment)
{
    #define USEC_PER_SEC 1000000L
    static struct timespec prev = {0, 0};
    struct timespec now, diff;
    unsigned int diff_us = 0;
    unsigned int now_us = 0;

    clock_gettime(CLOCK_MONOTONIC, &now);
    now_us = now.tv_sec*USEC_PER_SEC + now.tv_nsec/1000;
    diff_us = (now.tv_sec - prev.tv_sec) * USEC_PER_SEC + (now.tv_nsec - prev.tv_nsec)/1000;

    APPL_TRACE_DEBUG4("[%s] ts %08d, diff : %08d, queue sz %d", comment, now_us, diff_us,
                btif_media_cb.TxAaQ.count);

    prev = now;
}

const char* dump_media_event(UINT16 event)
{
    switch(event)
    {
        CASE_RETURN_STR(BTIF_MEDIA_START_AA_TX)
        CASE_RETURN_STR(BTIF_MEDIA_STOP_AA_TX)
        CASE_RETURN_STR(BTIF_MEDIA_AA_RX_RDY)
        CASE_RETURN_STR(BTIF_MEDIA_UIPC_RX_RDY)
        CASE_RETURN_STR(BTIF_MEDIA_SBC_ENC_INIT)
        CASE_RETURN_STR(BTIF_MEDIA_SBC_ENC_UPDATE)
        CASE_RETURN_STR(BTIF_MEDIA_SBC_DEC_INIT)
        CASE_RETURN_STR(BTIF_MEDIA_VIDEO_DEC_INIT)
        CASE_RETURN_STR(BTIF_MEDIA_FLUSH_AA_TX)
        CASE_RETURN_STR(BTIF_MEDIA_FLUSH_AA_RX)
        CASE_RETURN_STR(BTIF_MEDIA_AUDIO_FEEDING_INIT)
        CASE_RETURN_STR(BTIF_MEDIA_AUDIO_RECEIVING_INIT)

        default:
            return "UNKNOWN MEDIA EVENT";
    }
}

/*****************************************************************************
 **  A2DP CTRL PATH
 *****************************************************************************/

static const char* dump_a2dp_ctrl_event(UINT8 event)
{
    switch(event)
    {
        CASE_RETURN_STR(A2DP_CTRL_CMD_NONE)
        CASE_RETURN_STR(A2DP_CTRL_CMD_CHECK_READY)
        CASE_RETURN_STR(A2DP_CTRL_CMD_START)
        CASE_RETURN_STR(A2DP_CTRL_CMD_STOP)
        CASE_RETURN_STR(A2DP_CTRL_CMD_SUSPEND)
        default:
            return "UNKNOWN MSG ID";
    }
}

static void btif_audiopath_detached(void)
{
    APPL_TRACE_EVENT0("## AUDIO PATH DETACHED ##");

    /*  send stop request only if we are actively streaming and haven't received
        a stop request. Potentially audioflinger detached abnormally */
    if (btif_media_cb.is_tx_timer)
    {
        /* post stop event and wait for audio path to stop */
        btif_dispatch_sm_event(BTIF_AV_STOP_STREAM_REQ_EVT, NULL, 0);
    }
}

static void a2dp_cmd_acknowledge(int status)
{
    UINT8 ack = status;

    APPL_TRACE_EVENT2("## a2dp ack : %s, status %d ##", dump_a2dp_ctrl_event(btif_media_cb.a2dp_cmd_pending), status);

    /* sanity check */
    if (btif_media_cb.a2dp_cmd_pending == A2DP_CTRL_CMD_NONE)
    {
        APPL_TRACE_ERROR0("warning : no command pending, ignore ack");
        return;
    }

    /* clear pending */
    btif_media_cb.a2dp_cmd_pending = A2DP_CTRL_CMD_NONE;

    /* acknowledge start request */
    UIPC_Send(UIPC_CH_ID_AV_CTRL, 0, &ack, 1);
}


static void btif_recv_ctrl_data(void)
{
    UINT8 cmd = 0;
    int n;

    n = UIPC_Read(UIPC_CH_ID_AV_CTRL, NULL, &cmd, 1);

    /* detach on ctrl channel means audioflinger process was terminated */
    if (n == 0)
    {
        APPL_TRACE_EVENT0("CTRL CH DETACHED");
        UIPC_Close(UIPC_CH_ID_AV_CTRL);
        /* we can operate only on datachannel, if af client wants to
           do send additional commands the ctrl channel would be reestablished */
        //btif_audiopath_detached();
        return;
    }

    APPL_TRACE_DEBUG1("a2dp-ctrl-cmd : %s", dump_a2dp_ctrl_event(cmd));

    btif_media_cb.a2dp_cmd_pending = cmd;

    switch(cmd)
    {
        case A2DP_CTRL_CMD_CHECK_READY:

            if (media_task_running == MEDIA_TASK_STATE_SHUTTING_DOWN)
            {
                a2dp_cmd_acknowledge(A2DP_CTRL_ACK_FAILURE);
                return;
            }

            /* check whether av is ready to setup a2dp datapath */
            if ((btif_av_stream_ready() == TRUE) || (btif_av_stream_started_ready() == TRUE))
            {
                a2dp_cmd_acknowledge(A2DP_CTRL_ACK_SUCCESS);
            }
            else
            {
                a2dp_cmd_acknowledge(A2DP_CTRL_ACK_FAILURE);
            }
            break;

        case A2DP_CTRL_CMD_START:

            if (btif_av_stream_ready() == TRUE)
            {
                /* setup audio data channel listener */
                UIPC_Open(UIPC_CH_ID_AV_AUDIO, btif_a2dp_data_cb);

                /* post start event and wait for audio path to open */
                btif_dispatch_sm_event(BTIF_AV_START_STREAM_REQ_EVT, NULL, 0);
            }
            else if (btif_av_stream_started_ready())
            {
                /* already started, setup audio data channel listener
                   and ack back immediately */
                UIPC_Open(UIPC_CH_ID_AV_AUDIO, btif_a2dp_data_cb);

                a2dp_cmd_acknowledge(A2DP_CTRL_ACK_SUCCESS);
            }
            else
            {
                a2dp_cmd_acknowledge(A2DP_CTRL_ACK_FAILURE);
                break;
            }
            break;

        case A2DP_CTRL_CMD_STOP:

            if (btif_media_cb.is_tx_timer == FALSE)
            {
                /* we are already stopped, just ack back */
                a2dp_cmd_acknowledge(A2DP_CTRL_ACK_SUCCESS);
                break;
            }

            btif_dispatch_sm_event(BTIF_AV_STOP_STREAM_REQ_EVT, NULL, 0);
            break;

        case A2DP_CTRL_CMD_SUSPEND:
            /* local suspend */
            if (btif_av_stream_started_ready())
            {
                btif_dispatch_sm_event(BTIF_AV_SUSPEND_STREAM_REQ_EVT, NULL, 0);
            }
            else
            {
                /* if we are not in started state, just ack back ok and let
                   audioflinger close the channel. This can happen if we are
                   remotely suspended */
                a2dp_cmd_acknowledge(A2DP_CTRL_ACK_SUCCESS);
            }
            break;

        default:
            APPL_TRACE_ERROR1("UNSUPPORTED CMD (%d)", cmd);
            a2dp_cmd_acknowledge(A2DP_CTRL_ACK_FAILURE);
            break;
    }
    APPL_TRACE_DEBUG1("a2dp-ctrl-cmd : %s DONE", dump_a2dp_ctrl_event(cmd));
}

static void btif_a2dp_ctrl_cb(tUIPC_CH_ID ch_id, tUIPC_EVENT event)
{
    APPL_TRACE_DEBUG1("A2DP-CTRL-CHANNEL EVENT %s", dump_uipc_event(event));

    switch(event)
    {
        case UIPC_OPEN_EVT:
            /* fetch av statemachine handle */
            btif_media_cb.av_sm_hdl = btif_av_get_sm_handle();
            break;

        case UIPC_CLOSE_EVT:
            /* restart ctrl server unless we are shutting down */
            if (media_task_running == MEDIA_TASK_STATE_ON)
                UIPC_Open(UIPC_CH_ID_AV_CTRL , btif_a2dp_ctrl_cb);
            break;

        case UIPC_RX_DATA_READY_EVT:
            btif_recv_ctrl_data();
            break;

        default :
            APPL_TRACE_ERROR1("### A2DP-CTRL-CHANNEL EVENT %d NOT HANDLED ###", event);
            break;
    }
}

static void btif_a2dp_data_cb(tUIPC_CH_ID ch_id, tUIPC_EVENT event)
{
    APPL_TRACE_DEBUG1("BTIF MEDIA (A2DP-DATA) EVENT %s", dump_uipc_event(event));

    switch(event)
    {
        case UIPC_OPEN_EVT:

            /*  read directly from media task from here on (keep callback for
                connection events */
            UIPC_Ioctl(UIPC_CH_ID_AV_AUDIO, UIPC_REG_REMOVE_ACTIVE_READSET, NULL);

            /* Start the media task to encode SBC */
            btif_media_task_start_aa_req();

            /* make sure we update any changed sbc encoder params */
            btif_a2dp_encoder_update();

            /* ack back when media task is fully started */
            break;

        case UIPC_CLOSE_EVT:
            a2dp_cmd_acknowledge(A2DP_CTRL_ACK_SUCCESS);
            btif_audiopath_detached();
            break;

        default :
            APPL_TRACE_ERROR1("### A2DP-DATA EVENT %d NOT HANDLED ###", event);
            break;
    }
}


/*****************************************************************************
 **  BTIF ADAPTATION
 *****************************************************************************/

static void btif_a2dp_encoder_init(void)
{
    UINT16 minmtu;
    tBTIF_MEDIA_INIT_AUDIO msg;
    tA2D_SBC_CIE sbc_config;

    /* lookup table for converting channel mode */
    UINT16 codec_mode_tbl[5] = { SBC_JOINT_STEREO, SBC_STEREO, SBC_DUAL, 0, SBC_MONO };

    /* lookup table for converting number of blocks */
    UINT16 codec_block_tbl[5] = { 16, 12, 8, 0, 4 };

    /* lookup table to convert freq */
    UINT16 freq_block_tbl[5] = { SBC_sf48000, SBC_sf44100, SBC_sf32000, 0, SBC_sf16000 };

    APPL_TRACE_DEBUG0("btif_a2dp_encoder_init");

    /* Retrieve the current SBC configuration (default if currently not used) */
    bta_av_co_audio_get_sbc_config(&sbc_config, &minmtu);
    msg.NumOfSubBands = (sbc_config.num_subbands == A2D_SBC_IE_SUBBAND_4) ? 4 : 8;
    msg.NumOfBlocks = codec_block_tbl[sbc_config.block_len >> 5];
    msg.AllocationMethod = (sbc_config.alloc_mthd == A2D_SBC_IE_ALLOC_MD_L) ? SBC_LOUDNESS : SBC_SNR;
    msg.ChannelMode = codec_mode_tbl[sbc_config.ch_mode >> 1];
    msg.SamplingFreq = freq_block_tbl[sbc_config.samp_freq >> 5];
    msg.MtuSize = minmtu;

    APPL_TRACE_EVENT1("msg.ChannelMode %x", msg.ChannelMode);

    /* Init the media task to encode SBC properly */
    btif_media_task_enc_init_req(&msg);
}

static void btif_a2dp_encoder_update(void)
{
    UINT16 minmtu;
    tA2D_SBC_CIE sbc_config;
    tBTIF_MEDIA_UPDATE_AUDIO msg;
    UINT8 pref_min;
    UINT8 pref_max;

    APPL_TRACE_DEBUG0("btif_a2dp_encoder_update");

    /* Retrieve the current SBC configuration (default if currently not used) */
    bta_av_co_audio_get_sbc_config(&sbc_config, &minmtu);

    APPL_TRACE_DEBUG4("btif_a2dp_encoder_update: Common min_bitpool:%d(0x%x) max_bitpool:%d(0x%x)",
            sbc_config.min_bitpool, sbc_config.min_bitpool,
            sbc_config.max_bitpool, sbc_config.max_bitpool);

    if (sbc_config.min_bitpool > sbc_config.max_bitpool)
    {
        APPL_TRACE_ERROR0("btif_a2dp_encoder_update: ERROR btif_a2dp_encoder_update min_bitpool > max_bitpool");
    }

    /* check if remote sink has a preferred bitpool range */
    if (bta_av_co_get_remote_bitpool_pref(&pref_min, &pref_max) == TRUE)
    {
        /* adjust our preferred bitpool with the remote preference if within
           our capable range */

        if (pref_min < sbc_config.min_bitpool)
            pref_min = sbc_config.min_bitpool;

        if (pref_max > sbc_config.max_bitpool)
            pref_max = sbc_config.max_bitpool;

        msg.MinBitPool = pref_min;
        msg.MaxBitPool = pref_max;

        if ((pref_min != sbc_config.min_bitpool) || (pref_max != sbc_config.max_bitpool))
        {
            APPL_TRACE_EVENT2("## adjusted our bitpool range to peer pref [%d:%d] ##",
                pref_min, pref_max);
        }
    }
    else
    {
        msg.MinBitPool = sbc_config.min_bitpool;
        msg.MaxBitPool = sbc_config.max_bitpool;
    }

    msg.MinMtuSize = minmtu;

    /* Update the media task to encode SBC properly */
    btif_media_task_enc_update_req(&msg);
}


/*****************************************************************************
**
** Function        btif_a2dp_start_media_task
**
** Description
**
** Returns
**
*******************************************************************************/

int btif_a2dp_start_media_task(void)
{
    int retval;

    if (media_task_running != MEDIA_TASK_STATE_OFF)
    {
        APPL_TRACE_ERROR0("warning : media task already running");
        return GKI_FAILURE;
    }

    APPL_TRACE_EVENT0("## A2DP START MEDIA TASK ##");

    /* start a2dp media task */
    retval = GKI_create_task((TASKPTR)btif_media_task, A2DP_MEDIA_TASK,
                A2DP_MEDIA_TASK_TASK_STR,
                (UINT16 *) ((UINT8 *)a2dp_media_task_stack + A2DP_MEDIA_TASK_STACK_SIZE),
                sizeof(a2dp_media_task_stack));

    if (retval != GKI_SUCCESS)
        return retval;

    /* wait for task to come up to sure we are able to send messages to it */
    while (media_task_running == MEDIA_TASK_STATE_OFF)
        usleep(10);

    APPL_TRACE_EVENT0("## A2DP MEDIA TASK STARTED ##");

    return retval;
}

/*****************************************************************************
**
** Function        btif_a2dp_stop_media_task
**
** Description
**
** Returns
**
*******************************************************************************/

void btif_a2dp_stop_media_task(void)
{
    APPL_TRACE_EVENT0("## A2DP STOP MEDIA TASK ##");
    GKI_destroy_task(BT_MEDIA_TASK);
}

/*****************************************************************************
**
** Function        btif_a2dp_on_init
**
** Description
**
** Returns
**
*******************************************************************************/

void btif_a2dp_on_init(void)
{
    //tput_mon(1, 0, 1);
}


/*****************************************************************************
**
** Function        btif_a2dp_setup_codec
**
** Description
**
** Returns
**
*******************************************************************************/

void btif_a2dp_setup_codec(void)
{
    tBTIF_AV_MEDIA_FEEDINGS media_feeding;
    tBTIF_STATUS status;

    APPL_TRACE_EVENT0("## A2DP SETUP CODEC ##");

    GKI_disable();

    /* for now hardcode 44.1 khz 16 bit stereo */
    media_feeding.cfg.pcm.sampling_freq = 44100;
    media_feeding.cfg.pcm.bit_per_sample = 16;
    media_feeding.cfg.pcm.num_channel = 2;
    media_feeding.format = BTIF_AV_CODEC_PCM;

    if (bta_av_co_audio_set_codec(&media_feeding, &status))
    {
        tBTIF_MEDIA_INIT_AUDIO_FEEDING mfeed;

        /* Init the encoding task */
        btif_a2dp_encoder_init();

        /* Build the media task configuration */
        mfeed.feeding = media_feeding;
        mfeed.feeding_mode = BTIF_AV_FEEDING_ASYNCHRONOUS;
        /* Send message to Media task to configure transcoding */
        btif_media_task_audio_feeding_init_req(&mfeed);
    }

    GKI_enable();
}


/*****************************************************************************
**
** Function        btif_a2dp_on_idle
**
** Description
**
** Returns
**
*******************************************************************************/

void btif_a2dp_on_idle(void)
{
    APPL_TRACE_EVENT0("## ON A2DP IDLE ##");

    /* Make sure media task is stopped */
    btif_media_task_stop_aa_req();

    bta_av_co_init();
}

/*****************************************************************************
**
** Function        btif_a2dp_on_open
**
** Description
**
** Returns
**
*******************************************************************************/

void btif_a2dp_on_open(void)
{
    APPL_TRACE_EVENT0("## ON A2DP OPEN ##");

    /* always use callback to notify socket events */
    UIPC_Open(UIPC_CH_ID_AV_AUDIO, btif_a2dp_data_cb);
}

/*****************************************************************************
**
** Function        btif_a2dp_on_started
**
** Description
**
** Returns
**
*******************************************************************************/

void btif_a2dp_on_started(tBTA_AV_START *p_av)
{
    tBTIF_AV_MEDIA_FEEDINGS media_feeding;
    tBTIF_STATUS status;

    APPL_TRACE_EVENT0("## ON A2DP STARTED ##");

    if (p_av->status == BTA_AV_SUCCESS)
    {
        if (p_av->suspending == FALSE)
        {
            if (p_av->initiator)
            {
                a2dp_cmd_acknowledge(A2DP_CTRL_ACK_SUCCESS);
            }
            else
            {
                /* we were remotely started,  make sure codec
                   is setup before datapath is started */
                btif_a2dp_setup_codec();
            }

            /* media task is autostarted upon a2dp audiopath connection */
        }
    }
    else
    {
        a2dp_cmd_acknowledge(A2DP_CTRL_ACK_FAILURE);
    }
}


/*****************************************************************************
**
** Function        btif_a2dp_on_stopped
**
** Description
**
** Returns
**
*******************************************************************************/

void btif_a2dp_on_stopped(tBTA_AV_SUSPEND *p_av)
{
    APPL_TRACE_EVENT0("## ON A2DP STOPPED ##");

    /* allow using this api for other than suspend */
    if (p_av != NULL)
    {
        if (p_av->status != BTA_AV_SUCCESS)
        {
            APPL_TRACE_EVENT1("AV STOP FAILED (%d)", p_av->status);

            if (p_av->initiator)
                a2dp_cmd_acknowledge(A2DP_CTRL_ACK_FAILURE);
            return;
        }
    }

    /* ensure tx frames are immediately suspended */
    btif_media_cb.tx_flush = 1;

    /* request to stop media task  */
    btif_media_task_aa_tx_flush_req();
    btif_media_task_stop_aa_req();

    /* once stream is fully stopped we will ack back */
}


/*****************************************************************************
**
** Function        btif_a2dp_on_suspended
**
** Description
**
** Returns
**
*******************************************************************************/

void btif_a2dp_on_suspended(tBTA_AV_SUSPEND *p_av)
{
    APPL_TRACE_EVENT0("## ON A2DP SUSPENDED ##");

    /* check for status failures */
    if (p_av->status != BTA_AV_SUCCESS)
    {
        if (p_av->initiator == TRUE)
            a2dp_cmd_acknowledge(A2DP_CTRL_ACK_FAILURE);
    }

    /* once stream is fully stopped we will ack back */

    /* ensure tx frames are immediately flushed */
    btif_media_cb.tx_flush = 1;

    /* stop timer tick */
    btif_media_task_stop_aa_req();
}

/* when true media task discards any tx frames */
void btif_a2dp_set_tx_flush(BOOLEAN enable)
{
    APPL_TRACE_EVENT1("## DROP TX %d ##", enable);
    btif_media_cb.tx_flush = enable;
}

/*****************************************************************************
**
** Function        btif_calc_pcmtime
**
** Description     Calculates the pcmtime equivalent of a datapacket
**
** Returns         microseconds
**
*******************************************************************************/

static int btif_calc_pcmtime(UINT32 bytes_processed)
{
    int pcm_time_us = 0;
    tBTIF_AV_MEDIA_FEED_CFG *p_cfg;

    p_cfg = &btif_media_cb.media_feeding.cfg;

    /* calculate corresponding pcm time based on data processed */
    switch(btif_media_cb.media_feeding.format)
    {
        case BTIF_AV_CODEC_PCM:
            pcm_time_us = (bytes_processed*1000000)/
                          (p_cfg->pcm.num_channel*p_cfg->pcm.sampling_freq*p_cfg->pcm.bit_per_sample/8);
            break;

        default :
            APPL_TRACE_ERROR1("mediafeeding format invalid : %d", btif_media_cb.media_feeding.format);
            break;
    }

    return pcm_time_us;
}


/*******************************************************************************
 **
 ** Function         btif_media_task_aa_handle_timer
 **
 ** Description
 **
 ** Returns          void
 **
 *******************************************************************************/

static void btif_media_task_aa_handle_timer(void)
{
#if (defined(DEBUG_MEDIA_AV_FLOW) && (DEBUG_MEDIA_AV_FLOW == TRUE))
    static UINT16 Debug = 0;
    APPL_TRACE_DEBUG1("btif_media_task_aa_handle_timer: %d", Debug++);
#endif

    log_tstamps_us("media task tx timer");

#if (BTA_AV_INCLUDED == TRUE)
    btif_media_send_aa_frame();
#endif
}

#if (BTA_AV_INCLUDED == TRUE)
/*******************************************************************************
 **
 ** Function         btif_media_task_aa_handle_timer
 **
 ** Description
 **
 ** Returns          void
 **
 *******************************************************************************/
static void btif_media_task_aa_handle_uipc_rx_rdy(void)
{
#if (defined(DEBUG_MEDIA_AV_FLOW) && (DEBUG_MEDIA_AV_FLOW == TRUE))
    static UINT16 Debug = 0;
    APPL_TRACE_DEBUG1("btif_media_task_aa_handle_uipc_rx_rdy: %d", Debug++);
#endif

    /* process all the UIPC data */
    btif_media_aa_prep_2_send(0xFF);

    /* send it */
    VERBOSE("btif_media_task_aa_handle_uipc_rx_rdy calls bta_av_ci_src_data_ready");
    bta_av_ci_src_data_ready(BTA_AV_CHNL_AUDIO);
}
#endif

/*******************************************************************************
 **
 ** Function         btif_media_task_init
 **
 ** Description
 **
 ** Returns          void
 **
 *******************************************************************************/

void btif_media_task_init(void)
{
    memset(&(btif_media_cb), 0, sizeof(btif_media_cb));

    UIPC_Init(NULL);

#if (BTA_AV_INCLUDED == TRUE)
    UIPC_Open(UIPC_CH_ID_AV_CTRL , btif_a2dp_ctrl_cb);
#endif


}
/*******************************************************************************
 **
 ** Function         btif_media_task
 **
 ** Description      Task for SBC encoder.  This task receives an
 **                  event when the waveIn interface has a pcm data buffer
 **                  ready.  On receiving the event, handle all ready pcm
 **                  data buffers.  If stream is started, run the SBC encoder
 **                  on each chunk of pcm samples and build an output packet
 **                  consisting of one or more encoded SBC frames.
 **
 ** Returns          void
 **
 *******************************************************************************/
int btif_media_task(void *p)
{
    UINT16 event;
    BT_HDR *p_msg;

    VERBOSE("================ MEDIA TASK STARTING ================");

    btif_media_task_init();

    media_task_running = MEDIA_TASK_STATE_ON;

    raise_priority_a2dp(TASK_HIGH_MEDIA);

    while (1)
    {
        event = GKI_wait(0xffff, 0);

        VERBOSE("================= MEDIA TASK EVENT %d ===============", event);

        if (event & BTIF_MEDIA_TASK_CMD)
        {
            /* Process all messages in the queue */
            while ((p_msg = (BT_HDR *) GKI_read_mbox(BTIF_MEDIA_TASK_CMD_MBOX)) != NULL)
            {
                btif_media_task_handle_cmd(p_msg);
            }
        }

        if (event & BTIF_MEDIA_TASK_DATA)
        {
            /* Process all messages in the queue */
            while ((p_msg = (BT_HDR *) GKI_read_mbox(BTIF_MEDIA_TASK_DATA_MBOX)) != NULL)
            {
                btif_media_task_handle_media(p_msg);
            }
        }

        if (event & BTIF_MEDIA_AA_TASK_TIMER)
        {
            /* advance audio timer expiration */
            btif_media_task_aa_handle_timer();
        }


        VERBOSE("=============== MEDIA TASK EVENT %d DONE ============", event);

        /* When we get this event we exit the task  - should only happen on GKI_shutdown  */
        if (event & BTIF_MEDIA_TASK_KILL)
        {
            /* make sure no channels are restarted while shutting down */
            media_task_running = MEDIA_TASK_STATE_SHUTTING_DOWN;

            /* this calls blocks until uipc is fully closed */
            UIPC_Close(UIPC_CH_ID_ALL);
            break;
        }
    }

    /* Clear media task flag */
    media_task_running = MEDIA_TASK_STATE_OFF;

    APPL_TRACE_DEBUG0("MEDIA TASK EXITING");

    return 0;
}


/*******************************************************************************
 **
 ** Function         btif_media_task_send_cmd_evt
 **
 ** Description
 **
 ** Returns          TRUE is success
 **
 *******************************************************************************/
BOOLEAN btif_media_task_send_cmd_evt(UINT16 Evt)
{
    BT_HDR *p_buf;
    if (NULL == (p_buf = GKI_getbuf(sizeof(BT_HDR))))
    {
        return FALSE;
    }

    p_buf->event = Evt;

    GKI_send_msg(BT_MEDIA_TASK, BTIF_MEDIA_TASK_CMD_MBOX, p_buf);
    return TRUE;
}

/*******************************************************************************
 **
 ** Function         btif_media_flush_q
 **
 ** Description
 **
 ** Returns          void
 **
 *******************************************************************************/
static void btif_media_flush_q(BUFFER_Q *p_q)
{
    while (GKI_IS_QUEUE_EMPTY(p_q) == FALSE)
    {
        GKI_freebuf(GKI_dequeue(p_q));
    }
}


/*******************************************************************************
 **
 ** Function         btif_media_task_handle_cmd
 **
 ** Description
 **
 ** Returns          void
 **
 *******************************************************************************/
static void btif_media_task_handle_cmd(BT_HDR *p_msg)
{
    VERBOSE("btif_media_task_handle_cmd : %d %s", p_msg->event, dump_media_event(p_msg->event));

    switch (p_msg->event)
    {
#if (BTA_AV_INCLUDED == TRUE)
    case BTIF_MEDIA_START_AA_TX:
        btif_media_task_aa_start_tx();
        break;
    case BTIF_MEDIA_STOP_AA_TX:
        btif_media_task_aa_stop_tx();
        break;
    case BTIF_MEDIA_SBC_ENC_INIT:
        btif_media_task_enc_init(p_msg);
        break;
    case BTIF_MEDIA_SBC_ENC_UPDATE:
        btif_media_task_enc_update(p_msg);
        break;
    case BTIF_MEDIA_AUDIO_FEEDING_INIT:
        btif_media_task_audio_feeding_init(p_msg);
        break;
    case BTIF_MEDIA_FLUSH_AA_TX:
        btif_media_task_aa_tx_flush(p_msg);
        break;
    case BTIF_MEDIA_UIPC_RX_RDY:
        btif_media_task_aa_handle_uipc_rx_rdy();
        break;
#endif
    default:
        APPL_TRACE_ERROR1("ERROR in btif_media_task_handle_cmd unknown event %d", p_msg->event);
    }
    GKI_freebuf(p_msg);
    VERBOSE("btif_media_task_handle_cmd : %s DONE", dump_media_event(p_msg->event));
}

/*******************************************************************************
 **
 ** Function         btif_media_task_handle_media
 **
 ** Description
 **
 ** Returns          void
 **
 *******************************************************************************/
static void btif_media_task_handle_media(BT_HDR *p_msg)
{
    APPL_TRACE_ERROR0("ERROR btif_media_task_handle_media: not in use");

    GKI_freebuf(p_msg);
}




#if (BTA_AV_INCLUDED == TRUE)
/*******************************************************************************
 **
 ** Function         btif_media_task_enc_init_req
 **
 ** Description
 **
 ** Returns          TRUE is success
 **
 *******************************************************************************/
BOOLEAN btif_media_task_enc_init_req(tBTIF_MEDIA_INIT_AUDIO *p_msg)
{
    tBTIF_MEDIA_INIT_AUDIO *p_buf;
    if (NULL == (p_buf = GKI_getbuf(sizeof(tBTIF_MEDIA_INIT_AUDIO))))
    {
        return FALSE;
    }

    memcpy(p_buf, p_msg, sizeof(tBTIF_MEDIA_INIT_AUDIO));
    p_buf->hdr.event = BTIF_MEDIA_SBC_ENC_INIT;

    GKI_send_msg(BT_MEDIA_TASK, BTIF_MEDIA_TASK_CMD_MBOX, p_buf);
    return TRUE;
}

/*******************************************************************************
 **
 ** Function         btif_media_task_enc_update_req
 **
 ** Description
 **
 ** Returns          TRUE is success
 **
 *******************************************************************************/
BOOLEAN btif_media_task_enc_update_req(tBTIF_MEDIA_UPDATE_AUDIO *p_msg)
{
    tBTIF_MEDIA_UPDATE_AUDIO *p_buf;
    if (NULL == (p_buf = GKI_getbuf(sizeof(tBTIF_MEDIA_UPDATE_AUDIO))))
    {
        return FALSE;
    }

    memcpy(p_buf, p_msg, sizeof(tBTIF_MEDIA_UPDATE_AUDIO));
    p_buf->hdr.event = BTIF_MEDIA_SBC_ENC_UPDATE;

    GKI_send_msg(BT_MEDIA_TASK, BTIF_MEDIA_TASK_CMD_MBOX, p_buf);
    return TRUE;
}

/*******************************************************************************
 **
 ** Function         btif_media_task_audio_feeding_init_req
 **
 ** Description
 **
 ** Returns          TRUE is success
 **
 *******************************************************************************/
BOOLEAN btif_media_task_audio_feeding_init_req(tBTIF_MEDIA_INIT_AUDIO_FEEDING *p_msg)
{
    tBTIF_MEDIA_INIT_AUDIO_FEEDING *p_buf;
    if (NULL == (p_buf = GKI_getbuf(sizeof(tBTIF_MEDIA_INIT_AUDIO_FEEDING))))
    {
        return FALSE;
    }

    memcpy(p_buf, p_msg, sizeof(tBTIF_MEDIA_INIT_AUDIO_FEEDING));
    p_buf->hdr.event = BTIF_MEDIA_AUDIO_FEEDING_INIT;

    GKI_send_msg(BT_MEDIA_TASK, BTIF_MEDIA_TASK_CMD_MBOX, p_buf);
    return TRUE;
}

/*******************************************************************************
 **
 ** Function         btif_media_task_start_aa_req
 **
 ** Description
 **
 ** Returns          TRUE is success
 **
 *******************************************************************************/
BOOLEAN btif_media_task_start_aa_req(void)
{
    BT_HDR *p_buf;
    if (NULL == (p_buf = GKI_getbuf(sizeof(BT_HDR))))
    {
        APPL_TRACE_EVENT0("GKI failed");
        return FALSE;
    }

    p_buf->event = BTIF_MEDIA_START_AA_TX;

    GKI_send_msg(BT_MEDIA_TASK, BTIF_MEDIA_TASK_CMD_MBOX, p_buf);
    return TRUE;
}

/*******************************************************************************
 **
 ** Function         btif_media_task_stop_aa_req
 **
 ** Description
 **
 ** Returns          TRUE is success
 **
 *******************************************************************************/
BOOLEAN btif_media_task_stop_aa_req(void)
{
    BT_HDR *p_buf;
    if (NULL == (p_buf = GKI_getbuf(sizeof(BT_HDR))))
    {
        return FALSE;
    }

    p_buf->event = BTIF_MEDIA_STOP_AA_TX;

    GKI_send_msg(BT_MEDIA_TASK, BTIF_MEDIA_TASK_CMD_MBOX, p_buf);
    return TRUE;
}

/*******************************************************************************
 **
 ** Function         btif_media_task_aa_tx_flush_req
 **
 ** Description
 **
 ** Returns          TRUE is success
 **
 *******************************************************************************/
BOOLEAN btif_media_task_aa_tx_flush_req(void)
{
    BT_HDR *p_buf;
    if (NULL == (p_buf = GKI_getbuf(sizeof(BT_HDR))))
    {
        return FALSE;
    }

    p_buf->event = BTIF_MEDIA_FLUSH_AA_TX;

    GKI_send_msg(BT_MEDIA_TASK, BTIF_MEDIA_TASK_CMD_MBOX, p_buf);
    return TRUE;
}

/*******************************************************************************
 **
 ** Function         btif_media_task_aa_tx_flush
 **
 ** Description
 **
 ** Returns          void
 **
 *******************************************************************************/
static void btif_media_task_aa_tx_flush(BT_HDR *p_msg)
{
    /* Flush all enqueued GKI music buffers (encoded) */
    APPL_TRACE_DEBUG0("btif_media_task_aa_tx_flush");

    btif_media_flush_q(&(btif_media_cb.TxAaQ));

    UIPC_Ioctl(UIPC_CH_ID_AV_AUDIO, UIPC_REQ_RX_FLUSH, NULL);
}

/*******************************************************************************
 **
 ** Function       btif_media_task_enc_init
 **
 ** Description    Initialize encoding task
 **
 ** Returns        void
 **
 *******************************************************************************/
static void btif_media_task_enc_init(BT_HDR *p_msg)
{
    tBTIF_MEDIA_INIT_AUDIO *pInitAudio = (tBTIF_MEDIA_INIT_AUDIO *) p_msg;

    APPL_TRACE_DEBUG0("btif_media_task_enc_init");

    btif_media_cb.timestamp = 0;

    /* SBC encoder config (enforced even if not used) */
    btif_media_cb.encoder.s16ChannelMode = pInitAudio->ChannelMode;
    btif_media_cb.encoder.s16NumOfSubBands = pInitAudio->NumOfSubBands;
    btif_media_cb.encoder.s16NumOfBlocks = pInitAudio->NumOfBlocks;
    btif_media_cb.encoder.s16AllocationMethod = pInitAudio->AllocationMethod;
    btif_media_cb.encoder.s16SamplingFreq = pInitAudio->SamplingFreq;

    btif_media_cb.encoder.u16BitRate = DEFAULT_SBC_BITRATE;
    /* Default transcoding is PCM to SBC, modified by feeding configuration */
    btif_media_cb.TxTranscoding = BTIF_MEDIA_TRSCD_PCM_2_SBC;
    btif_media_cb.TxAaMtuSize = ((BTIF_MEDIA_AA_BUF_SIZE-BTIF_MEDIA_AA_SBC_OFFSET-sizeof(BT_HDR))
            < pInitAudio->MtuSize) ? (BTIF_MEDIA_AA_BUF_SIZE - BTIF_MEDIA_AA_SBC_OFFSET
            - sizeof(BT_HDR)) : pInitAudio->MtuSize;

    APPL_TRACE_EVENT3("btif_media_task_enc_init busy %d, mtu %d, peer mtu %d",
                     btif_media_cb.busy_level, btif_media_cb.TxAaMtuSize, pInitAudio->MtuSize);
    APPL_TRACE_EVENT6("      ch mode %d, subnd %d, nb blk %d, alloc %d, rate %d, freq %d",
            btif_media_cb.encoder.s16ChannelMode, btif_media_cb.encoder.s16NumOfSubBands,
            btif_media_cb.encoder.s16NumOfBlocks,
            btif_media_cb.encoder.s16AllocationMethod, btif_media_cb.encoder.u16BitRate,
            btif_media_cb.encoder.s16SamplingFreq);

    /* Reset entirely the SBC encoder */
    SBC_Encoder_Init(&(btif_media_cb.encoder));
    APPL_TRACE_DEBUG1("btif_media_task_enc_init bit pool %d", btif_media_cb.encoder.s16BitPool);
}

/*******************************************************************************
 **
 ** Function       btif_media_task_enc_update
 **
 ** Description    Update encoding task
 **
 ** Returns        void
 **
 *******************************************************************************/

static void btif_media_task_enc_update(BT_HDR *p_msg)
{
    tBTIF_MEDIA_UPDATE_AUDIO * pUpdateAudio = (tBTIF_MEDIA_UPDATE_AUDIO *) p_msg;
    SBC_ENC_PARAMS *pstrEncParams = &btif_media_cb.encoder;
    UINT16 s16SamplingFreq;
    SINT16 s16BitPool;
    SINT16 s16BitRate;
    SINT16 s16FrameLen;
    UINT8 protect = 0;

    APPL_TRACE_DEBUG3("btif_media_task_enc_update : minmtu %d, maxbp %d minbp %d",
            pUpdateAudio->MinMtuSize, pUpdateAudio->MaxBitPool, pUpdateAudio->MinBitPool);

    /* Only update the bitrate and MTU size while timer is running to make sure it has been initialized */
    //if (btif_media_cb.is_tx_timer)
    {
        btif_media_cb.TxAaMtuSize = ((BTIF_MEDIA_AA_BUF_SIZE - BTIF_MEDIA_AA_SBC_OFFSET - sizeof(BT_HDR))
                < pUpdateAudio->MinMtuSize) ? (BTIF_MEDIA_AA_BUF_SIZE - BTIF_MEDIA_AA_SBC_OFFSET
                - sizeof(BT_HDR)) : pUpdateAudio->MinMtuSize;

        /* Set the initial target bit rate */
        pstrEncParams->u16BitRate = DEFAULT_SBC_BITRATE;

        if (pstrEncParams->s16SamplingFreq == SBC_sf16000)
            s16SamplingFreq = 16000;
        else if (pstrEncParams->s16SamplingFreq == SBC_sf32000)
            s16SamplingFreq = 32000;
        else if (pstrEncParams->s16SamplingFreq == SBC_sf44100)
            s16SamplingFreq = 44100;
        else
            s16SamplingFreq = 48000;

        do
        {
            if ((pstrEncParams->s16ChannelMode == SBC_JOINT_STEREO) ||
                (pstrEncParams->s16ChannelMode == SBC_STEREO) )
            {
                s16BitPool = (SINT16)( (pstrEncParams->u16BitRate *
                    pstrEncParams->s16NumOfSubBands * 1000 / s16SamplingFreq)
                    -( (32 + (4 * pstrEncParams->s16NumOfSubBands *
                    pstrEncParams->s16NumOfChannels)
                    + ( (pstrEncParams->s16ChannelMode - 2) *
                    pstrEncParams->s16NumOfSubBands )   )
                    / pstrEncParams->s16NumOfBlocks) );

                s16FrameLen = 4 + (4*pstrEncParams->s16NumOfSubBands*
                    pstrEncParams->s16NumOfChannels)/8
                    + ( ((pstrEncParams->s16ChannelMode - 2) *
                    pstrEncParams->s16NumOfSubBands)
                    + (pstrEncParams->s16NumOfBlocks * s16BitPool) ) / 8;

                s16BitRate = (8 * s16FrameLen * s16SamplingFreq)
                    / (pstrEncParams->s16NumOfSubBands *
                    pstrEncParams->s16NumOfBlocks * 1000);

                if (s16BitRate > pstrEncParams->u16BitRate)
                    s16BitPool--;

                if(pstrEncParams->s16NumOfSubBands == 8)
                    s16BitPool = (s16BitPool > 255) ? 255 : s16BitPool;
                else
                    s16BitPool = (s16BitPool > 128) ? 128 : s16BitPool;
            }
            else
            {
                s16BitPool = (SINT16)( ((pstrEncParams->s16NumOfSubBands *
                    pstrEncParams->u16BitRate * 1000)
                    / (s16SamplingFreq * pstrEncParams->s16NumOfChannels))
                    -( ( (32 / pstrEncParams->s16NumOfChannels) +
                    (4 * pstrEncParams->s16NumOfSubBands) )
                    /   pstrEncParams->s16NumOfBlocks ) );

                pstrEncParams->s16BitPool = (s16BitPool >
                    (16 * pstrEncParams->s16NumOfSubBands))
                    ? (16*pstrEncParams->s16NumOfSubBands) : s16BitPool;
            }

            if (s16BitPool < 0)
            {
                s16BitPool = 0;
            }

            APPL_TRACE_EVENT2("bitpool candidate : %d (%d kbps)", s16BitPool, pstrEncParams->u16BitRate);

            if (s16BitPool > pUpdateAudio->MaxBitPool)
            {
                APPL_TRACE_WARNING1("btif_media_task_enc_update computed bitpool too large (%d)", s16BitPool);
                /* Decrease bitrate */
                btif_media_cb.encoder.u16BitRate -= BTIF_MEDIA_BITRATE_STEP;
                /* Record that we have decreased the bitrate */
                protect |= 1;
            }
            else if (s16BitPool < pUpdateAudio->MinBitPool)
            {
                APPL_TRACE_WARNING1("btif_media_task_enc_update computed bitpool too small (%d)", s16BitPool);
                /* Increase bitrate */
                btif_media_cb.encoder.u16BitRate += BTIF_MEDIA_BITRATE_STEP;
                /* Record that we have increased the bitrate */
                protect |= 2;
            }
            else
            {
                break;
            }
            /* In case we have already increased and decreased the bitrate, just stop */
            if (protect == 3)
            {
                APPL_TRACE_ERROR0("btif_media_task_enc_update could not find bitpool in range");
                break;
            }
        } while (1);

        /* Finally update the bitpool in the encoder structure */
        pstrEncParams->s16BitPool = s16BitPool;

        APPL_TRACE_DEBUG2("btif_media_task_enc_update final bit rate %d, final bit pool %d",
                btif_media_cb.encoder.u16BitRate, btif_media_cb.encoder.s16BitPool);

        /* make sure we reinitialize encoder with new settings */
        SBC_Encoder_Init(&(btif_media_cb.encoder));
    }
}

/*******************************************************************************
 **
 ** Function         btif_media_task_pcm2sbc_init
 **
 ** Description      Init encoding task for PCM to SBC according to feeding
 **
 ** Returns          void
 **
 *******************************************************************************/
static void btif_media_task_pcm2sbc_init(tBTIF_MEDIA_INIT_AUDIO_FEEDING * p_feeding)
{
    BOOLEAN reconfig_needed = FALSE;

    APPL_TRACE_DEBUG0("PCM feeding:");
    APPL_TRACE_DEBUG1("sampling_freq:%d", p_feeding->feeding.cfg.pcm.sampling_freq);
    APPL_TRACE_DEBUG1("num_channel:%d", p_feeding->feeding.cfg.pcm.num_channel);
    APPL_TRACE_DEBUG1("bit_per_sample:%d", p_feeding->feeding.cfg.pcm.bit_per_sample);


    /* Check the PCM feeding sampling_freq */
    switch (p_feeding->feeding.cfg.pcm.sampling_freq)
    {
        case  8000:
        case 12000:
        case 16000:
        case 24000:
        case 32000:
        case 48000:
            /* For these sampling_freq the AV connection must be 48000 */
            if (btif_media_cb.encoder.s16SamplingFreq != SBC_sf48000)
            {
                /* Reconfiguration needed at 48000 */
                APPL_TRACE_DEBUG0("SBC Reconfiguration needed at 48000");
                btif_media_cb.encoder.s16SamplingFreq = SBC_sf48000;
                reconfig_needed = TRUE;
            }
            break;

        case 11025:
        case 22050:
        case 44100:
            /* For these sampling_freq the AV connection must be 44100 */
            if (btif_media_cb.encoder.s16SamplingFreq != SBC_sf44100)
            {
                /* Reconfiguration needed at 44100 */
                APPL_TRACE_DEBUG0("SBC Reconfiguration needed at 44100");
                btif_media_cb.encoder.s16SamplingFreq = SBC_sf44100;
                reconfig_needed = TRUE;
            }
            break;
        default:
            APPL_TRACE_DEBUG0("Feeding PCM sampling_freq unsupported");
            break;
    }

    /* Some AV Headsets do not support Mono => always ask for Stereo */
    if (btif_media_cb.encoder.s16ChannelMode == SBC_MONO)
    {
        APPL_TRACE_DEBUG0("SBC Reconfiguration needed in Stereo");
        btif_media_cb.encoder.s16ChannelMode = SBC_JOINT_STEREO;
        reconfig_needed = TRUE;
    }

    if (reconfig_needed != FALSE)
    {
        APPL_TRACE_DEBUG0("btif_media_task_pcm2sbc_init calls SBC_Encoder_Init");
        APPL_TRACE_DEBUG1("btif_media_task_pcm2sbc_init mtu %d", btif_media_cb.TxAaMtuSize);
        APPL_TRACE_DEBUG6("btif_media_task_pcm2sbc_init ch mode %d, nbsubd %d, nb blk %d, alloc method %d, bit rate %d, Smp freq %d",
                btif_media_cb.encoder.s16ChannelMode, btif_media_cb.encoder.s16NumOfSubBands, btif_media_cb.encoder.s16NumOfBlocks,
                btif_media_cb.encoder.s16AllocationMethod, btif_media_cb.encoder.u16BitRate, btif_media_cb.encoder.s16SamplingFreq);
        SBC_Encoder_Init(&(btif_media_cb.encoder));
    }
    else
    {
        APPL_TRACE_DEBUG0("btif_media_task_pcm2sbc_init no SBC reconfig needed");
    }
}


/*******************************************************************************
 **
 ** Function         btif_media_task_audio_feeding_init
 **
 ** Description      Initialize the audio path according to the feeding format
 **
 ** Returns          void
 **
 *******************************************************************************/
static void btif_media_task_audio_feeding_init(BT_HDR *p_msg)
{
    tBTIF_MEDIA_INIT_AUDIO_FEEDING *p_feeding = (tBTIF_MEDIA_INIT_AUDIO_FEEDING *) p_msg;

    APPL_TRACE_DEBUG1("btif_media_task_audio_feeding_init format:%d", p_feeding->feeding.format);

    /* Save Media Feeding information */
    btif_media_cb.feeding_mode = p_feeding->feeding_mode;
    btif_media_cb.media_feeding = p_feeding->feeding;

    /* Handle different feeding formats */
    switch (p_feeding->feeding.format)
    {
        case BTIF_AV_CODEC_PCM:
            btif_media_cb.TxTranscoding = BTIF_MEDIA_TRSCD_PCM_2_SBC;
            btif_media_task_pcm2sbc_init(p_feeding);
            break;

        default :
            APPL_TRACE_ERROR1("unknown feeding format %d", p_feeding->feeding.format);
            break;
    }
}

/*******************************************************************************
 **
 ** Function         btif_media_task_uipc_cback
 **
 ** Description      UIPC call back function for synchronous mode only
 **
 ** Returns          void
 **
 *******************************************************************************/
static void btif_media_task_uipc_cback(BT_HDR *p_msg)
{
    /* Sanity check */
    if (NULL == p_msg)
    {
        return;
    }

    /* Just handle RX_EVT */
    if (p_msg->event != UIPC_RX_DATA_EVT)
    {
        return;
    }

    p_msg->event = BTIF_MEDIA_UIPC_RX_RDY;

    GKI_send_msg(BT_MEDIA_TASK, BTIF_MEDIA_TASK_CMD_MBOX, p_msg);
}

/*******************************************************************************
 **
 ** Function         btif_media_task_feeding_state_reset
 **
 ** Description      Reset the media feeding state
 **
 ** Returns          void
 **
 *******************************************************************************/
static void btif_media_task_feeding_state_reset(void)
{
    /* By default, just clear the entire state */
    memset(&btif_media_cb.media_feeding_state, 0, sizeof(btif_media_cb.media_feeding_state));
}
/*******************************************************************************
 **
 ** Function         btif_media_task_aa_start_tx
 **
 ** Description      Start media task encoding
 **
 ** Returns          void
 **
 *******************************************************************************/
static void btif_media_task_aa_start_tx(void)
{
    APPL_TRACE_DEBUG2("btif_media_task_aa_start_tx is timer %d, feeding mode %d",
            btif_media_cb.is_tx_timer, btif_media_cb.feeding_mode);


    /* Use a timer to poll the UIPC, get rid of the UIPC call back */
    // UIPC_Ioctl(UIPC_CH_ID_AV_AUDIO, UIPC_REG_CBACK, NULL);

    btif_media_cb.is_tx_timer = TRUE;

    /* Reset the media feeding state */
    btif_media_task_feeding_state_reset();

    APPL_TRACE_EVENT2("starting timer %d ticks (%d)", GKI_MS_TO_TICKS(BTIF_MEDIA_TIME_TICK), TICKS_PER_SEC);
    GKI_start_timer(BTIF_MEDIA_AA_TASK_TIMER_ID, GKI_MS_TO_TICKS(BTIF_MEDIA_TIME_TICK), TRUE);
}

/*******************************************************************************
 **
 ** Function         btif_media_task_aa_stop_tx
 **
 ** Description      Stop media task encoding
 **
 ** Returns          void
 **
 *******************************************************************************/
static void btif_media_task_aa_stop_tx(void)
{
    APPL_TRACE_DEBUG1("btif_media_task_aa_stop_tx is timer: %d", btif_media_cb.is_tx_timer);

    /* Stop the timer first */
    GKI_stop_timer(BTIF_MEDIA_AA_TASK_TIMER_ID);
    btif_media_cb.is_tx_timer = FALSE;

    UIPC_Close(UIPC_CH_ID_AV_AUDIO);

    /* audio engine stopped, reset tx suspended flag */
    btif_media_cb.tx_flush = 0;

    /* Reset the media feeding state */
    btif_media_task_feeding_state_reset();
}

/*******************************************************************************
 **
 ** Function         btif_get_num_aa_frame
 **
 ** Description
 **
 ** Returns          The number of media frames in this time slice
 **
 *******************************************************************************/


static UINT8 btif_get_num_aa_frame(void)
{
    UINT8 result=0;

    switch (btif_media_cb.TxTranscoding)
    {
        case BTIF_MEDIA_TRSCD_PCM_2_SBC:
            switch (btif_media_cb.encoder.s16SamplingFreq)
            {
            case SBC_sf16000:
                if (!btif_media_cb.scaling_disabled &&
                    (btif_media_cb.media_feeding_state.pcm.aa_frame_counter++ % 2) == 0)
                {
                    result = BTIF_MEDIA_FR_PER_TICKS_16-1;
                }
                else
                {
                    result = BTIF_MEDIA_FR_PER_TICKS_16;
                }
                break;

            case SBC_sf32000:
                result = BTIF_MEDIA_FR_PER_TICKS_32;
                break;

            case SBC_sf48000:
                if (!btif_media_cb.scaling_disabled &&
                    (btif_media_cb.media_feeding_state.pcm.aa_frame_counter++ % 2) == 0)
                {
                    result = BTIF_MEDIA_FR_PER_TICKS_48-1;
                }
                else
                {
                    result = BTIF_MEDIA_FR_PER_TICKS_48;
                }
                break;

            case SBC_sf44100:
                if (!btif_media_cb.scaling_disabled &&
                    (btif_media_cb.media_feeding_state.pcm.aa_frame_counter++ % 64) < 7)
                {
                    result = BTIF_MEDIA_FR_PER_TICKS_44_1-1;
                }
                else
                {
                    result = BTIF_MEDIA_FR_PER_TICKS_44_1;
                }
                break;
            }

            VERBOSE("WRITE %d FRAMES", result);
            break;

        default:
            APPL_TRACE_ERROR1("ERROR btif_get_num_aa_frame Unsupported transcoding format 0x%x",
                    btif_media_cb.TxTranscoding);
            result = 0;
            break;
    }

#if (defined(DEBUG_MEDIA_AV_FLOW) && (DEBUG_MEDIA_AV_FLOW == TRUE))
    APPL_TRACE_DEBUG1("btif_get_num_aa_frame returns %d", result);
#endif

    return result;
}

/*******************************************************************************
 **
 ** Function         btif_media_aa_readbuf
 **
 ** Description      This function is called by the av_co to get the next buffer to send
 **
 **
 ** Returns          void
 *******************************************************************************/
BT_HDR *btif_media_aa_readbuf(void)
{
    return GKI_dequeue(&(btif_media_cb.TxAaQ));
}

/*******************************************************************************
 **
 ** Function         btif_media_aa_read_feeding
 **
 ** Description
 **
 ** Returns          void
 **
 *******************************************************************************/

BOOLEAN btif_media_aa_read_feeding(tUIPC_CH_ID channel_id)
{
    UINT16 event;
    /* coverity[SIGN_EXTENSION] False-positive: Parameter are always in range avoiding sign extension*/
    UINT16 blocm_x_subband = btif_media_cb.encoder.s16NumOfSubBands * btif_media_cb.encoder.s16NumOfBlocks;
    UINT32 read_size;
    UINT16 sbc_sampling = 48000;
    UINT32 src_samples;
    UINT16 bytes_needed = blocm_x_subband * btif_media_cb.encoder.s16NumOfChannels * sizeof(SINT16);
    static UINT16 up_sampled_buffer[SBC_MAX_NUM_FRAME * SBC_MAX_NUM_OF_BLOCKS
            * SBC_MAX_NUM_OF_CHANNELS * SBC_MAX_NUM_OF_SUBBANDS * 2];
    static UINT16 read_buffer[SBC_MAX_NUM_FRAME * SBC_MAX_NUM_OF_BLOCKS
            * SBC_MAX_NUM_OF_CHANNELS * SBC_MAX_NUM_OF_SUBBANDS];
    UINT32 src_size_used;
    UINT32 dst_size_used;
    BOOLEAN fract_needed;
    INT32   fract_max;
    INT32   fract_threshold;
    UINT32  nb_byte_read;

    /* Get the SBC sampling rate */
    switch (btif_media_cb.encoder.s16SamplingFreq)
    {
    case SBC_sf48000:
        sbc_sampling = 48000;
        break;
    case SBC_sf44100:
        sbc_sampling = 44100;
        break;
    case SBC_sf32000:
        sbc_sampling = 32000;
        break;
    case SBC_sf16000:
        sbc_sampling = 16000;
        break;
    }

    /* Some Feeding PCM frequencies require to split the number of sample */
    /* to read. */
    /* E.g 128/6=21.3333 => read 22 and 21 and 21 => max = 2; threshold = 0*/
    fract_needed = FALSE;   /* Default */
    switch (btif_media_cb.media_feeding.cfg.pcm.sampling_freq)
    {
    case 32000:
    case 8000:
        fract_needed = TRUE;
        fract_max = 2;          /* 0, 1 and 2 */
        fract_threshold = 0;    /* Add one for the first */
        break;
    case 16000:
        fract_needed = TRUE;
        fract_max = 2;          /* 0, 1 and 2 */
        fract_threshold = 1;    /* Add one for the first two frames*/
        break;
    }

    /* Compute number of sample to read from source */
    src_samples = blocm_x_subband;
    src_samples *= btif_media_cb.media_feeding.cfg.pcm.sampling_freq;
    src_samples /= sbc_sampling;

    /* The previous division may have a remainder not null */
    if (fract_needed)
    {
        if (btif_media_cb.media_feeding_state.pcm.aa_feed_counter <= fract_threshold)
        {
            src_samples++; /* for every read before threshold add one sample */
        }

        /* do nothing if counter >= threshold */
        btif_media_cb.media_feeding_state.pcm.aa_feed_counter++; /* one more read */
        if (btif_media_cb.media_feeding_state.pcm.aa_feed_counter > fract_max)
        {
            btif_media_cb.media_feeding_state.pcm.aa_feed_counter = 0;
        }
    }

    /* Compute number of bytes to read from source */
    read_size = src_samples;
    read_size *= btif_media_cb.media_feeding.cfg.pcm.num_channel;
    read_size *= (btif_media_cb.media_feeding.cfg.pcm.bit_per_sample / 8);

    /* Read Data from UIPC channel */
    nb_byte_read = UIPC_Read(channel_id, &event, (UINT8 *)read_buffer, read_size);

    //tput_mon(TRUE, nb_byte_read, FALSE);

    if (nb_byte_read < read_size)
    {
        APPL_TRACE_WARNING2("### UNDERRUN :: ONLY READ %d BYTES OUT OF %d ###",
                nb_byte_read, read_size);

        if (nb_byte_read == 0)
            return FALSE;

        if(btif_media_cb.feeding_mode == BTIF_AV_FEEDING_ASYNCHRONOUS)
        {
            /* Fill the unfilled part of the read buffer with silence (0) */
            memset(((UINT8 *)read_buffer) + nb_byte_read, 0, read_size - nb_byte_read);
            nb_byte_read = read_size;
        }
    }

    /* Initialize PCM up-sampling engine */
    bta_av_sbc_init_up_sample(btif_media_cb.media_feeding.cfg.pcm.sampling_freq,
            sbc_sampling, btif_media_cb.media_feeding.cfg.pcm.bit_per_sample,
            btif_media_cb.media_feeding.cfg.pcm.num_channel);

    /* re-sample read buffer */
    /* The output PCM buffer will be stereo, 16 bit per sec */
    dst_size_used = bta_av_sbc_up_sample((UINT8 *)read_buffer,
            (UINT8 *)up_sampled_buffer + btif_media_cb.media_feeding_state.pcm.aa_feed_residue,
            nb_byte_read,
            sizeof(up_sampled_buffer) - btif_media_cb.media_feeding_state.pcm.aa_feed_residue,
            &src_size_used);

#if (defined(DEBUG_MEDIA_AV_FLOW) && (DEBUG_MEDIA_AV_FLOW == TRUE))
    APPL_TRACE_DEBUG3("btif_media_aa_read_feeding read_size:%d src_size_used:%d dst_size_used:%d",
            read_size, src_size_used, dst_size_used);
#endif

    /* update the residue */
    btif_media_cb.media_feeding_state.pcm.aa_feed_residue += dst_size_used;

    /* only copy the pcm sample when we have up-sampled enough PCM */
    if(btif_media_cb.media_feeding_state.pcm.aa_feed_residue >= bytes_needed)
    {
        /* Copy the output pcm samples in SBC encoding buffer */
        memcpy((UINT8 *)btif_media_cb.encoder.as16PcmBuffer,
                (UINT8 *)up_sampled_buffer,
                bytes_needed);
        /* update the residue */
        btif_media_cb.media_feeding_state.pcm.aa_feed_residue -= bytes_needed;

        if (btif_media_cb.media_feeding_state.pcm.aa_feed_residue != 0)
        {
            memcpy((UINT8 *)up_sampled_buffer,
                   (UINT8 *)up_sampled_buffer + bytes_needed,
                   btif_media_cb.media_feeding_state.pcm.aa_feed_residue);
        }
        return TRUE;
    }

#if (defined(DEBUG_MEDIA_AV_FLOW) && (DEBUG_MEDIA_AV_FLOW == TRUE))
    APPL_TRACE_DEBUG3("btif_media_aa_read_feeding residue:%d, dst_size_used %d, bytes_needed %d",
            btif_media_cb.media_feeding_state.pcm.aa_feed_residue, dst_size_used, bytes_needed);
#endif

    return FALSE;
}

/*******************************************************************************
 **
 ** Function         btif_media_aa_prep_sbc_2_send
 **
 ** Description
 **
 ** Returns          void
 **
 *******************************************************************************/
static void btif_media_aa_prep_sbc_2_send(UINT8 nb_frame)
{
    BT_HDR * p_buf;
    UINT16 blocm_x_subband = btif_media_cb.encoder.s16NumOfSubBands * btif_media_cb.encoder.s16NumOfBlocks;

#if (defined(DEBUG_MEDIA_AV_FLOW) && (DEBUG_MEDIA_AV_FLOW == TRUE))
    APPL_TRACE_DEBUG2("btif_media_aa_prep_sbc_2_send nb_frame %d, TxAaQ %d", nb_frame, btif_media_cb.TxAaQ.count);
#endif
    while (nb_frame)
    {
        if (NULL == (p_buf = GKI_getpoolbuf(BTIF_MEDIA_AA_POOL_ID)))
        {
            APPL_TRACE_ERROR1 ("ERROR btif_media_aa_prep_sbc_2_send no buffer TxCnt %d ", btif_media_cb.TxAaQ.count);
            return;
        }

        /* Init buffer */
        p_buf->offset = BTIF_MEDIA_AA_SBC_OFFSET;
        p_buf->len = 0;
        p_buf->layer_specific = 0;

        do
        {
            /* Write @ of allocated buffer in encoder.pu8Packet */
            btif_media_cb.encoder.pu8Packet = (UINT8 *) (p_buf + 1) + p_buf->offset + p_buf->len;
            /* Fill allocated buffer with 0 */
            /* coverity[SIGN_EXTENSION] False-positive: Parameter are always in range avoiding sign extension*/
            memset(btif_media_cb.encoder.as16PcmBuffer, 0, blocm_x_subband
                    * btif_media_cb.encoder.s16NumOfChannels);

            /* Read PCM data and upsample them if needed */
            if (btif_media_aa_read_feeding(UIPC_CH_ID_AV_AUDIO))
            {
                /* SBC encode and descramble frame */
                SBC_Encoder(&(btif_media_cb.encoder));
                A2D_SbcChkFrInit(btif_media_cb.encoder.pu8Packet);
                A2D_SbcDescramble(btif_media_cb.encoder.pu8Packet, btif_media_cb.encoder.u16PacketLength);
                /* Update SBC frame length */
                p_buf->len += btif_media_cb.encoder.u16PacketLength;
                nb_frame--;
                p_buf->layer_specific++;
            }
            else
            {
                /* no more pcm to read */
                nb_frame = 0;

                /* break read loop if timer was stopped (media task stopped) */
                if ( btif_media_cb.is_tx_timer == FALSE )
                    return;
            }

        } while (((p_buf->len + btif_media_cb.encoder.u16PacketLength) < btif_media_cb.TxAaMtuSize)
                && (p_buf->layer_specific < 0x0F) && nb_frame);

        /* coverity[SIGN_EXTENSION] False-positive: Parameter are always in range avoiding sign extension*/
        btif_media_cb.timestamp += p_buf->layer_specific * blocm_x_subband;

        /* store the time stamp in the buffer to send */
        *((UINT32 *) (p_buf + 1)) = btif_media_cb.timestamp;

        VERBOSE("TX QUEUE NOW %d", btif_media_cb.TxAaQ.count);

        if (btif_media_cb.tx_flush)
        {
            APPL_TRACE_DEBUG0("### tx suspended, discarded frame ###");

            if (btif_media_cb.TxAaQ.count > 0)
                btif_media_flush_q(&(btif_media_cb.TxAaQ));

            GKI_freebuf(p_buf);
            return;
        }

        /* Enqueue the encoded SBC frame in AA Tx Queue */
        GKI_enqueue(&(btif_media_cb.TxAaQ), p_buf);
    }
}


/*******************************************************************************
 **
 ** Function         btif_media_aa_prep_2_send
 **
 ** Description
 **
 ** Returns          void
 **
 *******************************************************************************/

static void btif_media_aa_prep_2_send(UINT8 nb_frame)
{
    VERBOSE("btif_media_aa_prep_2_send : %d frames (queue %d)", nb_frame,
                       btif_media_cb.TxAaQ.count);

    /* Remove all the buffers not sent until there are only 4 in the queue */
    while (btif_media_cb.TxAaQ.count >= MAX_OUTPUT_BUFFER_QUEUE_SZ)
    {
        APPL_TRACE_WARNING1("btif_media_aa_prep_2_send congestion buf count %d",btif_media_cb.TxAaQ.count);
        GKI_freebuf(GKI_dequeue(&(btif_media_cb.TxAaQ)));
    }

    switch (btif_media_cb.TxTranscoding)
    {
    case BTIF_MEDIA_TRSCD_PCM_2_SBC:
        btif_media_aa_prep_sbc_2_send(nb_frame);
        break;


    default:
        APPL_TRACE_ERROR1("ERROR btif_media_aa_prep_2_send unsupported transcoding format 0x%x",btif_media_cb.TxTranscoding);
        break;
    }
}

/*******************************************************************************
 **
 ** Function         btif_media_send_aa_frame
 **
 ** Description
 **
 ** Returns          void
 **
 *******************************************************************************/
static void btif_media_send_aa_frame(void)
{
    UINT8 nb_frame_2_send;

    /* get the number of frame to send */
    nb_frame_2_send = btif_get_num_aa_frame();

    /* format and Q buffer to send */
    btif_media_aa_prep_2_send(nb_frame_2_send);

    /* send it */
    VERBOSE("btif_media_send_aa_frame : send %d frames", nb_frame_2_send);
    bta_av_ci_src_data_ready(BTA_AV_CHNL_AUDIO);
}

/*******************************************************************************
 **
 ** Function         btif_media_check_iop_exceptions
 **
 ** Description    Perform any device specific iop changes
 **
 ** Returns          void
 **
 *******************************************************************************/

void btif_media_check_iop_exceptions(UINT8 *peer_bda)
{
    /* disable rate scaling for pcm carkit */
    if ((peer_bda[0] == 0x00) &&
        (peer_bda[1] == 0x0E) &&
        (peer_bda[2] == 0x9F))
    {
        BTIF_TRACE_WARNING0("detected pcm carkit, disable rate scaling");
        btif_media_cb.scaling_disabled = TRUE;
    }
    else
    {
        btif_media_cb.scaling_disabled = FALSE;
    }
}


#endif /* BTA_AV_INCLUDED == TRUE */

/*******************************************************************************
 **
 ** Function         dump_codec_info
 **
 ** Description      Decode and display codec_info (for debug)
 **
 ** Returns          void
 **
 *******************************************************************************/
void dump_codec_info(unsigned char *p_codec)
{
    tA2D_STATUS a2d_status;
    tA2D_SBC_CIE sbc_cie;

    a2d_status = A2D_ParsSbcInfo(&sbc_cie, p_codec, FALSE);
    if (a2d_status != A2D_SUCCESS)
    {
        APPL_TRACE_ERROR1("ERROR dump_codec_info A2D_ParsSbcInfo fail:%d", a2d_status);
        return;
    }

    APPL_TRACE_DEBUG0("dump_codec_info");

    if (sbc_cie.samp_freq == A2D_SBC_IE_SAMP_FREQ_16)
    {    APPL_TRACE_DEBUG1("\tsamp_freq:%d (16000)", sbc_cie.samp_freq);}
    else  if (sbc_cie.samp_freq == A2D_SBC_IE_SAMP_FREQ_32)
    {    APPL_TRACE_DEBUG1("\tsamp_freq:%d (32000)", sbc_cie.samp_freq);}
    else  if (sbc_cie.samp_freq == A2D_SBC_IE_SAMP_FREQ_44)
    {    APPL_TRACE_DEBUG1("\tsamp_freq:%d (44.100)", sbc_cie.samp_freq);}
    else  if (sbc_cie.samp_freq == A2D_SBC_IE_SAMP_FREQ_48)
    {    APPL_TRACE_DEBUG1("\tsamp_freq:%d (48000)", sbc_cie.samp_freq);}
    else
    {    APPL_TRACE_DEBUG1("\tBAD samp_freq:%d", sbc_cie.samp_freq);}

    if (sbc_cie.ch_mode == A2D_SBC_IE_CH_MD_MONO)
    {    APPL_TRACE_DEBUG1("\tch_mode:%d (Mono)", sbc_cie.ch_mode);}
    else  if (sbc_cie.ch_mode == A2D_SBC_IE_CH_MD_DUAL)
    {    APPL_TRACE_DEBUG1("\tch_mode:%d (Dual)", sbc_cie.ch_mode);}
    else  if (sbc_cie.ch_mode == A2D_SBC_IE_CH_MD_STEREO)
    {    APPL_TRACE_DEBUG1("\tch_mode:%d (Stereo)", sbc_cie.ch_mode);}
    else  if (sbc_cie.ch_mode == A2D_SBC_IE_CH_MD_JOINT)
    {    APPL_TRACE_DEBUG1("\tch_mode:%d (Joint)", sbc_cie.ch_mode);}
    else
    {    APPL_TRACE_DEBUG1("\tBAD ch_mode:%d", sbc_cie.ch_mode);}

    if (sbc_cie.block_len == A2D_SBC_IE_BLOCKS_4)
    {    APPL_TRACE_DEBUG1("\tblock_len:%d (4)", sbc_cie.block_len);}
    else  if (sbc_cie.block_len == A2D_SBC_IE_BLOCKS_8)
    {    APPL_TRACE_DEBUG1("\tblock_len:%d (8)", sbc_cie.block_len);}
    else  if (sbc_cie.block_len == A2D_SBC_IE_BLOCKS_12)
    {    APPL_TRACE_DEBUG1("\tblock_len:%d (12)", sbc_cie.block_len);}
    else  if (sbc_cie.block_len == A2D_SBC_IE_BLOCKS_16)
    {    APPL_TRACE_DEBUG1("\tblock_len:%d (16)", sbc_cie.block_len);}
    else
    {    APPL_TRACE_DEBUG1("\tBAD block_len:%d", sbc_cie.block_len);}

    if (sbc_cie.num_subbands == A2D_SBC_IE_SUBBAND_4)
    {    APPL_TRACE_DEBUG1("\tnum_subbands:%d (4)", sbc_cie.num_subbands);}
    else  if (sbc_cie.num_subbands == A2D_SBC_IE_SUBBAND_8)
    {    APPL_TRACE_DEBUG1("\tnum_subbands:%d (8)", sbc_cie.num_subbands);}
    else
    {    APPL_TRACE_DEBUG1("\tBAD num_subbands:%d", sbc_cie.num_subbands);}

    if (sbc_cie.alloc_mthd == A2D_SBC_IE_ALLOC_MD_S)
    {    APPL_TRACE_DEBUG1("\talloc_mthd:%d (SNR)", sbc_cie.alloc_mthd);}
    else  if (sbc_cie.alloc_mthd == A2D_SBC_IE_ALLOC_MD_L)
    {    APPL_TRACE_DEBUG1("\talloc_mthd:%d (Loundess)", sbc_cie.alloc_mthd);}
    else
    {    APPL_TRACE_DEBUG1("\tBAD alloc_mthd:%d", sbc_cie.alloc_mthd);}

    APPL_TRACE_DEBUG2("\tBit pool Min:%d Max:%d", sbc_cie.min_bitpool, sbc_cie.max_bitpool);

}

