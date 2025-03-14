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

/************************************************************************************
 *
 *  Filename:      btif_config_util.h
 *
 *  Description:   Bluetooth configuration utility api
 *
 ***********************************************************************************/

#ifndef BTIF_CONFIG_UTIL_H
#define BTIF_CONFIG_UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
** Constants & Macros
********************************************************************************/

#define BLUEZ_PATH "/data/misc/bluetoothd/"
#define BLUEZ_PATH_BAK "/data/misc/bluetoothd_bak"
#define BLUEZ_LINKKEY  "linkkeys"
#define BLUEZ_NAMES "names"
#define BLUEZ_PROFILES "profiles"
#define BLUEZ_CLASSES "classes"
#define BLUEZ_TYPES "types"
#define BLUEZ_CONFIG "config"
#define BLUEZ_ALIASES "aliases"


/*******************************************************************************
**  Functions
********************************************************************************/

int btif_config_save_file(const char* file_name);
int btif_config_load_file(const char* file_name);
int load_bluez_adapter_info(char* adapter_path, int size);
int load_bluez_linkkeys(const char* adapter_path);

#ifdef __cplusplus
}
#endif

#endif
