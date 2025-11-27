#ifndef RP_SYSTEM_TAG_PARMS_H
#define RP_SYSTEM_TAG_PARMS_H
#include <Pack/types_pack.h>

#include <egg/core.h>

//! @addtogroup rp_system
//! @{

// Forward declarations
class RPSysTagParameters;

#if defined(NONMATCHING) || defined(COMPAT_ANY)
typedef const char* TagType;
#else
typedef char* TagType;
#endif

/**
 * @brief Base class for tag parameters
 */
class RPSysTagParm {
public:
    /**
     * @brief Constructor
     *
     * @param pParent Parent container
     * @param pTag Parameter tag
     */
    RPSysTagParm(RPSysTagParameters* pParent, TagType pTag);

    /**
     * @brief Reads the parameter's value
     *
     * @param rStream Input stream
     */
    virtual void read(EGG::Stream& /* rStream */) {} // at 0x8
    /**
     * @brief Writes the parameter's value
     *
     * @param rStream Output stream
     */
    virtual void write(EGG::Stream& /* rStream */) {} // at 0xC
    /**
     * @brief Prints the parameter's value
     */
    virtual void dump() {} // at 0x10

    /**
     * @brief Gets the parameter's tag name
     */
    TagType getTag();

    /**
     * @brief Accesses the next parameter
     */
    RPSysTagParm* getNext();
    /**
     * @brief Sets the next parameter
     *
     * @param pNext Next parameter
     */
    void setNext(RPSysTagParm* pNext);

private:
    //! Parameter tag
    TagType mpTag; // at 0x4
    //! Next parameter in group
    RPSysTagParm* mpNext; // at 0x8
};

/**
 * @brief Primitive-typed tag parameter
 *
 * @tparam Parameter primitive type
 */
template <typename T> class RPSysPrimTagParm : public RPSysTagParm {
public:
    /**
     * @brief Constructor
     *
     * @param pParent Parent container
     * @param pTag Parameter tag
     */
    RPSysPrimTagParm(RPSysTagParameters* pParent, TagType pTag)
        : RPSysTagParm(pParent, pTag) {}

    /**
     * @brief Reads the parameter's value
     *
     * @param rStream Input stream
     */
    virtual void read(EGG::Stream& rStream) override; // at 0x8
    /**
     * @brief Writes the parameter's value
     *
     * @param rStream Output stream
     */
    virtual void write(EGG::Stream& rStream) override; // at 0xC
    /**
     * @brief Prints the parameter's value
     */
    virtual void dump() override; // at 0x10

    /**
     * @brief Sets the parameter's value
     *
     * @param value New value
     */
    void set(T value) {
        mValue = value;
    }

    /**
     * @brief Accesses the parameter's value
     */
    T& operator()() {
        return mValue;
    }

private:
    //! Parameter value
    T mValue; // at 0xC
};

/**
 * @brief String-typed tag parameter
 */
class RPSysStringTagParm : public RPSysTagParm {
public:
    /**
     * @brief Constructor
     *
     * @param pParent Parent container
     * @param pTag Parameter tag
     */
    RPSysStringTagParm(RPSysTagParameters* pParent, TagType pTag);

    /**
     * @brief Reads the parameter's value
     *
     * @param rStream Input stream
     */
    virtual void read(EGG::Stream& rStream) override; // at 0x8
    /**
     * @brief Writes the parameter's value
     *
     * @param rStream Output stream
     */
    virtual void write(EGG::Stream& rStream) override; // at 0xC
    /**
     * @brief Prints the parameter's value
     */
    virtual void dump() override; // at 0x10

    /**
     * @brief Sets the parameter's value
     *
     * @param value New value
     */
    void set(TagType pValue) {
        mpValue = pValue;
    }

    /**
     * @brief Accesses the parameter's value
     */
    TagType& operator()() {
        return mpValue;
    }

private:
    //! Parameter value
    TagType mpValue; // at 0xC
};

/**
 * @brief Group of tag parameters
 */
class RPSysTagParameters {
public:
    /**
     * @brief Constructor
     *
     * @param pName Parameter group name
     */
    explicit RPSysTagParameters(TagType pName);

    /**
     * @brief Appends a new child parameter to this group
     *
     * @param pChild Child parameter
     */
    void add(RPSysTagParm* pChild);

private:
    //! Name of parameter group
    TagType mpName; // at 0x0
    //! Child parameters
    RPSysTagParm* mpParameters; // at 0x4
};

//! @}

#endif
