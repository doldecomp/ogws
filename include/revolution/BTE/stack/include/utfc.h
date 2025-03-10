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
 *  UTF conversion utilities.
 *
 ******************************************************************************/
#ifndef UTFC_H
#define UTFC_H

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
**
** Function         utfc_16_to_8
**
** Description      Convert a UTF-16 array to a null-terminated UTF-8 string.
**                  Illegal characters are skipped.
**
** Returns          Length of UTF-8 string in bytes.
**
*******************************************************************************/
extern UINT16 utfc_16_to_8(UINT8 *p_utf8, UINT16 utf8_len, UINT16 *p_utf16, UINT16 utf16_len);

/*******************************************************************************
**
** Function         utfc_8_to_16
**
** Description      Convert a null-terminated UTF-8 string to a UTF-16 array.
**                  Illegal characters are skipped.  The UTF-16 array is
**                  appended with a zero (null) character.
**
** Returns          Length of UTF-16 array including null character.
**
*******************************************************************************/
extern UINT16 utfc_8_to_16(UINT16 *p_utf16, UINT16 utf16_len, UINT8 *p_utf8);

#ifdef __cplusplus
}
#endif

#endif /* UTFC_H */
