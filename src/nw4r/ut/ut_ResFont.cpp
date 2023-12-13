#pragma ipa file // TODO: REMOVE AFTER REFACTOR

#include <nw4r/ut.h>

#define MAGIC_RESFONT 'RFNT'
#define MAGIC_RESFONT_UNPACKED 'RFNU'

#define MAGIC_BLK_FONTINFO 'FINF'
#define MAGIC_BLK_TEXGLYPH 'TGLP'
#define MAGIC_BLK_CHARWIDTH 'CWDH'
#define MAGIC_BLK_CHARMAP 'CMAP'
#define MAGIC_BLK_GLGR 'GLGR'

namespace nw4r {
namespace ut {
namespace {

template <typename T> void ResolveOffset(T*& ptr, void* base) {
    ptr = reinterpret_cast<T*>(static_cast<char*>(base) +
                               reinterpret_cast<std::ptrdiff_t>(ptr));
}

} // namespace

ResFont::ResFont() {}

ResFont::~ResFont() {}

bool ResFont::SetResource(void* buffer) {
    BinaryFileHeader* header = static_cast<BinaryFileHeader*>(buffer);
    FontInformation* info = NULL;

    if (!IsManaging(NULL)) {
        return false;
    }

    if (header->magic == MAGIC_RESFONT_UNPACKED) {
        BinaryBlockHeader* block = reinterpret_cast<BinaryBlockHeader*>(
            reinterpret_cast<char*>(header) + header->headerSize);

        for (int i = 0; i < header->numBlocks; i++) {
            if (block->magic == MAGIC_BLK_FONTINFO) {
                info = reinterpret_cast<FontInformation*>(block + 1);
                break;
            }

            block = reinterpret_cast<BinaryBlockHeader*>(
                reinterpret_cast<char*>(block) + block->length);
        }
    } else {
        if (header->version == NW4R_VERSION(1, 04)) {
            if (!IsValidBinaryFile(header, MAGIC_RESFONT, NW4R_VERSION(1, 04),
                                   2)) {
                return false;
            }
        } else if (!IsValidBinaryFile(header, MAGIC_RESFONT,
                                      NW4R_VERSION(1, 02), 2)) {
            return false;
        }

        info = Rebuild(header);
    }

    if (info == NULL) {
        return false;
    }

    SetResourceBuffer(header, info);
    InitReaderFunc(GetEncoding());

    return true;
}

FontInformation* ResFont::Rebuild(BinaryFileHeader* header) {
    BinaryBlockHeader* block = reinterpret_cast<BinaryBlockHeader*>(
        reinterpret_cast<char*>(header) + header->headerSize);
    FontInformation* info = NULL;

    for (int i = 0; i < header->numBlocks; i++) {
        switch (block->magic) {
        case MAGIC_BLK_FONTINFO:
            info = reinterpret_cast<FontInformation*>(block + 1);
            ResolveOffset<FontTextureGlyph>(info->fontGlyph, header);

            if (info->fontWidth != 0) {
                ResolveOffset<FontWidth>(info->fontWidth, header);
            }

            if (info->fontMap != 0) {
                ResolveOffset<FontCodeMap>(info->fontMap, header);
            }
            break;
        case MAGIC_BLK_TEXGLYPH:
            ResolveOffset<u8>(
                reinterpret_cast<FontTextureGlyph*>(block + 1)->sheetImage,
                header);
            break;
        case MAGIC_BLK_CHARWIDTH:
            FontWidth* width = reinterpret_cast<FontWidth*>(block + 1);
            if (width->next != 0) {
                ResolveOffset<FontWidth>(width->next, header);
            }
            break;
        case MAGIC_BLK_CHARMAP:
            FontCodeMap* map = reinterpret_cast<FontCodeMap*>(block + 1);
            if (map->next != 0) {
                ResolveOffset<FontCodeMap>(map->next, header);
            }
            break;
        case MAGIC_BLK_GLGR:
            break;
        default:
            return NULL;
        }

        block = reinterpret_cast<BinaryBlockHeader*>(
            reinterpret_cast<char*>(block) + block->length);
    }

    header->magic = MAGIC_RESFONT_UNPACKED;
    return info;
}

} // namespace ut
} // namespace nw4r
