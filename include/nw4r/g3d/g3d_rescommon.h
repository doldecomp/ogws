#ifndef NW4R_G3D_RES_COMMON_H
#define NW4R_G3D_RES_COMMON_H
#include <nw4r/types_nw4r.h>

#include <revolution/GX.h>

/**
 * Define ResName pascal string.
 */
#define NW4R_G3D_RESNAME_DEF(VAR, STR)                                         \
    ResNameData ResNameData_##VAR ALIGN(32) = {sizeof(STR) - 1, STR}

namespace nw4r {
namespace g3d {

template <typename T> class ResCommon {
public:
    ResCommon(void* pData) : mpData(static_cast<T*>(pData)) {}
    ResCommon(const void* pData) : mpData(static_cast<const T*>(pData)) {}

    bool IsValid() const {
        return mpData != NULL;
    }

    T* ptr() {
        return mpData;
    }
    const T* ptr() const {
        return mpData;
    }

    T& ref() {
        return *mpData;
    }
    const T& ref() const {
        return *mpData;
    }

    template <typename T> T* ofs_to_ptr_raw(s32 ofs) {
        return reinterpret_cast<T*>((char*)mpData + ofs);
    }
    template <typename T> const T* ofs_to_ptr_raw(s32 ofs) const {
        return reinterpret_cast<const T*>((char*)mpData + ofs);
    }

    template <typename T> T* ofs_to_ptr(s32 ofs) {
        if (ofs != 0) {
            return reinterpret_cast<T*>((char*)mpData + ofs);
        }

        return NULL;
    }
    template <typename T> const T* ofs_to_ptr(s32 ofs) const {
        if (ofs != 0) {
            return reinterpret_cast<const T*>((char*)mpData + ofs);
        }

        return NULL;
    }

    template <typename T> T ofs_to_obj(s32 ofs) {
        if (ofs != 0) {
            return T((char*)mpData + ofs);
        }

        return T(NULL);
    }
    template <typename T> T ofs_to_obj(s32 ofs) const {
        if (ofs != 0) {
            return T((char*)mpData + ofs);
        }

        return T(NULL);
    }

private:
    T* mpData;
};

struct ResNameData {
    u32 len;     // at 0x0
    char str[4]; // at 0x4
};

class ResName : public ResCommon<const ResNameData> {
public:
    ResName(const void* pData) : ResCommon(pData) {}

    u32 GetLength() const {
        return ref().len;
    }

    const char* GetName() const {
        return ref().str;
    }

    bool operator==(ResName rhs) const;
};

namespace detail {

// TODO: Remove
typedef u8 CPCmd[6];
typedef u8 BPCmd[5];

/******************************************************************************
 *
 * Primitive read/write
 *
 ******************************************************************************/
inline u8 ResRead_u8(const u8* pPtr) {
    return *pPtr;
}

inline u32 ResRead_u32(const u8* pPtr) {
    u32 value = ResRead_u8(pPtr++) << 24;
    value |= ResRead_u8(pPtr++) << 16;
    value |= ResRead_u8(pPtr++) << 8;
    value |= ResRead_u8(pPtr++) << 0;
    return value;
}

inline void ResWrite_u8(u8* pPtr, u8 data) {
    *pPtr = data;
}

inline void ResWrite_u16(u8* pPtr, u16 data) {
    ResWrite_u8(pPtr++, data >> 8);
    ResWrite_u8(pPtr++, data >> 0);
}

inline void ResWrite_u32(u8* pPtr, u32 data) {
    ResWrite_u8(pPtr++, data >> 24);
    ResWrite_u8(pPtr++, data >> 16);
    ResWrite_u8(pPtr++, data >> 8);
    ResWrite_u8(pPtr++, data >> 0);
}

/******************************************************************************
 *
 * GX Blitting Processor (BP)
 *
 ******************************************************************************/
inline void ResReadBPCmd(const u8* pPtr, u32* pOut) {
    // Skip over FIFO command byte
    *pOut = ResRead_u32(pPtr + 1);
}

void ResWriteBPCmd(u8* pPtr, u32 reg);
void ResWriteBPCmd(u8* pPtr, u32 reg, u32 mask);
void ResWriteSSMask(u8* pPtr, u32 value);

/******************************************************************************
 *
 * GX Command Processor (CP)
 *
 ******************************************************************************/
inline void ResReadCPCmd(const u8* pPtr, u32* pOut) {
    // Skip over FIFO command byte + addr byte
    *pOut = ResRead_u32(pPtr + 2);
}

void ResWriteCPCmd(u8* pPtr, u8 addr, u32 value);

/******************************************************************************
 *
 * GX Transform Unit (XF)
 *
 ******************************************************************************/
void ResWriteXFCmd(u8* pPtr, u16 addr, u32 value);

} // namespace detail
} // namespace g3d
} // namespace nw4r

#endif
