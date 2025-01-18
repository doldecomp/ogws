#include <revolution/NWC24.h>

void NWC24Data_Init(NWC24Data* data) {
    data->ptr = NULL;
    data->size = 0;
}

void NWC24Data_SetDataP(NWC24Data* data, const void* ptr, u32 size) {
    data->ptr = ptr;
    data->size = size;
}

void NWC24Date_Init(NWC24Date* date) {
    date->year = 2000;
    date->month = 1;
    date->day = 1;
    date->hour = 12;
    date->min = 0;
    date->sec = 0;
    date->BYTE_0x7 = 0;
}

void NWC24iConvIdToStr(u64 addr, char* out) {
    u64 a = addr;
    int i;

    // Count nibbles in u64
    const int n = sizeof(u64) * 2;

    for (i = n - 1; i >= 0; i--) {
        out[i] = '0' + a % 10;
        a /= 10;
    }

    out[n] = '\0';
}
