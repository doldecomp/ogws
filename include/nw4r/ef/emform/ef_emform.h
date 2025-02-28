#ifndef NW4R_EF_EMFORM_EMFORM_H
#define NW4R_EF_EMFORM_EMFORM_H
#include <nw4r/types_nw4r.h>

namespace nw4r {
namespace ef {

// Forward declarations
class EmitterForm;

enum EmitFormType {
    EMITFORMTYPE_DISC,
    EMITFORMTYPE_LINE,
    EMITFORMTYPE_CUBE = 5,
    EMITFORMTYPE_CYLINDER = 7,
    EMITFORMTYPE_SPHERE,
    EMITFORMTYPE_POINT,
    EMITFORMTYPE_TORUS,
};

class EmitFormBuilder {
public:
    virtual EmitterForm* Create(EmitFormType type); // at 0x8
};

} // namespace ef
} // namespace nw4r

#endif
