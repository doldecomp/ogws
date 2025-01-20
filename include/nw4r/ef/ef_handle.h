#ifndef NW4R_EF_HANDLE_H
#define NW4R_EF_HANDLE_H
#include <nw4r/ef/ef_linkedobject.h>
#include <nw4r/ef/ef_referencedobject.h>
#include <nw4r/ef/ef_types.h>

namespace nw4r {
namespace ef {

class HandleBase {
private:
    u32 mObjectID;         // at 0x0
    LinkedObject* mObject; // at 0x4

public:
    HandleBase();
    HandleBase(const HandleBase& rOther);
    HandleBase(LinkedObject* pObject);

    HandleBase& operator=(const HandleBase& rOther);
    HandleBase& operator=(LinkedObject* pObject);

    bool IsValid() const;
    LinkedObject* GetPtr() const;
};

template <typename T> class Handle : public HandleBase {
public:
    Handle(const Handle& rOther) : HandleBase(rOther) {}
    Handle(T* pObject) : HandleBase(static_cast<LinkedObject*>(pObject)) {}

    Handle& operator=(T* pObject) {
        *this = static_cast<LinkedObject*>(pObject);
    }

    bool IsAlive() const {
        ReferencedObject::LifeStatus status = GetLifeStatus();

        return status == ReferencedObject::NW4R_EF_LS_ACTIVE ||
               status == ReferencedObject::NW4R_EF_LS_WAIT;
    }

    T* GetPtr() const {
        return static_cast<T*>(HandleBase::GetPtr());
    }

    ReferencedObject::LifeStatus GetLifeStatus() const {
        T* pObject = static_cast<T*>(HandleBase::GetPtr());

        if (pObject == NULL) {
            return ReferencedObject::NW4R_EF_LS_CLOSED;
        }

        return pObject->GetLifeStatus();
    }
};

} // namespace ef
} // namespace nw4r

#endif
