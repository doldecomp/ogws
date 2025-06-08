/**
 * Compatability macros for deprecated/future C++ features
 */

#ifndef LANG_H
#define LANG_H

#if __cplusplus >= 199711L
#define noexcept throw()
#define override
#endif

#endif
