#include <revolution/VF.h>

extern PF_VOLUME_SET VFipf_vol_set;
static u8 FAT_DELETED = 0xE5;

static u32 VFiPFENT_compareAttr(u8 attr, u8 attr_required, u8 attr_unwanted) {
    u32 is_valid;

    is_valid = 1;
    if (attr == 0) {
        attr = 0x40;
    }
    if (attr_required & 0x80) {
        s32 req = attr_required & 0x7F;
        s32 unw = attr_unwanted & 0x7F;
        if (req != 0 && req != (req & attr) || ((attr_unwanted & 0x7F) != 0) && (unw == ((attr_unwanted & 0x7F) & attr))) {
            is_valid = 0;
        }
    } else {
        if ((attr_required != 0x7F && attr != attr_required) && (!(attr & attr_required) || (attr & attr_unwanted))) {
            is_valid = 0;
        }
    }
    return is_valid;
}

static s32 VFiPFENT_compareEntryName(struct PF_DIR_ENT* p_ent, struct PF_STR* p_pattern, u8 attr) {
    s32 is_match;

    // TODO: dumb hack to prevent inlining
    s32 i;
    for (i = 0; i < 0; i++) {
    }

    is_match = 1;
    if (p_ent->num_entry_LFNs != 0 && p_ent->ordinal == 1) {
        if (p_ent->check_sum == VFiPFENT_CalcCheckSum(p_ent)) {
            is_match = !(VFiPFPATH_cmpNameUni((u16*)p_ent, p_pattern) == 0);
        }
    }

    if (is_match == 1) {
        if ((VFipf_vol_set.setting & 2) == 2 && (attr & 8) == 0) {
            if (VFiPFPATH_cmpName((s8*)p_ent->short_name, p_pattern, 0) == 0) {
                is_match = 0;
            }
        } else {
            if (VFiPFPATH_cmpName((s8*)p_ent->short_name, p_pattern, 1) == 0) {
                is_match = 0;
            }
        }
    }

    return is_match;
}

static s32 VFiPFENT_getEntry(struct PF_DIR_ENT* p_ent, struct PF_ENT_ITER* p_iter, struct PF_STR* p_pattern, u8 attr_required, u8 attr_unwanted, u32* logical_index) {
    s32 err;
    s32 is_match;
    u32 is_valid;
    u8 attr;
    s32 lengthName;
    s8 filename[13];

    attr = p_iter->buf[11];
    is_valid = attr & 0xF;

    if ((s32)is_valid == 0xF) {
        is_match = 1;
    } else {
        if (VFiPFENT_compareAttr(attr, attr_required, attr_unwanted) == 0) {
            is_match = 1;
        } else {
            if ((attr & 8) != 0) {
                p_ent->num_entry_LFNs = 0;
                p_ent->long_name[0] = 0;
            }

            VFiPFPATH_getShortName((s8*)p_ent->short_name, p_iter->buf, p_iter->buf[11]);
            if (p_ent->short_name[0] == 5) {
                p_ent->short_name[0] = 0xE5;
            }

            is_match = VFiPFENT_compareEntryName(p_ent, p_pattern, attr);

            if (is_match == 1) {
                (*logical_index)++;
            }
        }
    }

    if (is_match == 1) {
        if ((s32)is_valid == 0xF) {
            if (VFiPFENT_LoadLFNEntryFieldsFromBuf(p_ent, p_iter->buf) != 0) {
                p_ent->num_entry_LFNs = 0;
                p_ent->long_name[0] = 0;
            }
        } else {
            p_ent->num_entry_LFNs = 0;
            p_ent->long_name[0] = 0;
        }
        return -1;
    }

    if (p_ent->num_entry_LFNs == 0 && (p_iter->buf[12] & 0x18) != 0) {
        u16 i;
        u8 sum;
        u8 sum_buf[16];

        VFiPFPATH_getLongNameformShortName((s8*)p_ent->short_name, filename, p_iter->buf[12]);
        lengthName = VFiPFPATH_transformInUnicode((u16*)p_ent->long_name, filename);

        p_ent->num_entry_LFNs = (lengthName / 13) + (lengthName % 13 != 0);

        VFiPFPATH_putShortName(sum_buf, (s8*)p_ent->short_name, 0);
        sum = 0;
        for (i = 0; i < 11; i++) {
            sum = (sum >> 1) + ((sum & 1) ? 0x80 : 0) + sum_buf[i];
        }
        p_ent->check_sum = sum;
        p_ent->ordinal = 1;
    }

    p_ent->attr = p_iter->buf[11];
    p_ent->small_letter_flag = p_iter->buf[12];
    p_ent->create_time_ms = p_iter->buf[13];
    p_ent->create_time = SWAP16(*(u16*)&p_iter->buf[14]);
    p_ent->create_date = SWAP16(*(u16*)&p_iter->buf[16]);
    p_ent->access_date = SWAP16(*(u16*)&p_iter->buf[18]);
    p_ent->modify_time = SWAP16(*(u16*)&p_iter->buf[22]);
    p_ent->modify_date = SWAP16(*(u16*)&p_iter->buf[24]);
    p_ent->file_size = SWAP32(*(u32*)&p_iter->buf[28]);

    p_ent->start_cluster = ((SWAP16(*(u16*)&p_iter->buf[20])) << 16) | ((u16)(SWAP16(*(u16*)&p_iter->buf[26])));

    p_ent->entry_sector = p_iter->sector;
    p_ent->entry_offset = p_iter->offset;

    if ((p_ent->attr & 0x10) != 0 && p_ent->start_cluster == 0) {
        p_ent->start_cluster = 1;
    }
    return 0;
}

static s32 VFiPFENT_searchEmptyTailSFN(struct PF_FFD* p_ffd, u32 tail_index, const s8* pattern, u32* p_tail_bit) {
    struct PF_ENT_ITER iter;
    u8 attr;
    s32 err;
    u32 bit_pos;
    u32 sfn_taillen;
    u32 sfn_baselen;
    u32 i;
    s8 sfnbuf[13];
    s8 patbuf[13];
    struct PF_VOLUME* p_vol;

    p_vol = p_ffd->p_vol;
    VFipf_memset(p_tail_bit, 0, 4 * p_vol->tail_entry.tracker_size);
    iter.ffd = *p_ffd;
    for (err = VFiPFENT_ITER_IteratorInitialize(&iter, 0); !VFiPFENT_ITER_IsAtLogicalEnd(&iter); err = VFiPFENT_ITER_Advance(&iter, 0)) {
        if (err) {
            return err;
        }
        if (!iter.buf[0]) {
            break;
        }
        if (iter.buf[0] != 229 && (iter.buf[11] & 0xF) != 0xF && (iter.buf[11] & 8) == 0) {
            VFiPFPATH_getShortName(sfnbuf, iter.buf, 0);
            for (sfn_taillen = 1; sfnbuf[sfn_taillen] != 126 && sfnbuf[sfn_taillen] && sfn_taillen < 7; ++sfn_taillen);
            if (sfn_taillen < 7 && sfnbuf[sfn_taillen] == 126) {
                for (sfn_baselen = sfn_taillen + 1; sfnbuf[sfn_baselen] >= 48 && sfnbuf[sfn_baselen] <= 57; ++sfn_baselen);
                if (sfnbuf[sfn_baselen] == 46 || !sfnbuf[sfn_baselen]) {
                    i = sfn_baselen - sfn_taillen - 1;
                    bit_pos = 0;
                    while (i) {
                        bit_pos = bit_pos * 10;
                        bit_pos += sfnbuf[sfn_baselen - i] - 48;
                        i--;
                    }
                    VFipf_strcpy(patbuf, pattern);
                    VFiPFPATH_parseShortNameNumeric(patbuf, bit_pos);
                    if (!VFiPFPATH_cmpTailSFN(sfnbuf, patbuf) && bit_pos >= tail_index && bit_pos < 32 * p_vol->tail_entry.tracker_size + tail_index) {
                        bit_pos -= tail_index;
                        p_tail_bit[bit_pos >> 5] |= 1u << bit_pos;
                    }
                }
            }
        }
    }
    return 0;
}

static s32 VFiPFENT_findEmptyTailSFN(struct PF_DIR_ENT* p_ent_containig_dir, const s8* name, u32* p_tails) {
    struct PF_FFD ffd;
    struct PF_FAT_HINT hint;
    s32 err;
    u32 num;
    struct PF_VOLUME* p_vol;
    u32 track_num;

    p_vol = p_ent_containig_dir->p_vol;
    *p_tails = 1;
    VFiPFFAT_InitFFD(&ffd, &hint, p_ent_containig_dir->p_vol, &p_ent_containig_dir->start_cluster);
    for (num = 1; num <= 0xF423F; num += 32 * p_vol->tail_entry.tracker_size) {
        err = VFiPFENT_searchEmptyTailSFN(&ffd, num, name, p_vol->tail_entry.tracker_bits);
        if (err) {
            return err;
        }
        for (track_num = 0; track_num < p_vol->tail_entry.tracker_size; ++track_num) {
            if (p_vol->tail_entry.tracker_bits[track_num] != -1) {
                while ((p_vol->tail_entry.tracker_bits[track_num] & 1) != 0) {
                    p_vol->tail_entry.tracker_bits[track_num] >>= 1;
                    ++*p_tails;
                }
                num = 1000000;
                break;
            }
            *p_tails += 32;
        }
    }
    return 0;
}

u8 VFiPFENT_CalcCheckSum(struct PF_DIR_ENT* p_ent) {
    u16 i;
    u8 sum;
    u8 buf[13];

    VFiPFPATH_putShortName(buf, p_ent->short_name, 0);
    sum = 0;
    for (i = 0; i < 0xB; i++) {
        sum = (sum >> 1) + (((sum & 0x1) != 0) ? 0x80 : 0) + buf[i];
    }
    return sum;
}

void VFiPFENT_LoadShortNameFromBuf(struct PF_DIR_ENT* p_ent, const u8* buf) {
    VFiPFPATH_getShortName(p_ent->short_name, buf, buf[11]);
    if (p_ent->short_name[0] == 5) {
        p_ent->short_name[0] = -27;
    }
}

void VFiPFENT_loadEntryNumericFieldsFromBuf(struct PF_DIR_ENT* p_ent, const u8* buf) {
    p_ent->attr = buf[11];
    p_ent->small_letter_flag = buf[12];
    p_ent->create_time_ms = buf[13];

    p_ent->create_time = SWAP16(*(u16*)&buf[14]);
    p_ent->create_date = SWAP16(*(u16*)&buf[16]);
    p_ent->access_date = SWAP16(*(u16*)&buf[18]);
    p_ent->modify_time = SWAP16(*(u16*)&buf[22]);
    p_ent->modify_date = SWAP16(*(u16*)&buf[24]);
    p_ent->file_size = SWAP32(*(u32*)&buf[28]);

    p_ent->start_cluster = ((SWAP16(*(u16*)&buf[20])) << 16) | ((u16)(SWAP16(*(u16*)&buf[26])));
}

s32 VFiPFENT_LoadLFNEntryFieldsFromBuf(struct PF_DIR_ENT* p_ent, const u8* buf) {
    u8 ordinal;
    u8 check_sum;
    u32 is_last;
    u8* p;
    u16* q;
    u16* q_after;

    ordinal = buf[0];
    check_sum = buf[13];

    if ((ordinal & ~0x40) > 20) {
        p_ent->ordinal = 0;
        p_ent->check_sum = 0;
        p_ent->num_entry_LFNs = 0;
        return 33;
    }

    if (ordinal & 0x40) {
        ordinal &= ~0x40;
        p_ent->num_entry_LFNs = 0;
        is_last = 1;
    } else {
        is_last = 0;
        if (p_ent->num_entry_LFNs == 0) {
            return 33;
        }

        if (ordinal != p_ent->ordinal - 1 || check_sum != p_ent->check_sum) {
            p_ent->ordinal = 0;
            p_ent->check_sum = 0;
            p_ent->num_entry_LFNs = 0;
            return 33;
        }
    }

    p_ent->ordinal = ordinal;
    p_ent->check_sum = check_sum;

    p = (u8*)p_ent->long_name + (ordinal - 1) * 26;

    VFipf_memcpy(p, (void*)(buf + 1), 10);
    VFipf_memcpy(p + 10, (void*)(buf + 14), 12);
    VFipf_memcpy(p + 22, (void*)(buf + 28), 4);

    VFiPF_LE16_TO_U16_STR(p, 10);
    VFiPF_LE16_TO_U16_STR(p + 10, 12);
    VFiPF_LE16_TO_U16_STR(p + 22, 4);

    if (is_last) {
        *((u16*)(p + 26)) = 0;
        q = (u16*)p;
        q_after = (u16*)(p + 26);

        while (q < q_after) {
            if (*q == 0x0000) {
                q++;
                break;
            }
            q++;
        }

        while (q < q_after) {
            if (*q != 0xFFFF) {
                p_ent->num_entry_LFNs = 0;
                return 33;
            }
            q++;
        }
    }

    p_ent->num_entry_LFNs++;
    return 0;
}

void VFiPFENT_storeLFNEntryFieldsToBuf(u8* buf, struct PF_DIR_ENT* p_ent, u8 ord, u8 sum, u32 is_last) {
    u8* p_seg;
    u16* p;
    u16* p_after;

    if (is_last) {
        buf[0] = ord | 0x40;
    } else {
        buf[0] = ord;
    }

    buf[11] = 0x0F;
    buf[13] = sum;
    buf[12] = 0;
    *(u16*)&buf[26] = 0;

    p_seg = (u8*)p_ent->long_name + (u32)(ord - 1) * 26;

    if (is_last) {
        p = (u16*)p_seg;
        p_after = (u16*)(p_seg + 26);

        while (p < p_after) {
            if (*p == 0) {
                p++;
                break;
            }
            p++;
        }

        while (p < p_after) {
            *p++ = 0xFFFF;
        }
    }

    VFipf_memcpy(buf + 1, p_seg, 10);
    VFipf_memcpy(buf + 14, p_seg + 10, 12);
    VFipf_memcpy(buf + 28, p_seg + 22, 4);

    VFiPF_LE16_TO_U16_STR(buf + 1, 10);
    VFiPF_LE16_TO_U16_STR(buf + 14, 12);
    VFiPF_LE16_TO_U16_STR(buf + 28, 4);
}

s32 VFiPFENT_findEntryPos(struct PF_FFD* p_ffd, struct PF_DIR_ENT* p_ent, u32 index_search_from, struct PF_STR* p_pattern, u8 attr_required, u8 attr_unwanted, u32* p_lpos, u32* p_ppos) {
    s32 err;
    struct PF_ENT_ITER iter;
    u32 logical_index;
    u32 is_extsfn;

    is_extsfn = 0;

    if (!p_ffd) {
        *p_lpos = 999999;
        *p_ppos = 999999;
        return 10;
    }

    if (!p_ent) {
        *p_lpos = 999999;
        *p_ppos = 999999;
        return 10;
    }

    if (index_search_from >= 999999) {
        *p_lpos = 999999;
        *p_ppos = 999999;
        return 10;
    }

    if (!p_pattern) {
        *p_lpos = 999999;
        *p_ppos = 999999;
        return 10;
    }

    if ((attr_required & attr_unwanted) != 0) {
        *p_lpos = 999999;
        *p_ppos = 999999;
        return 10;
    }

    *p_lpos = 0;
    *p_ppos = 0;

    p_ent->num_entry_LFNs = 0;
    p_ent->ordinal = 0;
    p_ent->check_sum = 0;
    p_ent->long_name[0] = 0;

    logical_index = 0;

    if ((VFipf_vol_set.setting & 2) == 2) {
        is_extsfn = VFiPFPATH_GetExtShortNameIndex(p_pattern, &index_search_from);
    }

    iter.ffd = *p_ffd;

    if (is_extsfn == 1) {
        err = VFiPFENT_ITER_IteratorInitialize(&iter, index_search_from - 1);
        if (err != 0) {
            *p_lpos = 999999;
            *p_ppos = 999999;
            return err;
        }

        err = VFiPFENT_getEntry(p_ent, &iter, p_pattern, attr_required, attr_unwanted, &logical_index);

        if (err == 0) {
            *p_lpos = 999999;
            *p_ppos = 999999;
            return 3;
        }

        if ((iter.buf[0] & 0x40) != 0) {
            err = VFiPFENT_ITER_IteratorInitialize(&iter, index_search_from);
            if (err != 0) {
                *p_lpos = 999999;
                *p_ppos = 999999;
                return err;
            }

            err = VFiPFENT_getEntry(p_ent, &iter, p_pattern, attr_required, attr_unwanted, &logical_index);

            if (err == 0) {
                p_ent->p_vol = p_ffd->p_vol;
                *p_lpos = logical_index;
                *p_ppos = iter.index;
                return 0;
            }
        }

    } else {
        err = VFiPFENT_ITER_IteratorInitialize(&iter, index_search_from);
        while (VFiPFENT_ITER_IsAtLogicalEnd(&iter) == 0) {
            if (err != 0) {
                *p_lpos = 999999;
                *p_ppos = 999999;
                return err;
            }
            if (iter.buf[0] == 0) {
                break;
            }
            if (iter.buf[0] == 0xE5) {
                p_ent->num_entry_LFNs = 0;
                p_ent->long_name[0] = 0;

            } else {
                err = VFiPFENT_getEntry(p_ent, &iter, p_pattern, attr_required, attr_unwanted, &logical_index);

                if (err == 0) {
                    p_ent->p_vol = p_ffd->p_vol;
                    *p_lpos = logical_index;
                    *p_ppos = iter.index;
                    return 0;
                }
            }

            err = VFiPFENT_ITER_Advance(&iter, 0);
        }
    }

    *p_lpos = 999999;
    *p_ppos = 999999;
    return 3;
}

s32 VFiPFENT_findEntry(struct PF_FFD* p_ffd, struct PF_DIR_ENT* p_ent, u32 index_search_from, struct PF_STR* p_pattern, u8 attr_required, u8 attr_unwanted) {
    u32 logical_pos;
    u32 physical_pos;

    return VFiPFENT_findEntryPos(p_ffd, p_ent, index_search_from, p_pattern, attr_required, attr_unwanted, &logical_pos, &physical_pos);
}

s32 VFiPFENT_allocateEntryPos(struct PF_DIR_ENT* p_ent, u8 num_entries, struct PF_FFD* p_ffd, u32* p_next_chain, struct PF_STR* p_filename, u32* p_pos) {
    s32 err;
    struct PF_VOLUME* p_vol;
    struct PF_ENT_ITER iter;
    struct PF_DIR_ENT wk_ent;
    u32 wk_sector;
    u16 wk_offset;
    u32 prev_sector;
    u32 next_sector1;
    u32 next_sector2;
    u32 is_found;
    u32 sector;
    u32 count_unused_entries;
    u32 physical_index;
    u32 dummy_index;

    if (!p_ffd) {
        return 10;
    }
    if (!p_ffd->p_vol) {
        return 10;
    }
    if (!num_entries) {
        return 10;
    }
    if (num_entries > 21) {
        return 10;
    }

    if ((VFipf_vol_set.setting & 2) == 2) {
        if ((u32)VFiPFPATH_CheckExtShortNameSignature(p_filename) == 1) {
            return 1;
        }
    }

    p_vol = p_ffd->p_vol;
    count_unused_entries = 0;
    physical_index = 0;

    wk_sector = -1;
    wk_offset = 0;
    p_next_chain[1] = -1;
    p_next_chain[0] = -1;
    prev_sector = -1;
    next_sector2 = -1;
    next_sector1 = -1;
    is_found = 0;

    iter.sector = 0;
    iter.index = 0;
    iter.ffd = *p_ffd;
    err = VFiPFENT_ITER_IteratorInitialize(&iter, 0);

    while (1) {
        if (err != 0) {
            if (err == 16) {
                break;
            }
            return err;
        }

        if (iter.sector == -1) {
            break;
        }
        if (is_found == 0 && count_unused_entries == 0) {
            wk_offset = iter.offset;
            wk_sector = iter.sector;
            prev_sector = iter.sector;
        }
        if (is_found == 0) {
            if (iter.buf[0] == 0 || iter.buf[0] == 0xE5) {
                if (prev_sector != iter.sector) {
                    if (next_sector1 == -1) {
                        next_sector1 = iter.sector;
                    } else {
                        next_sector2 = iter.sector;
                    }
                    prev_sector = iter.sector;
                }
                count_unused_entries++;
            } else {
                count_unused_entries = 0;
                next_sector1 = -1;
                next_sector2 = -1;
            }
        }
        if (count_unused_entries >= num_entries) {
            if (is_found == 0) {
                physical_index = iter.index;
                is_found = 1;
            }
            if (iter.buf[0] == 0) {
                break;
            }
        }
        if (iter.buf[0] != 0 && iter.buf[0] != 0xE5) {
            err = VFiPFENT_getEntry(&wk_ent, &iter, p_filename, 0x7F, 0, &dummy_index);
            if (err == 0) {
                *p_ent = wk_ent;
                p_ent->p_vol = p_ffd->p_vol;
                return 8;
            }
        }
        if (iter.offset + 32 == p_vol->bpb.bytes_per_sector) {
            err = VFiPFFAT_GetSectorSpecified(p_ffd, iter.file_sector_index + 1, 0, &sector);
            if (err != 0) {
                return err;
            }
            if (sector == -1 && is_found == 1) {
                break;
            }
        }
        err = VFiPFENT_ITER_Advance(&iter, 1);
    }

    if (is_found == 0) {
        return 5;
    }

    p_next_chain[0] = next_sector1;
    p_next_chain[1] = next_sector2;
    p_ent->entry_sector = wk_sector;
    p_ent->entry_offset = wk_offset;
    *p_pos = physical_index;
    return 0;
}

s32 VFiPFENT_allocateEntry(struct PF_DIR_ENT* p_ent, u8 num_entries, struct PF_FFD* p_ffd, u32* p_next_chain, struct PF_STR* p_filename) {
    u32 position;

    return VFiPFENT_allocateEntryPos(p_ent, num_entries, p_ffd, p_next_chain, p_filename, &position);
}

s32 VFiPFENT_GetRootDir(struct PF_VOLUME* p_vol, struct PF_DIR_ENT* p_ent) {
    if (!p_vol) {
        return 10;
    }
    if (!p_ent) {
        return 10;
    }
    if ((p_vol->flags & 2) == 0) {
        return 9;
    }

    p_ent->long_name[0] = 92;
    p_ent->long_name[1] = 0;

    p_ent->num_entry_LFNs = 0;
    p_ent->ordinal = 0;
    p_ent->check_sum = 0;

    p_ent->short_name[0] = 92;
    p_ent->short_name[1] = 0;
    p_ent->small_letter_flag = 0;

    p_ent->attr = 0x10;

    p_ent->create_time_ms = 0;
    p_ent->create_time = 0;
    p_ent->create_date = 0;
    p_ent->access_date = 0;
    p_ent->modify_time = 0;
    p_ent->modify_date = 0;
    p_ent->file_size = 0;

    p_ent->p_vol = p_vol;
    p_ent->path_len = 3;
    p_ent->start_cluster = 1;
    p_ent->entry_sector = -1;
    p_ent->entry_offset = 0;

    return 0;
}

s32 VFiPFENT_MakeRootDir(struct PF_VOLUME* p_vol) {
    struct PF_CACHE_PAGE* p_page;
    u32 sector;
    u32 success_size;
    s32 err;

    if (!p_vol) {
        return 10;
    }

    switch (p_vol->bpb.fat_type) {
        case FAT_32:
            VFiPFFAT_MakeRootDir(p_vol);
            break;
        case FAT_12:
        case FAT_16:
            err = VFiPFCACHE_AllocateDataPage(p_vol, 0xFFFFFFFF, &p_page);
            if (err != 0) {
                return err;
            }

            VFipf_memset(p_page->p_buf, 0, p_vol->bpb.bytes_per_sector);

            for (sector = p_vol->bpb.first_root_dir_sector; sector < p_vol->bpb.first_data_sector; sector++) {
                err = VFiPFSEC_WriteData(p_vol, p_page->p_buf, sector, 0, p_vol->bpb.bytes_per_sector, &success_size, 0);
                if (err != 0) {
                    VFiPFCACHE_FreeDataPage(p_vol, p_page);
                    return err;
                }

                if (success_size != p_vol->bpb.bytes_per_sector) {
                    VFiPFCACHE_FreeDataPage(p_vol, p_page);
                    return 17;
                }
            }

            VFiPFCACHE_FreeDataPage(p_vol, p_page);
            break;
        default:
            return 7;
    }

    // VFiPFVOL_LoadVolumeLabelFromBuf((const u8*)"NO NAME    ", p_vol);
    VFiPFVOL_LoadVolumeLabelFromBuf((const u8*)"NO NAME    \0\0\0\0", p_vol);
    return 0;
}

s32 VFiPFENT_updateEntry(struct PF_DIR_ENT* p_ent, u32 flag) {
    struct PF_VOLUME* p_vol;
    u32 success_size;
    u8 buf[32];
    s32 err;

    if (!p_ent) {
        return 10;
    }

    p_vol = p_ent->p_vol;
    if (!p_vol) {
        return 10;
    }

    if (p_ent->entry_sector < p_vol->bpb.first_data_sector - p_vol->bpb.num_root_dir_sectors) {
        return 28;
    }

    if (p_ent->entry_sector >= p_vol->bpb.total_sectors) {
        return 16;
    }

    if (p_ent->start_cluster == 1) {
        return 14;
    }

    if (flag == 1) {
        p_ent->attr |= 0x20;
    }

    VFiPFPATH_putShortName(buf, p_ent->short_name, p_ent->attr);

    if (buf[0] == 0xE5) {
        buf[0] = 5;
    }

    buf[11] = p_ent->attr;
    buf[12] = p_ent->small_letter_flag;
    buf[13] = p_ent->create_time_ms;

    *(u16*)&buf[14] = SWAP16(p_ent->create_time);
    *(u16*)&buf[16] = SWAP16(p_ent->create_date);
    *(u16*)&buf[18] = SWAP16(p_ent->access_date);
    *(u16*)&buf[22] = SWAP16(p_ent->modify_time);
    *(u16*)&buf[24] = SWAP16(p_ent->modify_date);
    *(u16*)&buf[20] = SWAP16((u16)(p_ent->start_cluster >> 16));
    *(u16*)&buf[26] = SWAP16(p_ent->start_cluster);
    *(u32*)&buf[28] = SWAP32(p_ent->file_size);

    err = VFiPFSEC_WriteData(p_vol, buf, p_ent->entry_sector, p_ent->entry_offset, 32, &success_size, 0);

    if (err != 0) {
        return err;
    }

    return (success_size != 32) ? 17 : 0;
}

s32 VFiPFENT_AdjustSFN(struct PF_DIR_ENT* p_ent, s8* p_short_name) {
    u32 i;
    u32 tail_num;
    s32 err;

    for (i = 1; p_short_name[i] != 126 && p_short_name[i] != 0 && i < 7; ++i) {
    }

    if (i < 7 && p_short_name[i] == 126) {
        for (i = i + 1; p_short_name[i] >= 48 && p_short_name[i] <= 57; ++i) {
        }

        if (p_short_name[i] == 46 || p_short_name[i] == 0) {
            err = VFiPFENT_findEmptyTailSFN(p_ent, p_short_name, &tail_num);
            if (err != 0) {
                return err;
            }

            if (tail_num != 1) {
                VFiPFPATH_parseShortNameNumeric(p_short_name, tail_num);
            }
        }
    }
    return 0;
}

s32 VFiPFENT_RemoveEntry(struct PF_DIR_ENT* p_ent, struct PF_ENT_ITER* p_iter) {
    u32 success_size;
    s32 err;
    u32 entry_sector;
    u16 entry_offset;
    u32 i;
    struct PF_VOLUME* p_vol;
    u8 dir_fb_free[1];

    dir_fb_free[0] = FAT_DELETED;
    p_vol = p_ent->p_vol;

    if (!p_vol) {
        return 10;
    }
    if (!p_ent) {
        return 10;
    }
    if (!p_iter) {
        return 10;
    }

    if (p_ent->num_entry_LFNs != 0 && (p_ent->small_letter_flag & 0x18) == 0) {
        for (i = 1; i <= p_ent->num_entry_LFNs; ++i) {
            err = VFiPFENT_ITER_Retreat(p_iter, 0);
            if (err != 0) {
                return err;
            }

            err = VFiPFSEC_WriteData(p_vol, dir_fb_free, p_iter->sector, p_iter->offset, 1, &success_size, 0);
            if (err != 0) {
                return err;
            }

            if (success_size != 1) {
                return 17;
            }
        }
    }

    err = VFiPFSEC_WriteData(p_vol, dir_fb_free, p_ent->entry_sector, p_ent->entry_offset, 1, &success_size, 0);
    if (err != 0) {
        return err;
    }

    if (success_size != 1) {
        return 17;
    } else {
        err = VFiPFCACHE_FlushDataCacheSpecific(p_vol, 0);
        if (err != 0) {
            return err;
        }
        return 0;
    }
}

u8 VFiPFENT_getcurrentDateTimeForEnt(u16* p_date, u16* p_time) {
    struct PF_SYS_DATE sys_date;
    struct PF_SYS_TIME sys_time;

    VFiPFSYS_TimeStamp(&sys_date, &sys_time);

    *p_date = (((sys_date.sys_year - 1980) & 0x7F) << 9) | ((sys_date.sys_month & 0x0F) << 5) | ((sys_date.sys_day & 0x1F) << 0);
    *p_time = ((sys_time.sys_hour & 0x1F) << 11) | ((sys_time.sys_min & 0x3F) << 5) | ((sys_time.sys_sec >> 1) & 0x1F);

    return sys_time.sys_ms;
}
