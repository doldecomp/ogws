#include <RVLFaceLib/RVLFaceLibInternal.h>
#include <string.h>

BOOL RFLiCheckValidInfo(const RFLiCharInfo* info) {
    if (info->faceline.type > 7) {
        return FALSE;
    }
    if (info->faceline.color > 5) {
        return FALSE;
    }
    if (info->faceline.texture > 11) {
        return FALSE;
    }

    if (info->hair.type > 71) {
        return FALSE;
    }
    if (info->hair.color > 7) {
        return FALSE;
    }
    if (info->hair.flip > 1) {
        return FALSE;
    }

    if (info->eye.type > 47) {
        return FALSE;
    }
    if (info->eye.color > 5) {
        return FALSE;
    }
    if (info->eye.scale > 7) {
        return FALSE;
    }
    if (info->eye.rotate > 7) {
        return FALSE;
    }
    if (info->eye.x > 12) {
        return FALSE;
    }
    if (info->eye.y > 18) {
        return FALSE;
    }

    if (info->eyebrow.type > 23) {
        return FALSE;
    }
    if (info->eyebrow.color > 7) {
        return FALSE;
    }
    if (info->eyebrow.scale > 8) {
        return FALSE;
    }
    if (info->eyebrow.rotate > 11) {
        return FALSE;
    }
    if (info->eyebrow.x > 12) {
        return FALSE;
    }
    if (info->eyebrow.y < 3) {
        return FALSE;
    }
    if (info->eyebrow.y > 18) {
        return FALSE;
    }

    if (info->nose.type > 11) {
        return FALSE;
    }
    if (info->nose.scale > 8) {
        return FALSE;
    }
    if (info->nose.y > 18) {
        return FALSE;
    }

    if (info->mouth.type > 23) {
        return FALSE;
    }
    if (info->mouth.color > 2) {
        return FALSE;
    }
    if (info->mouth.scale > 8) {
        return FALSE;
    }
    if (info->mouth.y > 18) {
        return FALSE;
    }

    if (info->beard.mustache > 3) {
        return FALSE;
    }
    if (info->beard.type > 3) {
        return FALSE;
    }
    if (info->beard.color > 7) {
        return FALSE;
    }
    if (info->beard.scale > 8) {
        return FALSE;
    }
    if (info->beard.y > 16) {
        return FALSE;
    }

    if (info->glass.type > 8) {
        return FALSE;
    }
    if (info->glass.color > 5) {
        return FALSE;
    }
    if (info->glass.scale > 7) {
        return FALSE;
    }
    if (info->glass.y > 20) {
        return FALSE;
    }

    if (info->mole.type > 1) {
        return FALSE;
    }
    if (info->mole.scale > 8) {
        return FALSE;
    }
    if (info->mole.x > 16) {
        return FALSE;
    }
    if (info->mole.y > 30) {
        return FALSE;
    }

    if (!RFLiIsValidName2(info)) {
        return FALSE;
    }

    if (info->body.height > 128) {
        return FALSE;
    }
    if (info->body.build > 128) {
        return FALSE;
    }

    if (info->personal.sex > 1) {
        return FALSE;
    }
    if (!RFLiCheckBirthday(info->personal.bmonth, info->personal.bday)) {
        return FALSE;
    }
    if (info->personal.color >= RFLFavoriteColor_Max) {
        return FALSE;
    }

    if (RFLiIsSpecialID(info->createID) && !info->personal.localOnly) {
        return FALSE;
    }

    return TRUE;
}

BOOL RFLiIsValidOnNAND(const RFLiCharInfo* info) {
    return !RFLiIsTemporaryID(info->createID);
}

BOOL RFLiIsSameFaceCore(const RFLiCharInfo* lhs, const RFLiCharInfo* rhs) {
    if ((lhs->eye.rawdata & ~0b11111) != (rhs->eye.rawdata & ~0b11111)) {
        return FALSE;
    }

    if ((lhs->eyebrow.rawdata & ~0b111111) !=
        (rhs->eyebrow.rawdata & ~0b111111)) {
        return FALSE;
    }

    if ((s32)lhs->mouth.rawdata != rhs->mouth.rawdata) {
        return FALSE;
    }

    if ((s32)lhs->beard.rawdata != rhs->beard.rawdata) {
        return FALSE;
    }

    if ((lhs->glass.rawdata & 0xFFFF & ~0b1) !=
        (rhs->glass.rawdata & 0xFFFF & ~0b1)) {
        return FALSE;
    }

    if ((lhs->mole.rawdata & 0xFFFF & ~0b1) !=
        (rhs->mole.rawdata & 0xFFFF & ~0b1)) {
        return FALSE;
    }

    if ((lhs->nose.rawdata & 0xFFFF & ~0b111) !=
        (rhs->nose.rawdata & 0xFFFF & ~0b111)) {
        return FALSE;
    }

    if ((lhs->hair.rawdata & 0xFFFF & ~0b11111) !=
        (rhs->hair.rawdata & 0xFFFF & ~0b11111)) {
        return FALSE;
    }

    if ((lhs->faceline.rawdata & 0xFFFF & ~0b111111) !=
        (rhs->faceline.rawdata & 0xFFFF & ~0b111111)) {
        return FALSE;
    }

    return TRUE;
}

RFLErrcode RFLiPickupCharInfo(RFLiCharInfo* info, RFLDataSource source,
                              struct RFLMiddleDB* db, u16 index) {
    RFLErrcode err;

    if (!RFLAvailable()) {
        return RFLErrcode_NotAvailable;
    }

    switch (source) {
    case RFLDataSource_Official:
        err = RFLiGetCharInfo(info, index);
        break;
    case RFLDataSource_Controller1:
    case RFLDataSource_Controller2:
    case RFLDataSource_Controller3:
    case RFLDataSource_Controller4:
        if (RFLiGetControllerData(info, source - RFLDataSource_Controller1,
                                  index & 0xFF, FALSE)) {
            err = RFLErrcode_Success;
        } else {
            err = RFLErrcode_Broken;
        }
        break;
    case RFLDataSource_Middle:
        if (RFLiGetCharInfoMiddleDB(info, db, index)) {
            err = RFLErrcode_Success;
        } else {
            err = RFLErrcode_Broken;
        }
        break;
    case RFLDataSource_Default:
        RFLiGetDefaultData(info, index);
        err = RFLErrcode_Success;
        break;
    }

    if (err == RFLErrcode_Success) {
        if (!RFLiIsValidID(info->createID)) {
            err = RFLErrcode_Broken;
        } else if (!RFLiCheckValidInfo(info)) {
            err = RFLErrcode_Broken;
        }
    }

    return err;
}

static void copyChar2Additional_(RFLAdditionalInfo* dst,
                                 const RFLiCharInfo* src) {
    u8 height;
    u8 build;

    memcpy(dst->name, src->personal.name, sizeof(wchar_t) * RFL_NAME_LEN);
    dst->name[RFL_NAME_LEN] = '\0';

    memcpy(dst->creator, src->personal.creator,
           sizeof(wchar_t) * RFL_CREATOR_LEN);
    // @bug Copy paste error
    dst->name[RFL_CREATOR_LEN] = '\0';

    dst->sex = src->personal.sex;

    if (RFLiCheckBirthday(src->personal.bmonth, src->personal.bday)) {
        dst->bmonth = src->personal.bmonth;
        dst->bday = src->personal.bday;
    } else {
        dst->bmonth = 0;
        dst->bday = 0;
    }

    dst->color = src->personal.color;
    dst->favorite = src->personal.favorite;

    height = src->body.height;
    build = src->body.build;

    if (height > 127) {
        height = 127;
    }
    if (build > 127) {
        build = 127;
    }

    dst->height = height;
    dst->build = build;
    memcpy(dst->createID, src->createID, sizeof(RFLCreateID));
    dst->reserved = 0;
    dst->skinColor = RFLiGetFacelineColor(src);
}

RFLErrcode RFLGetAdditionalInfo(RFLAdditionalInfo* addi, RFLDataSource source,
                                struct RFLMiddleDB* db, u16 index) {
    RFLiCharInfo info;
    RFLErrcode err;

    err = RFLiPickupCharInfo(&info, source, db, index);
    if (err == RFLErrcode_Success) {
        copyChar2Additional_(addi, &info);
    }

    return err;
}

BOOL RFLiCheckBirthday(u8 month, u8 day) {
    // (One-indexed)
    static const u8 scDayMax[12 + 1] = {0,  31, 29, 31, 30, 31, 30,
                                        31, 31, 30, 31, 30, 31};

    if (month == 0 && day != 0) {
        return FALSE;
    }

    if (month != 0 && day == 0) {
        return FALSE;
    }

    if (month > 12 || day > 31) {
        return FALSE;
    }

    return day <= scDayMax[month];
}