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
 *  This is the interface file for file system call-in functions.
 *
 ******************************************************************************/
#ifndef BTA_FS_CI_H
#define BTA_FS_CI_H

#include "bta_fs_co.h"

/*****************************************************************************
**  Constants and data types
*****************************************************************************/

/* Open Complete Event */
typedef struct
{
    BT_HDR            hdr;
    tBTA_FS_CO_STATUS status;
    UINT32            file_size;
    int               fd;
    const char        *p_file;
} tBTA_FS_CI_OPEN_EVT;

/* Read Ready Event */
typedef struct
{
    BT_HDR            hdr;
    tBTA_FS_CO_STATUS status;
    int               fd;
    UINT16            num_read;
} tBTA_FS_CI_READ_EVT;

/* Write Ready Event */
typedef struct
{
    BT_HDR            hdr;
    tBTA_FS_CO_STATUS status;
    int               fd;
} tBTA_FS_CI_WRITE_EVT;

/* Get Directory Entry Event */
typedef struct
{
    BT_HDR            hdr;
    tBTA_FS_CO_STATUS status;
} tBTA_FS_CI_GETDIR_EVT;

/* Resume Information Event */
typedef struct
{
    BT_HDR            hdr;
    tBTA_FS_CO_STATUS status;
    BD_ADDR_PTR       p_addr;
    UINT8             *p_sess_info;
    UINT32            timeout;
    UINT32            offset;
    UINT8             ssn;
    UINT8             info;
} tBTA_FS_CI_RESUME_EVT;

/* Action Complete Event */
typedef struct
{
    BT_HDR            hdr;
    tBTA_FS_CO_STATUS status;
} tBTA_FS_CI_ACTION_EVT;


/*****************************************************************************
**  Function Declarations
*****************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
**
** Function         bta_fs_ci_write
**
** Description      This function sends an event to BTA indicating the phone
**                  has written the number of bytes specified in the call-out
**                  function, bta_fs_co_write(), and is ready for more data.
**                  This function is used to control the TX data flow.
**                  Note: The data buffer is released by the stack aioer
**                        calling this function.
**
** Parameters       fd - file descriptor passed to the stack in the
**                       bta_fs_ci_open call-in function.
**                  status - BTA_FS_CO_OK, BTA_FS_CO_NOSPACE, or BTA_FS_CO_FAIL
**                  evt - Used Internally by BTA -> MUST be same value passed
**                       in call-out function.
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void bta_fs_ci_write(int fd, tBTA_FS_CO_STATUS status, UINT16 evt);

/*******************************************************************************
**
** Function         bta_fs_ci_read
**
** Description      This function sends an event to BTA indicating the phone has
**                  read in the requested amount of data specified in the
**                  bta_fs_co_read() call-out function.  It should only be called
**                  when the requested number of bytes has been read in, or aioer
**                  the end of the file has been detected.
**
** Parameters       fd - file descriptor passed to the stack in the
**                       bta_fs_ci_open call-in function.
**                  num_bytes_read - number of bytes read into the buffer
**                      specified in the read callout-function.
**                  status - BTA_FS_CO_OK if full buffer of data,
**                           BTA_FS_CO_EOF if the end of file has been reached,
**                           BTA_FS_CO_FAIL if an error has occurred.
**                  evt - Used Internally by BTA -> MUST be same value passed
**                       in call-out function.
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void bta_fs_ci_read(int fd, UINT16 num_bytes_read,
                                   tBTA_FS_CO_STATUS status, UINT16 evt);

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
BTA_API extern void bta_fs_ci_open(int fd, tBTA_FS_CO_STATUS status,
                                   UINT32 file_size, UINT16 evt);

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
**                  evt - Used Internally by BTA -> MUST be same value passed
**                       in call-out function.
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void bta_fs_ci_direntry(tBTA_FS_CO_STATUS status, UINT16 evt);

/*******************************************************************************
**
** Function         bta_fs_ci_resume
**
** Description      This function is called in response to the
**                  bta_fs_co_resume call-out function.
**
** Parameters       p_sess_info - the stored session ID and related information.
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
BTA_API extern void bta_fs_ci_resume (BD_ADDR_PTR p_addr, UINT8 *p_sess_info,
                                      UINT32 timeout, UINT32 offset, UINT8 ssn, UINT8 info,
                                      tBTA_FS_CO_STATUS status, UINT16 evt);

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
BTA_API extern void bta_fs_ci_action(tBTA_FS_CO_STATUS status, UINT16 evt);

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
BTA_API extern void bta_fs_ci_resume_op(int fd, tBTA_FS_CO_STATUS status, const char *p_file,
                                        UINT32 file_size, UINT16 evt);

#ifdef __cplusplus
}
#endif

#endif /* BTA_FS_CI_H */

