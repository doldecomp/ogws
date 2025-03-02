#ifndef NW4R_UT_RUNTIME_TYPE_INFO_H
#define NW4R_UT_RUNTIME_TYPE_INFO_H
#include <nw4r/types_nw4r.h>

namespace nw4r {
namespace ut {
namespace detail {

/******************************************************************************
 *
 * RuntimeTypeInfo
 *
 ******************************************************************************/
struct RuntimeTypeInfo {
    explicit RuntimeTypeInfo(const RuntimeTypeInfo* pBase)
        : mParentTypeInfo(pBase) {}

    bool IsDerivedFrom(const RuntimeTypeInfo* pInfo) const {
        for (const RuntimeTypeInfo* pIt = this; pIt != NULL;
             pIt = pIt->mParentTypeInfo) {

            if (pIt == pInfo) {
                return true;
            }
        }

        return false;
    }

    const RuntimeTypeInfo* mParentTypeInfo; // at 0x0
};

template <typename T>
inline const RuntimeTypeInfo* GetTypeInfoFromPtr_(T* /* pPtr */) {
    return &T::typeInfo;
}

} // namespace detail

/******************************************************************************
 *
 * DynamicCast
 *
 ******************************************************************************/
template <typename TDerived, typename TBase>
inline TDerived DynamicCast(TBase* pPtr) {
    const detail::RuntimeTypeInfo* pDerivedTypeInfo =
        detail::GetTypeInfoFromPtr_(static_cast<TDerived>(NULL));

    // Downcast only if possible
    if (pPtr->GetRuntimeTypeInfo()->IsDerivedFrom(pDerivedTypeInfo)) {
        return static_cast<TDerived>(pPtr);
    }

    return NULL;
}

} // namespace ut
} // namespace nw4r

/******************************************************************************
 *
 * Macros
 *
 ******************************************************************************/
/**
 * Declare type RTTI and accessor function.
 */
#define NW4R_UT_RTTI_DECL(T)                                                   \
    virtual const nw4r::ut::detail::RuntimeTypeInfo* GetRuntimeTypeInfo()      \
        const {                                                                \
        return &typeInfo;                                                      \
    }                                                                          \
                                                                               \
    static nw4r::ut::detail::RuntimeTypeInfo typeInfo;

/**
 * Define type RTTI (base type).
 */
#define NW4R_UT_RTTI_DEF_BASE(T)                                               \
    nw4r::ut::detail::RuntimeTypeInfo T::typeInfo(NULL)

/**
 * Define type RTTI (derived type).
 */
#define NW4R_UT_RTTI_DEF_DERIVED(T, BASE)                                      \
    nw4r::ut::detail::RuntimeTypeInfo T::typeInfo(&BASE::typeInfo)

#endif
