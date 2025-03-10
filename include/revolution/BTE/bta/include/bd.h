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
 *  BD address services.
 *
 ******************************************************************************/
#ifndef BD_H
#define BD_H

/*****************************************************************************
**  Constants and data types
*****************************************************************************/

/* bd addr length and type */
#ifndef BD_ADDR_LEN
#define BD_ADDR_LEN     6
typedef UINT8 BD_ADDR[BD_ADDR_LEN];
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/* global constant for "any" bd addr */
extern const BD_ADDR bd_addr_any;
extern const BD_ADDR bd_addr_null;
/*****************************************************************************
**  Function Declarations
*****************************************************************************/

/*******************************************************************************
**
** Function         bdcpy
**
** Description      Copy bd addr b to a.
**
**
** Returns          void
**
*******************************************************************************/
extern void bdcpy(BD_ADDR a, const BD_ADDR b);

/*******************************************************************************
**
** Function         bdcmp
**
** Description      Compare bd addr b to a.
**
**
** Returns          Zero if b==a, nonzero otherwise (like memcmp).
**
*******************************************************************************/
extern int bdcmp(const BD_ADDR a, const BD_ADDR b);

/*******************************************************************************
**
** Function         bdcmpany
**
** Description      Compare bd addr to "any" bd addr.
**
**
** Returns          Zero if a equals bd_addr_any.
**
*******************************************************************************/
extern int bdcmpany(const BD_ADDR a);

/*******************************************************************************
**
** Function         bdsetany
**
** Description      Set bd addr to "any" bd addr.
**
**
** Returns          void
**
*******************************************************************************/
extern void bdsetany(BD_ADDR a);

#ifdef __cplusplus
}
#endif

#endif /* BD_H */

