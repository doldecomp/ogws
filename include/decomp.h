#ifndef DECOMP_H
#define DECOMP_H

// Codewarrior tricks for matching decomp
// (Functions are given prototypes for -requireprotos)
#ifdef __MWERKS__
// Force BSS order
#define CW_FORCE_ORDER(module, ...)                                              \
    void fake_function(...);                                                   \
    void FORCE_BSS##module##x(void);                                           \
    void FORCE_BSS##module##x(void) { fake_function(__VA_ARGS__); }
// Force strings into pool
#define CW_FORCE_STRINGS(module, ...)                                          \
    void fake_function(...);                                                   \
    void FORCE_STRINGS##module(void);                                          \
    void FORCE_STRINGS##module(void) { fake_function(__VA_ARGS__); }
#else
#define CW_FORCE_ORDER(module, ...)
#define CW_FORCE_STRINGS(module, ...)
#endif

#endif