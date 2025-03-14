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

/****************************************************************************
 *
 *  Name:       btsnoopdisp.c
 *
 *  Function:   this file contains functions to generate a BTSNOOP file
 *
 *
 ****************************************************************************/
#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <sys/prctl.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

/* for gettimeofday */
#include <sys/time.h>
/* for the S_* open parameters */
#include <sys/stat.h>
/* for write */
#include <unistd.h>
/* for O_* open parameters */
#include <fcntl.h>
/* defines the O_* open parameters */
#include <fcntl.h>

#define LOG_TAG "BTSNOOP-DISP"
#include <cutils/log.h>

#include "bt_hci_bdroid.h"
#include "utils.h"

#ifndef BTSNOOP_DBG
#define BTSNOOP_DBG FALSE
#endif

#if (BTSNOOP_DBG == TRUE)
#define SNOOPDBG(param, ...) {ALOGD(param, ## __VA_ARGS__);}
#else
#define SNOOPDBG(param, ...) {}
#endif

/* file descriptor of the BT snoop file (by default, -1 means disabled) */
int hci_btsnoop_fd = -1;

/* Macro to perform a multiplication of 2 unsigned 32bit values and store the result
 * in an unsigned 64 bit value (as two 32 bit variables):
 * u64 = u32In1 * u32In2
 * u32OutLow = u64[31:0]
 * u32OutHi = u64[63:32]
 * basically the algorithm:
 * (hi1*2^16 + lo1)*(hi2*2^16 + lo2) = lo1*lo2 + (hi1*hi2)*2^32 + (hi1*lo2 + hi2*lo1)*2^16
 * and the carry is propagated 16 bit by 16 bit:
 * result[15:0] = lo1*lo2 & 0xFFFF
 * result[31:16] = ((lo1*lo2) >> 16) + (hi1*lo2 + hi2*lo1)
 * and so on
 */
#define HCIDISP_MULT_64(u32In1, u32In2, u32OutLo, u32OutHi)                             \
do {                                                                                    \
    uint32_t u32In1Tmp = u32In1;                                                          \
    uint32_t u32In2Tmp = u32In2;                                                          \
    uint32_t u32Tmp, u32Carry;                                                            \
    u32OutLo = (u32In1Tmp & 0xFFFF) * (u32In2Tmp & 0xFFFF);              /*lo1*lo2*/    \
    u32OutHi = ((u32In1Tmp >> 16) & 0xFFFF) * ((u32In2Tmp >> 16) & 0xFFFF); /*hi1*hi2*/ \
    u32Tmp = (u32In1Tmp & 0xFFFF) * ((u32In2Tmp >> 16) & 0xFFFF);  /*lo1*hi2*/          \
    u32Carry = (uint32_t)((u32OutLo>>16)&0xFFFF);                                         \
    u32Carry += (u32Tmp&0xFFFF);                                                        \
    u32OutLo += (u32Tmp << 16) ;                                                        \
    u32OutHi += (u32Tmp >> 16);                                                         \
    u32Tmp = ((u32In1Tmp >> 16) & 0xFFFF) * (u32In2Tmp & 0xFFFF);                       \
    u32Carry += (u32Tmp)&0xFFFF;                                                        \
    u32Carry>>=16;                                                                      \
    u32OutLo += (u32Tmp << 16);                                                         \
    u32OutHi += (u32Tmp >> 16);                                                         \
    u32OutHi += u32Carry;                                                               \
} while (0)

/* Macro to make an addition of 2 64 bit values:
 * result = (u32OutHi & u32OutLo) + (u32InHi & u32InLo)
 * u32OutHi = result[63:32]
 * u32OutLo = result[31:0]
 */
#define HCIDISP_ADD_64(u32InLo, u32InHi, u32OutLo, u32OutHi)                            \
do {                                                                                    \
    (u32OutLo) += (u32InLo);                                                            \
    if ((u32OutLo) < (u32InLo)) (u32OutHi)++;                                           \
    (u32OutHi) += (u32InHi);                                                            \
} while (0)

/* EPOCH in microseconds since 01/01/0000 : 0x00dcddb3.0f2f8000 */
#define BTSNOOP_EPOCH_HI 0x00dcddb3U
#define BTSNOOP_EPOCH_LO 0x0f2f8000U

/*******************************************************************************
 **
 ** Function         tv_to_btsnoop_ts
 **
 ** Description      This function generate a BT Snoop timestamp.
 **
 ** Returns          void
 **
 ** NOTE
 ** The return value is 64 bit as 2 32 bit variables out_lo and * out_hi.
 ** A BT Snoop timestamp is the number of microseconds since 01/01/0000.
 ** The timeval structure contains the number of microseconds since EPOCH
 ** (01/01/1970) encoded as: tv.tv_sec, number of seconds since EPOCH and
 ** tv_usec, number of microseconds in current second
 **
 ** Therefore the algorithm is:
 **  result = tv.tv_sec * 1000000
 **  result += tv.tv_usec
 **  result += EPOCH_OFFSET
 *******************************************************************************/
static void tv_to_btsnoop_ts(uint32_t *out_lo, uint32_t *out_hi, struct timeval *tv)
{
    /* multiply the seconds by 1000000 */
    HCIDISP_MULT_64(tv->tv_sec, 0xf4240, *out_lo, *out_hi);

    /* add the microseconds */
    HCIDISP_ADD_64((uint32_t)tv->tv_usec, 0, *out_lo, *out_hi);

    /* add the epoch */
    HCIDISP_ADD_64(BTSNOOP_EPOCH_LO, BTSNOOP_EPOCH_HI, *out_lo, *out_hi);
}

/*******************************************************************************
 **
 ** Function         l_to_be
 **
 ** Description      Function to convert a 32 bit value into big endian format
 **
 ** Returns          32 bit value in big endian format
*******************************************************************************/
static uint32_t l_to_be(uint32_t x)
{
    #if __BIG_ENDIAN != TRUE
    x = (x >> 24) |
        ((x >> 8) & 0xFF00) |
        ((x << 8) & 0xFF0000) |
        (x << 24);
    #endif
    return x;
}

/*******************************************************************************
 **
 ** Function         btsnoop_is_open
 **
 ** Description      Function to check if BTSNOOP is open
 **
 ** Returns          1 if open otherwise 0
*******************************************************************************/
int btsnoop_is_open(void)
{
#if defined(BTSNOOPDISP_INCLUDED) && (BTSNOOPDISP_INCLUDED == TRUE)
    SNOOPDBG("btsnoop_is_open: snoop fd = %d\n", hci_btsnoop_fd);

    if (hci_btsnoop_fd != -1)
    {
        return 1;
    }
    return 0;
#else
    return 2;  /* Snoop not available  */
#endif
}

/*******************************************************************************
 **
 ** Function         btsnoop_log_open
 **
 ** Description      Function to open the BTSNOOP file
 **
 ** Returns          None
*******************************************************************************/
static int btsnoop_log_open(char *btsnoop_logfile)
{
#if defined(BTSNOOPDISP_INCLUDED) && (BTSNOOPDISP_INCLUDED == TRUE)
    hci_btsnoop_fd = -1;

    SNOOPDBG("btsnoop_log_open: snoop log file = %s\n", btsnoop_logfile);

    /* write the BT snoop header */
    if ((btsnoop_logfile != NULL) && (strlen(btsnoop_logfile) != 0))
    {
        hci_btsnoop_fd = open(btsnoop_logfile, \
                              O_WRONLY|O_CREAT|O_TRUNC, \
                              S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
        if (hci_btsnoop_fd == -1)
        {
            perror("open");
            SNOOPDBG("btsnoop_log_open: Unable to open snoop log file\n");
            hci_btsnoop_fd = -1;
            return 0;
        }
        write(hci_btsnoop_fd, "btsnoop\0\0\0\0\1\0\0\x3\xea", 16);
        return 1;
    }
#endif
    return 2;  /* Snoop not available  */
}

/*******************************************************************************
 **
 ** Function         btsnoop_log_close
 **
 ** Description      Function to close the BTSNOOP file
 **
 ** Returns          None
*******************************************************************************/
static int btsnoop_log_close(void)
{
#if defined(BTSNOOPDISP_INCLUDED) && (BTSNOOPDISP_INCLUDED == TRUE)
    /* write the BT snoop header */
    if (hci_btsnoop_fd != -1)
    {
        SNOOPDBG("btsnoop_log_close: Closing snoop log file\n");
        close(hci_btsnoop_fd);
        hci_btsnoop_fd = -1;
        return 1;
    }
    return 0;
#else
    return 2;  /* Snoop not available  */
#endif
}

/*******************************************************************************
 **
 ** Function         btsnoop_hci_cmd
 **
 ** Description      Function to add a command in the BTSNOOP file
 **
 ** Returns          None
*******************************************************************************/
void btsnoop_hci_cmd(uint8_t *p)
{
    SNOOPDBG("btsnoop_hci_cmd: fd = %d", hci_btsnoop_fd);

    if (hci_btsnoop_fd != -1)
    {
        uint32_t value, value_hi;
        struct timeval tv;

        /* since these display functions are called from different contexts */
        utils_lock();

        /* store the length in both original and included fields */
        value = l_to_be(p[2] + 4);
        write(hci_btsnoop_fd, &value, 4);
        write(hci_btsnoop_fd, &value, 4);
        /* flags: command sent from the host */
        value = l_to_be(2);
        write(hci_btsnoop_fd, &value, 4);
        /* drops: none */
        value = 0;
        write(hci_btsnoop_fd, &value, 4);
        /* time */
        gettimeofday(&tv, NULL);
        tv_to_btsnoop_ts(&value, &value_hi, &tv);
        value_hi = l_to_be(value_hi);
        value = l_to_be(value);
        write(hci_btsnoop_fd, &value_hi, 4);
        write(hci_btsnoop_fd, &value, 4);
        /* data */
        write(hci_btsnoop_fd, "\x1", 1);
        write(hci_btsnoop_fd, p, p[2] + 3);

        /* since these display functions are called from different contexts */
        utils_unlock();
    }
}

/*******************************************************************************
 **
 ** Function         btsnoop_hci_evt
 **
 ** Description      Function to add a event in the BTSNOOP file
 **
 ** Returns          None
*******************************************************************************/
void btsnoop_hci_evt(uint8_t *p)
{
    SNOOPDBG("btsnoop_hci_evt: fd = %d", hci_btsnoop_fd);

    if (hci_btsnoop_fd != -1)
    {
        uint32_t value, value_hi;
        struct timeval tv;

        /* since these display functions are called from different contexts */
        utils_lock();

        /* store the length in both original and included fields */
        value = l_to_be(p[1] + 3);
        write(hci_btsnoop_fd, &value, 4);
        write(hci_btsnoop_fd, &value, 4);
        /* flags: event received in the host */
        value = l_to_be(3);
        write(hci_btsnoop_fd, &value, 4);
        /* drops: none */
        value = 0;
        write(hci_btsnoop_fd, &value, 4);
        /* time */
        gettimeofday(&tv, NULL);
        tv_to_btsnoop_ts(&value, &value_hi, &tv);
        value_hi = l_to_be(value_hi);
        value = l_to_be(value);
        write(hci_btsnoop_fd, &value_hi, 4);
        write(hci_btsnoop_fd, &value, 4);
        /* data */
        write(hci_btsnoop_fd, "\x4", 1);
        write(hci_btsnoop_fd, p, p[1] + 2);

        /* since these display functions are called from different contexts */
        utils_unlock();
    }
}

/*******************************************************************************
 **
 ** Function         btsnoop_sco_data
 **
 ** Description      Function to add a SCO data packet in the BTSNOOP file
 **
 ** Returns          None
*******************************************************************************/
void btsnoop_sco_data(uint8_t *p, uint8_t is_rcvd)
{
    SNOOPDBG("btsnoop_sco_data: fd = %d", hci_btsnoop_fd);

    if (hci_btsnoop_fd != -1)
    {
        uint32_t value, value_hi;
        struct timeval tv;

        /* since these display functions are called from different contexts */
        utils_lock();

        /* store the length in both original and included fields */
        value = l_to_be(p[2] + 4);
        write(hci_btsnoop_fd, &value, 4);
        write(hci_btsnoop_fd, &value, 4);
        /* flags: data can be sent or received */
        value = l_to_be(is_rcvd?1:0);
        write(hci_btsnoop_fd, &value, 4);
        /* drops: none */
        value = 0;
        write(hci_btsnoop_fd, &value, 4);
        /* time */
        gettimeofday(&tv, NULL);
        tv_to_btsnoop_ts(&value, &value_hi, &tv);
        value_hi = l_to_be(value_hi);
        value = l_to_be(value);
        write(hci_btsnoop_fd, &value_hi, 4);
        write(hci_btsnoop_fd, &value, 4);
        /* data */
        write(hci_btsnoop_fd, "\x3", 1);
        write(hci_btsnoop_fd, p, p[2] + 3);

        /* since these display functions are called from different contexts */
        utils_unlock();
    }
}

/*******************************************************************************
 **
 ** Function         btsnoop_acl_data
 **
 ** Description      Function to add an ACL data packet in the BTSNOOP file
 **
 ** Returns          None
*******************************************************************************/
void btsnoop_acl_data(uint8_t *p, uint8_t is_rcvd)
{
    SNOOPDBG("btsnoop_acl_data: fd = %d", hci_btsnoop_fd);
    if (hci_btsnoop_fd != -1)
    {
        uint32_t value, value_hi;
        struct timeval tv;

        /* since these display functions are called from different contexts */
        utils_lock();

        /* store the length in both original and included fields */
        value = l_to_be((p[3]<<8) + p[2] + 5);
        write(hci_btsnoop_fd, &value, 4);
        write(hci_btsnoop_fd, &value, 4);
        /* flags: data can be sent or received */
        value = l_to_be(is_rcvd?1:0);
        write(hci_btsnoop_fd, &value, 4);
        /* drops: none */
        value = 0;
        write(hci_btsnoop_fd, &value, 4);
        /* time */
        gettimeofday(&tv, NULL);
        tv_to_btsnoop_ts(&value, &value_hi, &tv);
        value_hi = l_to_be(value_hi);
        value = l_to_be(value);
        write(hci_btsnoop_fd, &value_hi, 4);
        write(hci_btsnoop_fd, &value, 4);
        /* data */
        write(hci_btsnoop_fd, "\x2", 1);
        write(hci_btsnoop_fd, p, (p[3]<<8) + p[2] + 4);

        /* since these display functions are called from different contexts */
        utils_unlock();
    }
}


/********************************************************************************
 ** API allow external realtime parsing of output using e.g hcidump
 *********************************************************************************/

#define EXT_PARSER_PORT 4330

static pthread_t thread_id;
static int s_listen = -1;
static int ext_parser_fd = -1;

static void ext_parser_detached(void);

static int ext_parser_accept(int port)
{
    socklen_t           clilen;
    struct sockaddr_in  cliaddr, servaddr;
    int s, srvlen;
    int n = 1;
    int size_n;
    int result = 0;

    ALOGD("waiting for connection on port %d", port);

    s_listen = socket(AF_INET, SOCK_STREAM, 0);

    if (s_listen < 0)
    {
        ALOGE("listener not created: listen fd %d", s_listen);
        return -1;
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(port);

    srvlen = sizeof(servaddr);

    /* allow reuse of sock addr upon bind */
    result = setsockopt(s_listen, SOL_SOCKET, SO_REUSEADDR, &n, sizeof(n));

    if (result<0)
    {
        perror("setsockopt");
    }

    result = bind(s_listen, (struct sockaddr *) &servaddr, srvlen);

    if (result < 0)
        perror("bind");

    result = listen(s_listen, 1);

    if (result < 0)
        perror("listen");

    clilen = sizeof(struct sockaddr_in);

    s = accept(s_listen, (struct sockaddr *) &cliaddr, &clilen);

    if (s < 0)
{
        perror("accept");
        return -1;
    }

    ALOGD("connected (%d)", s);

    return s;
}

static int send_ext_parser(char *p, int len)
{
    int n;

    /* check if io socket is connected */
    if (ext_parser_fd == -1)
        return 0;

    SNOOPDBG("write %d to snoop socket\n", len);

    n = write(ext_parser_fd, p, len);

    if (n<=0)
    {
        ext_parser_detached();
    }

    return n;
}

static void ext_parser_detached(void)
{
    ALOGD("ext parser detached");

    if (ext_parser_fd>0)
        close(ext_parser_fd);

    if (s_listen > 0)
        close(s_listen);

    ext_parser_fd = -1;
    s_listen = -1;
}

static void interruptFn (int sig)
{
    ALOGD("interruptFn");
    pthread_exit(0);
}

static void ext_parser_thread(void* param)
{
    int fd;
    int sig = SIGUSR2;
    sigset_t sigSet;
    sigemptyset (&sigSet);
    sigaddset (&sigSet, sig);

    ALOGD("ext_parser_thread");

    prctl(PR_SET_NAME, (unsigned long)"BtsnoopExtParser", 0, 0, 0);

    pthread_sigmask (SIG_UNBLOCK, &sigSet, NULL);

    struct sigaction act;
    act.sa_handler = interruptFn;
    sigaction (sig, &act, NULL );

    do
    {
        fd = ext_parser_accept(EXT_PARSER_PORT);

        ext_parser_fd = fd;

        ALOGD("ext parser attached on fd %d\n", ext_parser_fd);
    } while (1);
}

void btsnoop_stop_listener(void)
{
    ALOGD("btsnoop_init");
    ext_parser_detached();
}

void btsnoop_init(void)
{
#if defined(BTSNOOP_EXT_PARSER_INCLUDED) && (BTSNOOP_EXT_PARSER_INCLUDED == TRUE)
    ALOGD("btsnoop_init");

    /* always setup ext listener port */
    if (pthread_create(&thread_id, NULL,
                       (void*)ext_parser_thread,NULL)!=0)
      perror("pthread_create");
#endif
}

void btsnoop_open(char *p_path)
{
#if defined(BTSNOOPDISP_INCLUDED) && (BTSNOOPDISP_INCLUDED == TRUE)
    ALOGD("btsnoop_open");
    btsnoop_log_open(p_path);
#endif // BTSNOOPDISP_INCLUDED
}

void btsnoop_close(void)
{
#if defined(BTSNOOPDISP_INCLUDED) && (BTSNOOPDISP_INCLUDED == TRUE)
    ALOGD("btsnoop_close");
    btsnoop_log_close();
#endif
}

void btsnoop_cleanup (void)
{
#if defined(BTSNOOP_EXT_PARSER_INCLUDED) && (BTSNOOP_EXT_PARSER_INCLUDED == TRUE)
    ALOGD("btsnoop_cleanup");
    pthread_kill(thread_id, SIGUSR2);
    pthread_join(thread_id, NULL);
    ext_parser_detached();
#endif
}


#define HCIT_TYPE_COMMAND   1
#define HCIT_TYPE_ACL_DATA  2
#define HCIT_TYPE_SCO_DATA  3
#define HCIT_TYPE_EVENT     4

void btsnoop_capture(HC_BT_HDR *p_buf, uint8_t is_rcvd)
{
    uint8_t *p = (uint8_t *)(p_buf + 1) + p_buf->offset;

    SNOOPDBG("btsnoop_capture: fd = %d, type %x, rcvd %d, ext %d", \
             hci_btsnoop_fd, p_buf->event, is_rcvd, ext_parser_fd);

#if defined(BTSNOOP_EXT_PARSER_INCLUDED) && (BTSNOOP_EXT_PARSER_INCLUDED == TRUE)
    if (ext_parser_fd > 0)
    {
        uint8_t tmp = *p;

        /* borrow one byte for H4 packet type indicator */
        p--;

        switch (p_buf->event & MSG_EVT_MASK)
        {
              case MSG_HC_TO_STACK_HCI_EVT:
                  *p = HCIT_TYPE_EVENT;
                  break;
              case MSG_HC_TO_STACK_HCI_ACL:
              case MSG_STACK_TO_HC_HCI_ACL:
                  *p = HCIT_TYPE_ACL_DATA;
                  break;
              case MSG_HC_TO_STACK_HCI_SCO:
              case MSG_STACK_TO_HC_HCI_SCO:
                  *p = HCIT_TYPE_SCO_DATA;
                  break;
              case MSG_STACK_TO_HC_HCI_CMD:
                  *p = HCIT_TYPE_COMMAND;
                  break;
        }

        send_ext_parser((char*)p, p_buf->len+1);
        *(++p) = tmp;
        return;
    }
#endif

#if defined(BTSNOOPDISP_INCLUDED) && (BTSNOOPDISP_INCLUDED == TRUE)
    if (hci_btsnoop_fd == -1)
        return;

    switch (p_buf->event & MSG_EVT_MASK)
    {
        case MSG_HC_TO_STACK_HCI_EVT:
            SNOOPDBG("TYPE : EVT");
            btsnoop_hci_evt(p);
            break;
        case MSG_HC_TO_STACK_HCI_ACL:
        case MSG_STACK_TO_HC_HCI_ACL:
            SNOOPDBG("TYPE : ACL");
            btsnoop_acl_data(p, is_rcvd);
            break;
        case MSG_HC_TO_STACK_HCI_SCO:
        case MSG_STACK_TO_HC_HCI_SCO:
            SNOOPDBG("TYPE : SCO");
            btsnoop_sco_data(p, is_rcvd);
            break;
        case MSG_STACK_TO_HC_HCI_CMD:
            SNOOPDBG("TYPE : CMD");
            btsnoop_hci_cmd(p);
            break;
    }
#endif // BTSNOOPDISP_INCLUDED
}


