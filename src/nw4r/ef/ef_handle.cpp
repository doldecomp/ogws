#include <nw4r/ef.h>

namespace nw4r {
namespace ef {

HandleBase::HandleBase() : mObjectID(NULL), mObject(NULL) {}

HandleBase::HandleBase(const HandleBase& rOther)
    : mObjectID(rOther.mObjectID), mObject(rOther.mObject) {}

HandleBase::HandleBase(LinkedObject* pObject) {
    if (pObject == NULL) {
        mObjectID = 0;
        mObject = NULL;
    } else {
        mObjectID = pObject->mObjectID;
        mObject = pObject;
    }
}

HandleBase& HandleBase::operator=(const HandleBase& rOther) {
    mObjectID = rOther.mObjectID;
    mObject = rOther.mObject;

    return *this;
}

HandleBase& HandleBase::operator=(LinkedObject* pObject) {
    if (pObject == NULL) {
        mObjectID = 0;
        mObject = NULL;
    } else {
        mObjectID = pObject->mObjectID;
        mObject = pObject;
    }

    return *this;
}

bool HandleBase::IsValid() const {
    if (mObject == NULL) {
        return false;
    }

    return mObjectID == mObject->mObjectID;
}

LinkedObject* HandleBase::GetPtr() const {
    return IsValid() ? mObject : NULL;
}

} // namespace ef
} // namespace nw4r
