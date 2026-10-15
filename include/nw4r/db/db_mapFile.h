#ifndef NW4R_DB_MAP_FILE_H
#define NW4R_DB_MAP_FILE_H

#include <nw4r/types_nw4r.h>

#include <revolution/OS.h>

namespace nw4r {
namespace db {

struct MapFile {
    u8* mapBuf;                     // at 0x0
    const OSModuleInfo* moduleInfo; // at 0x4
    s32 fileEntry;                  // at 0x8
    MapFile* next;                  // at 0xC
};

MapFile* MapFile_RegistOnMem(void* pMapWork, u8* pMapData, u32 fileSize,
                             const OSModuleInfo* pModuleInfo);
MapFile* MapFile_RegistOnDvd(void* pMapWork, const char* pPath,
                             const OSModuleInfo* pModuleInfo);

void MapFile_Unregist(MapFile* pMapFile);
void MapFile_UnregistAll();

bool MapFile_Exists();
bool MapFile_QuerySymbol(u32 address, u8* pBuffer, u32 maxlen);

} // namespace db
} // namespace nw4r

#endif
