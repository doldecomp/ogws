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
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/statfs.h>
#include <sys/vfs.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <limits.h>
#include "gki.h"
#include "bta_fs_co.h"
#include "bta_fs_ci.h"
#include <inttypes.h>

#ifndef AID_SYSTEM
#define AID_SYSTEM        1000
#define AID_BLUETOOTH     1002
#define AID_SDCARD_RW     1015
#define AID_MISC          9998
#endif

#define FAT_FS 0x4d44
const unsigned short BT_UID= AID_BLUETOOTH;
const unsigned short BT_GID= AID_BLUETOOTH;

/* enable additional debugging traces that should be compiled out by default! */
#ifndef BTA_FS_DEBUG
#define BTA_FS_DEBUG TRUE
#define LOG_TAG  "BTA_FS_CO"
#define LOGI(format, ...)  fprintf (stdout, LOG_TAG format"\n", ## __VA_ARGS__)
#endif

#if (defined BTA_PBS_INCLUDED) && (BTA_PBS_INCLUDED == TRUE)
extern const tBTA_PBS_CFG bta_pbs_cfg;
#endif



static int del_path (const char *path)
{
    DIR *dir;
    struct dirent *de;
    int ret = 0;
    char nameBuffer[PATH_MAX] = {0};
    struct stat statBuffer;
    BTIF_TRACE_DEBUG1("in del_path for path:%s", path);
    dir = opendir(path);

    if (dir == NULL) {
        BTIF_TRACE_DEBUG1("opendir failed on path:%s", path);
        return -1;
    }

    char *filenameOffset;

    strncpy(nameBuffer, path, PATH_MAX - 1);
    strcat(nameBuffer, "/");
    int nameLen = strlen(nameBuffer);
    filenameOffset = nameBuffer + nameLen;

    for (;;) {
        de = readdir(dir);

        if (de == NULL) {
            BTIF_TRACE_DEBUG1("readdir failed for path:%s", path);
            //ret = -1;
            break;
        }

        if (0 == strcmp(de->d_name, ".") || 0 == strcmp(de->d_name, ".."))
           continue;

        if((int)strlen(de->d_name) > PATH_MAX - nameLen) {
            BTIF_TRACE_DEBUG1("d_name len:%d is too big", strlen(de->d_name));
            ret = -1;
            break;
        }

        strcpy(filenameOffset, de->d_name);

        ret = lstat (nameBuffer, &statBuffer);

        if (ret != 0) {
            BTIF_TRACE_DEBUG1("lstat failed for path:%s", nameBuffer);
            break;
        }

        if(S_ISDIR(statBuffer.st_mode)) {

            ret = del_path(nameBuffer);
            if(ret != 0)
                break;
        } else {
            ret = unlink(nameBuffer);
            if (ret != 0) {
                BTIF_TRACE_DEBUG1("unlink failed for path:%s", nameBuffer);
                break;
            }
        }
    }

    closedir(dir);
    if(ret == 0) {
        ret = rmdir(path);
        BTIF_TRACE_DEBUG2("rmdir return:%d for path:%s", ret, path);
    }

    return ret;

}

inline int getAccess(int accType, struct stat *buffer, char *p_path)
{

    struct statfs fsbuffer;
    int idType;

    if(! buffer)
	return BTA_FS_CO_FAIL;

    //idType= (buffer->st_uid== BT_UID) ? 1 : (buffer->st_uid== BT_GID) ? 2 : 3;
    if(buffer->st_uid == BT_UID)
        idType = 1;
    else if(buffer->st_gid == BT_GID ||
            buffer->st_gid == AID_SYSTEM ||
            buffer->st_gid == AID_MISC ||
            buffer->st_gid == AID_SDCARD_RW)
        idType = 2;
    else idType = 3;

    if(statfs(p_path, &fsbuffer)==0)
    {
        if(fsbuffer.f_type == FAT_FS)
	    return BTA_FS_CO_OK;
    }
    else {
        return BTA_FS_CO_FAIL;
    }

    switch(accType) {
        case 4:
	if(idType== 1) {	//Id is User Id
	   if(buffer-> st_mode & S_IRUSR)
	       return BTA_FS_CO_OK;
	}
	else if(idType==2) {   //Id is Group Id
	    if(buffer-> st_mode & S_IRGRP)
	       return BTA_FS_CO_OK;
	}
	else {			//Id is Others
	    if(buffer-> st_mode & S_IROTH)
	       return BTA_FS_CO_OK;
	}
	break;

	case 6:
	if(idType== 1) {	//Id is User Id
	   if((buffer-> st_mode & S_IRUSR) && (buffer-> st_mode & S_IWUSR))
	       return BTA_FS_CO_OK;
	}
	else if(idType==2) {   //Id is Group Id
	    if((buffer-> st_mode & S_IRGRP) && (buffer-> st_mode & S_IWGRP))
	       return BTA_FS_CO_OK;
	}
	else {			//Id is Others
	    if((buffer-> st_mode & S_IROTH) && (buffer-> st_mode & S_IWOTH))
	       return BTA_FS_CO_OK;
	}
	break;

	default:
	return BTA_FS_CO_OK;
    }
    BTIF_TRACE_DEBUG0("*************FTP- Access Failed **********");
    return BTA_FS_CO_EACCES;
}


/*****************************************************************************
**  Function Declarations
*****************************************************************************/

/*******************************************************************************
**
** Function         bta_fs_convert_oflags
**
** Description      This function converts the open flags from BTA into MFS.
**
** Returns          BTA FS status value.
**
*******************************************************************************/
int bta_fs_convert_bta_oflags(int bta_oflags)
{
    int oflags = 0; /* Initially read only */

    /* Only one of these can be set: Read Only, Read/Write, or Write Only */
    if (bta_oflags & BTA_FS_O_RDWR)
        oflags |= O_RDWR;
    else if (bta_oflags & BTA_FS_O_WRONLY)
        oflags |= O_WRONLY;

    /* OR in any other flags that are set by BTA */
    if (bta_oflags & BTA_FS_O_CREAT)
        oflags |= O_CREAT;

    if (bta_oflags & BTA_FS_O_EXCL)
        oflags |= O_EXCL;

    if (bta_oflags & BTA_FS_O_TRUNC)
        oflags |= O_TRUNC;

    return (oflags);
}



/*******************************************************************************
 **
 ** Function        btapp_fs_check_space
 **
 ** Description     determines access and if there is enough space for given files size on given path
 **
 ** Parameters      p_path  - Fully qualified path and file name.
 **                           WARNING: file name is stripped off! so it must be present!
 **                 size    - size of file to put (0 if unavailable or not applicable)
 **                 app_id  - in case application specific treatement is required (e.g opp versus ftp)
 ** Returns         0 if enough space, otherwise errno failure codes
 **
 *******************************************************************************/
static int btapp_fs_check_space( const char *p_path, const UINT32 size, const UINT8 app_id )
{

    unsigned long long max_space;
    struct statfs fs_buffer;
    int err = 0;
    char *p_dir;
    char *p_end;

    if(size==BTA_FS_LEN_UNKNOWN)
        return 0;
    /* fail silently in case of no memory. write will catch if not enough space */

    if (NULL != (p_dir = (char *) GKI_getbuf(strlen(p_path) + 1)))
    {
        strcpy(p_dir, p_path);
        if (NULL != (p_end = strrchr(p_dir, '/')))
        {

            *p_end = '\0';
            /* get fs info and calculate available space. if not enough, the fs error EFBIG is returned */

            if (0 == statfs(p_dir, &fs_buffer))
            {

                max_space = fs_buffer.f_bavail * fs_buffer.f_bsize;
#if (BTA_FS_DEBUG==TRUE)
                BTIF_TRACE_DEBUG2("btapp_fs_enough_space(file size: %d): (uint)max_size: %u", size, (UINT32)max_space);
#endif
                if (max_space < size)
                    err = EFBIG;
            }
            else
            {
                err = errno;
                BTIF_TRACE_WARNING1("btapp_fs_enough_space(): statfs() failed with err: %d", err);
            }
        }
        else
        {
            err = ENOENT;
        }
        GKI_freebuf(p_dir);
    }
    else
    {
        err = ENOMEM;
    }
    return err;

} /* btapp_fs_check_access_space() */


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

void bta_fs_co_open(const char *p_path, int oflags, UINT32 size, UINT16 evt,
                    UINT8 app_id)
{

    tBTA_FS_CO_STATUS  status;
    UINT32  file_size = 0;
    struct  stat file_stat;
    int fd = -1;
    int err = 0;

    /* Convert BTA oflags into os specific flags */
    oflags = bta_fs_convert_bta_oflags(oflags);

    /* check available space in case of write access. oflags are in OS format! */
    if (oflags & (O_RDWR|O_WRONLY))
    {
        err = btapp_fs_check_space(p_path, size, app_id);
    }

    if ( 0==err )
    {
        if ((fd = open(p_path, oflags | O_NONBLOCK, 0666)) >= 0)
        {
            if (fstat(fd, &file_stat) == 0)
            {
                file_size = file_stat.st_size;
                if (oflags & O_CREAT)
                {
                    fchown(fd, BT_UID, BT_GID);
                    BTIF_TRACE_DEBUG0("\n ******CHANGED OWNERSHIP SUCCESSFULLY**********");
                }
            }
        }

        else
        {
            err = errno;
        }
    }

    BTIF_TRACE_DEBUG4("[CO] bta_fs_co_open: handle:%d err:%d, flags:%x, app id:%d",
            fd, err, oflags, app_id);
    BTIF_TRACE_DEBUG1("file=%s", p_path);

    /* convert fs error into bta_fs err. erro is set by first call to enough space to a valid value
     * and needs only updating in case of error. This reports correct failure to remote obex! */

    switch (err)
    {

    case 0:
        status = BTA_FS_CO_OK;
        break;
    case EACCES:
        status = BTA_FS_CO_EACCES;
        break;
    case EFBIG: /* file to big for available fs space */
        status = BTA_FS_CO_ENOSPACE;
        break;
    default:
        status = BTA_FS_CO_FAIL;
        break;
    }
    bta_fs_ci_open(fd, status, file_size, evt);
}

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
tBTA_FS_CO_STATUS bta_fs_co_close(int fd, UINT8 app_id)
{
    tBTA_FS_CO_STATUS status = BTA_FS_CO_OK;
    int err;

    BTIF_TRACE_DEBUG2("[CO] bta_fs_co_close: handle:%d, app id:%d",
        fd, app_id);
    if (close (fd) < 0)
    {
        err = errno;
        status = BTA_FS_CO_FAIL;
        BTIF_TRACE_WARNING3("[CO] bta_fs_co_close: handle:%d error=%d app_id:%d", fd, err, app_id);
    }

    return (status);
}

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
void bta_fs_co_read(int fd, UINT8 *p_buf, UINT16 nbytes, UINT16 evt, UINT8 ssn, UINT8 app_id)
{
    tBTA_FS_CO_STATUS  status = BTA_FS_CO_OK;
    INT32   num_read;
    int     err;

    if ((num_read = read (fd, p_buf, nbytes)) < 0)
    {
        err = errno;
        status = BTA_FS_CO_FAIL;
        BTIF_TRACE_WARNING3("[CO] bta_fs_co_read: handle:%d error=%d app_id:%d",
                            fd, err, app_id);
    }
    else if (num_read < nbytes)
        status = BTA_FS_CO_EOF;

    bta_fs_ci_read(fd, (UINT16)num_read, status, evt);
}

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
void bta_fs_co_write(int fd, const UINT8 *p_buf, UINT16 nbytes, UINT16 evt,
                     UINT8 ssn, UINT8 app_id)
{
    tBTA_FS_CO_STATUS  status = BTA_FS_CO_OK;
    INT32   num_written;
    int     err=0;

    if ((num_written = write (fd, p_buf, nbytes)) < 0)
    {
        err = errno;
        status = BTA_FS_CO_FAIL;
    }
/*    BTIF_TRACE_DEBUG3("[CO] bta_fs_co_write: handle:%d error=%d, num_written:%d", fd, err, num_written);*/

    bta_fs_ci_write(fd, status, evt);
}

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
**                  origin  - Initial position.
**
** Returns          void
**
*******************************************************************************/
void bta_fs_co_seek (int fd, INT32 offset, INT16 origin, UINT8 app_id)
{
    lseek(fd, offset, origin);
}

/*******************************************************************************
**
** Function         bta_fs_co_access
**
** Description      This function is called to check the existence of
**                  a file or directory, and return whether or not it is a
**                  directory or length of the file.
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
tBTA_FS_CO_STATUS bta_fs_co_access(const char *p_path, int mode, BOOLEAN *p_is_dir,
                                   UINT8 app_id)
{
    int err;
    int os_mode = 0;
    tBTA_FS_CO_STATUS status = BTA_FS_CO_OK;
    struct stat buffer;

    #if (TRUE==BTA_FS_DEBUG)
    LOGI("***********CHECKING ACCESS TO = %s", p_path);
    #endif

    #if (defined BTA_PBS_INCLUDED) && (BTA_PBS_INCLUDED == TRUE)

    if (app_id == UI_PBS_ID)
    {

        *p_is_dir = TRUE;

        #if (TRUE==BTA_FS_DEBUG)
        LOGI("***********SUPPORTED REPO = %d", bta_pbs_cfg.supported_repositories);
        #endif
        //Check if SIM contact requested,  and if so if it's supported.
        //If not, return error!
        if (strstr(p_path,"SIM1") && !(bta_pbs_cfg.supported_repositories & 0x2)) {
            LOGI("***********RETURNING FAIL!");
            return BTA_FS_CO_FAIL;
        }

        #if (TRUE==BTA_FS_DEBUG)
        LOGI("***********RETURNING success!");
        #endif
        return (status);
    }
    #endif


    *p_is_dir = FALSE;

    if (mode == BTA_FS_ACC_RDWR)
        os_mode = 6;
    else if (mode == BTA_FS_ACC_READ)
        os_mode = 4;

    if (stat(p_path, &buffer) == 0)
    {
	/* Determine if the object is a file or directory */
        if (S_ISDIR(buffer.st_mode))
            *p_is_dir = TRUE;
    }
    else
    {
	BTIF_TRACE_DEBUG0("stat() failed! ");
        return BTA_FS_CO_FAIL;
    }

    status=getAccess (os_mode, &buffer, (char*)p_path);
    return (status);
}

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
tBTA_FS_CO_STATUS bta_fs_co_mkdir(const char *p_path, UINT8 app_id)
{
    int err;
    tBTA_FS_CO_STATUS status = BTA_FS_CO_OK;

    if ((mkdir (p_path, 0666)) != 0)
    {
        err = errno;
        status = BTA_FS_CO_FAIL;
        BTIF_TRACE_WARNING3("[CO] bta_fs_co_mkdir: error=%d, path [%s] app_id:%d",
                            err, p_path, app_id);
    }
    return (status);
}

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
tBTA_FS_CO_STATUS bta_fs_co_rmdir(const char *p_path, UINT8 app_id)
{
    int err, path_len;
    tBTA_FS_CO_STATUS status = BTA_FS_CO_OK;
    struct stat buffer;
    char *dirName, *tmp = NULL;

    path_len = strlen( p_path )+1;
    BTIF_TRACE_DEBUG2( "bta_fs_co_rmdir( app_id: %d ): path_len: %d", app_id, path_len );
#if (TRUE==BTA_FS_DEBUG)
    BTIF_TRACE_DEBUG1( "bta_fs_co_rmdir():path_len: %d, p_path", app_id );
    BTIF_TRACE_DEBUG0( p_path );
#endif

    /* allocate a temp buffer for path with 0 char. make sure not to crash if path is too big! */
    dirName = (char*) calloc(1, path_len+1);
    if ( NULL != dirName )
    {
        strcpy( dirName, p_path );
    }
    else
    {
        BTIF_TRACE_WARNING2( "bta_fs_co_rmdir( app_id: %d ) for path_len: %d::out of memory",
                             app_id, path_len );
        return BTA_FS_CO_FAIL;
    }

    if (NULL!= (tmp = strrchr(dirName, '/')))
    {
        *tmp = '\0';
    }
    if (stat(dirName, &buffer) == 0)
    {
        status = getAccess(6, &buffer, dirName);
    }
    else
    {
        free(dirName);
#if (TRUE==BTA_FS_DEBUG)
        BTIF_TRACE_WARNING0( "bta_fs_co_rmdir()::stat(dirName) failed" );
#endif
        return BTA_FS_CO_FAIL;
    }

    free(dirName);
    if (status != BTA_FS_CO_OK)
    {
#if (TRUE==BTA_FS_DEBUG)
        BTIF_TRACE_WARNING0( "bta_fs_co_rmdir()::getAccess(dirName) FAILED");
#endif
        return status;
    }

    if (stat(p_path, &buffer) == 0)
    {
        status = getAccess(6, &buffer, (char*)p_path);
    }
    else
    {
#if (TRUE==BTA_FS_DEBUG)
        BTIF_TRACE_WARNING0( "bta_fs_co_rmdir()::stat(p_path) FAILED");
#endif
        return BTA_FS_CO_FAIL;
    }

    if (status != BTA_FS_CO_OK)
    {
#if (TRUE==BTA_FS_DEBUG)
        BTIF_TRACE_DEBUG0( "bta_fs_co_rmdir()::getAccess(p_path) FAILED");
#endif
        return status;
    }
    //if ((rmdir (p_path)) != 0)
    if (del_path(p_path) != 0)
    {
        err = errno;
        BTIF_TRACE_WARNING1( "bta_fs_co_rmdir():rmdir/del_path FAILED with err: %d", err );
        if (err == EACCES)
            status = BTA_FS_CO_EACCES;
        else if (err == ENOTEMPTY)
            status = BTA_FS_CO_ENOTEMPTY;
        else
            status = BTA_FS_CO_FAIL;
    }
    return (status);
}

/*******************************************************************************
**
** Function         bta_fs_co_unlink
**
** Description      This function is called to remove a file whose name
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
tBTA_FS_CO_STATUS bta_fs_co_unlink(const char *p_path, UINT8 app_id)
{
    BTIF_TRACE_DEBUG0("bta_fs_co_unlink");
    int err;
    tBTA_FS_CO_STATUS status = BTA_FS_CO_OK;
    char *dirName, *tmp=NULL;
    struct stat buffer;

    if(! p_path)
        return BTA_FS_CO_FAIL;

    /* buffer needs to be NULL terminated - so add one more byte to be zero'd out */
#if 0
    dirName= (char*) calloc(1, strlen(p_path));  /* <--- this can cause problems  */
#else
    dirName= (char*) calloc(1, strlen(p_path) + 1);
#endif

    strncpy(dirName, p_path, strlen(p_path));
    if((tmp=strrchr(dirName, '/')))
    {
	    *tmp='\0';
    }
    if (stat(dirName, &buffer) == 0)
    {
        status=getAccess (6, &buffer, dirName);
        free(dirName);
    }
    else
    {
        BTIF_TRACE_DEBUG0("stat() failed! ");
        free(dirName);
        return BTA_FS_CO_FAIL;
    }

    if(status!= BTA_FS_CO_OK)
	return status;

    if ((unlink (p_path)) != 0)
    {
        err = errno;
        if (err == EACCES)
            status = BTA_FS_CO_EACCES;
        else
            status = BTA_FS_CO_FAIL;
    }
    return (status);

}

/*******************************************************************************
**
** Function         bta_fs_co_getdirentry
**
** Description      This function is called to get a directory entry for the
**                  specified p_path.  The first/next directory should be filled
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
void bta_fs_co_getdirentry(const char *p_path, BOOLEAN first_item,
                           tBTA_FS_DIRENTRY *p_entry, UINT16 evt, UINT8 app_id)
{
    tBTA_FS_CO_STATUS    co_status = BTA_FS_CO_FAIL;
    int                  status = -1;    /* '0' - success, '-1' - fail */
    struct tm           *p_tm;
    DIR *dir;
    struct dirent *dirent;
    struct stat buf;
    char fullname[500];

    BTIF_TRACE_DEBUG0("Entered bta_fs_co_getdirentry");

    /* First item is to be retrieved */
    if (first_item)
    {
        BTIF_TRACE_DEBUG1("bta_fs_co_getdirentry: path = %s", p_path);

        dir = opendir(p_path);
        if(dir == NULL)
        {
     	    BTIF_TRACE_DEBUG1("bta_fs_co_getdirentry: dir is NULL so error out with errno=%d", errno);
            co_status = BTA_FS_CO_EODIR;
            bta_fs_ci_direntry(co_status, evt);
            return;
        }

        BTIF_TRACE_DEBUG1("bta_fs_co_getdirentry: dir = %p", dir);
        if((dirent = readdir(dir)) != NULL)
        {
            p_entry->refdata = (UINT32) dir;     /* Save this for future searches */
            status = 0;
            BTIF_TRACE_DEBUG1("bta_fs_co_getdirentry: dirent = %p", dirent);
        }
        else
        {
            BTIF_TRACE_DEBUG1("bta_fs_co_getdirentry: dirent = %p", dirent);
            /* Close the search if there are no more items */
            closedir( (DIR*) p_entry->refdata);
            co_status = BTA_FS_CO_EODIR;
        }
    }
    else    /* Get the next entry based on the p_ref data from previous search */
    {
        if ((dirent = readdir((DIR*)p_entry->refdata))  == NULL)
        {
            /* Close the search if there are no more items */
            closedir( (DIR*) p_entry->refdata);
            co_status = BTA_FS_CO_EODIR;
            BTIF_TRACE_DEBUG1("bta_fs_co_getdirentry: dirent = %p", dirent);
        }
        else
        {
            BTIF_TRACE_DEBUG1("bta_fs_co_getdirentry: dirent = %p", dirent);
            status = 0;
        }
    }

    if (status == 0)
    {
        BTIF_TRACE_DEBUG0("bta_fs_co_getdirentry: status = 0");

        sprintf(fullname, "%s/%s", p_path,  dirent->d_name);

        /* Load new values into the return structure (refdata is left untouched) */
        if (stat(fullname, &buf) == 0) {
            p_entry->filesize = buf.st_size;
            p_entry->mode = 0; /* Default is normal read/write file access */

            if (S_ISDIR(buf.st_mode))
                p_entry->mode |= BTA_FS_A_DIR;
            else
                p_entry->mode |= BTA_FS_A_RDONLY;

            strcpy(p_entry->p_name, dirent->d_name);
#if 0
            fprintf(stderr, "bta_fs_co_getdirentry(): %s %9d %d\n",
                            dirent->d_name,
                            buf.st_size,
                            p_entry->mode);
#endif
            p_tm = localtime((const time_t*)&buf.st_mtime);
            if (p_tm != NULL)
            {
                sprintf(p_entry->crtime, "%04d%02d%02dT%02d%02d%02dZ",
                        p_tm->tm_year + 1900,   /* Base Year ISO 6201 */
                        p_tm->tm_mon + 1,       /* month starts at 0 */
                        p_tm->tm_mday,
                        p_tm->tm_hour,
                        p_tm->tm_min,
                        p_tm->tm_sec);
            }
            else
                p_entry->crtime[0] = '\0';  /* No valid time */
#if 0
            fprintf(stderr, "bta_fs_co_getdirentry(): %s %9d %d %s\n",
                            dirent->d_name,
                            p_entry->filesize,
                            p_entry->mode,
                            p_entry->crtime);
#endif
            co_status = BTA_FS_CO_OK;
        } else {
            BTIF_TRACE_WARNING0("stat() failed! ");
            co_status = BTA_FS_CO_EACCES;
        }
    }
    BTIF_TRACE_DEBUG0("bta_fs_co_getdirentry: calling bta_fs_ci_getdirentry");

    bta_fs_ci_direntry(co_status, evt);
}




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
void bta_fs_co_setdir(const char *p_path, UINT8 app_id)
{
    BTIF_TRACE_DEBUG2("Entered %s. New path: %s", __FUNCTION__, p_path);
}

/*******************************************************************************
** OBEX14 Reliable Session not supported. Stub associated callouts.
******************************************************************************/

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
void bta_fs_co_resume(UINT16 evt, UINT8 app_id)
{
    BTIF_TRACE_WARNING0("[CO] bta_fs_co_resume - NOT implemented");
}

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
void bta_fs_co_set_perms(const char *p_src_path,  UINT8 *p_perms, UINT16 evt, UINT8 app_id)
{
    BTIF_TRACE_WARNING0("[CO] bta_fs_co_set_perms - NOT implemented");
}

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
void bta_fs_co_rename(const char *p_src_path, const char *p_dest_path, UINT8 *p_perms, UINT16 evt, UINT8 app_id)
{
    BTIF_TRACE_WARNING0("[CO] bta_fs_co_rename - NOT implemented");
}

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
void bta_fs_co_copy(const char *p_src_path, const char *p_dest_path, UINT8 *p_perms, UINT16 evt, UINT8 app_id)
{
    BTIF_TRACE_WARNING0("[CO] bta_fs_co_copy - NOT implemented");
}

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
void bta_fs_co_resume_op(UINT32 offset, UINT16 evt, UINT8 app_id)
{
    BTIF_TRACE_WARNING0("[CO] bta_fs_co_resume_op - NOT implemented");
}


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
void bta_fs_co_session_info(BD_ADDR bd_addr, UINT8 *p_sess_info, UINT8 ssn,
                                           tBTA_FS_CO_SESS_ST new_st, char *p_path, UINT8 *p_info, UINT8 app_id)
{
    BTIF_TRACE_WARNING0("[CO] bta_fs_co_session_info - NOT implemented");
}


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
void bta_fs_co_suspend(BD_ADDR bd_addr, UINT8 *p_sess_info, UINT8 ssn,
                                      UINT32 *p_timeout, UINT32 *p_offset, UINT8 info, UINT8 app_id)
{
    BTIF_TRACE_WARNING0("[CO] bta_fs_co_suspend - NOT implemented");
}

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
void bta_fs_co_sess_ssn(int fd, UINT8 ssn, UINT8 app_id)
{
    BTIF_TRACE_WARNING0("[CO] bta_fs_co_suspend - NOT implemented");
}

