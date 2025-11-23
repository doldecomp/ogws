#include <Pack/RPSystem.h>

/******************************************************************************
 *
 * RPSysTagParm
 *
 ******************************************************************************/

/**
 * @brief Constructor
 *
 * @param pParent Parent container
 * @param pTag Parameter tag
 */
#if defined(NONMATCHING) || defined(COMPAT_ANY)
RPSysTagParm::RPSysTagParm(RPSysTagParameters* pParent, const char* pTag)
#else
RPSysTagParm::RPSysTagParm(RPSysTagParameters* pParent, char* pTag)
#endif
    : mpTag(pTag), mpNext(NULL) {

    pParent->add(this);
}

/**
 * @brief Gets the parameter's tag name
 */
const char* RPSysTagParm::getTag() {
    return mpTag;
}

/**
 * @brief Accesses the next parameter
 */
RPSysTagParm* RPSysTagParm::getNext() {
    return mpNext;
}
/**
 * @brief Sets the next parameter
 *
 * @param pNext Next parameter
 */
void RPSysTagParm::setNext(RPSysTagParm* pNext) {
    mpNext = pNext;
}

/******************************************************************************
 *
 * RPSysPrimTagParm<int>
 *
 ******************************************************************************/

/**
 * @brief Reads the parameter's value
 *
 * @param rStream Input stream
 */
template <> void RPSysPrimTagParm<int>::read(EGG::Stream& rStream) {
    mValue = rStream.read_s32();
}

/**
 * @brief Writes the parameter's value
 *
 * @param rStream Output stream
 */
template <> void RPSysPrimTagParm<int>::write(EGG::Stream& rStream) {
    rStream.write_s32(mValue);
}

/**
 * @brief Prints the parameter's value
 */
template <> void RPSysPrimTagParm<int>::dump() {}

/******************************************************************************
 *
 * RPSysStringTagParm
 *
 ******************************************************************************/

/**
 * @brief Constructor
 *
 * @param pParent Parent container
 * @param pTag Parameter tag
 */
#if defined(NONMATCHING) || defined(COMPAT_ANY)
RPSysStringTagParm::RPSysStringTagParm(RPSysTagParameters* pParent,
                                       const char* pTag)
    : RPSysTagParm(pParent, pTag), mpValue(NULL) {}
#else
RPSysStringTagParm::RPSysStringTagParm(RPSysTagParameters* pParent, char* pTag)
    : RPSysTagParm(pParent, pTag), mpValue(NULL) {}
#endif

/**
 * @brief Reads the parameter's value
 *
 * @param rStream Input stream
 */
void RPSysStringTagParm::read(EGG::Stream& rStream) {
    mpValue = rStream.readString(NULL, 0);
}

/**
 * @brief Writes the parameter's value
 *
 * @param rStream Output stream
 */
void RPSysStringTagParm::write(EGG::Stream& rStream) {
    rStream.writeString(const_cast<char*>(mpValue));
}

/**
 * @brief Prints the parameter's value
 */
void RPSysStringTagParm::dump() {}

/******************************************************************************
 *
 * RPSysTagParameters
 *
 ******************************************************************************/

/**
 * @brief Constructor
 *
 * @param pName Parameter group name
 */
#if defined(NONMATCHING) || defined(COMPAT_ANY)
RPSysTagParameters::RPSysTagParameters(const char* pName)
    : mpName(pName), mpParameters(NULL) {}
#else
RPSysTagParameters::RPSysTagParameters(char* pName)
    : mpName(pName), mpParameters(NULL) {}
#endif

/**
 * @brief Appends a new child parameter to this group
 *
 * @param pChild Child parameter
 */
void RPSysTagParameters::add(RPSysTagParm* pChild) {
    if (mpParameters != NULL) {
        pChild->setNext(mpParameters);
        mpParameters = pChild;
    } else {
        mpParameters = pChild;
    }
}
