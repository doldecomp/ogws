#include <string.h>
#include "g3d_resdict.h"

namespace nw4r
{
    namespace g3d
    {
        const ResDicEntry * ResDic::Get(ResName rn) const
        {
            u32 len = rn.GetLength();
            const char *name = rn.GetName();
            const ResDicData &dict = this->mDict.ref();
            const ResDicEntry *r5 = &dict.mEntries[0];
            const ResDicEntry *r31 = &dict.mEntries[r5->unk_index];

            while (r5->INT_0x0 > r31->INT_0x0)
            {
                r5 = r31;

                u32 val = r31->INT_0x0 & 7;
                
                if (r31->INT_0x0 >> 3 < len && (name[r31->INT_0x0 >> 3] >> val) & 1)
                {
                    r31 = mDict.ref().mEntries + r31->unk_index2;
                }
                else
                {
                    r31 = mDict.ref().mEntries + r31->unk_index;
                }
            }

            const void *resPtr = (const char *)mDict.ptr() + r31->INT_0x8 - 4;
            
            if (rn == ResName(resPtr))
            {
                return r31;
            }

            return NULL;
        }

        const ResDicEntry * ResDic::Get(const char* name, u32 len) const
        {
            const ResDicData &dict = this->mDict.ref();
            const ResDicEntry *r7 = &dict.mEntries[0];
            const ResDicEntry *r31 = &dict.mEntries[r7->unk_index];

            while (r7->INT_0x0 > r31->INT_0x0)
            {
                r7 = r31;

                u32 val = r31->INT_0x0 & 7;
                
                if ((r31->INT_0x0 >> 3 < len) && (name[r31->INT_0x0 >> 3] >> val) & 1)
                {
                    r31 = mDict.ref().mEntries + r31->unk_index2;
                }
                else
                {
                    r31 = mDict.ref().mEntries + r31->unk_index;
                }
            }

            if (r31->INT_0x8)
            {
				const char *cmp = r31->INT_0x8 ? (const char *)mDict.ptr() + r31->INT_0x8 : NULL;
                
                if (strcmp(name, cmp) == 0) return r31;
            }

            return NULL;
        }

        const void * ResDic::operator[](const char *key) const
        {
            if (mDict.IsValid() && key)
            {
                const ResDicEntry *entry = Get(key, strlen(key));
                
				if (entry) return mDict.ofs_to_ptr_raw<void>(entry->INT_0xC);
            }

            return NULL;
        }

        const void * ResDic::operator[](ResName rn) const
        {
			if (mDict.IsValid() && rn.mRes.IsValid())
            {
				const ResDicEntry *entry = Get(rn.mRes.ptr());
                
				if (entry) return mDict.ofs_to_ptr_raw<void>(entry->INT_0xC);
            }
			
            return NULL;
        }
		
		s32 ResDic::GetIndex(ResName rn) const
        {
            if (mDict.IsValid() && rn.mRes.IsValid())
            {
                const ResDicEntry *entry = Get(rn.mRes.ptr());
				
                if (entry) return entry - (mDict.ref().mEntries + 1);
            }

            return -1;
        }
    }
}