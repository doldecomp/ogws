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

/*******************************************************************************
 *
 *  Filename:      btif_sock.h
 *
 *  Description:   Bluetooth socket Interface
 *
 *******************************************************************************/

#ifndef BTIF_SOCK_H
#define BTIF_SOCK_H

#include <hardware/bt_sock.h>

bt_status_t btif_sock_init();
btsock_interface_t *btif_sock_get_interface();
void btif_sock_cleanup();

#endif
