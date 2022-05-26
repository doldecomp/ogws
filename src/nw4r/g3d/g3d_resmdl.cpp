#pragma ipa file

#include "g3d_resmdl.h"
#include "g3d_resdict.h"
#include "g3d_resvtx.h"
#include "g3d_resmat.h"
#include "g3d_resshp.h"
#include "g3d_resfile.h"

namespace nw4r
{
    namespace g3d
    {
        u8 * ResMdl::GetResByteCode(const char *pName) const
        {
            ResMdlData& ref = mMdl.ref();
            return static_cast<u8 *>(mMdl.ofs_to_obj<ResDic>(ref.mByteCodeDictOfs)[pName]);
        }

        ResNode ResMdl::GetResNode(const char *pName) const
        {
            ResMdlData& ref = mMdl.ref();
            return mMdl.ofs_to_obj<ResDic>(ref.mNodeDictOfs)[pName];
        }

        ResNode ResMdl::GetResNode(ResName rn) const
        {
            ResMdlData& ref = mMdl.ref();
            return mMdl.ofs_to_obj<ResDic>(ref.mNodeDictOfs)[rn];
        }

        ResNode ResMdl::GetResNode(int i) const
        {
            ResMdlData& ref = mMdl.ref();
            return mMdl.ofs_to_obj<ResDic>(ref.mNodeDictOfs)[i];
        }

        ResNode ResMdl::GetResNode(u32 i) const
        {
            ResMdlData& ref = mMdl.ref();
            return mMdl.ofs_to_obj<ResDic>(ref.mNodeDictOfs)[i];
        }

        u32 ResMdl::GetResNodeNumEntries() const
        {
            ResMdlData& ref = mMdl.ref();
            return mMdl.ofs_to_obj<ResDic>(ref.mNodeDictOfs).GetNumData();
        }

        ResVtxPos ResMdl::GetResVtxPos(ResName rn) const
        {
            ResMdlData& ref = mMdl.ref();
            return mMdl.ofs_to_obj<ResDic>(ref.mVtxPosDictOfs)[rn];
        }

        ResVtxPos ResMdl::GetResVtxPos(int i) const
        {
            ResMdlData& ref = mMdl.ref();
            return mMdl.ofs_to_obj<ResDic>(ref.mVtxPosDictOfs)[i];
        }

        ResVtxPos ResMdl::GetResVtxPos(u32 i) const
        {
            ResMdlData& ref = mMdl.ref();
            return mMdl.ofs_to_obj<ResDic>(ref.mVtxPosDictOfs)[i];
        }

        u32 ResMdl::GetResVtxPosNumEntries() const
        {
            ResMdlData& ref = mMdl.ref();
            return mMdl.ofs_to_obj<ResDic>(ref.mVtxPosDictOfs).GetNumData();
        }

        ResVtxNrm ResMdl::GetResVtxNrm(ResName rn) const
        {
            ResMdlData& ref = mMdl.ref();
            return mMdl.ofs_to_obj<ResDic>(ref.mVtxNrmDictOfs)[rn];
        }

        ResVtxNrm ResMdl::GetResVtxNrm(int i) const
        {
            ResMdlData& ref = mMdl.ref();
            return mMdl.ofs_to_obj<ResDic>(ref.mVtxNrmDictOfs)[i];
        }

        ResVtxNrm ResMdl::GetResVtxNrm(u32 i) const
        {
            ResMdlData& ref = mMdl.ref();
            return mMdl.ofs_to_obj<ResDic>(ref.mVtxNrmDictOfs)[i];
        }

        u32 ResMdl::GetResVtxNrmNumEntries() const
        {
            ResMdlData& ref = mMdl.ref();
            return mMdl.ofs_to_obj<ResDic>(ref.mVtxNrmDictOfs).GetNumData();
        }

        ResVtxClr ResMdl::GetResVtxClr(ResName rn) const
        {
            ResMdlData& ref = mMdl.ref();
            return mMdl.ofs_to_obj<ResDic>(ref.mVtxClrDictOfs)[rn];
        }

        ResVtxClr ResMdl::GetResVtxClr(int i) const
        {
            ResMdlData& ref = mMdl.ref();
            return mMdl.ofs_to_obj<ResDic>(ref.mVtxClrDictOfs)[i];
        }

        ResVtxClr ResMdl::GetResVtxClr(u32 i) const
        {
            ResMdlData& ref = mMdl.ref();
            return mMdl.ofs_to_obj<ResDic>(ref.mVtxClrDictOfs)[i];
        }

        u32 ResMdl::GetResVtxClrNumEntries() const
        {
            ResMdlData& ref = mMdl.ref();
            return mMdl.ofs_to_obj<ResDic>(ref.mVtxClrDictOfs).GetNumData();
        }

        ResVtxTexCoord ResMdl::GetResVtxTexCoord(int i) const
        {
            ResMdlData& ref = mMdl.ref();
            return mMdl.ofs_to_obj<ResDic>(ref.mVtxTexCoordDictOfs)[i];
        }

        ResMat ResMdl::GetResMat(const char *pName) const
        {
            ResMdlData& ref = mMdl.ref();
            return mMdl.ofs_to_obj<ResDic>(ref.mMatDictOfs)[pName];
        }

        ResMat ResMdl::GetResMat(ResName rn) const
        {
            ResMdlData& ref = mMdl.ref();
            return mMdl.ofs_to_obj<ResDic>(ref.mMatDictOfs)[rn];
        }

        ResMat ResMdl::GetResMat(int i) const
        {
            ResMdlData& ref = mMdl.ref();
            return mMdl.ofs_to_obj<ResDic>(ref.mMatDictOfs)[i];
        }

        ResMat ResMdl::GetResMat(u32 i) const
        {
            ResMdlData& ref = mMdl.ref();
            return mMdl.ofs_to_obj<ResDic>(ref.mMatDictOfs)[i];
        }

        u32 ResMdl::GetResMatNumEntries() const
        {
            ResMdlData& ref = mMdl.ref();
            return mMdl.ofs_to_obj<ResDic>(ref.mMatDictOfs).GetNumData();
        }

        ResShp ResMdl::GetResShp(const char *pName) const
        {
            ResMdlData& ref = mMdl.ref();
            return mMdl.ofs_to_obj<ResDic>(ref.mShpDictOfs)[pName];
        }

        ResShp ResMdl::GetResShp(int i) const
        {
            ResMdlData& ref = mMdl.ref();
            return mMdl.ofs_to_obj<ResDic>(ref.mShpDictOfs)[i];
        }

        ResShp ResMdl::GetResShp(u32 i) const
        {
            ResMdlData& ref = mMdl.ref();
            return mMdl.ofs_to_obj<ResDic>(ref.mShpDictOfs)[i];
        }

        u32 ResMdl::GetResShpNumEntries() const
        {
            ResMdlData& ref = mMdl.ref();
            return mMdl.ofs_to_obj<ResDic>(ref.mShpDictOfs).GetNumData();
        }

        ResTexPlttInfo ResMdl::GetResTexPlttInfoOffsetFromTexName(int i) const
        {
            ResMdlData& ref = mMdl.ref();
            return mMdl.ofs_to_obj<ResDic>(ref.mPlttTexInfoOfs)[i];
        }

        u32 ResMdl::GetResTexPlttInfoOffsetFromTexNameNumEntries() const
        {
            ResMdlData& ref = mMdl.ref();
            return mMdl.ofs_to_obj<ResDic>(ref.mPlttTexInfoOfs).GetNumData();
        }

        bool ResMdl::Bind(ResFile rf)
        {
            u32 i;
            bool b = true;

            u32 numMat = GetResMatNumEntries();
            for (i = 0; i < numMat; i++)
            {
                b = GetResMat(i).Bind(rf) && b;
            }

            return b;
        }

        void ResMdl::Release()
        {
            u32 i;
            u32 numMat = GetResMatNumEntries();
            for (i = 0; i < numMat; i++)
            {
                GetResMat(i).Release();
            }
        }
        
        void ResMdl::Init()
        {
            u32 i;

            u32 numMat = GetResMatNumEntries();
            for (i = 0; i < numMat; i++)
            {
                GetResMat(i).Init();
            }

            u32 numShp = GetResShpNumEntries();
            for (i = 0; i < numShp; i++)
            {
                GetResShp(i).Init();
            }

            u32 numVtxPos = GetResVtxPosNumEntries();
            for (i = 0; i < numVtxPos; i++)
            {
                GetResVtxPos(i).Init();
            }

            u32 numVtxNum = GetResVtxNrmNumEntries();
            for (i = 0; i < numVtxNum; i++)
            {
                GetResVtxNrm(i).Init();
            }

            u32 numVtxClr = GetResVtxClrNumEntries();
            for (i = 0; i < numVtxClr; i++)
            {
                GetResVtxClr(i).Init();
            }

            u32 numVtxTex = GetResVtxTexCoordNumEntries();
            for (i = 0; i < numVtxTex; i++)
            {
                GetResVtxTexCoord(i).Init();
            }
        }

        void ResMdl::Terminate()
        {
            u32 i;
            u32 numShp = GetResShpNumEntries();
            for (i = 0; i < numShp; i++)
            {
                GetResShp(i).Terminate();
            }
        }
    }
}