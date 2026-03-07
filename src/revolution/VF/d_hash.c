#include <revolution/VF.h>

static int _MakeWStr(const s8* i_Name);
void dHash_InitHashTable();
static s32 dHash_SearchHashW(const u16* i_Name);
int dHash_GetArg(const s8* i_Name);
int dHash_SetArgW(const u16* i_Name, u8 i_Arg);
int dHash_SetArg(const s8* i_Name, u8 i_Arg);

typedef struct {
    u16 Name[8];
    u8 arg;
} pHashCell;

extern PF_VOLUME_SET VFipf_vol_set;

static u16 l_tmpWName[8];
static pHashCell hashTable[31];

int _MakeWStr(const s8* i_Name) {
    u32 len;
    const s8* Id = i_Name; 
    int next2nd;
    int skip = 0;
    u32 i;

    for (len = 0; Id[len] != '\0'; ++len) {}
    if (len >= 8) {
        return 0;
    }

    for (next2nd = 0; Id[next2nd] != '\0'; ++next2nd) {}

    for (i = 0; i < next2nd; ++i) {
        if (skip) {
            skip = 0;
            continue;
        }
        if (VFipf_vol_set.codeset.is_oem_mb_char(Id[i], 1)) {
            skip = 1;
            l_tmpWName[i] = ((s8)Id[i] << 8) | (u16)(s8)Id[i + 1];
        } else {
            l_tmpWName[i] = (s8)Id[i];
        }
    }
    
    l_tmpWName[7] = 0;
    l_tmpWName[i] = 0;
    
    return 1;
}

void dHash_InitHashTable() {
    int i;

    for (i = 0; i < 30; i++) {
        hashTable[i].Name[0] = 0;
        hashTable[i].arg = 0;
    }

    hashTable[30].Name[0] = 0;
    hashTable[30].arg = 0;
}

s32 dHash_SearchHashW(const u16* i_Name) {
    s32 firstHash;
    int len;
    int i;
    int hashval;
    int k;
    const u16* str0_p;
    const u16* str1_p;
    int len2;
    int success;

    for (len = 0; i_Name[len] != 0; ++len) {}

    if (len >= 8) {
        firstHash = -1;
    } else {
        hashval = 0;
        k = 0;
        for (i = 0; i < len; ++i) {
            if (k > 7) {
                k = 0;
            }
            hashval += i_Name[i] << (k * 4);
            k++;
        }
        firstHash = (u32)hashval % 31;
    }

    if (firstHash == -1) {
        return -1;
    }

    for (len2 = 0; i_Name[len2] != 0; ++len2) {}

    for (k = 0; k < 15; ++k) {
        int hash = (firstHash + k * k) % 31;

        for (len = 0; hashTable[hash].Name[len] != 0; ++len) {}

        if (len2 == len) {
            str0_p = i_Name;
            str1_p = hashTable[hash].Name;
            success = 1;

            for (i = 0; i < len2; ++i) {
                if (*str0_p != *str1_p) {
                    success = 0;
                    break;
                }
                str0_p++;
                str1_p++;
            }

            if (success) {
                return hash;
            }
        }
    }

    return -1;
}

int dHash_GetArg(const s8* i_Name) {
    int searchHash;

    if (_MakeWStr(i_Name)) {
        searchHash = dHash_SearchHashW(l_tmpWName);
        if (searchHash == -1) {
            return -1;
        } else {
            return hashTable[searchHash].arg;
        }
    }

    return -1;
}

int dHash_SetArgW(const u16* i_Name, u8 i_Arg) {
    s32 newHash;

    if (_MakeWStr((const s8*)i_Name)) {
        u32 len;
        for (len = 0; l_tmpWName[len] != 0; ++len) {}

        if (len >= 8) {
            newHash = -1;
        } else {
            u32 hashval = 0;
            u32 shift = 0;
            u32 i;
            
            for (i = 0; i < len; ++i) {
                if (shift > 7) {
                    shift = 0;
                }
                hashval += l_tmpWName[i] << (shift * 4);
                shift++;
            }
            newHash = (u32)hashval % 31;
        }

        if (newHash != -1) {
            if (hashTable[newHash].Name[0] != 0) {
                int k;
                for (k = 1; k < 15; ++k) {
                    int hash = (newHash + k * k) % 31;
                    if (hashTable[hash].Name[0] == 0) {
                        newHash = hash;
                        break;
                    }
                }
                if (k == 15) {
                    newHash = -1;
                }
            }
        }

        if (newHash != -1) {
            VFipf_memcpy(&hashTable[newHash], l_tmpWName, 16);
            hashTable[newHash].arg = i_Arg;
            return 1;
        }
    }

    return 0;
}

int dHash_SetArg(const s8* i_Name, u8 i_Arg) {
    if (_MakeWStr(i_Name)) {
        long hash = dHash_SearchHashW(l_tmpWName);
        if (hash != -1) {
            if (hash >= 0 && hash < 31) {
                hashTable[hash].Name[0] = 0;
                hashTable[hash].arg = 0;
            }
            return 1;
        }
        return 0;
    }
    return 0;
}
