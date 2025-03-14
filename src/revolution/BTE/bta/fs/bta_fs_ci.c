/******************************************************************************
 *
 *  Copyright (C) 2003-2012 Broadcom Corporation
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
 *
 *  This is the implementation file for the file system call-in functions.
 *
 ******************************************************************************/
#include <string.h>

#include "bta_api.h"
#include "bta_sys.h"
#include "bta_fs_ci.h"
#include "gki.h"
#include "bd.h"

/*******************************************************************************
**
** Function         bta_fs_ci_write
**
** Description      This function sends an event to IO indicating the phone
**                  has written the number of bytes specified in the call-out
**                  function, bta_fs_co_write(), and is ready for more data.
**                  This function is used to control the TX data flow.
**                  Note: The data buffer is released by the stack after
**                        calling this function.
**
** Parameters       fd - file descriptor passed to the stack in the
**                       bta_fs_ci_open call-in function.
**                  status - BTA_FS_CO_OK or BTA_FS_CO_FAIL
**
** Returns          void
**
*******************************************************************************/
void bta_fs_ci_write(int fd, tBTA_FS_CO_STATUS status, UINT16 evt)
{
    tBTA_FS_CI_WRITE_EVT  *p_evt;

    if ((p_evt = (tBTA_FS_CI_WRITE_EVT *) GKI_getbuf(sizeof(tBTA_FS_CI_WRITE_EVT))) != NULL)
    {
        p_evt->hdr.event = evt;
        p_evt->fd = fd;
        p_evt->status = status;

        bta_sys_sendmsg(p_evt);
    }
}

/*******************************************************************************
**
** Function         bta_fs_ci_read
**
** Description      This function sends an event to BTA indicating the phone has
**                  read in the requested amount of data specified in the
**                  bta_fs_co_read() call-out function.  It should only be called
**                  when the requested number of bytes has been read in, or after
**                  the end of the file has been detected.
**
** Parameters       fd - file descriptor passed to the stack in the
**                       bta_fs_ci_open call-in function.
**                  num_bytes_read - number of bytes read into the buffer
**                      specified in the read callout-function.
**                  status - BTA_FS_CO_OK if full buffer of data,
**                           BTA_FS_CO_EOF if the end of file has been reached,
**                           BTA_FS_CO_FAIL if an error has occurred.
**
** Returns          void
**
*******************************************************************************/
void bta_fs_ci_read(int fd, UINT16 num_bytes_read, tBTA_FS_CO_STATUS status, UINT16 evt)
{
    tBTA_FS_CI_READ_EVT  *p_evt;

    if ((p_evt = (tBTA_FS_CI_READ_EVT *) GKI_getbuf(sizeof(tBTA_FS_CI_READ_EVT))) != NULL)
    {
        p_evt->hdr.event = evt;
        p_evt->fd        = fd;
        p_evt->status    = status;
        p_evt->num_read  = num_bytes_read;

        bta_sys_sendmsg(p_evt);
    }
}

/*******************************************************************************
**
** Function         bta_fs_ci_open
**
** Description      This function sends an event to BTA indicating the phone has
**                  finished opening a file for reading or writing.
**
** Parameters       fd - file descriptor passed to the stack in the
**                       bta_fs_ci_open call-in function.
**                  status - BTA_FS_CO_OK if file was opened in mode specified
**                                          in the call-out function.
**                           BTA_FS_CO_EACCES if the file exists, but contains
**                                          the wrong access permissions.
**                           BTA_FS_CO_FAIL if any other error has occurred.
**                  file_size - The total size of the file
**                  evt - Used Internally by BTA -> MUST be same value passed
**                       in call-out function.
**
** Returns          void
**
*******************************************************************************/
void bta_fs_ci_open(int fd, tBTA_FS_CO_STATUS status, UINT32 file_size, UINT16 evt)
{
    tBTA_FS_CI_OPEN_EVT  *p_evt;

    if ((p_evt = (tBTA_FS_CI_OPEN_EVT *) GKI_getbuf(sizeof(tBTA_FS_CI_OPEN_EVT))) != NULL)
    {
        p_evt->hdr.event = evt;
        p_evt->fd        = fd;
        p_evt->status    = status;
        p_evt->file_size = file_size;
        p_evt->p_file    = NULL;

        bta_sys_sendmsg(p_evt);
    }
}

/*******************************************************************************
**
** Function         bta_fs_ci_direntry
**
** Description      This function is called in response to the
**                  bta_fs_co_getdirentry call-out function.
**
** Parameters       status - BTA_FS_CO_OK if p_entry points to a valid entry.
**                           BTA_FS_CO_EODIR if no more entries (p_entry is ignored).
**                           BTA_FS_CO_FAIL if any errors have occurred.
**
** Returns          void
**
*******************************************************************************/
void bta_fs_ci_direntry(tBTA_FS_CO_STATUS status, UINT16 evt)
{
    tBTA_FS_CI_GETDIR_EVT  *p_evt;

    if ((p_evt = (tBTA_FS_CI_GETDIR_EVT *)GKI_getbuf(sizeof(tBTA_FS_CI_GETDIR_EVT))) != NULL)
    {
        p_evt->hdr.event = evt;
        p_evt->status = status;
        bta_sys_sendmsg(p_evt);
    }
}

/*******************************************************************************
**
** Function         bta_fs_ci_resume
**
** Description      This function is called in response to the
**                  bta_fs_co_resume call-out function.
**
** Parameters       p_sess_info - the stored session ID and related information.
**                  timeout - the timeout for this suspended session.
**                  ssn     - the stored session sequence number.
**                  info    - the stored BTA specific information (like last active operation).
**                  status  - BTA_FS_CO_OK if p_entry points to a valid entry.
**                            BTA_FS_CO_FAIL if any errors have occurred.
**                  evt - Used Internally by BTA -> MUST be same value passed
**                       in call-out function.
**
** Returns          void
**
*******************************************************************************/
void bta_fs_ci_resume (BD_ADDR_PTR p_addr, UINT8 *p_sess_info,
                       UINT32 timeout, UINT32 offset, UINT8 ssn, UINT8 info,
                       tBTA_FS_CO_STATUS status, UINT16 evt)
{
    tBTA_FS_CI_RESUME_EVT  *p_evt;
    UINT16  size = sizeof(tBTA_FS_CI_RESUME_EVT) + sizeof(BD_ADDR);

    if ((p_evt = (tBTA_FS_CI_RESUME_EVT *)GKI_getbuf(size)) != NULL)
    {
        p_evt->p_addr       = NULL;
        if (p_addr != NULL)
        {
            p_evt->p_addr   = (BD_ADDR_PTR)(p_evt + 1);
            bdcpy(p_evt->p_addr, p_addr);
        }
        p_evt->hdr.event    = evt;
        p_evt->p_sess_info  = p_sess_info;
        p_evt->timeout      = timeout;
        p_evt->offset       = offset;
        p_evt->ssn          = ssn;
        p_evt->info         = info;
        p_evt->status       = status;
        bta_sys_sendmsg(p_evt);
    }
}

/*******************************************************************************
**
** Function         bta_fs_ci_action
**
** Description      This function is called in response to one of the action
**                  call-out functions: bta_fs_co_copy, bta_fs_co_rename or
**                  bta_fs_co_set_perms.
**
** Parameters       status  - BTA_FS_CO_OK if the action is succession.
**                            BTA_FS_CO_FAIL if any errors have occurred.
**                  evt - Used Internally by BTA -> MUST be same value passed
**                       in call-out function.
**
** Returns          void
**
*******************************************************************************/
void bta_fs_ci_action(tBTA_FS_CO_STATUS status, UINT16 evt)
{
    tBTA_FS_CI_ACTION_EVT  *p_evt;

    if ((p_evt = (tBTA_FS_CI_ACTION_EVT *) GKI_getbuf(sizeof(tBTA_FS_CI_ACTION_EVT))) != NULL)
    {
        p_evt->hdr.event = evt;
        p_evt->status    = status;

        bta_sys_sendmsg(p_evt);
    }
}

/*******************************************************************************
**
** Function         bta_fs_ci_resume_op
**
** Description      This function sends an event to BTA indicating the phone has
**                  finished opening a file for reading or writing on resume.
**
** Parameters       fd - file descriptor passed to the stack in the
**                       bta_fs_ci_open call-in function.
**                  status - BTA_FS_CO_OK if file was opened in mode specified
**                                          in the call-out function.
**                           BTA_FS_CO_EACCES if the file exists, but contains
**                                          the wrong access permissions.
**                           BTA_FS_CO_FAIL if any other error has occurred.
**                  p_file - The file name associated with fd
**                  file_size - The total size of the file
**                  evt - Used Internally by BTA -> MUST be same value passed
**                       in call-out function.
**
** Returns          void
**
*******************************************************************************/
void bta_fs_ci_resume_op(int fd, tBTA_FS_CO_STATUS status, const char *p_file,
                         UINT32 file_size, UINT16 evt)
{
    tBTA_FS_CI_OPEN_EVT  *p_evt;
    UINT16  file_len = strlen(p_file) + 1;
    UINT16  size = sizeof(tBTA_FS_CI_OPEN_EVT) + file_len;
    char *p;

    if ((p_evt = (tBTA_FS_CI_OPEN_EVT *) GKI_getbuf(size)) != NULL)
    {
        p_evt->hdr.event = evt;
        p_evt->fd        = fd;
        p_evt->status    = status;
        p_evt->file_size = file_size;
        p   = (char *)(p_evt + 1);
        BCM_STRNCPY_S (p, file_len, p_file, file_len-1);
        p[file_len] = '\0';
        p_evt->p_file    = (const char *)p;

        bta_sys_sendmsg(p_evt);
    }
}
