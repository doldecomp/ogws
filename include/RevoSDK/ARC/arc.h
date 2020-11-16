#ifndef REVOSDK_ARC_H
#define REVOSDK_ARC_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

// based on WiiCore
enum ARCType
{
  //! The entry is a file.
  //! Accessed via rxArchiveFile with rxArchiveFileOpen/rxArchiveFileOpenLow
  //!
  RX_ARCHIVE_FILE,

  //! The entry is a folder.
  //!
  RX_ARCHIVE_FOLDER
};

struct ARCHandle
{
  const struct ARCHeader* mHeader; //!< 00 Pointer to the archive header.
  const struct ARCNode* mNodes; //!< 04 Array of nodes for each archive entry.
  const u8* mFileData;         //!< 08 File data buffer, accessed by nodes.
  u32 mCount;                  //!< 0C Number of nodes in the archive.
  const char* mStrings;        //!< 10 String buffer, accessed by nodes.
  u32 mFstSize;                //!< 14 Total bytesize of nodes and strings.
  u32 mCurrentPath;            //!< 18 The current directory of the archive.
};

struct ARCFile
{
  struct ARCHandle* parent; //!< 00 The archive the file is a part of.
  u32 offset;        //!< 04 Offset into the archive's file data buffer.
  u32 size;          //!< 08 Size of the file.
};

struct ARCEntry
{
  struct ARCHandle* parent;       //!< 00 The archive the file is a part of.
  u32 path;                //!< 04 Special ID corresponding to a file path.
                           //!< Accepted by rxArchiveFileOpenLow.
  enum ARCType node_type; //!< The entry type.
  const char* name;        //!< 0C Name of this entry in specific.
                           //!< (Not an absolute path)
};

struct ARCDir
{
  struct ARCHandle* parent; //!< 00 The archive the file is a part of.
  u32 path_begin;    //!< 04 The lower bound of the iterator range.
  u32 path_it;       //!< 08 The current position of the iterator.
  u32 path_end;      //!< 0C The upper bound of the iterator range.
};

struct ARCNode {
  union {
    struct {
      u32 is_folder : 8;
      u32 name : 24;
    };
    u32 packed_type_name;
  };
  union {
    struct {
      u32 offset;
      u32 size;
    } file;
    struct {
      u32 parent;
      u32 sibling_next;
    } folder;
  };
};

struct ARCHeader {
  u32 magic; // 00
  struct {
    s32 offset; // 04
    s32 size;   // 08
  } nodes;
  struct {
    s32 offset; // 0C
  } files;

  u8 _10[0x10];
};

BOOL ARCInitHandle(void *, struct ARCHandle *);
BOOL ARCOpen(const struct ARCHandle *, const char *, struct ARCFile *);
BOOL ARCFastOpen(const struct ARCHandle *, s32, struct ARCFile *);
s32 ARCConvertPathToEntrynum(struct ARCHandle *, const char *);
void * ARCGetStartAddrInMem(const struct ARCFile *);
s32 ARCGetStartOffset(const struct ARCFile *);
u32 ARCGetLength(const struct ARCFile *);
BOOL ARCClose(struct ARCFile *);
BOOL ARCChangeDir(struct ARCHandle *, const char *);
BOOL ARCOpenDir(const struct ARCHandle *, const char *, struct ARCDir *);
BOOL ARCReadDir(struct ARCDir *, struct ARCEntry *);
BOOL ARCCloseDir(struct ARCDir *);

#ifdef __cplusplus
}
#endif
#endif