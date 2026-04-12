#include <Pack/RPGraphics.h>

#include <nw4r/g3d.h>

RPGrpProjectionObject::RPGrpProjectionObject(u8 viewNo) : mViewNo(viewNo) {
    mCamera.Identity();
    mCamera.SetCameraType(RPGrpCamera::ECameraType_Anm);
}

void RPGrpProjectionObject::Calc(nw4r::g3d::Camera cam) {
    mCamera.CalcMatrix();
    mCamera.SaveCameraMatrix();

    cam.SetCameraMtxDirectly(mCamera.GetSavedCameraMatrix());
    mScreen.CopyToG3D(cam);
}

void RPGrpProjectionObject::LoadScnCamera(RPGrpHandle handle, const char* pName,
                                          f32 frame) {
    const nw4r::g3d::ResAnmScn scn =
        RPGrpModelResManager::GetCurrent()
            ->GetData<RPGrpModelResManager::Type_ResAnmScn>(handle, pName);

    mCamera.LoadScnCameraMatrix(scn, mViewNo, frame);
    mScreen.LoadScnCamera(scn, mViewNo, frame);
}
