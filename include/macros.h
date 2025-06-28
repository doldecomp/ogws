#ifndef MACROS_H
#define MACROS_H

#define __CONCAT(x, y) x##y
#define CONCAT(x, y) __CONCAT(x, y)

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))

#define CLAMP(low, high, x)                                                    \
    ((x) > (high) ? (high) : ((x) < (low) ? (low) : (x)))

#define ROUND_UP(x, align) (((x) + (align) - 1) & (-(align)))
#define ROUND_UP_PTR(x, align)                                                 \
    ((void*)((((u32)(x)) + (align) - 1) & (~((align) - 1))))

#define ROUND_DOWN(x, align) ((x) & (-(align)))
#define ROUND_DOWN_PTR(x, align) ((void*)(((u32)(x)) & (~((align) - 1))))

#define PTR_DISTANCE(start, end) ((u8*)(end) - (u8*)(start))

#define ARRAY_SIZE(x) (sizeof((x)) / sizeof((x)[0]))

#define ALIGN(x) __attribute__((aligned(x)))

#define DECL_SECTION(x) __declspec(section x)
#define DECL_WEAK __declspec(weak)

#ifdef __MWERKS__

#define DECLTYPE(x) __decltype__(x)
#define MEMCLR(x) __memclr((x), sizeof(*(x)))
#define ARRAY_AT_ADDRESS(addr) [] : (addr)
#define AT_ADDRESS(addr) : (addr)
#define PPC_ASM asm

// For VSCode
#elif defined(__INTELLISENSE__)
#ifdef __clang__ 
    #define MEMCLR(x) __builtin_memset((x), 0, sizeof(*(x)));
    #define DECLTYPE(x) __decltype(x)
#endif
// 'Zero Size Array' hack to avoid incomplete type like `u8 foo[];`. 
// the real fix is to make the AT_ADDRESS macro work in clang.
#define ARRAY_AT_ADDRESS(addr) [0]
#define AT_ADDRESS(addr)
// this macro was created with the following regex:
// search `asm \{([^{}]*\n?)*\}` replace `PPC_ASM ($1)`
#define PPC_ASM(...)
#define asm
#define __attribute__(x)
#define __declspec(x)
#endif

#endif
