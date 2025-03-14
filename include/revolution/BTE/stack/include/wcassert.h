/******************************************************************************
 *
 *  Copyright (C) 1999-2012 Broadcom Corporation
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
#ifndef WC_ASSERT_H
#define WC_ASSERT_H


#ifdef _DEBUG

#include "bt_target.h"



/* debug settings*/
#ifndef WC_DEBUG_LEVEL
#define WC_DEBUG_LEVEL 0
#endif

#if WC_DEBUG_LEVEL == 0

#include "stdio.h"  /* for printf()*/

#ifdef __cplusplus
extern "C" wc_assert(char *message, char *file, UINT32 line);
#else
void wc_assert(char *message, char *file, UINT32 line);
#endif

#define WC_ASSERT(_x) if ( !(_x) ) wc_assert("ASSERT at %s line %d\n", __FILE__, __LINE__);
#define WC_ASSERT_ALWAYS() wc_assert("ASSERT! at %s line %d\n", __FILE__, __LINE__);

#elif WC_DEBUG_LEVEL == 1

#include "assert.h"

#define WC_ASSERT(_x)        assert(_x);
#define WC_ASSERT_ALWAYS()   assert(0);
#endif  /* WC_DEBUG_LEVEL*/

#else /* _DEBUG*/

#ifndef WC_ASSERT
#define WC_ASSERT(_x)         ;
#endif

#ifndef WC_ASSERT_ALWAYS
#define WC_ASSERT_ALWAYS()    ;
#endif

#endif /* _DEBUG*/
#endif /* WC_ASSERT_H*/
