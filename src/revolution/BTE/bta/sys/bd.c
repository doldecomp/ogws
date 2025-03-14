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

#include "data_types.h"
#include "bd.h"

/*****************************************************************************
**  Constants
*****************************************************************************/

/* global constant for "any" bd addr */
const BD_ADDR bd_addr_any = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
const BD_ADDR bd_addr_null= {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

/*****************************************************************************
**  Functions
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
void bdcpy(BD_ADDR a, const BD_ADDR b)
{
    int i;

    for (i = BD_ADDR_LEN; i != 0; i--)
    {
        *a++ = *b++;
    }
}

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
int bdcmp(const BD_ADDR a, const BD_ADDR b)
{
    int i;

    for (i = BD_ADDR_LEN; i != 0; i--)
    {
        if (*a++ != *b++)
        {
            return -1;
        }
    }
    return 0;
}

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
int bdcmpany(const BD_ADDR a)
{
    return bdcmp(a, bd_addr_any);
}

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
void bdsetany(BD_ADDR a)
{
    bdcpy(a, bd_addr_any);
}
