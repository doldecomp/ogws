#pragma ipa file
#pragma opt_loop_invariants off
#pragma opt_propagation off
#pragma opt_lifetimes off
#pragma opt_strength_reduction off
#include "g3d_resfile.h"
#include "g3d_resmdl.h"
#include "g3d_restex.h"
#include "g3d_resanmchr.h"
#include "g3d_resanmvis.h"
#include "g3d_resanmclr.h"
#include "g3d_resanmtexpat.h"
#include "g3d_resanmtexsrt.h"
#include "g3d_resanmshp.h"
#include "g3d_resanmscn.h"

namespace nw4r
{
	namespace g3d
	{
		namespace
		{
			NW4R_G3D_CREATE_RES_NAME_DATA(Models, "3DModels(NW4R)");
			NW4R_G3D_CREATE_RES_NAME_DATA(Pltts, "Palettes(NW4R)");
			NW4R_G3D_CREATE_RES_NAME_DATA(Textures, "Textures(NW4R)");
			NW4R_G3D_CREATE_RES_NAME_DATA(AnmChr, "AnmChr(NW4R)");
			NW4R_G3D_CREATE_RES_NAME_DATA(AnmVis, "AnmVis(NW4R)");
			NW4R_G3D_CREATE_RES_NAME_DATA(AnmClr, "AnmClr(NW4R)");
			NW4R_G3D_CREATE_RES_NAME_DATA(AnmTexPat, "AnmTexPat(NW4R)");
			NW4R_G3D_CREATE_RES_NAME_DATA(AnmTexSrt, "AnmTexSrt(NW4R)");
			NW4R_G3D_CREATE_RES_NAME_DATA(AnmShp, "AnmShp(NW4R)");
			NW4R_G3D_CREATE_RES_NAME_DATA(AnmScn, "AnmScn(NW4R)");
			NW4R_G3D_CREATE_RES_NAME_DATA(Ext, "External");
		}
		
		ResMdl ResFile::GetResMdl(const char * pName) const
		{
			void * pMdlDicData = ResDic(&ref().mRootData)[&ResNameData_Models];
			
			if (pMdlDicData) return ResDic(pMdlDicData)[pName];
			
			return NULL;
		}
		
		ResMdl ResFile::GetResMdl(int i) const
		{
			void * pMdlDicData = ResDic(&ref().mRootData)[&ResNameData_Models];
			
			if (pMdlDicData) return ResDic(pMdlDicData)[i];
			
			return NULL;
		}
		
		ResMdl ResFile::GetResMdl(u32 i) const
		{
			return GetResMdl((int)i);
		}
		
		ResPltt ResFile::GetResPltt(const char * pName) const
		{
			void * pPlttDicData = ResDic(&ref().mRootData)[&ResNameData_Pltts];
			
			if (pPlttDicData) return ResDic(pPlttDicData)[pName];
			
			return NULL;
		}
		
		ResPltt ResFile::GetResPltt(ResName name) const
		{
			void * pPlttDicData = ResDic(&ref().mRootData)[&ResNameData_Pltts];
			
			if (pPlttDicData) return ResDic(pPlttDicData)[name];
			
			return NULL;
		}
		
		ResPltt ResFile::GetResPltt(int i) const
		{
			void * pPlttDicData = ResDic(&ref().mRootData)[&ResNameData_Pltts];
			
			if (pPlttDicData) return ResDic(pPlttDicData)[i];
			
			return NULL;
		}
		
		ResPltt ResFile::GetResPltt(u32 i) const
		{
			return GetResPltt((int)i);
		}
		
		ResTex ResFile::GetResTex(const char * pName) const
		{
			void * pTexDicData = ResDic(&ref().mRootData)[&ResNameData_Textures];
			
			if (pTexDicData) return ResDic(pTexDicData)[pName];
			
			return NULL;
		}
		
		ResTex ResFile::GetResTex(ResName name) const
		{
			void * pTexDicData = ResDic(&ref().mRootData)[&ResNameData_Textures];
			
			if (pTexDicData) return ResDic(pTexDicData)[name];
			
			return NULL;
		}
		
		ResTex ResFile::GetResTex(int i) const
		{
			void * pTexDicData = ResDic(&ref().mRootData)[&ResNameData_Textures];
			
			if (pTexDicData) return ResDic(pTexDicData)[i];
			
			return NULL;
		}
		
		ResTex ResFile::GetResTex(u32 i) const
		{
			return GetResTex((int)i);
		}
		
		ResAnmChr ResFile::GetResAnmChr(const char * pName) const
		{
			void * pAnmChrDicData = ResDic(&ref().mRootData)[&ResNameData_AnmChr];
			
			if (pAnmChrDicData) return ResDic(pAnmChrDicData)[pName];
			
			return NULL;
		}
		
		ResAnmChr ResFile::GetResAnmChr(int i) const
		{
			void * pAnmChrDicData = ResDic(&ref().mRootData)[&ResNameData_AnmChr];
			
			if (pAnmChrDicData) return ResDic(pAnmChrDicData)[i];
			
			return NULL;
		}
		
		ResAnmChr ResFile::GetResAnmChr(u32 i) const
		{
			return GetResAnmChr((int)i);
		}
		
		ResAnmVis ResFile::GetResAnmVis(const char * pName) const
		{
			void * pAnmVisDicData = ResDic(&ref().mRootData)[&ResNameData_AnmVis];
			
			if (pAnmVisDicData) return ResDic(pAnmVisDicData)[pName];
			
			return NULL;
		}
		
		ResAnmVis ResFile::GetResAnmVis(int i) const
		{
			void * pAnmVisDicData = ResDic(&ref().mRootData)[&ResNameData_AnmVis];
			
			if (pAnmVisDicData) return ResDic(pAnmVisDicData)[i];
			
			return NULL;
		}
		
		ResAnmVis ResFile::GetResAnmVis(u32 i) const
		{
			return GetResAnmVis((int)i);
		}
		
		ResAnmClr ResFile::GetResAnmClr(const char * pName) const
		{
			void * pAnmClrDicData = ResDic(&ref().mRootData)[&ResNameData_AnmClr];
			
			if (pAnmClrDicData) return ResDic(pAnmClrDicData)[pName];
			
			return NULL;
		}
		
		ResAnmClr ResFile::GetResAnmClr(int i) const
		{
			void * pAnmClrDicData = ResDic(&ref().mRootData)[&ResNameData_AnmClr];
			
			if (pAnmClrDicData) return ResDic(pAnmClrDicData)[i];
			
			return NULL;
		}
		
		ResAnmClr ResFile::GetResAnmClr(u32 i) const
		{
			return GetResAnmClr((int)i);
		}
		
		ResAnmTexPat ResFile::GetResAnmTexPat(const char * pName) const
		{
			void * pAnmTexPatDicData = ResDic(&ref().mRootData)[&ResNameData_AnmTexPat];
			
			if (pAnmTexPatDicData) return ResDic(pAnmTexPatDicData)[pName];
			
			return NULL;
		}
		
		ResAnmTexPat ResFile::GetResAnmTexPat(int i) const
		{
			void * pAnmTexPatDicData = ResDic(&ref().mRootData)[&ResNameData_AnmTexPat];
			
			if (pAnmTexPatDicData) return ResDic(pAnmTexPatDicData)[i];
			
			return NULL;
		}
		
		ResAnmTexPat ResFile::GetResAnmTexPat(u32 i) const
		{
			return GetResAnmTexPat((int)i);
		}
		
		ResAnmTexSrt ResFile::GetResAnmTexSrt(const char * pName) const
		{
			void * pAnmTexSrtDicData = ResDic(&ref().mRootData)[&ResNameData_AnmTexSrt];
			
			if (pAnmTexSrtDicData) return ResDic(pAnmTexSrtDicData)[pName];
			
			return NULL;
		}
		
		ResAnmTexSrt ResFile::GetResAnmTexSrt(int i) const
		{
			void * pAnmTexSrtDicData = ResDic(&ref().mRootData)[&ResNameData_AnmTexSrt];
			
			if (pAnmTexSrtDicData) return ResDic(pAnmTexSrtDicData)[i];
			
			return NULL;
		}
		
		ResAnmTexSrt ResFile::GetResAnmTexSrt(u32 i) const
		{
			return GetResAnmTexSrt((int)i);
		}
		
		ResAnmShp ResFile::GetResAnmShp(const char * pName) const
		{
			void * pAnmShpDicData = ResDic(&ref().mRootData)[&ResNameData_AnmShp];
			
			if (pAnmShpDicData) return ResDic(pAnmShpDicData)[pName];
			
			return NULL;
		}
		
		ResAnmShp ResFile::GetResAnmShp(int i) const
		{
			void * pAnmShpDicData = ResDic(&ref().mRootData)[&ResNameData_AnmShp];
			
			if (pAnmShpDicData) return ResDic(pAnmShpDicData)[i];
			
			return NULL;
		}
		
		ResAnmShp ResFile::GetResAnmShp(u32 i) const
		{
			return GetResAnmShp((int)i);
		}
		
		ResAnmScn ResFile::GetResAnmScn(const char * pName) const
		{
			void * pAnmScnDicData = ResDic(&ref().mRootData)[&ResNameData_AnmScn];
			
			if (pAnmScnDicData) return ResDic(pAnmScnDicData)[pName];
			
			return NULL;
		}
		
		ResAnmScn ResFile::GetResAnmScn(int i) const
		{
			void * pAnmScnDicData = ResDic(&ref().mRootData)[&ResNameData_AnmScn];
			
			if (pAnmScnDicData) return ResDic(pAnmScnDicData)[i];
			
			return NULL;
		}
		
		ResAnmScn ResFile::GetResAnmScn(u32 i) const
		{
			return GetResAnmScn((int)i);
		}
		
		u32 ResFile::GetResMdlNumEntries() const
		{
			void * pMdlDicData = ResDic(&ref().mRootData)[&ResNameData_Models];
			
			if (pMdlDicData) return ResDic(pMdlDicData).GetNumData();
			
			return 0;
		}
		
		u32 ResFile::GetResPlttNumEntries() const
		{
			void * pPlttDicData = ResDic(&ref().mRootData)[&ResNameData_Pltts];
			
			if (pPlttDicData) return ResDic(pPlttDicData).GetNumData();
			
			return 0;
		}
		
		u32 ResFile::GetResTexNumEntries() const
		{
			void * pTexDicData = ResDic(&ref().mRootData)[&ResNameData_Textures];
			
			if (pTexDicData) return ResDic(pTexDicData).GetNumData();
			
			return 0;
		}
		
		u32 ResFile::GetResAnmChrNumEntries() const
		{
			void * pAnmChrDicData = ResDic(&ref().mRootData)[&ResNameData_AnmChr];
			
			if (pAnmChrDicData) return ResDic(pAnmChrDicData).GetNumData();
			
			return 0;
		}
		
		u32 ResFile::GetResAnmVisNumEntries() const
		{
			void * pAnmVisDicData = ResDic(&ref().mRootData)[&ResNameData_AnmVis];
			
			if (pAnmVisDicData) return ResDic(pAnmVisDicData).GetNumData();
			
			return 0;
		}
		
		u32 ResFile::GetResAnmClrNumEntries() const
		{
			void * pAnmClrDicData = ResDic(&ref().mRootData)[&ResNameData_AnmClr];
			
			if (pAnmClrDicData) return ResDic(pAnmClrDicData).GetNumData();
			
			return 0;
		}
		
		u32 ResFile::GetResAnmTexPatNumEntries() const
		{
			void * pAnmTexPatDicData = ResDic(&ref().mRootData)[&ResNameData_AnmTexPat];
			
			if (pAnmTexPatDicData) return ResDic(pAnmTexPatDicData).GetNumData();
			
			return 0;
		}
		
		u32 ResFile::GetResAnmTexSrtNumEntries() const
		{
			void * pAnmTexSrtDicData = ResDic(&ref().mRootData)[&ResNameData_AnmTexSrt];
			
			if (pAnmTexSrtDicData) return ResDic(pAnmTexSrtDicData).GetNumData();
			
			return 0;
		}
		
		u32 ResFile::GetResAnmShpNumEntries() const
		{
			void * pAnmShpDicData = ResDic(&ref().mRootData)[&ResNameData_AnmShp];
			
			if (pAnmShpDicData) return ResDic(pAnmShpDicData).GetNumData();
			
			return 0;
		}
		
		u32 ResFile::GetResAnmScnNumEntries() const
		{
			void * pAnmScnDicData = ResDic(&ref().mRootData)[&ResNameData_AnmScn];
			
			if (pAnmScnDicData) return ResDic(pAnmScnDicData).GetNumData();
			
			return 0;
		}
		
		bool ResFile::Bind(ResFile file)
		{
			u32 i;
			bool ret = true;
			
			u32 mdlCount = GetResMdlNumEntries();
			
			for (i = 0; i < mdlCount; i++)
			{
				ret = GetResMdl(i).Bind(file) && ret;
			}
			
			u32 anmTexPatCount = GetResAnmTexPatNumEntries();
			
			for (i = 0; i < anmTexPatCount; i++)
			{
				ret = GetResAnmTexPat(i).Bind(file);
			}
			
			return ret;
		}
		
		void ResFile::Release()
		{
			u32 i;
			
			u32 mdlCount = GetResMdlNumEntries();
			
			for (i = 0; i < mdlCount; i++)
			{
				GetResMdl(i).Release();
			}
			
			u32 anmTexPatCount = GetResAnmTexPatNumEntries();
			
			for (i = 0; i < anmTexPatCount; i++)
			{
				GetResAnmTexPat(i).Release();
			}
		}
		
		void ResFile::Init()
		{
			u32 i;
			
			u32 mdlCount = GetResMdlNumEntries();
			
			for (i = 0; i < mdlCount; i++)
			{
				GetResMdl(i).Init();
			}
			
			u32 texCount = GetResTexNumEntries();
			
			for (i = 0; i < texCount; i++)
			{
				GetResTex(i).Init();
			}
			
			u32 plttCount = GetResPlttNumEntries();
			
			for (i = 0; i < plttCount; i++)
			{
				GetResPltt(i).DCStore(false);
			}
		}
		
		void ResFile::Terminate()
		{
			u32 mdlCount = GetResMdlNumEntries();
			
			for (u32 i = 0; i < mdlCount; i++)
			{
				GetResMdl(i).Terminate();
			}
		}
		
		bool ResFile::CheckRevision() const
		{
			u32 i;
			
			u32 mdlCount = GetResMdlNumEntries();
			
			for (i = 0; i < mdlCount; i++)
			{
				if (!GetResMdl(i).CheckRevision()) return false;
			}
			
			u32 texCount = GetResTexNumEntries();
			
			for (i = 0; i < texCount; i++)
			{
				if (!GetResTex(i).CheckRevision()) return false;
			}
			
			u32 plttCount = GetResPlttNumEntries();
			
			for (i = 0; i < plttCount; i++)
			{
				if (!GetResPltt(i).CheckRevision()) return false;
			}
			
			u32 anmChrCount = GetResAnmChrNumEntries();
			
			for (i = 0; i < anmChrCount; i++)
			{
				if (!GetResAnmChr(i).CheckRevision()) return false;
			}
			
			u32 anmVisCount = GetResAnmVisNumEntries();
			
			for (i = 0; i < anmVisCount; i++)
			{
				if (!GetResAnmVis(i).CheckRevision()) return false;
			}
			
			u32 anmClrCount = GetResAnmClrNumEntries();
			
			for (i = 0; i < anmClrCount; i++)
			{
				if (!GetResAnmClr(i).CheckRevision()) return false;
			}
			
			u32 anmTexPatCount = GetResAnmTexPatNumEntries();
			
			for (i = 0; i < anmTexPatCount; i++)
			{
				if (!GetResAnmTexPat(i).CheckRevision()) return false;
			}
			
			u32 anmTexSrtCount = GetResAnmTexSrtNumEntries();
			
			for (i = 0; i < anmTexSrtCount; i++)
			{
				if (!GetResAnmTexSrt(i).CheckRevision()) return false;
			}
			
			u32 anmShpCount = GetResAnmShpNumEntries();
			
			for (i = 0; i < anmShpCount; i++)
			{
				if (!GetResAnmShp(i).CheckRevision()) return false;
			}
			
			u32 anmScnCount = GetResAnmScnNumEntries();
			
			for (i = 0; i < anmScnCount; i++)
			{
				if (!GetResAnmScn(i).CheckRevision()) return false;
			}
			
			return true;
		}
		
		// This is needed in order to instantiate ResNameData_Ext
		void * INSTANTIATE_UNUSED()
		{
			return &ResNameData_Ext;
		}
	}
}