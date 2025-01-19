#include <nw4r/ef.h>

namespace nw4r {
namespace ef {

static EmitterFormDisc gEmitterFormDisc;
static EmitterFormLine gEmitterFormLine;
static EmitterFormCylinder gEmitterFormCylinder;
static EmitterFormSphere gEmitterFormSphere;
static EmitterFormTorus gEmitterFormTorus;
static EmitterFormCube gEmitterFormCube;
static EmitterFormPoint gEmitterFormPoint;

EmitterForm* EmitFormBuilder::Create(EmitFormType type) {
    switch (type) {
    case EMITFORMTYPE_DISC: {
        return &gEmitterFormDisc;
    }

    case EMITFORMTYPE_LINE: {
        return &gEmitterFormLine;
    }

    case EMITFORMTYPE_CYLINDER: {
        return &gEmitterFormCylinder;
    }

    case EMITFORMTYPE_SPHERE: {
        return &gEmitterFormSphere;
    }

    case EMITFORMTYPE_TORUS: {
        return &gEmitterFormTorus;
    }

    case EMITFORMTYPE_CUBE: {
        return &gEmitterFormCube;
    }

    case EMITFORMTYPE_POINT: {
        return &gEmitterFormPoint;
    }

    default: {
        return NULL;
    }
    }
}

} // namespace ef
} // namespace nw4r
