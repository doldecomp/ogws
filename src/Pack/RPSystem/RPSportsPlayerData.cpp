#include <Pack/RPSystem.h>

/**
 * @brief Constructor
 */
RPSportsPlayerData::RPSportsPlayerData() {
    reset();
}

/**
 * @brief Resets the data to a default save state
 */
void RPSportsPlayerData::reset() {
    mPlayerFlags.makeAllZero();

    for (int i = 0; i < RFL_CREATEID_LEN; i++) {
        mCreateID.data[i] = 0;
    }

    mDebutTime = 0;
    mHandFlags.makeAllZero();

    for (int i = 0; i < ESport_Max; i++) {
        mSkillLevels[i] = 0.0f;

        for (int j = 0; j < SKILL_HISTORY_LENGTH; j++) {
            mSkillGraphDelta[i][j] = 0;
        }

        mStandardFirstDates[i] = 0;

        for (int j = 0; j < EGame_Max; j++) {
            mTrainingFirstDates[i][j] = 0;
        }

        mPlayCounts[i] = 0;

        for (int j = 0; j < EGame_Max; j++) {
            mTrainingPlayCounts[i][j] = 0;
            mTrainingMedals[i][j] = EMedal_None;
        }
    }

    unk272 = 0;
    mTnsDifficulty = 0.1f;
    mTnsSuccess = 0.1f;
    for (int i = 0; i < EGame_Max; i++) {
        mTnsTrainingBests[i] = 0;
    }

    mBsbHomerunRunsBest = 0;
    mBsbHomerunDistBest = 0;
    mBsbUchiwakeBest = 0;
    mBsbRenzokuBest = 0;

    unk284 = 0;
    mBowStandardBest = 0;
    mBowPerfectCount = 0;
    for (int i = 0; i < EGame_Max; i++) {
        mBowTrainingBests[i] = 0;
    }

    for (int i = 0; i < ECourse_Max; i++) {
        mGolStandardBests[i] = +99;
    }
    mGolAceCount = 0;
    mGolTrainingBests[EGame_1st] = 0;
    mGolTrainingBests[EGame_3rd] = 0;
    // Hitting the Green - 300.0 meters
    mGolTrainingBests[EGame_2nd] = 30000;

    for (int i = 0; i < EGame_Max; i++) {
        mBoxTrainingBests[i] = 0;
    }

    mPhysicalEndFirstDate = 0;
    mPhysicalEndCount = 0;
    for (int i = 0; i < EStat_Max; i++) {
        mPhysicalLastStats[i] = 0;
        mPhysicalLastEvents[i] = 0;
    }
    for (int i = 0; i < ESport_Max; i++) {
        for (int j = 0; j < EGame_Max; j++) {
            mPhysicalStatSumBests[i][j] = 0;
        }
    }
    mPhysicalEndLastDate = 0;
    for (int i = 0; i < PHYSICAL_HISTORY_LENGTH; i++) {
        mPhysicalStatSumHistory[i] = 0xFFFF;
        mPhysicalDateHistory[i] = 0;
    }
    mPhysicalBeginLastDate = 0;
    for (int i = 0; i < static_cast<int>(ARRAY_SIZE(unk43E)); i++) {
        unk43E[i] = 0;
    }
}

/**
 * @brief Gets the hand type used for the specified sport's primary control
 *
 * @param sport Sport ID
 */
RPSportsPlayerData::EHand
RPSportsPlayerData::getHandPrimary(ESport sport) const {
    return mHandFlags.onBit(sport) ? EHand_Left : EHand_Right;
}

/**
 * @brief Gets the hand type used for the specified sport's secondary
 * control
 *
 * @param sport Sport ID
 */
RPSportsPlayerData::EHand
RPSportsPlayerData::getHandSecondary(ESport sport) const {
    // First set of bits are for the primary control
    return mHandFlags.onBit(ESport_Max + sport) ? EHand_Left : EHand_Right;
}

/**
 * @brief Sets the hand type used for the specified sport's primary control
 *
 * @param hand Hand type
 * @param sport Sport ID
 */
void RPSportsPlayerData::setHandPrimary(EHand hand, ESport sport) {
    if (hand != EHand_Right) {
        mHandFlags.setBit(sport);
    } else {
        mHandFlags.resetBit(sport);
    }
}

/**
 * @brief Sets the hand type used for the specified sport's secondary
 * control
 *
 * @param hand Hand type
 * @param sport Sport ID
 */
void RPSportsPlayerData::setHandSecondary(EHand hand, ESport sport) {
    // First set of bits are for the primary control
    if (hand != EHand_Right) {
        mHandFlags.setBit(ESport_Max + sport);
    } else {
        mHandFlags.resetBit(ESport_Max + sport);
    }
}

/**
 * @brief Gets the skill level in the specified sport
 *
 * @param sport Sport ID
 */
f32 RPSportsPlayerData::getSkillLevel(ESport sport) const {
    return mSkillLevels[sport];
}

/**
 * @brief Sets the skill level in the specified sport
 *
 * @param sport Sport ID
 * @param skill Skill level
 */
void RPSportsPlayerData::setSkillLevel(ESport sport, f32 skill) {
    mSkillLevels[sport] = skill;
}

/**
 * @brief Gets a point from the specified sport's skill graph
 *
 * @param sport Sport ID
 * @param idx Graph point index
 */
s16 RPSportsPlayerData::getSkillGraphPoint(ESport sport, u32 idx) const {
    return mSkillGraphDelta[sport][idx];
}

/**
 * @brief Sets a point in the specified sport's skill graph
 *
 * @param value Point value (delta)
 * @param sport Sport ID
 * @param idx Graph point index
 */
void RPSportsPlayerData::setSkillGraphPoint(s16 value, ESport sport, u32 idx) {
    mSkillGraphDelta[sport][idx] = value;
}

/**
 * @brief Gets the first date when the standard mode of the specified sport
 * was played
 *
 * @param sport Sport ID
 */
RPTime16 RPSportsPlayerData::getStandardFirstDate(ESport sport) const {
    return mStandardFirstDates[sport];
}

/**
 * @brief Sets the first date when the standard mode of the specified sport
 * was played
 *
 * @param date First play date
 * @param sport Sport ID
 */
void RPSportsPlayerData::setStandardFirstDate(RPTime16 date, ESport sport) {
    mStandardFirstDates[sport] = date;
}

/**
 * @brief Gets the first date when the specified training game was played
 *
 * @param sport Sport ID
 * @param game Training game ID
 */
RPTime16 RPSportsPlayerData::getTrainingFirstDate(ESport sport,
                                                  EGame game) const {
    return mTrainingFirstDates[sport][game];
}

/**
 * @brief Sets the first date when the specified training game was played
 *
 * @param date First play date
 * @param sport Sport ID
 * @param game Training game ID
 */
void RPSportsPlayerData::setTrainingFirstDate(RPTime16 date, ESport sport,
                                              EGame game) {
    mTrainingFirstDates[sport][game] = date;
}

/**
 * @brief Gets the play count for the standard mode of the specified sport
 *
 * @param sport Sport ID
 */
u16 RPSportsPlayerData::getStandardPlayCount(ESport sport) const {
    return mPlayCounts[sport];
}

/**
 * @brief Sets the play count for the standard mode of the specified sport
 *
 * @param count Play count
 * @param sport Sport ID
 */
void RPSportsPlayerData::setStandardPlayCount(u16 count, ESport sport) {
    mPlayCounts[sport] = count;
}

/**
 * @brief Gets the play count for the specified training game
 *
 * @param sport Sport ID
 * @param game Training game
 */
u16 RPSportsPlayerData::getTrainingPlayCount(ESport sport, EGame game) const {
    return mTrainingPlayCounts[sport][game];
}

/**
 * @brief Sets the play count for the specified training game
 *
 * @param count Play count
 * @param sport Sport ID
 * @param game Training game
 */
void RPSportsPlayerData::setTrainingPlayCount(u16 count, ESport sport,
                                              EGame game) {
    mTrainingPlayCounts[sport][game] = count;
}

/**
 * @brief Gets the medal type earned in the specified training game
 *
 * @param sport Sport ID
 * @param game Training game ID
 */
u8 RPSportsPlayerData::getTrainingMedal(ESport sport, EGame game) const {
    return mTrainingMedals[sport][game];
}

/**
 * @brief Sets the medal type earned in the specified training game
 *
 * @param medal Medal type
 * @param sport Sport ID
 * @param game Training game ID
 */
void RPSportsPlayerData::setTrainingMedal(u8 medal, ESport sport, EGame game) {
    mTrainingMedals[sport][game] = medal;
}

/**
 * @brief Tests whether this player has completed a round of any sport
 */
bool RPSportsPlayerData::isFirstPlay() const {
    return mPlayerFlags.onBit(EFlag_FirstPlay);
}
/**
 * @brief Marks that this player has completed a round of any sport
 */
void RPSportsPlayerData::setFirstPlay() {
    mPlayerFlags.setBit(EFlag_FirstPlay);
}

/**
 * @brief Tests whether this player has defeated the specified sport's
 * champion
 *
 * @param sport Sport ID
 */
bool RPSportsPlayerData::isDefeatChampion(ESport sport) const {
    return mPlayerFlags.onBit(EFlag_Champion + sport);
}

/**
 * @brief Marks that this player has defeated the specified sport's champion
 *
 * @param sport Sport ID
 */
void RPSportsPlayerData::setDefeatChampion(ESport sport) {
    mPlayerFlags.setBit(EFlag_Champion + sport);
}

/**
 * @brief Gets the difficulty of the Tennis CPU players
 */
f32 RPSportsPlayerData::getTnsDifficulty() const {
    return mTnsDifficulty;
}

/**
 * @brief Sets the difficulty of the Tennis CPU players
 *
 * @param difficulty New CPU difficulty
 */
void RPSportsPlayerData::setTnsDifficulty(f32 difficulty) {
    mTnsDifficulty = difficulty;
}

/**
 * @brief Gets the Tennis player success factor
 */
f32 RPSportsPlayerData::getTnsSuccess() const {
    return mTnsSuccess;
}

/**
 * @brief Sets the Tennis player success factor
 *
 * @param success New player success factor
 */
void RPSportsPlayerData::setTnsSuccess(f32 success) {
    mTnsSuccess = success;
}

/**
 * @brief Gets the best score in the specified Tennis training game
 *
 * @param game Training game ID
 */
u8 RPSportsPlayerData::getTnsTrainingBest(EGame game) const {
    return mTnsTrainingBests[game];
}

/**
 * @brief Sets the best score in the specified Tennis training game
 *
 * @param score Best score
 * @param game Training game ID
 */
void RPSportsPlayerData::setTnsTrainingBest(u8 score, EGame game) {
    // @bug This can somewhat easily overflow with a high score.
    // It will reflect on the UI, but not save correctly.
    mTnsTrainingBests[game] = score;
}

/**
 * @brief Gets the best home run count record in Hitting Home Runs
 */
u8 RPSportsPlayerData::getBsbHomerunRunsBest() const {
    return mBsbHomerunRunsBest;
}

/**
 * @brief Sets the best home run count record in Hitting Home Runs
 *
 * @param runs Best home run count
 */
void RPSportsPlayerData::setBsbHomerunRunsBest(u8 runs) {
    mBsbHomerunRunsBest = runs;
}

/**
 * @brief Gets the best total distance record in Hitting Home Runs
 */
u16 RPSportsPlayerData::getBsbHomerunDistBest() const {
    return mBsbHomerunDistBest;
}

/**
 * @brief Sets the best total distance record in Hitting Home Runs
 *
 * @param dist Best total distance
 */
void RPSportsPlayerData::setBsbHomerunDistBest(u16 dist) {
    mBsbHomerunDistBest = dist;
}

/**
 * @brief Gets the best score in Swing Control
 */
u8 RPSportsPlayerData::getBsbUchiwakeBest() const {
    return mBsbUchiwakeBest;
}

/**
 * @brief Sets the best score in Swing Control
 *
 * @param score Best score
 */
void RPSportsPlayerData::setBsbUchiwakeBest(u8 score) {
    mBsbUchiwakeBest = score;
}

/**
 * @brief Gets the best score in Batting Practice
 */
u8 RPSportsPlayerData::getBsbRenzokuBest() const {
    return mBsbRenzokuBest;
}

/**
 * @brief Sets the best score in Batting Practice
 *
 * @param score Best score
 */
void RPSportsPlayerData::setBsbRenzokuBest(u8 score) {
    mBsbRenzokuBest = score;
}

/**
 * @brief Gets the best score in Bowling
 */
u16 RPSportsPlayerData::getBowStandardBest() const {
    return mBowStandardBest;
}

/**
 * @brief Sets the best score in Bowling
 *
 * @param score Best score
 */
void RPSportsPlayerData::setBowStandardBest(u16 score) {
    mBowStandardBest = score;
}

/**
 * @brief Gets the number of perfect games bowled
 */
u8 RPSportsPlayerData::getBowPerfectCount() const {
    return mBowPerfectCount;
}

/**
 * @brief Sets the number of perfect games bowled
 *
 * @param count Perfect game count
 */
void RPSportsPlayerData::setBowPerfectCount(u8 count) {
    mBowPerfectCount = count;
}

/**
 * @brief Gets the best score in the specified Bowling training game
 *
 * @param game Training game ID
 */
u16 RPSportsPlayerData::getBowTrainingBest(EGame game) const {
    return mBowTrainingBests[game];
}

/**
 * @brief Sets the best score in the specified Bowling training game
 *
 * @param score Best score
 * @param game Training game ID
 */
void RPSportsPlayerData::setBowTrainingBest(u16 score, EGame game) {
    mBowTrainingBests[game] = score;
}

/**
 * @brief Gets the best Golf score on the specified course
 *
 * @param course Golf course ID
 */
s8 RPSportsPlayerData::getGolStandardBest(ECourse course) const {
    return mGolStandardBests[course];
}

/**
 * @brief Sets the best Golf score on the specified course
 *
 * @param score Best score
 * @param course Golf course ID
 */
void RPSportsPlayerData::setGolStandardBest(s8 score, ECourse course) {
    mGolStandardBests[course] = score;
}

/**
 * @brief Gets the amount of hole-in-ones hit
 */
u8 RPSportsPlayerData::getGolAceCount() const {
    return mGolAceCount;
}

/**
 * @brief Sets the amount of hole-in-ones hit
 *
 * @param count Hole-in-one count
 */
void RPSportsPlayerData::setGolAceCount(u8 count) {
    mGolAceCount = count;
}

/**
 * @brief Gets the best score in the specified Golf training game
 *
 * @param game Training game ID
 */
u16 RPSportsPlayerData::getGolTrainingBest(EGame game) const {
    return mGolTrainingBests[game];
}

/**
 * @brief Set the best score in the specified Golf training game
 *
 * @param score Best score
 * @param game Training game ID
 */
void RPSportsPlayerData::setGolTrainingBest(u16 score, EGame game) {
    mGolTrainingBests[game] = score;
}

/**
 * @brief Gets the best score in the specified Boxing training game
 *
 * @param game Training game ID
 */
u16 RPSportsPlayerData::getBoxTrainingBest(EGame game) const {
    return mBoxTrainingBests[game];
}

/**
 * @brief Set the best score in the specified Boxing training game
 *
 * @param score Best score
 * @param game Training game ID
 */
void RPSportsPlayerData::setBoxTrainingBest(u16 score, EGame game) {
    mBoxTrainingBests[game] = score;
}

/**
 * @brief Gets the date of the first completed fitness test
 */
RPTime16 RPSportsPlayerData::getPhysicalEndFirstDate() const {
    return mPhysicalEndFirstDate;
}

/**
 * @brief Sets the date of the first completed fitness test
 *
 * @param date Date of first test completion
 */
void RPSportsPlayerData::setPhysicalEndFirstDate(RPTime16 date) {
    mPhysicalEndFirstDate = date;
}

/**
 * @brief Gets the number of completed fitness tests
 */
u16 RPSportsPlayerData::getPhysicalEndCount() const {
    return mPhysicalEndCount;
}

/**
 * @brief Sets the number of completed fitness tests
 *
 * @param count Number of completed fitness tests
 */
void RPSportsPlayerData::setPhysicalEndCount(u16 count) {
    mPhysicalEndCount = count;
}

/**
 * @brief Gets the most recent value of the specified fitness test stat
 *
 * @param stat Fitness test stat ID
 */
u16 RPSportsPlayerData::getPhysicalStat(EStat stat) const {
    return mPhysicalLastStats[stat];
}

/**
 * @brief Sets the most recent value of the specified fitness test stat
 *
 * @param value Stat value
 * @param stat Fitness test stat ID
 */
void RPSportsPlayerData::setPhysicalStat(u16 value, EStat stat) {
    mPhysicalLastStats[stat] = value;
}

/**
 * @brief Gets the specified event from the most recent fitness test
 *
 * @param idx Event index
 * @return Packed event ID
 */
u8 RPSportsPlayerData::getPhysicalEvent(u32 idx) const {
    return mPhysicalLastEvents[idx];
}

/**
 * @brief Sets the specified event of the most recent fitness test
 *
 * @param event Packed event index
 * @param idx Event index
 */
void RPSportsPlayerData::setPhysicalEvent(u8 event, u32 idx) {
    mPhysicalLastEvents[idx] = event;
}

/**
 * @brief Gets the fitness stat sum record in the specified training game
 *
 * @param sport Sport ID
 * @param game Training game ID
 */
u16 RPSportsPlayerData::getPhysicalStatSumBest(ESport sport, EGame game) const {
    return mPhysicalStatSumBests[sport][game];
}

/**
 * @brief Sets the fitness stat sum record in the specified training game
 *
 * @param sum Fitness stat sum
 * @param sport Sport ID
 * @param game Training game ID
 */
void RPSportsPlayerData::setPhysicalStatSumBest(u16 sum, ESport sport,
                                                EGame game) {
    mPhysicalStatSumBests[sport][game] = sum;
}

/**
 * @brief Gets the date of the most recently completed fitness test
 */
RPTime16 RPSportsPlayerData::getPhysicalEndLastDate() const {
    return mPhysicalEndLastDate;
}

/**
 * @brief Sets the date of the most recently completed fitness test
 *
 * @param date Date of last test completion
 */
void RPSportsPlayerData::setPhysicalEndLastDate(RPTime16 date) {
    mPhysicalEndLastDate = date;
}

/**
 * @brief Gets the specified fitness stat sum from the test history
 *
 * @param idx Fitness test history index
 */
u16 RPSportsPlayerData::getPhysicalStatSumHistory(u32 idx) const {
    return mPhysicalStatSumHistory[idx];
}

/**
 * @brief Sets the specified fitness stat sum in the test history
 *
 * @param sum Fitness stat sum
 * @param idx Fitness test history index
 */
void RPSportsPlayerData::setPhysicalStatSumHistory(u16 sum, u32 idx) {
    mPhysicalStatSumHistory[idx] = sum;
}

/**
 * @brief Gets the specified fitness test completion date from the test
 * history
 *
 * @param idx Fitness test history index
 */
RPTime16 RPSportsPlayerData::getPhysicalDateHistory(u32 idx) const {
    return mPhysicalDateHistory[idx];
}

/**
 * @brief Sets the specified fitness test completion date in the test
 * history
 *
 * @param date Date of test completion
 * @param idx Fitness test history index
 */
void RPSportsPlayerData::setPhysicalDateHistory(RPTime16 date, u32 idx) {
    mPhysicalDateHistory[idx] = date;
}

/**
 * @brief Gets the date of the most recently started fitness test
 */
RPTime16 RPSportsPlayerData::getPhysicalBeginLastDate() const {
    return mPhysicalBeginLastDate;
}

/**
 * @brief Sets the date of the most recently started fitness test
 *
 * @param date Start date of the last test
 */
void RPSportsPlayerData::setPhysicalBeginLastDate(RPTime16 date) {
    mPhysicalBeginLastDate = date;
}

/**
 * @brief Tests whether this player has been registered with the player list
 */
bool RPSportsPlayerData::isRegistered() const {
    return mPlayerFlags.onBit(EFlag_Registered);
}

/**
 * @brief Sets whether this player has been registered with the player list
 *
 * @param registered Registration status
 */
void RPSportsPlayerData::setRegistered(bool registered) {
    mPlayerFlags.changeBit(EFlag_Registered, registered);
}

/**
 * @brief Gets this player's Mii create ID
 *
 * @param[out] pCreateID Mii create ID
 */
void RPSportsPlayerData::getCreateID(RFLCreateID* pCreateID) const {
    for (int i = 0; i < RFL_CREATEID_LEN; i++) {
        pCreateID->data[i] = mCreateID.data[i];
    }
}

/**
 * @brief Set this player's Mii create ID
 *
 * @param pCreateID Mii create ID
 */
void RPSportsPlayerData::setCreateID(const RFLCreateID* pCreateID) {
    for (int i = 0; i < RFL_CREATEID_LEN; i++) {
        mCreateID.data[i] = pCreateID->data[i];
    }
}

/**
 * @brief Gets the time this player was registered with the player list
 */
RPTime32 RPSportsPlayerData::getDebutTime() const {
    return mDebutTime;
}

/**
 * @brief Sets the time this player was registered with the player list
 *
 * @param time Debut time
 */
void RPSportsPlayerData::setDebutTime(RPTime32 time) {
    mDebutTime = time;
}

/**
 * @brief Deserializes this object from the specified stream
 *
 * @param rStrm Memory stream
 */
void RPSportsPlayerData::read(EGG::RamStream& rStrm) {
    mPlayerFlags = rStrm.read_u32();

    for (int i = 0; i < RFL_CREATEID_LEN; i++) {
        mCreateID.data[i] = rStrm.read_u8();
    }

    mDebutTime = rStrm.read_u32();
    mHandFlags = rStrm.read_u8();

    for (int i = 0; i < ESport_Max; i++) {
        mSkillLevels[i] = rStrm.read_f32();

        for (int j = 0; j < SKILL_HISTORY_LENGTH; j++) {
            mSkillGraphDelta[i][j] = rStrm.read_s16();
        }

        mStandardFirstDates[i] = rStrm.read_u16();

        for (int j = 0; j < EGame_Max; j++) {
            mTrainingFirstDates[i][j] = rStrm.read_u16();
        }

        mPlayCounts[i] = rStrm.read_u16();

        for (int j = 0; j < EGame_Max; j++) {
            mTrainingPlayCounts[i][j] = rStrm.read_u16();
            mTrainingMedals[i][j] = rStrm.read_u8();
        }
    }

    unk272 = rStrm.read_u16();
    mTnsDifficulty = rStrm.read_f32();
    mTnsSuccess = rStrm.read_f32();
    for (int i = 0; i < EGame_Max; i++) {
        mTnsTrainingBests[i] = rStrm.read_u8();
    }

    mBsbHomerunRunsBest = rStrm.read_u8();
    mBsbHomerunDistBest = rStrm.read_u16();
    mBsbUchiwakeBest = rStrm.read_u8();
    mBsbRenzokuBest = rStrm.read_u8();

    unk284 = rStrm.read_u16();
    mBowStandardBest = rStrm.read_u16();
    mBowPerfectCount = rStrm.read_u8();
    for (int i = 0; i < EGame_Max; i++) {
        mBowTrainingBests[i] = rStrm.read_u16();
    }

    for (int i = 0; i < ECourse_Max; i++) {
        mGolStandardBests[i] = rStrm.read_s8();
    }
    mGolAceCount = rStrm.read_u8();
    for (int i = 0; i < EGame_Max; i++) {
        mGolTrainingBests[i] = rStrm.read_u16();
    }

    for (int i = 0; i < EGame_Max; i++) {
        mBoxTrainingBests[i] = rStrm.read_u16();
    }

    mPhysicalEndFirstDate = rStrm.read_u16();
    mPhysicalEndCount = rStrm.read_u16();

    // @bug These arrays are only the same length by chance
#if defined(BUG_FIX)
    for (int i = 0; i < EStat_Max; i++) {
        mPhysicalLastStats[i] = rStrm.read_u16();
    }

    for (int i = 0; i < PHYSICAL_EVENT_NUM; i++) {
        mPhysicalLastEvents[i] = rStrm.read_u8();
    }
#else
    for (int i = 0; i < EStat_Max; i++) {
        mPhysicalLastStats[i] = rStrm.read_u16();
        mPhysicalLastEvents[i] = rStrm.read_u8();
    }
#endif

    for (int i = 0; i < ESport_Max; i++) {
        for (int j = 0; j < EGame_Max; j++) {
            mPhysicalStatSumBests[i][j] = rStrm.read_u16();
        }
    }
    mPhysicalEndLastDate = rStrm.read_u16();
    for (int i = 0; i < PHYSICAL_HISTORY_LENGTH; i++) {
        mPhysicalStatSumHistory[i] = rStrm.read_u16();
        mPhysicalDateHistory[i] = rStrm.read_u16();
    }
    mPhysicalBeginLastDate = rStrm.read_u16();
    for (int i = 0; i < static_cast<int>(ARRAY_SIZE(unk43E)); i++) {
        unk43E[i] = rStrm.read_u16();
    }
}

/**
 * @brief Serializes this object to the specified stream
 *
 * @param rStrm Memory stream
 */
void RPSportsPlayerData::write(EGG::RamStream& rStrm) {
    rStrm.write_u32(mPlayerFlags);

    for (int i = 0; i < RFL_CREATEID_LEN; i++) {
        rStrm.write_u8(mCreateID.data[i]);
    }

    rStrm.write_u32(mDebutTime);
    rStrm.write_u8(mHandFlags);

    for (int i = 0; i < ESport_Max; i++) {
        rStrm.write_f32(mSkillLevels[i]);

        for (int j = 0; j < SKILL_HISTORY_LENGTH; j++) {
            rStrm.write_s16(mSkillGraphDelta[i][j]);
        }

        rStrm.write_u16(mStandardFirstDates[i]);

        for (int j = 0; j < EGame_Max; j++) {
            rStrm.write_u16(mTrainingFirstDates[i][j]);
        }

        rStrm.write_u16(mPlayCounts[i]);

        for (int j = 0; j < EGame_Max; j++) {
            rStrm.write_u16(mTrainingPlayCounts[i][j]);
            rStrm.write_u8(mTrainingMedals[i][j]);
        }
    }

    rStrm.write_u16(unk272);
    rStrm.write_f32(mTnsDifficulty);
    rStrm.write_f32(mTnsSuccess);
    for (int i = 0; i < EGame_Max; i++) {
        rStrm.write_u8(mTnsTrainingBests[i]);
    }

    rStrm.write_u8(mBsbHomerunRunsBest);
    rStrm.write_u16(mBsbHomerunDistBest);
    rStrm.write_u8(mBsbUchiwakeBest);
    rStrm.write_u8(mBsbRenzokuBest);

    rStrm.write_u16(unk284);
    rStrm.write_u16(mBowStandardBest);
    rStrm.write_u8(mBowPerfectCount);
    for (int i = 0; i < EGame_Max; i++) {
        rStrm.write_u16(mBowTrainingBests[i]);
    }

    for (int i = 0; i < ECourse_Max; i++) {
        rStrm.write_s8(mGolStandardBests[i]);
    }
    rStrm.write_u8(mGolAceCount);
    for (int i = 0; i < EGame_Max; i++) {
        rStrm.write_u16(mGolTrainingBests[i]);
    }

    for (int i = 0; i < EGame_Max; i++) {
        rStrm.write_u16(mBoxTrainingBests[i]);
    }

    rStrm.write_u16(mPhysicalEndFirstDate);
    rStrm.write_u16(mPhysicalEndCount);

    // @bug These arrays are only the same length by chance
#if defined(BUG_FIX)
    for (int i = 0; i < EStat_Max; i++) {
        rStrm.write_u16(mPhysicalLastStats[i]);
    }

    for (int i = 0; i < PHYSICAL_EVENT_NUM; i++) {
        rStrm.write_u8(mPhysicalLastEvents[i]);
    }
#else
    for (int i = 0; i < EStat_Max; i++) {
        rStrm.write_u16(mPhysicalLastStats[i]);
        rStrm.write_u8(mPhysicalLastEvents[i]);
    }
#endif

    for (int i = 0; i < ESport_Max; i++) {
        for (int j = 0; j < EGame_Max; j++) {
            rStrm.write_u16(mPhysicalStatSumBests[i][j]);
        }
    }
    rStrm.write_u16(mPhysicalEndLastDate);
    for (int i = 0; i < PHYSICAL_HISTORY_LENGTH; i++) {
        rStrm.write_u16(mPhysicalStatSumHistory[i]);
        rStrm.write_u16(mPhysicalDateHistory[i]);
    }
    rStrm.write_u16(mPhysicalBeginLastDate);
    for (int i = 0; i < static_cast<int>(ARRAY_SIZE(unk43E)); i++) {
        rStrm.write_u16(unk43E[i]);
    }
}
