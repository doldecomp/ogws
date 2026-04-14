#include <Pack/RPGraphics.h>

#include <egg/gfxe.h>

RPGrpTexture::RPGrpTexture(const EGG::ResTIMG* pRes) {
    EGG::GXUtility::getTexObj(&mGXTexObj, *pRes);
}

RPGrpTexture::RPGrpTexture(RPGrpHandle handle, const char* pName) {
    nw4r::g3d::ResFile file =
        RPGrpModelResManager::GetCurrent()
            ->GetData<RPGrpModelResManager::Type_ResFile>(handle);

    EGG::GXUtility::getTexObj(&mGXTexObj, file.GetResTex(pName), GX_CLAMP,
                              GX_CLAMP, GX_LINEAR, GX_LINEAR);
}
