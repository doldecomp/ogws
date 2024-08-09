#ifndef NW4R_SND_UTIL_H
#define NW4R_SND_UTIL_H
#include "types_nw4r.h"
#include "snd_Common.h"

namespace nw4r
{
    namespace snd
    {
        namespace detail
        {
            namespace Util
            {
                enum RefType
                {
                    REFTYPE_ADDRESS,
                    REFTYPE_OFFSET,
                };
                
                template <typename T0, typename T1, typename T2, typename T3>
                struct DataRef
                {
                    u8 mType; // at 0x0
                    u8 BYTE_0x1;
                    u32 INT_0x4;
                };
                
                template <typename T>
                struct Table
                {
                    u32 mCount; // at 0x0
                    T mEntries[]; // at 0x4
                };
                
                enum PanCurve
                {
                    PAN_CURVE_SQRT,
                    PAN_CURVE_SINCOS,
                    PAN_CURVE_LINEAR,
                };

                struct PanInfo
                {
                    PanCurve curve; // at 0x0
                    bool centerZero; // at 0x4
                    bool zeroClamp; // at 0x5

                    PanInfo() :
                        curve(PAN_CURVE_SQRT),
                        centerZero(false),
                        zeroClamp(false) {}
                };

                template <typename T0, typename T1, typename T2, typename T3>
                inline const T0 * GetDataRefAddress0(const DataRef<T0, T1, T2, T3> & dataRef, const void * ptr)
                {
                    return (const T0 *)GetDataRefAddressImpl((RefType)dataRef.mType, dataRef.INT_0x4, ptr);
                }
                
                template <typename T0, typename T1, typename T2, typename T3>
                inline const T1 * GetDataRefAddress1(const DataRef<T0, T1, T2, T3> & dataRef, const void * ptr)
                {
                    return (const T1 *)GetDataRefAddressImpl((RefType)dataRef.mType, dataRef.INT_0x4, ptr);
                }
                
                template <typename T0, typename T1, typename T2, typename T3>
                inline const T2 * GetDataRefAddress2(const DataRef<T0, T1, T2, T3> & dataRef, const void * ptr)
                {
                    return (const T2 *)GetDataRefAddressImpl((RefType)dataRef.mType, dataRef.INT_0x4, ptr);
                }
                
                template <typename T0, typename T1, typename T2, typename T3>
                inline const T3 * GetDataRefAddress3(const DataRef<T0, T1, T2, T3> & dataRef, const void * ptr)
                {
                    return (const T3 *)GetDataRefAddressImpl((RefType)dataRef.mType, dataRef.INT_0x4, ptr);
                }

                f32 CalcPitchRatio(int);
                f32 CalcVolumeRatio(f32);
                f32 CalcPanRatio(f32, const PanInfo&);
                f32 CalcSurroundPanRatio(f32, const PanInfo&);
                int CalcLpfFreq(f32);
                void GetRemoteFilterCoefs(int, u16 *, u16 *, u16 *, u16 *, u16 *);
                u16 CalcRandom();
                const void * GetDataRefAddressImpl(RefType, u32, const void *);
            }
        }
    }
}

#endif