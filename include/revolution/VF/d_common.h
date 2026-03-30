#ifndef RVL_SDK_VF_D_COMMON_H
#define RVL_SDK_VF_D_COMMON_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

void dCommon_DevideBuff32(void* i_buf, u32 i_size, u32* i_1st_size_p, void* i_2nd_pp, u32* i_2nd_size_p, void* i_3rd_pp, u32* i_3rd_size_p);
int dCommon_IsPrfFile(void* i_buff_p);
void dCommon_PrintSignature(struct PR_BINHEADER* i_header_p);
s32 dCommon_MakeFsInfoSec(u8* buf, u32 fsInfoSize);
u32 dCommon_GetPhysicalOffset(u32 startBlock, u32 BPS, u32 reservedSecNum);
enum FatType dCommon_GetNiceFatType(u32* spf, u32 SPU, u32 SPC, u32 BPS);
u32 dCommon_GetReservedSecFromFatType(enum FatType fatType);
u32 dCommon_GetRootEntNumFromFatType(enum FatType fatType);
void dCommon_MakeBootSector(u8* buf, enum FatType* type, u32 SPU, u32 SPC, u32 BPS, u8 jump0_1, u8 jump2, u32 secPerTrack, u32 reservedSecNum, u32 rootEntNum, u8 mediaDesc);
int dCommon_ReadDummyBPB(u32 num_blocks, u8* buf, u32 block, u32* p_num_success, struct PDM_DISK* p_disk, s32* p_err, s32 (*makeBS)(struct PDM_DISK*, u8*, enum FatType*), s32 (*makeFS)(u8*));
int dCommon_WriteDummyBPB(u32 num_blocks, u32 block, u32* p_num_success, struct PDM_DISK* p_disk, s32* p_err);
void dCommon_initDriveInfo();
u32 dCommon_getFileSizeFromDisk(struct PDM_DISK* p_disk);
void dCommon_setFileSizeToDisk(struct PDM_DISK* p_disk, u32 i_fileSize);
s32 dCommon_getLastDeviceErrorFromDisk(struct PDM_DISK* p_disk);
void dCommon_setLastDeviceErrorToDisk(struct PDM_DISK* p_disk, s32 i_lastDevErr);
void dCommon_setLastDeviceErrorToDisk2(s32 i_handleIdx, s32 i_lastDevErr);
s32 dCommon_getHandleIdxFromDisk(struct PDM_DISK* p_disk);
void dCommon_setFatTypeToDisk(struct PDM_DISK* p_disk, u32 i_fatType);
u32 dCommon_getResvSecNumFromDisk(struct PDM_DISK* p_disk);
void dCommon_setResvSecNumToDisk(struct PDM_DISK* p_disk, u32 i_reservedSecNum);
u32 dCommon_getRootEntNumFromDisk(struct PDM_DISK* p_disk);
void dCommon_setRootEntNumToDisk(struct PDM_DISK* p_disk, u32 i_rootEntNum);
s32 dCommon_flush_from_handle_p(struct VF_HANDLE_TYPE* i_handle_p, int i_setLastDeviceError);

#ifdef __cplusplus
}
#endif
#endif
