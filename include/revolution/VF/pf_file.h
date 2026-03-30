#ifndef RVL_SDK_VF_PF_FILE_H
#define RVL_SDK_VF_PF_FILE_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

u32 VFiPFFILE_Cursor_AdvanceToRead(struct PF_FILE* p_file, u32 n, u32 sector);
s32 VFiPFFILE_Cursor_ReadHeadSector(struct PF_VOLUME* p_vol, struct PF_FILE* p_file, u8* p_buf, u32 size, u32* p_size_read);
s32 VFiPFFILE_Cursor_ReadBodySectors(struct PF_VOLUME* p_vol, struct PF_FILE* p_file, u8* p_buf, u32 size, u32* p_size_read);
s32 VFiPFFILE_Cursor_ReadTailSector(struct PF_VOLUME* p_vol, struct PF_FILE* p_file, u8* p_buf, u32 size, u32* p_size_read);
s32 VFiPFFILE_Cursor_Read(struct PF_FILE* p_file, u8* p_buf, u32 size, u32* p_size_read);
s32 VFiPFFILE_Cursor_WriteHeadSector(struct PF_VOLUME* p_vol, struct PF_FILE* p_file, u8* p_buf, u32 size, u32* p_size_write);
s32 VFiPFFILE_Cursor_WriteTailSector(struct PF_VOLUME* p_vol, struct PF_FILE* p_file, u8* p_buf, u32 size, u32 append_size, u32* p_size_write);
s32 VFiPFFILE_Cursor_Write_Overwrite(struct PF_VOLUME* p_vol, struct PF_FILE* p_file, u8* p_buf, u32 size, u32* p_size_write);
s32 VFiPFFILE_Cursor_Write(struct PF_FILE* p_file, u8* p_buf, u32 size, u32* p_size_write);
void VFiPFFILE_Cursor_MoveToClusterEnd(struct PF_FILE* p_file, u32 size);
struct PF_SFD* VFiPFFILE_GetSFD(struct PF_VOLUME* p_vol, struct PF_DIR_ENT* p_ent);
s32 VFiPFFILE_createEmptyFile(struct PF_VOLUME* p_vol, struct PF_DIR_ENT* p_file_ent, struct PF_STR* p_filename, u32 namelength);
s32 VFiPFFILE_p_fopen(struct PF_VOLUME* p_vol, struct PF_STR* p_path_str, s32 mode, struct PF_FILE** pp_file);
s32 VFiPFFILE_p_fread(struct PF_VOLUME* p_vol, u8* p_buf, u32 size, u32 count, struct PF_FILE* p_file, u32* p_count_read);
s32 VFiPFFILE_p_fwrite(struct PF_VOLUME* p_vol, u8* p_buf, u32 size, u32 count, struct PF_FILE* p_file, u32* p_count_written);
s32 VFiPFFILE_p_finfo(struct PF_FILE* p_file, struct PF_INFO* p_info);
s32 VFiPFFILE_GetOpenedFile(struct PF_DIR_ENT* p_ent, struct PF_DIR_ENT** pp_open_ent);
void VFiPFFILE_FinalizeAllFiles(struct PF_VOLUME* p_vol);
s32 VFiPFFILE_remove(struct PF_STR* p_path_str);
s32 VFiPFFILE_fopen(struct PF_STR* p_path_str, s32 mode, struct PF_FILE** pp_file);
s32 VFiPFFILE_fclose(struct PF_FILE* p_file);
s32 VFiPFFILE_fread(u8* p_buf, u32 size, u32 count, struct PF_FILE* p_file, u32* p_count_read);
s32 VFiPFFILE_fwrite(u8* p_buf, u32 size, u32 count, struct PF_FILE* p_file, u32* p_count_written);
s32 VFiPFFILE_fseek(struct PF_FILE* p_file, s32 lOffset, s32 nOrigin);
s32 VFiPFFILE_finfo(struct PF_FILE* p_file, struct PF_INFO* p_info);

#ifdef __cplusplus
}
#endif
#endif
