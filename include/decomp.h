#ifndef DECOMP_H
#define DECOMP_H

#define __CONCAT(x, y) x##y
#define CONCAT(x, y) __CONCAT(x, y)

// Codewarrior tricks for matching decomp
// (Functions are given prototypes for -requireprotos)
#ifdef __MWERKS__
// Force reference specific data
#define DECOMP_FORCEACTIVE(module, ...)                                        \
    void fake_function(...);                                                   \
    void CONCAT(FORCEACTIVE##module, __LINE__)(void);                          \
    void CONCAT(FORCEACTIVE##module, __LINE__)(void) {                         \
        fake_function(__VA_ARGS__);                                            \
    }

// Force literal ordering, such as floats in sdata2
#define DECOMP_FORCELITERAL(module, ...)                                       \
    void CONCAT(FORCELITERAL##module, __LINE__)(void);                         \
    void CONCAT(FORCELITERAL##module, __LINE__)(void) { (__VA_ARGS__); }
#define DECOMP_DONT_INLINE __attribute__((never_inline))
#else
#define DECOMP_FORCEACTIVE(module, ...)
#define DECOMP_FORCELITERAL(module, x)
#define DECOMP_DONT_INLINE
#endif

#endif