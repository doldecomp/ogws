/**
 * Compatability macros for deprecated/future C++ features
 */

#ifndef DECOMP_LANG_H
#define DECOMP_LANG_H

#if __cplusplus < 201103L
#define noexcept throw()
#define override
#endif

#endif
