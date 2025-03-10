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
 *  This is the public interface file for the file system of BTA, Broadcom's
 *  Bluetooth application layer for mobile phones.
 *
 ******************************************************************************/
#ifndef BTA_FS_API_H
#define BTA_FS_API_H

#include "bta_api.h"

/*****************************************************************************
**  Constants and data types
*****************************************************************************/

/* Configuration structure */
typedef struct
{
    UINT16  max_file_len;           /* Maximum size file name */
    UINT16  max_path_len;           /* Maximum path length (includes appended file name) */
    char    path_separator;         /* 0x2f ('/'), or 0x5c ('\') */
} tBTA_FS_CFG;

extern tBTA_FS_CFG * p_bta_fs_cfg;

#endif /* BTA_FS_API_H */
