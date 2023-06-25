#include <types.h>

#define NUM_FRAGMENT 1

typedef struct ExtabInfo {
    void* section;           // at 0x0
    struct ExtabInfo* extab; // at 0x4
    void* codeStart;         // at 0x8
    u32 codeSize;            // at 0xC
} ExtabInfo;

typedef struct FragmentInfo {
    ExtabInfo* extab; // at 0x0
    void* toc;        // at 0x4
    BOOL regist;      // at 0x8
} FragmentInfo;

static FragmentInfo fragmentInfo[NUM_FRAGMENT];

int __register_fragment(ExtabInfo* extab, void* toc) {
    int i;
    FragmentInfo* frag;

    for (i = 0; i < NUM_FRAGMENT; i++) {
        frag = &fragmentInfo[i];

        if (!frag->regist) {
            frag->extab = extab;
            frag->toc = toc;
            frag->regist = TRUE;
            return 0;
        }
    }

    return -1;
}

void __unregister_fragment(int i) {
    FragmentInfo* frag;

    if (i < 0) {
        return;
    }

    if (i >= NUM_FRAGMENT) {
        return;
    }

    frag = &fragmentInfo[i];
    frag->extab = NULL;
    frag->toc = NULL;
    frag->regist = FALSE;
}
