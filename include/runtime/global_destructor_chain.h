#ifndef RUNTIME_GLOBAL_DESTRUCTOR_CHAIN_H
#define RUNTIME_GLOBAL_DESTRUCTOR_CHAIN_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

void __destroy_global_chain(void);

#ifdef __cplusplus
}
#endif
#endif
