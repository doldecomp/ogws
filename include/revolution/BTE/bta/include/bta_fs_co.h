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
 *  This is the interface file for the synchronization server call-out
 *  functions.
 *
 ******************************************************************************/
#ifndef BTA_FS_CO_H
#define BTA_FS_CO_H

#include <time.h>

#include "bta_api.h"
#include "goep_fs.h"
#include "obx_api.h"

/*****************************************************************************
**  Constants and Data Types
*****************************************************************************/

#ifndef BTA_FS_CO_MAX_SSN_ENTRIES
#define BTA_FS_CO_MAX_SSN_ENTRIES   10
#endif

/* Maximum path length supported by FS_CO */
#ifndef BTA_FS_CO_PATH_LEN
#define BTA_FS_CO_PATH_LEN          294
#endif

#ifndef BTA_FS_CO_TEST_ROOT
#define BTA_FS_CO_TEST_ROOT         "test_files"
#endif

#define BTA_FS_CO_TEST_TYPE_NONE    0
#define BTA_FS_CO_TEST_TYPE_REJECT  1
#define BTA_FS_CO_TEST_TYPE_SUSPEND 2

#ifndef BTA_FS_CO_TEST_AB_END
#define BTA_FS_CO_TEST_AB_END   BTA_FS_CO_TEST_TYPE_NONE
#endif

/**************************
**  Common Definitions
***************************/

/* Status codes returned by call-out functions, or in call-in functions as status */
#define BTA_FS_CO_OK            GOEP_OK
#define BTA_FS_CO_FAIL          GOEP_FAIL   /* Used to pass all other errors */
#define BTA_FS_CO_EACCES        GOEP_EACCES
#define BTA_FS_CO_ENOTEMPTY     GOEP_ENOTEMPTY
#define BTA_FS_CO_EOF           GOEP_EOF
#define BTA_FS_CO_EODIR         GOEP_EODIR
#define BTA_FS_CO_ENOSPACE      GOEP_ENOSPACE/* Returned in bta_fs_ci_open if no room */
#define BTA_FS_CO_EIS_DIR       GOEP_EIS_DIR
#define BTA_FS_CO_RESUME        GOEP_RESUME /* used in ci_open, on resume */
#define BTA_FS_CO_NONE          GOEP_NONE /* used in ci_open, on resume (no file to resume) */

typedef UINT16 tBTA_FS_CO_STATUS;

/* the index to the permission flags */
#define BTA_FS_PERM_USER    0
#define BTA_FS_PERM_GROUP   1
#define BTA_FS_PERM_OTHER   2
/* max number of the permission flags */
#define BTA_FS_PERM_SIZE    3

/* Flags passed to the open function (bta_fs_co_open)
**      Values are OR'd together. (First 3 are
**      mutually exclusive.
*/
#define BTA_FS_O_RDONLY         GOEP_O_RDONLY
#define BTA_FS_O_WRONLY         GOEP_O_WRONLY
#define BTA_FS_O_RDWR           GOEP_O_RDWR

#define BTA_FS_O_CREAT          GOEP_O_CREAT
#define BTA_FS_O_EXCL           GOEP_O_EXCL
#define BTA_FS_O_TRUNC          GOEP_O_TRUNC

#define BTA_FS_O_MODE_MASK(x)      (((UINT16)(x)) & 0x0003)

/* Origin for the bta_fs_co_seek function  */
#define BTA_FS_SEEK_SET         GOEP_SEEK_SET
#define BTA_FS_SEEK_CUR         GOEP_SEEK_CUR
#define BTA_FS_SEEK_END         GOEP_SEEK_END

/* mode field in bta_fs_co_access callout */
#define BTA_FS_ACC_EXIST        GOEP_ACC_EXIST
#define BTA_FS_ACC_READ         GOEP_ACC_READ
#define BTA_FS_ACC_RDWR         GOEP_ACC_RDWR

#define BTA_FS_LEN_UNKNOWN      GOEP_LEN_UNKNOWN
#define BTA_FS_INVALID_FD       GOEP_INVALID_FD
#define BTA_FS_INVALID_APP_ID   (0xFF)  /* this app_id is reserved */

/* mode field in tBTA_FS_DIRENTRY (OR'd together) */
#define BTA_FS_A_RDONLY         GOEP_A_RDONLY
#define BTA_FS_A_DIR            GOEP_A_DIR      /* Entry is a sub directory */

#define BTA_FS_CTIME_LEN        GOEP_CTIME_LEN  /* Creation time "yyyymmddTHHMMSSZ" */

/* Return structure type for a directory entry */
typedef struct
{
    UINT32  refdata;            /* holder for OS specific data used to get next entry */
    UINT32  filesize;
    char    crtime[BTA_FS_CTIME_LEN]; /* "yyyymmddTHHMMSSZ", or "" if none */
    char    *p_name;            /* Contains the addr of memory to copy name into */
    UINT8   mode;               /* BTA_FS_A_RDONLY and/or BTA_FS_A_DIR */
} tBTA_FS_DIRENTRY;

/* session state */
enum
{
    BTA_FS_CO_SESS_ST_NONE,
    BTA_FS_CO_SESS_ST_ACTIVE,
    BTA_FS_CO_SESS_ST_SUSPEND,
    BTA_FS_CO_SESS_ST_RESUMING
};
typedef UINT8   tBTA_FS_CO_SESS_ST;



/* a data type to keep an array of ssn/file offset - the info can be saved to NV */
typedef struct
{
    char        path[BTA_FS_CO_PATH_LEN + 1];   /* the "current path". path[0]==0-> root */
    char        file[BTA_FS_CO_PATH_LEN + 1];   /* file[0] !=0 on resume -> the previous suspended session had opened files */
    int         oflags;  /* the flag to open the file */
    BD_ADDR     bd_addr;
    UINT8       sess_info[OBX_SESSION_INFO_SIZE];
    UINT32      offset;         /* last file offset */
    UINT32      timeout;        /* the timeout value on suspend */
    time_t      suspend_time;   /* the time of suspend */
    UINT16      nbytes;         /* number of bytes for last read/write */
    UINT8       ssn;
    UINT8       info;           /* info for BTA on the client side */
    UINT8       app_id;
    tBTA_FS_CO_SESS_ST  sess_st;
} tBTA_FS_CO_SESSION;

/*****************************************************************************
**  Function Declarations
*****************************************************************************/
/**************************
**  Common Functions
***************************/
/*******************************************************************************
**
** Function         bta_fs_co_init
**
** Description      This function is executed as a part of the start up sequence
**                  to make sure the control block is initialized.
**
** Parameters       void.
**
** Returns          void
**
**
*******************************************************************************/
BTA_API extern void bta_fs_co_init(void);

/*******************************************************************************
**
** Function         bta_fs_co_open
**
** Description      This function is executed by BTA when a file is opened.
**                  The phone uses this function to open
**                  a file for reading or writing.
**
** Parameters       p_path  - Fully qualified path and file name.
**                  oflags  - permissions and mode (see constants above)
**                  size    - size of file to put (0 if unavailable or not applicable)
**                  evt     - event that must be passed into the call-in function.
**                  app_id  - application ID specified in the enable functions.
**                            It can be used to identify which profile is the caller
**                            of the call-out function.
**
** Returns          void
**
**                  Note: Upon completion of the request, a file descriptor (int),
**                        if successful, and an error code (tBTA_FS_CO_STATUS)
**                        are returned in the call-in function, bta_fs_ci_open().
**
*******************************************************************************/
BTA_API extern void bta_fs_co_open(const char *p_path, int oflags, UINT32 size,
                           UINT16 evt, UINT8 app_id);

/*******************************************************************************
**
** Function         bta_fs_co_session_info
**
** Description      This function is executed by BTA when a reliable session is
**                  established (p_sess_info != NULL) or ended (p_sess_info == NULL).
**
** Parameters       bd_addr     - the peer address
**                  p_sess_info - the session ID and related information.
**                  app_id  - application ID specified in the enable functions.
**                            It can be used to identify which profile is the caller
**                            of the call-out function.
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void bta_fs_co_session_info(BD_ADDR bd_addr, UINT8 *p_sess_info, UINT8 ssn,
                                           tBTA_FS_CO_SESS_ST new_st, char *p_path, UINT8 *p_info, UINT8 app_id);

/*******************************************************************************
**
** Function         bta_fs_co_resume_op
**
** Description      This function is executed by BTA when a reliable session is
**                  resumed and there was an interrupted operation.
**
** Parameters       offset  - the session ID and related information.
**                  evt     - event that must be passed into the call-in function.
**                  app_id  - application ID specified in the enable functions.
**                            It can be used to identify which profile is the caller
**                            of the call-out function.
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void bta_fs_co_resume_op(UINT32 offset, UINT16 evt, UINT8 app_id);

/*******************************************************************************
**
** Function         bta_fs_co_suspend
**
** Description      This function is executed by BTA when a reliable session is
**                  suspended.
**
** Parameters       bd_addr - the peer address
**                  ssn     - the session sequence number.
**                  info    - the BTA specific information (like last active operation).
**                  p_offset- the location to receive object offset of the suspended session
**                  app_id  - application ID specified in the enable functions.
**                            It can be used to identify which profile is the caller
**                            of the call-out function.
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void bta_fs_co_suspend(BD_ADDR bd_addr, UINT8 *p_sess_info, UINT8 ssn,
                                      UINT32 *p_timeout, UINT32 *p_offset, UINT8 info, UINT8 app_id);

/*******************************************************************************
**
** Function         bta_fs_co_resume
**
** Description      This function is executed by BTA when resuming a session.
**                  This is used to retrieve the session ID and related information
**
** Parameters       evt     - event that must be passed into the call-in function.
**                  app_id  - application ID specified in the enable functions.
**                            It can be used to identify which profile is the caller
**                            of the call-out function.
**
** Returns          void
**
**                  Note: Upon completion of the request, the related session information,
**                        if successful, and an error code (tBTA_FS_CO_STATUS)
**                        are returned in the call-in function, bta_fs_ci_resume().
**
*******************************************************************************/
BTA_API extern void bta_fs_co_resume(UINT16 evt, UINT8 app_id);

/*******************************************************************************
**
** Function         bta_fs_co_sess_ssn
**
** Description      This function is executed by BTA when resuming a session.
**                  This is used to inform call-out module if the ssn/file offset
**                  needs to be adjusted.
**
** Parameters       ssn     - the session sequence number of the first request
**                            after resume.
**                  app_id  - application ID specified in the enable functions.
**                            It can be used to identify which profile is the caller
**                            of the call-out function.
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void bta_fs_co_sess_ssn(int fd, UINT8 ssn, UINT8 app_id);

/*******************************************************************************
**
** Function         bta_fs_co_setdir
**
** Description      This function is executed by BTA when the server changes the
**                  local path
**
** Parameters       p_path  - the new path.
**                  app_id  - application ID specified in the enable functions.
**                            It can be used to identify which profile is the caller
**                            of the call-out function.
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void bta_fs_co_setdir(const char *p_path, UINT8 app_id);

/*******************************************************************************
**
** Function         bta_fs_co_close
**
** Description      This function is called by BTA when a connection to a
**                  client is closed.
**
** Parameters       fd      - file descriptor of file to close.
**                  app_id  - application ID specified in the enable functions.
**                            It can be used to identify which profile is the caller
**                            of the call-out function.
**
** Returns          (tBTA_FS_CO_STATUS) status of the call.
**                      [BTA_FS_CO_OK if successful],
**                      [BTA_FS_CO_FAIL if failed  ]
**
*******************************************************************************/
BTA_API extern tBTA_FS_CO_STATUS bta_fs_co_close(int fd, UINT8 app_id);

/*******************************************************************************
**
** Function         bta_fs_co_read
**
** Description      This function is called by BTA to read in data from the
**                  previously opened file on the phone.
**
** Parameters       fd      - file descriptor of file to read from.
**                  p_buf   - buffer to read the data into.
**                  nbytes  - number of bytes to read into the buffer.
**                  evt     - event that must be passed into the call-in function.
**                  ssn     - session sequence number. Ignored, if bta_fs_co_open
**							  was not called with BTA_FS_CO_RELIABLE.
**                  app_id  - application ID specified in the enable functions.
**                            It can be used to identify which profile is the caller
**                            of the call-out function.
**
** Returns          void
**
**                  Note: Upon completion of the request, bta_fs_ci_read() is
**                        called with the buffer of data, along with the number
**                        of bytes read into the buffer, and a status.  The
**                        call-in function should only be called when ALL requested
**                        bytes have been read, the end of file has been detected,
**                        or an error has occurred.
**
*******************************************************************************/
BTA_API extern void bta_fs_co_read(int fd, UINT8 *p_buf, UINT16 nbytes, UINT16 evt,
                           UINT8 ssn, UINT8 app_id);

/*******************************************************************************
**
** Function         bta_fs_co_write
**
** Description      This function is called by io to send file data to the
**                  phone.
**
** Parameters       fd      - file descriptor of file to write to.
**                  p_buf   - buffer to read the data from.
**                  nbytes  - number of bytes to write out to the file.
**                  evt     - event that must be passed into the call-in function.
**                  ssn     - session sequence number. Ignored, if bta_fs_co_open
**							  was not called with BTA_FS_CO_RELIABLE.
**                  app_id  - application ID specified in the enable functions.
**                            It can be used to identify which profile is the caller
**                            of the call-out function.
**
** Returns          void
**
**                  Note: Upon completion of the request, bta_fs_ci_write() is
**                        called with the file descriptor and the status.  The
**                        call-in function should only be called when ALL requested
**                        bytes have been written, or an error has been detected,
**
*******************************************************************************/
BTA_API extern void bta_fs_co_write(int fd, const UINT8 *p_buf, UINT16 nbytes, UINT16 evt,
                            UINT8 ssn, UINT8 app_id);

/*******************************************************************************
**
** Function         bta_fs_co_seek
**
** Description      This function is called by io to move the file pointer
**                  of a previously opened file to the specified location for
**                  the next read or write operation.
**
** Parameters       fd      - file descriptor of file.
**                  offset  - Number of bytes from origin.
**                  origin  - Initial position: BTA_FS_SEEK_SET, BTA_FS_SEEK_CUR,
**                            or BTA_FS_SEEK_END.
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void bta_fs_co_seek (int fd, INT32 offset, INT16 origin, UINT8 app_id);

/*******************************************************************************
**
** Function         bta_fs_co_access
**
** Description      This function is called to check the existence of a file or
**                  directory.
**
** Parameters       p_path   - (input) file or directory to access (fully qualified path).
**                  mode     - (input) [BTA_FS_ACC_EXIST, BTA_FS_ACC_READ, or BTA_FS_ACC_RDWR]
**                  p_is_dir - (output) returns TRUE if p_path specifies a directory.
**                  app_id   - (input) application ID specified in the enable functions.
**                                     It can be used to identify which profile is the caller
**                                     of the call-out function.
**
** Returns          (tBTA_FS_CO_STATUS) status of the call.
**                   [BTA_FS_CO_OK if it exists]
**                   [BTA_FS_CO_EACCES if permissions are wrong]
**                   [BTA_FS_CO_FAIL if it does not exist]
**
*******************************************************************************/
BTA_API extern tBTA_FS_CO_STATUS bta_fs_co_access(const char *p_path, int mode,
                                          BOOLEAN *p_is_dir, UINT8 app_id);

/*******************************************************************************
**
** Function         bta_fs_co_mkdir
**
** Description      This function is called to create a directory with
**                  the pathname given by path. The pathname is a null terminated
**                  string. All components of the path must already exist.
**
** Parameters       p_path   - (input) name of directory to create (fully qualified path).
**                  app_id   - (input) application ID specified in the enable functions.
**                                     It can be used to identify which profile is the caller
**                                     of the call-out function.
**
** Returns          (tBTA_FS_CO_STATUS) status of the call.
**                  [BTA_FS_CO_OK if successful]
**                  [BTA_FS_CO_FAIL if unsuccessful]
**
*******************************************************************************/
BTA_API extern tBTA_FS_CO_STATUS bta_fs_co_mkdir(const char *p_path, UINT8 app_id);

/*******************************************************************************
**
** Function         bta_fs_co_rmdir
**
** Description      This function is called to remove a directory whose
**                  name is given by path. The directory must be empty.
**
** Parameters       p_path   - (input) name of directory to remove (fully qualified path).
**                  app_id   - (input) application ID specified in the enable functions.
**                                     It can be used to identify which profile is the caller
**                                     of the call-out function.
**
** Returns          (tBTA_FS_CO_STATUS) status of the call.
**                      [BTA_FS_CO_OK if successful]
**                      [BTA_FS_CO_EACCES if read-only]
**                      [BTA_FS_CO_ENOTEMPTY if directory is not empty]
**                      [BTA_FS_CO_FAIL otherwise]
**
*******************************************************************************/
BTA_API extern tBTA_FS_CO_STATUS bta_fs_co_rmdir(const char *p_path, UINT8 app_id);

/*******************************************************************************
**
** Function         bta_fs_co_unlink
**
** Description      This function is called by to remove a file whose name
**                  is given by p_path.
**
** Parameters       p_path   - (input) name of file to remove (fully qualified path).
**                  app_id   - (input) application ID specified in the enable functions.
**                                     It can be used to identify which profile is the caller
**                                     of the call-out function.
**
** Returns          (tBTA_FS_CO_STATUS) status of the call.
**                      [BTA_FS_CO_OK if successful]
**                      [BTA_FS_CO_EACCES if read-only]
**                      [BTA_FS_CO_FAIL otherwise]
**
*******************************************************************************/
BTA_API extern tBTA_FS_CO_STATUS bta_fs_co_unlink(const char *p_path, UINT8 app_id);

/*******************************************************************************
**
** Function         bta_fs_co_getdirentry
**
** Description      This function is called to retrieve a directory entry for the
**                  specified path.  The first/next directory should be filled
**                  into the location specified by p_entry.
**
** Parameters       p_path      - directory to search (Fully qualified path)
**                  first_item  - TRUE if first search, FALSE if next search
**                                      (p_cur contains previous)
**                  p_entry (input/output) - Points to last entry data (valid when
**                                           first_item is FALSE)
**                  evt     - event that must be passed into the call-in function.
**                  app_id  - application ID specified in the enable functions.
**                            It can be used to identify which profile is the caller
**                            of the call-out function.
**
** Returns          void
**
**                  Note: Upon completion of the request, the status is passed
**                        in the bta_fs_ci_direntry() call-in function.
**                        BTA_FS_CO_OK is returned when p_entry is valid,
**                        BTA_FS_CO_EODIR is returned when no more entries [finished]
**                        BTA_FS_CO_FAIL is returned if an error occurred
**
*******************************************************************************/
BTA_API extern void bta_fs_co_getdirentry(const char *p_path, BOOLEAN first_item,
                                   tBTA_FS_DIRENTRY *p_entry, UINT16 evt,
                                   UINT8 app_id);

/*******************************************************************************
**
** Function         bta_fs_co_copy
**
** Description      This function is called to copy a file/directory whose
**                  name is given by p_src_path to p_dest_path.
**
** Parameters       p_src_path  - (input) name of file/directory to be copied (fully qualified path).
**                  p_dest_path - (input) new name of file/directory(fully qualified path).
**                  p_perms     - the permission of the new object.
**                  evt     - event that must be passed into the call-in function.
**                  app_id   - (input) application ID specified in the enable functions.
**                                     It can be used to identify which profile is the caller
**                                     of the call-out function.
**
** Returns          (tBTA_FS_CO_STATUS) status of the call.
**                      [BTA_FS_CO_OK if successful]
**                      [BTA_FS_CO_EIS_DIR if p_src_path is a folder]
**                      [BTA_FS_CO_EACCES if p_dest_path already exists or could not be created (invalid path);
**                                        or p_src_path is a directory and p_dest_path specifies a different path. ]
**                      [BTA_FS_CO_FAIL otherwise]
**
*******************************************************************************/
BTA_API extern void bta_fs_co_copy(const char *p_src_path, const char *p_dest_path, UINT8 *p_perms, UINT16 evt, UINT8 app_id);

/*******************************************************************************
**
** Function         bta_fs_co_rename
**
** Description      This function is called to move a file/directory whose
**                  name is given by p_src_path to p_dest_path.
**
** Parameters       p_src_path  - (input) name of file/directory to be moved (fully qualified path).
**                  p_dest_path - (input) new name of file/directory(fully qualified path).
**                  p_perms     - the permission of the new object.
**                  app_id   - (input) application ID specified in the enable functions.
**                                     It can be used to identify which profile is the caller
**                                     of the call-out function.
**
** Returns          (tBTA_FS_CO_STATUS) status of the call.
**                      [BTA_FS_CO_OK if successful]
**                      [BTA_FS_CO_EACCES if p_dest_path already exists or could not be created (invalid path);
**                                        or p_src_path is a directory and p_dest_path specifies a different path. ]
**                      [BTA_FS_CO_FAIL otherwise]
**
*******************************************************************************/
BTA_API extern void bta_fs_co_rename(const char *p_src_path, const char *p_dest_path, UINT8 *p_perms, UINT16 evt, UINT8 app_id);

/*******************************************************************************
**
** Function         bta_fs_co_set_perms
**
** Description      This function is called to set the permission a file/directory
**                  with name as p_src_path.
**
** Parameters       p_src_path  - (input) name of file/directory to set permission (fully qualified path).
**                  p_perms     - the permission .
**                  app_id   - (input) application ID specified in the enable functions.
**                                     It can be used to identify which profile is the caller
**                                     of the call-out function.
**
** Returns          (tBTA_FS_CO_STATUS) status of the call.
**                      [BTA_FS_CO_OK if successful]
**                      [BTA_FS_CO_EACCES if p_dest_path already exists or could not be created (invalid path);
**                                        or p_src_path is a directory and p_dest_path specifies a different path. ]
**                      [BTA_FS_CO_FAIL otherwise]
**
*******************************************************************************/
BTA_API extern void bta_fs_co_set_perms(const char *p_src_path,  UINT8 *p_perms, UINT16 evt, UINT8 app_id);

/*******************************************************************************
**
** Function         bta_fs_co_sess_fopen
**
** Description      This function is called by bta_fs_co_open to keep track of
**                  the opened file (for reliable session suspend/resume.)
**
** Parameters       p_path  - Fully qualified path and file name.
**                  oflags  - permissions and mode (see constants above)
**                  app_id  - application ID specified in the enable functions.
**                            It can be used to identify which profile is the caller
**                            of the call-out function.
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void bta_fs_co_sess_fopen(const char *p_path, int oflags, UINT8 app_id);

/*******************************************************************************
**
** Function         bta_fs_co_sess_fclose
**
** Description      This function is called by bta_fs_co_close
**
** Parameters       app_id  - application ID specified in the enable functions.
**                            It can be used to identify which profile is the caller
**                            of the call-out function.
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void bta_fs_co_sess_fclose(UINT8 app_id);

/*******************************************************************************
**
** Function         bta_fs_co_sess_offset
**
** Description      This function is called by bta_fs_co_write to keep track of
**                  the last file offset (Only the receiving side needs to keep
**                  track of the file offset)
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void bta_fs_co_sess_offset(UINT8 ssn, INT32 pos, UINT16 nbytes, UINT8 app_id);

/*******************************************************************************
**
** Function         bta_fs_co_suspended_addr
**
** Description      find the peer address of the suspended session control block
**                  for the given an app_id.
**
** Returns          the control block found.
**
*******************************************************************************/
BTA_API extern UINT8 *bta_fs_co_suspended_addr(UINT8 app_id);

/*******************************************************************************
**
** Function         bta_fs_co_num_suspended_session
**
** Description      find the number of suspended session control blocks for the
**                  given an app_id.
**
** Returns          the number of control blocks found.
**
*******************************************************************************/
BTA_API extern UINT8 bta_fs_co_num_suspended_session(UINT8 app_id);

/*******************************************************************************
**
** Function         bta_fs_co_get_active_session
**
** Description      find the active session control block for the given an app_id.
**
** Returns          the control block found.
**
*******************************************************************************/
BTA_API extern tBTA_FS_CO_SESSION *bta_fs_co_get_active_session(UINT8 app_id);

/*******************************************************************************
**
** Function         bta_fs_co_init_db
**
** Description      Initialize the session control blocks for platform.
**
** Returns          void
**
*******************************************************************************/
BTA_API extern void bta_fs_co_init_db (tBTA_FS_CO_SESSION *p_first);

/*******************************************************************************
**
** Function         bta_fs_convert_oflags
**
** Description      This function converts the open flags from BTA into MFS.
**
** Returns          BTA FS status value.
**
*******************************************************************************/
BTA_API extern int bta_fs_convert_bta_oflags(int bta_oflags);

#endif /* BTA_FS_CO_H */
