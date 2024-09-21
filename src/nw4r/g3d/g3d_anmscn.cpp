#include "g3d_anmscn.h"
#include <algorithm>

namespace nw4r
{
    namespace g3d
    {
        // https://decomp.me/scratch/FjaQH
        void AnmScn::GetLightSetting(LightSetting *pSetting)
        {
            u32 myNumLightSet = GetLightSetMaxRefNumber();
            u32 myNumAmb = GetAmbLightMaxRefNumber();
            u32 myNumDiffuse = GetDiffuseLightMaxRefNumber();
           
            if (myNumLightSet > 0)
            {
                u32 capacity = pSetting->GetNumLightSet();
                u32 numLightSet = std::min(myNumLightSet, capacity);

                for (u32 i = 0; i < numLightSet; i++)
                {
                    GetLightSet(pSetting->GetLightSet(i), i);
                }
            }

            if (myNumAmb > 0)
            {
                AmbLightObj *ambLights = pSetting->GetAmbLightObjArray();
                u32 capacity = pSetting->GetNumLightObj();
                u32 numAmb = std::min(myNumAmb, capacity);

                for (u32 i = 0; i < numAmb; i++)
                {
                    AmbLightObj *obj = &ambLights[i];
                    *(u32 *)&obj->r = GetAmbLightColor(i);
                }
            }

            if (myNumDiffuse > 0)
            {
                LightObj *lights = pSetting->GetLightObjArray();
                u32 capacity = pSetting->GetNumLightObj();
                u32 myNumAll = myNumDiffuse + GetNumSpecularLight();
                u32 numDiffuse = std::min(myNumDiffuse, capacity);
                u32 numAll = std::min(myNumAll, capacity);

                for (u32 i = 0; i < numDiffuse; i++)
                {
                    lights[i].Disable();
                }

                for (u32 i = 0; i < numDiffuse; i++)
                {
                    LightObj *diff = &lights[i];
                    LightObj *spec = NULL;
                    
                    if (!diff->IsEnable())
                    {
                        if (HasSpecularLight(i))
                        {
                            u32 id = GetSpecularLightID(i);
                            if (id < numAll) spec = &lights[id];
                        }

                        GetLight(diff, spec, i);
                    }
                }
            }
        }
    }
}
