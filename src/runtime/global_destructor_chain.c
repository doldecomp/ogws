#include <runtime/global_destructor_chain.h>

typedef void (*DtorFunction)(void* obj, s16 method);

typedef struct DtorLink {
    struct DtorLink* next; // at 0x0
    DtorFunction dtor;     // at 0x4
    void* object;          // at 0x8
} DtorLink;

DtorLink* __global_destructor_chain = NULL;

void __register_global_object(void* object, DtorFunction dtor, DtorLink* link) {
    link->next = __global_destructor_chain;
    link->dtor = dtor;
    link->object = object;
    __global_destructor_chain = link;
}

void __destroy_global_chain(void) {
    DtorLink* link;

    while (link = __global_destructor_chain) {
        // Pop destructor
        __global_destructor_chain = link->next;
        // Destroy object (-1 to destroy all bases)
        link->dtor(link->object, -1);
    }
}

#pragma section ".dtors$10"
DECL_SECTION(".dtors$10")
DECL_WEAK funcptr_t __destroy_global_chain_reference = __destroy_global_chain;
