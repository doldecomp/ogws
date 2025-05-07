#ifndef EGG_CORE_BIT_FLAG_H
#define EGG_CORE_BIT_FLAG_H
#include <egg/types_egg.h>

namespace EGG {

namespace detail {

// There's no chance this existed in the original library.
// One QoL improvement to TBitFlag is constraining T to u8, u16, and u32.
//
// Because we don't have C++20 constraints, or even C++11 type traits,
// we instead define these manually in a detail namespace.

template <typename T> struct TBitFlagValid {
    enum { value = false };
};

template <> struct TBitFlagValid<u8> {
    enum { value = true };
};
template <> struct TBitFlagValid<u16> {
    enum { value = true };
};
template <> struct TBitFlagValid<u32> {
    enum { value = true };
};

template <bool> struct TTypeTrap;

template <> struct TTypeTrap<true> {};

} // namespace detail

template <typename T> class TBitFlag {
public:
    typedef TBitFlag<T> self_type;
    typedef T value_type;

    TBitFlag() {
        makeAllZero();
    }

    TBitFlag(T value) : mValue(value) {}

    operator T() const {
        return mValue;
    }

    void makeAllZero() {
        mValue = static_cast<T>(0);
    }
    bool isZero() const {
        return mValue == 0;
    }

    T getDirect() const {
        return mValue;
    }
    void setDirect(T value) {
        mValue = value;
    }

    /******************************************************************************
     * Bit mask operations
     ******************************************************************************/
    self_type& set(T mask) {
        mValue |= mask;
        return *this;
    }
    self_type& reset(T mask) {
        mValue &= ~mask;
        return *this;
    }

    void change(T mask, bool on) {
        if (on) {
            set(mask);
        } else {
            reset(mask);
        }
    }

    bool on(T mask) const {
        return mValue & mask;
    }
    bool off(T mask) const {
        return !on(mask);
    }

    /******************************************************************************
     * Bit index operations
     ******************************************************************************/
    self_type& setBit(u8 bit) {
        set(makeMask(bit));
        return *this;
    }
    self_type& resetBit(u8 bit) {
        reset(makeMask(bit));
        return *this;
    }

    void changeBit(u8 bit, bool on) {
        change(makeMask(bit), on);
    }
    void toggleBit(u8 bit) {
        changeBit(bit, !onBit(bit));
    }

    bool onBit(u8 bit) const {
        return on(makeMask(bit));
    }
    bool offBit(u8 bit) const {
        return off(makeMask(bit));
    }

private:
    T makeMask(u8 bit) const {
        return 1 << bit;
    }

private:
    union {
        T mValue; // at 0x0

        // We require a union because, despite being an empty struct,
        // this still has a size of 1. This struct being a static member of
        // TBitFlag doesn't work either. Fortunately, sizeof(T) is always >= 1,
        // so we can safely union this and still get the compile time checks.
        detail::TTypeTrap<detail::TBitFlagValid<T>::value> trap;
    };
};

} // namespace EGG

#endif
