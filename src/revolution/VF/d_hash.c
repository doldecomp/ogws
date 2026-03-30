#include <revolution/VF.h>

typedef struct {
    u16 Name[8];
    u8 arg;
} pHashCell;

extern struct PF_VOLUME_SET VFipf_vol_set;

static u16 l_tmpWName[8];
static pHashCell hashTable[31];

static u32 _StrLen(const s8* i_Name) {
    u32 len;
    len = 0;
    while (*i_Name != '\0') {
        i_Name++;
        len++;
    }
    return len;
}

static u32 _StrLenW(const u16* i_Name) {
    u32 len;
    len = 0;
    while (*i_Name != 0) {
        i_Name++;
        len++;
    }
    return len;
}

static int _MakeWStr(const s8* i_Name) {
    u32 len;
    const s8* Id;  // TODO: type should be int
    int next2nd;
    const s8* p;      // Extra variable. Not in DWARF.
    u16* dst;         // Extra variable. Not in DWARF.
    const s8* pChar;  // Extra variable. Not in DWARF.
    int skip;         // Extra variable. Not in DWARF.
    u32 i;            // Extra variable. Not in DWARF.

    Id = i_Name;

    len = _StrLen(Id);
    if (len < 8) {
        p = Id;
        next2nd = 0;
        while ((*p) != 0) {
            p++;
            next2nd++;
        }

        dst = l_tmpWName;
        i = 0;
        skip = 0;
        while (i < next2nd) {
            if (skip) {
                skip = 0;
            } else {
                pChar = &Id[i];
                if (VFipf_vol_set.codeset.is_oem_mb_char(*pChar, 1)) {
                    skip = 1;
                    *dst = (u32)((((s8)pChar[0]) * 256) | ((u16)((s8)pChar[1])));
                } else {
                    *dst = (s8)pChar[0];
                }
            }
            dst++;
            i++;
        }

        l_tmpWName[7] = 0;
        l_tmpWName[i] = 0;
        return 1;
    }
    return 0;
}

static u16* _GetWStr(void) {
    return l_tmpWName;
}

static void _DeleteDataByIdx(int i_Idx) {
    pHashCell* pHashCell;
    if (i_Idx >= 0 && i_Idx < 31) {
        pHashCell = &hashTable[i_Idx];
        pHashCell->Name[0] = 0;
        pHashCell->arg = 0;
    }
}

void dHash_InitHashTable() {
    pHashCell* pHashCell = hashTable;
    int i;
    for (i = 0; i < 31; i++) {
        pHashCell->Name[0] = 0;
        pHashCell->arg = 0;
        pHashCell++;
    }
}

static s32 dHash_CalcFirstHashW(const u16* i_Name) {
    int len;
    u32 n;
    u32 hash;
    u32 weight;
    s32 firstHash;

    len = _StrLenW(i_Name);
    if (len < 8) {
        hash = 0;
        weight = 0;
        for (n = 0; n < len; n++) {
            if (weight > 7) {
                weight = 0;
            }
            hash += (i_Name[n] << (weight++ * 4));
        }
        firstHash = hash % 31;
    } else {
        firstHash = -1;
    }
    return firstHash;
}

static s32 dHash_CalcRehash(u32 i_FirstHash) {
    u32 hashval;
    u32 k;

    for (k = 1; k < 15; k++) {
        hashval = (i_FirstHash + k * k) % 31;
        if (hashTable[hashval].Name[0] == 0) {
            return hashval;
        }
    }
    return -1;
}

static s32 dHash_GetNewHashW(const u16* i_Name) {
    s32 firstHash;
    s32 newHash;

    firstHash = dHash_CalcFirstHashW(i_Name);
    if (firstHash != -1) {
        if (hashTable[firstHash].Name[0] != 0) {
            return dHash_CalcRehash(firstHash);
        } else {
            return firstHash;
        }
    }
    return -1;
}

static s32 dHash_SearchHashW(const u16* i_Name) {
    s32 firstHash;
    int len;
    int i;
    int hashval;
    int k;
    const u16* str0_p;
    const u16* str1_p;
    int len2;
    int success;

    firstHash = dHash_CalcFirstHashW(i_Name);
    if (firstHash != -1) {
        len2 = _StrLenW(i_Name);

        for (k = 0; k < 15; k++) {
            hashval = (firstHash + k * k) % 31;
            len = _StrLenW(hashTable[hashval].Name);

            if (len2 == len) {
                str0_p = i_Name;
                str1_p = hashTable[hashval].Name;
                success = 1;

                for (i = 0; i < len2; i++) {
                    if (*str0_p != *str1_p) {
                        success = 0;
                        break;
                    }
                    str0_p++;
                    str1_p++;
                }

                if (success) {
                    return hashval;
                }
            }
        }
    }
    return -1;
}

static int dHash_GetArgW(const u16* i_Name) {
    s32 searchHash;

    searchHash = dHash_SearchHashW(i_Name);
    if (searchHash == -1) {
        return -1;
    } else {
        return hashTable[searchHash].arg;
    }
}

int dHash_GetArg(const s8* i_Name) {
    if (_MakeWStr(i_Name) != 0) {
        return dHash_GetArgW(_GetWStr());
    }
    return -1;
}

static int dHash_SetArgW(const u16* i_Name, u8 i_Arg) {
    s32 newHash;

    newHash = dHash_GetNewHashW(i_Name);
    if (newHash != -1) {
        VFipf_memcpy(hashTable[newHash].Name, _GetWStr(), 16);
        hashTable[newHash].arg = i_Arg;
        return 1;
    }
    return 0;
}

int dHash_SetArg(const s8* i_Name, u8 i_Arg) {
    if (_MakeWStr(i_Name) != 0) {
        return dHash_SetArgW(_GetWStr(), i_Arg);
    }
    return 0;
}

static int dHash_DeleteDataW(const u16* i_Name) {
    s32 Hash;

    Hash = dHash_SearchHashW(i_Name);
    if (Hash != -1) {
        _DeleteDataByIdx(Hash);
        return 1;
    }
    return 0;
}

int dHash_DeleteData(const s8* i_Name) {
    if (_MakeWStr(i_Name)) {
        return dHash_DeleteDataW(_GetWStr());
    }
    return 0;
}
