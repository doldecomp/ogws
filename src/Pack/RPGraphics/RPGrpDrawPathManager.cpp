#include <Pack/RPGraphics.h>

RPGrpDrawPathManager*
RPGrpDrawPathManager::Construct(u32 pathFlags, RPGrpModelScene* pModelScene) {

    return new RPGrpDrawPathManager(pathFlags, pModelScene);
}

template <>
RPGrpDrawPathShadowTexture*
RPGrpDrawPath::Construct<RPGrpDrawPathShadowTexture>(
    EGG::ScnRenderer* pRenderer) {

    return new RPGrpDrawPathShadowTexture(pRenderer);
}

template <>
RPGrpDrawPathLightMap*
RPGrpDrawPath::Construct<RPGrpDrawPathLightMap>(EGG::ScnRenderer* pRenderer) {

    return new RPGrpDrawPathLightMap(pRenderer);
}

template <>
RPGrpDrawPathXluSnap*
RPGrpDrawPath::Construct<RPGrpDrawPathXluSnap>(EGG::ScnRenderer* pRenderer) {

    return new RPGrpDrawPathXluSnap(pRenderer);
}

template <>
RPGrpDrawPathBloom*
RPGrpDrawPath::Construct<RPGrpDrawPathBloom>(EGG::ScnRenderer* pRenderer) {

    return new RPGrpDrawPathBloom(pRenderer);
}

template <>
RPGrpDrawPathDOF*
RPGrpDrawPath::Construct<RPGrpDrawPathDOF>(EGG::ScnRenderer* pRenderer) {

    return new RPGrpDrawPathDOF(pRenderer);
}

template <>
RPGrpDrawPathHDR*
RPGrpDrawPath::Construct<RPGrpDrawPathHDR>(EGG::ScnRenderer* pRenderer) {

    return new RPGrpDrawPathHDR(pRenderer);
}

template <>
RPGrpDrawPathSV*
RPGrpDrawPath::Construct<RPGrpDrawPathSV>(EGG::ScnRenderer* pRenderer) {

    return new RPGrpDrawPathSV(pRenderer);
}

// RPGrpDrawPathManager::RPGrpDrawPathManager(u32 pathFlags,
//                                            RPGrpModelScene* pModelScene)
//     : unkC(1),
//       mpModelScene(pModelScene),
//       unk14(0),
//       mpDrawPathLightMap(NULL),
//       mpDrawPathShadowTexture(NULL),
//       mpDrawPathXluSnap(NULL),
//       mpDrawPathSV(NULL),
//       mpDrawPathHDR(NULL),
//       mpDrawPathBloom(NULL),
//       mpDrawPathDOF(NULL) {

//     if (pathFlags & EFlag_DrawPathSV) {
//         mpDrawPathSV = RPGrpDrawPath::Construct<RPGrpDrawPathSV>()
//     }
// }
