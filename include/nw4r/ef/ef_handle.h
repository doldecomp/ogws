#ifndef NW4R_EF_HANDLE_H
#define NW4R_EF_HANDLE_H
#include "types_nw4r.h"
#include <nw4r/ef/ef_linkedobject.h>

namespace nw4r {
namespace ef {

struct HandleBase {
    LinkedObject* PTR_0x0;
    LinkedObject* mPtr;

    HandleBase();
    HandleBase& operator=(const HandleBase&);
    HandleBase& operator=(LinkedObject*);
    bool IsValid() const;
    LinkedObject* GetPtr() const;
};

} // namespace ef
} // namespace nw4r

#endif
