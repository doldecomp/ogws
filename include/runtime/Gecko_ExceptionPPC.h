#ifndef RUNTIME_GECKO_EXCEPTION_PPC_H
#define RUNTIME_GECKO_EXCEPTION_PPC_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
typedef struct ExtabIndexInfo;

int __register_fragment(const struct ExtabIndexInfo* extab, void* toc);
void __unregister_fragment(int i);

#ifdef __cplusplus
}
#endif
#endif
