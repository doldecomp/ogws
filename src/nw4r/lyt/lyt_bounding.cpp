#include "lyt_bounding.h"

namespace nw4r
{
    namespace lyt
    {
        Bounding::Bounding(const res::Bounding *res, const ResBlockSet&) : Pane(res)
        {

        }

        Bounding::~Bounding()
        {

        }

        void Bounding::DrawSelf(const DrawInfo&)
        {

        }

        const ut::detail::RuntimeTypeInfo * Bounding::GetRuntimeTypeInfo() const
        {
            return &typeInfo;
        }

        ut::detail::RuntimeTypeInfo Bounding::typeInfo(&Pane::typeInfo);
    }
}