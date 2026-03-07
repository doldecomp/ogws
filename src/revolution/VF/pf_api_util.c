#include <revolution/VF.h>

int VFipf_error_to_api_error[40] = {
    0x00000000, 0x00000016, 0x00000016, 0x00000002,
    0x00000010, 0x0000005A, 0x0000001C, 0x00000008,
    0x00000011, 0x00000008, 0x00000016, 0x0000000D,
    0x00000058, 0x00000008, 0x00000008, 0x00000008,
    0x0000000D, 0x00000005, 0x00000008, 0x0000000D,
    0x00000002, 0x00000017, 0x00000018, 0x00000015,
    0x0000000D, 0x00000001, 0x00000008, 0x00000008,
    0x00000008, 0x00000008, 0x0000000C, 0x00000016,
    0x00000016, 0x00000008, 0x00000002, 0x00000008,
    0x00000008, 0x0000001B, 0x00000009, 0x0000002E
};

u32 VFiPFAPI_ParseOpenModeString(const char *mode_str) {
    u32 open_mode;
    u32 i;

    if (mode_str == 0) {
        return 10;
    }

    i = 1;

    switch (mode_str[0]) {
        case 'r':
            open_mode = 2;
            break;
        case 'w':
            open_mode = 1;
            break;
        case 'a':
            open_mode = 4;
            break;
        default:
            return 0;
    }

    if (mode_str[1] == 'b') {
        i = 2;
    }

    switch (mode_str[i++]) {
        case 0:
            return open_mode;

        case '+': {
            open_mode |= 8;
            break;
        }

        case 't':
        default:
            return 0;
    }

    switch (mode_str[i++]) {
        case 0: {
            return open_mode;
        }
    }

    return 0;
}

int VFiPFAPI_convertError(int err) {
    if (err == 0) {
        return 0;
    }
    if (err == -1) {
        return -1;
    }
    if (err > 0 && err < 160) {
        return VFipf_error_to_api_error[err];
    }
    if (err == 4096) {
        return 5;
    }
    return err;
}

int VFiPFAPI_convertReturnValue(int err) {
    return (-err | err) >> 31;
}

void* VFiPFAPI_convertReturnValue2NULL(int err, void* p_stream) {
    if (err) {
        return NULL;
    } else {
        return p_stream;
    }
}

int VFiPFAPI_convertReturnValue4unmount(int err) {
    if (err == 0) {
        return 0;
    }

    if (err == 1) {
        return 1;
    }

    return -1;
}
