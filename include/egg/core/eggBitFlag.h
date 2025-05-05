#ifndef EGG_CORE_BIT_FLAG_H
#define EGG_CORE_BIT_FLAG_H
#include <egg/types_egg.h>

namespace EGG {

template <typename T> class TBitFlag {
public:
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
    void set(T mask) {
        mValue |= mask;
    }
    void reset(T mask) {
        mValue &= ~mask;
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
    void setBit(u8 bit) {
        set(makeMask(bit));
    }
    void resetBit(u8 bit) {
        reset(makeMask(bit));
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
    T mValue; // at 0x0
};

} // namespace EGG

#endif
