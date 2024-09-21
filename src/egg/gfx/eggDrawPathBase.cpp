#pragma ipa file
#include "eggDrawPathBase.h"
#include "eggGXUtility.h"

namespace EGG
{
    DrawPathBase::DrawPathBase()
    {
    }

    void DrawPathBase::CopyGlobalScreen()
    {
        if (isVisible())
        {
            copyFromAnother(GXUtility::getScreen());
            calc();
        }
    }

    void DrawPathBase::calc()
    {
    }

    void DrawPathBase::calc_after_CalcWorld()
    {
    }
}
