#ifndef NW4R_SND_UTIL_H
#define NW4R_SND_UTIL_H
#include <nw4r/types_nw4r.h>

#include <nw4r/snd/snd_Types.h>

namespace nw4r {
namespace snd {
namespace detail {

class Util {
public:
    // 12 notes each with 256 microtones
    static const int SEMITONE_MAX = 12;
    static const int MICROTONE_MAX = 256;

    static const int VOLUME_MIN =
        static_cast<int>(10 * VOLUME_MIN_DB); // -90.4db
    static const int VOLUME_MAX =
        static_cast<int>(10 * VOLUME_MAX_DB); // +6.0db

public:
    /******************************************************************************
     *
     * Pan info
     *
     ******************************************************************************/
    enum PanCurve {
        PAN_CURVE_SQRT,
        PAN_CURVE_SINCOS,
        PAN_CURVE_LINEAR,
    };

    struct PanInfo {
        PanCurve curve;  // at 0x0
        bool centerZero; // at 0x4
        bool zeroClamp;  // at 0x5

        PanInfo()
            : curve(PAN_CURVE_SQRT), centerZero(false), zeroClamp(false) {}
    };

    /******************************************************************************
     *
     * DataRef
     *
     ******************************************************************************/
    enum RefType {
        REFTYPE_ADDRESS,
        REFTYPE_OFFSET,
    };

    enum DataType {
        DATATYPE_T0,
        DATATYPE_T1,
        DATATYPE_T2,
        DATATYPE_T3,
        DATATYPE_INVALID
    };

    template <typename T0, typename T1 = void, typename T2 = void,
              typename T3 = void>
    struct DataRef {
        u8 refType;   // at 0x0
        u8 dataType;  // at 0x1
        u16 reserved; // at 0x2
        u32 value;    // at 0x4
    };

    template <typename T0, typename T1, typename T2, typename T3>
    static inline const T0*
    GetDataRefAddress0(const DataRef<T0, T1, T2, T3>& rRef, const void* pBase) {
        return static_cast<const T0*>(GetDataRefAddressImpl(
            static_cast<RefType>(rRef.refType), rRef.value, pBase));
    }

    template <typename T0, typename T1, typename T2, typename T3>
    static inline const T1*
    GetDataRefAddress1(const DataRef<T0, T1, T2, T3>& rRef, const void* pBase) {
        return static_cast<const T1*>(GetDataRefAddressImpl(
            static_cast<RefType>(rRef.refType), rRef.value, pBase));
    }

    template <typename T0, typename T1, typename T2, typename T3>
    static inline const T2*
    GetDataRefAddress2(const DataRef<T0, T1, T2, T3>& rRef, const void* pBase) {
        return static_cast<const T2*>(GetDataRefAddressImpl(
            static_cast<RefType>(rRef.refType), rRef.value, pBase));
    }

    template <typename T0, typename T1, typename T2, typename T3>
    static inline const T3*
    GetDataRefAddress3(const DataRef<T0, T1, T2, T3>& rRef, const void* pBase) {
        return static_cast<const T3*>(GetDataRefAddressImpl(
            static_cast<RefType>(rRef.refType), rRef.value, pBase));
    }

    /******************************************************************************
     *
     * Table
     *
     ******************************************************************************/
    template <typename T> struct Table {
        u32 count;  // at 0x0
        T items[1]; // at 0x4
    };

    /******************************************************************************
     *
     * Read big endian value
     *
     ******************************************************************************/
#ifdef NW4R_LITLE_ENDIAN
    static inline u16 ReadBigEndian(u16 x) {
        return x >> 8 | x << 8;
    }

    static inline u32 ReadBigEndian(u32 x) {
        return (x >> 24) & 0x000000FF | (x >> 8) & 0x0000FF00 |
               (x << 8) & 0x00FF0000 | (x << 24) & 0xFF000000;
    }
#else
    static inline u16 ReadBigEndian(u16 x) {
        return x;
    }

    static inline u32 ReadBigEndian(u32 x) {
        return x;
    }
#endif

    /******************************************************************************
     *
     * Utility functions
     *
     ******************************************************************************/
    static f32 CalcPitchRatio(int pitch);
    static f32 CalcVolumeRatio(f32 db);
    static f32 CalcPanRatio(f32 pan, const PanInfo& rInfo);
    static f32 CalcSurroundPanRatio(f32 pan, const PanInfo& rInfo);
    static int CalcLpfFreq(f32 scale);
    static void GetRemoteFilterCoefs(int filter, u16* pB0, u16* pB1, u16* pB2,
                                     u16* pA1, u16* pA2);
    static u16 CalcRandom();

private:
    static const void* GetDataRefAddressImpl(RefType type, u32 value,
                                             const void* pBase);

private:
    // Chromatic scale (tbl[idx] / tbl[idx-1] == ~1.06)
    static const f32 NoteTable[SEMITONE_MAX];
    // Each note contains 256 microtones
    static const f32 PitchTable[MICROTONE_MAX];

    // Table index is the millibel / hundredth-of-a-decibel
    // dB(idx) = VOLUME_MIN_DB + (idx / 10)
    // tbl[idx] = 10 ** (dB(idx) / 20)
    static const int VOLUME_TABLE_SIZE = VOLUME_RANGE_MB + 1;
    static const f32 Decibel2RatioTable[VOLUME_TABLE_SIZE];

    // 1/256 step
    static const int PAN_TABLE_MIN = 0;
    static const int PAN_TABLE_MAX = 256;
    static const int PAN_TABLE_CENTER = PAN_TABLE_MAX / 2;
    static const int PAN_TABLE_SIZE = PAN_TABLE_MAX + 1;
    // tbl[idx] = sqrt(1 - (idx / PAN_TABLE_MAX))
    static const f32 Pan2RatioTableSqrt[PAN_TABLE_SIZE];
    // tbl[idx] = cos(idx * (PI / (2 * PAN_TABLE_MAX)))
    static const f32 Pan2RatioTableSinCos[PAN_TABLE_SIZE];
    // tbl[idx] = 1 - (idx * (1 / PAN_TABLE_MAX))
    static const f32 Pan2RatioTableLinear[PAN_TABLE_SIZE];

    // Pan curve tables
    static const int PAN_CURVE_NUM = PAN_CURVE_LINEAR + 1;
    static const f32* PanTableTable[PAN_CURVE_NUM];

    // Biquad filter coefficients (b0, b1, b2, a1, a2)
    static const int COEF_TABLE_MIN = 0;
    static const int COEF_TABLE_MAX = REMOTE_FILTER_MAX;
    static const int COEF_TABLE_SIZE = COEF_TABLE_MAX + 1;
    static const int IIR_COEF_COUNT = 5;
    static const u16 RemoteFilterCoefTable[COEF_TABLE_SIZE][IIR_COEF_COUNT];
};

} // namespace detail
} // namespace snd
} // namespace nw4r

#endif
