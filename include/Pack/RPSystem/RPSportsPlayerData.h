#ifndef RP_SYSTEM_SPORTS_PLAYER_DATA_H
#define RP_SYSTEM_SPORTS_PLAYER_DATA_H
#include <Pack/types_pack.h>

#include <RVLFaceLib.h>

#include <egg/core.h>

//! @addtogroup rp_system
//! @{

/**
 * @brief Sports Pack save file player data
 */
class RPSportsPlayerData {
public:
    /**
     * @brief Sport ID
     */
    enum ESport {
        ESport_Bsb, //!< Baseball
        ESport_Tns, //!< Tennis
        ESport_Gol, //!< Golf
        ESport_Bow, //!< Bowling
        ESport_Box, //!< Boxing

        ESport_Max
    };

    /**
     * @brief Training game ID
     */
    enum EGame {
        EGame_1st, //!< First of the three training games
        EGame_2nd, //!< Second of the three training games
        EGame_3rd, //!< Last of the three training games

        EGame_Max
    };

    /**
     * @brief Training game medal type
     */
    enum EMedal {
        EMedal_None,
        EMedal_Bronze,
        EMedal_Silver,
        EMedal_Gold,
        EMedal_Platinum,
    };

    /**
     * @brief Golf course ID
     */
    enum ECourse {
        ECourse_NineHole,     //!< Nine-hole
        ECourse_Beginner,     //!< Beginner (H1-H3)
        ECourse_Intermediate, //!< Intermediate (H4-H6)
        ECourse_Expert,       //!< Expert (H7-H9)

        ECourse_Max
    };

    /**
     * @brief Fitness test statistic
     */
    enum EStat {
        EStat_Stamina,
        EStat_Speed,
        EStat_Balance,

        EStat_Max
    };

    /**
     * @brief Handedness type
     */
    enum EHand {
        EHand_Right, //!< Right-handed
        EHand_Left,  //!< Left-handed
    };

public:
    /**
     * @brief Constructor
     */
    RPSportsPlayerData();

    /**
     * @brief Resets the data to a default save state
     */
    void reset();

    /**
     * @name Common
     */
    /**@{*/
    /**
     * @brief Gets the hand type used for the specified sport's primary control
     *
     * @param sport Sport ID
     */
    EHand getHandPrimary(ESport sport) const;
    /**
     * @brief Gets the hand type used for the specified sport's secondary
     * control
     *
     * @param sport Sport ID
     */
    EHand getHandSecondary(ESport sport) const;

    /**
     * @brief Sets the hand type used for the specified sport's primary control
     *
     * @param hand Hand type
     * @param sport Sport ID
     */
    void setHandPrimary(EHand hand, ESport sport);
    /**
     * @brief Sets the hand type used for the specified sport's secondary
     * control
     *
     * @param hand Hand type
     * @param sport Sport ID
     */
    void setHandSecondary(EHand hand, ESport sport);

    /**
     * @brief Gets the skill level in the specified sport
     *
     * @param sport Sport ID
     */
    f32 getSkillLevel(ESport sport) const;
    /**
     * @brief Sets the skill level in the specified sport
     *
     * @param sport Sport ID
     * @param skill Skill level
     */
    void setSkillLevel(ESport sport, f32 skill);

    /**
     * @brief Gets a point from the specified sport's skill graph
     *
     * @param sport Sport ID
     * @param idx Graph point index
     */
    s16 getSkillGraphPoint(ESport sport, u32 idx) const;
    /**
     * @brief Sets a point in the specified sport's skill graph
     *
     * @param value Point value (delta)
     * @param sport Sport ID
     * @param idx Graph point index
     */
    void setSkillGraphPoint(s16 value, ESport sport, u32 idx);

    /**
     * @brief Gets the first date when the standard mode of the specified sport
     * was played
     *
     * @param sport Sport ID
     */
    RPTime16 getStandardFirstDate(ESport sport) const;
    /**
     * @brief Sets the first date when the standard mode of the specified sport
     * was played
     *
     * @param date First play date
     * @param sport Sport ID
     */
    void setStandardFirstDate(RPTime16 date, ESport sport);

    /**
     * @brief Gets the first date when the specified training game was played
     *
     * @param sport Sport ID
     * @param game Training game ID
     */
    RPTime16 getTrainingFirstDate(ESport sport, EGame game) const;
    /**
     * @brief Sets the first date when the specified training game was played
     *
     * @param date First play date
     * @param sport Sport ID
     * @param game Training game ID
     */
    void setTrainingFirstDate(RPTime16 date, ESport sport, EGame game);

    /**
     * @brief Gets the play count for the standard mode of the specified sport
     *
     * @param sport Sport ID
     */
    u16 getStandardPlayCount(ESport sport) const;
    /**
     * @brief Sets the play count for the standard mode of the specified sport
     *
     * @param count Play count
     * @param sport Sport ID
     */
    void setStandardPlayCount(u16 count, ESport sport);

    /**
     * @brief Gets the play count for the specified training game
     *
     * @param sport Sport ID
     * @param game Training game ID
     */
    u16 getTrainingPlayCount(ESport sport, EGame game) const;
    /**
     * @brief Sets the play count for the specified training game
     *
     * @param count Play count
     * @param sport Sport ID
     * @param game Training game ID
     */
    void setTrainingPlayCount(u16 count, ESport sport, EGame game);

    /**
     * @brief Gets the medal type earned in the specified training game
     *
     * @param sport Sport ID
     * @param game Training game ID
     */
    u8 getTrainingMedal(ESport sport, EGame game) const;
    /**
     * @brief Sets the medal type earned in the specified training game
     *
     * @param medal Medal type
     * @param sport Sport ID
     * @param game Training game ID
     */
    void setTrainingMedal(u8 medal, ESport sport, EGame game);

    /**
     * @brief Tests whether this player has completed a round of any sport
     */
    bool isFirstPlay() const;
    /**
     * @brief Marks that this player has completed a round of any sport
     */
    void setFirstPlay();

    /**
     * @brief Tests whether this player has defeated the specified sport's
     * champion
     *
     * @param sport Sport ID
     */
    bool isDefeatChampion(ESport sport) const;
    /**
     * @brief Marks that this player has defeated the specified sport's champion
     *
     * @param sport Sport ID
     */
    void setDefeatChampion(ESport sport);
    /**@}*/

    /**
     * @name Tennis
     */
    /**@{*/
    /**
     * @brief Gets the difficulty of the Tennis CPU players
     */
    f32 getTnsDifficulty() const;
    /**
     * @brief Sets the difficulty of the Tennis CPU players
     *
     * @param difficulty New CPU difficulty
     */
    void setTnsDifficulty(f32 difficulty);

    /**
     * @brief Gets the Tennis player success factor
     */
    f32 getTnsSuccess() const;
    /**
     * @brief Sets the Tennis player success factor
     *
     * @param success New player success factor
     */
    void setTnsSuccess(f32 success);

    /**
     * @brief Gets the best score in the specified Tennis training game
     *
     * @param game Training game ID
     */
    u8 getTnsTrainingBest(EGame game) const;
    /**
     * @brief Sets the best score in the specified Tennis training game
     *
     * @param score Best score
     * @param game Training game ID
     */
    void setTnsTrainingBest(u8 score, EGame game);
    /**@}*/

    /**
     * @name Baseball
     */
    /**@{*/
    /**
     * @brief Gets the best home run count record in Hitting Home Runs
     */
    u8 getBsbHomerunRunsBest() const;
    /**
     * @brief Sets the best home run count record in Hitting Home Runs
     *
     * @param runs Best home run count
     */
    void setBsbHomerunRunsBest(u8 runs);

    /**
     * @brief Gets the best total distance record in Hitting Home Runs
     */
    u16 getBsbHomerunDistBest() const;
    /**
     * @brief Sets the best total distance record in Hitting Home Runs
     *
     * @param dist Best total distance
     */
    void setBsbHomerunDistBest(u16 dist);

    /**
     * @brief Gets the best score in Swing Control
     */
    u8 getBsbUchiwakeBest() const;
    /**
     * @brief Sets the best score in Swing Control
     *
     * @param score Best score
     */
    void setBsbUchiwakeBest(u8 score);

    /**
     * @brief Gets the best score in Batting Practice
     */
    u8 getBsbRenzokuBest() const;
    /**
     * @brief Sets the best score in Batting Practice
     *
     * @param score Best score
     */
    void setBsbRenzokuBest(u8 score);
    /**@}*/

    /**
     * @name Bowling
     */
    /**@{*/
    /**
     * @brief Gets the best score in Bowling
     */
    u16 getBowStandardBest() const;
    /**
     * @brief Sets the best score in Bowling
     *
     * @param score Best score
     */
    void setBowStandardBest(u16 score);

    /**
     * @brief Gets the number of perfect games bowled
     */
    u8 getBowPerfectCount() const;
    /**
     * @brief Sets the number of perfect games bowled
     *
     * @param count Perfect game count
     */
    void setBowPerfectCount(u8 count);

    /**
     * @brief Gets the best score in the specified Bowling training game
     *
     * @param game Training game ID
     */
    u16 getBowTrainingBest(EGame game) const;
    /**
     * @brief Sets the best score in the specified Bowling training game
     *
     * @param score Best score
     * @param game Training game ID
     */
    void setBowTrainingBest(u16 score, EGame game);
    /**@}*/

    /**
     * @name Golf
     */
    /**@{*/
    /**
     * @brief Gets the best Golf score on the specified course
     *
     * @param course Golf course ID
     */
    s8 getGolStandardBest(ECourse course) const;
    /**
     * @brief Sets the best Golf score on the specified course
     *
     * @param score Best score
     * @param course Golf course ID
     */
    void setGolStandardBest(s8 score, ECourse course);

    /**
     * @brief Gets the amount of hole-in-ones hit
     */
    u8 getGolAceCount() const;
    /**
     * @brief Sets the amount of hole-in-ones hit
     *
     * @param count Hole-in-one count
     */
    void setGolAceCount(u8 count);

    /**
     * @brief Gets the best score in the specified Golf training game
     *
     * @param game Training game ID
     */
    u16 getGolTrainingBest(EGame game) const;
    /**
     * @brief Set the best score in the specified Golf training game
     *
     * @param score Best score
     * @param game Training game ID
     */
    void setGolTrainingBest(u16 score, EGame game);
    /**@}*/

    /**
     * @name Boxing
     */
    /**@{*/
    /**
     * @brief Gets the best score in the specified Boxing training game
     *
     * @param game Training game ID
     */
    u16 getBoxTrainingBest(EGame game) const;
    /**
     * @brief Set the best score in the specified Boxing training game
     *
     * @param score Best score
     * @param game Training game ID
     */
    void setBoxTrainingBest(u16 score, EGame game);
    /**@}*/

    /**
     * @name Wii Fitness
     */
    /**@{*/
    /**
     * @brief Gets the date of the first completed fitness test
     */
    RPTime16 getPhysicalEndFirstDate() const;
    /**
     * @brief Sets the date of the first completed fitness test
     *
     * @param date Date of first test completion
     */
    void setPhysicalEndFirstDate(RPTime16 date);

    /**
     * @brief Gets the number of completed fitness tests
     */
    u16 getPhysicalEndCount() const;
    /**
     * @brief Sets the number of completed fitness tests
     *
     * @param count Number of completed fitness tests
     */
    void setPhysicalEndCount(u16 count);

    /**
     * @brief Gets the most recent value of the specified fitness test stat
     *
     * @param stat Fitness test stat ID
     */
    u16 getPhysicalStat(EStat stat) const;
    /**
     * @brief Sets the most recent value of the specified fitness test stat
     *
     * @param value Stat value
     * @param stat Fitness test stat ID
     */
    void setPhysicalStat(u16 value, EStat stat);

    /**
     * @brief Gets the specified event from the most recent fitness test
     *
     * @param idx Event index
     * @return Packed event ID
     */
    u8 getPhysicalEvent(u32 idx) const;
    /**
     * @brief Sets the specified event of the most recent fitness test
     *
     * @param event Packed event index
     * @param idx Event index
     */
    void setPhysicalEvent(u8 event, u32 idx);

    /**
     * @brief Gets the fitness stat sum record in the specified training game
     *
     * @param sport Sport ID
     * @param game Training game ID
     */
    u16 getPhysicalStatSumBest(ESport sport, EGame game) const;
    /**
     * @brief Sets the fitness stat sum record in the specified training game
     *
     * @param sum Fitness stat sum
     * @param sport Sport ID
     * @param game Training game ID
     */
    void setPhysicalStatSumBest(u16 sum, ESport sport, EGame game);

    /**
     * @brief Gets the date of the most recently completed fitness test
     */
    RPTime16 getPhysicalEndLastDate() const;
    /**
     * @brief Sets the date of the most recently completed fitness test
     *
     * @param date Date of last test completion
     */
    void setPhysicalEndLastDate(RPTime16 date);

    /**
     * @brief Gets the specified fitness stat sum from the test history
     *
     * @param idx Fitness test history index
     */
    u16 getPhysicalStatSumHistory(u32 idx) const;
    /**
     * @brief Sets the specified fitness stat sum in the test history
     *
     * @param sum Fitness stat sum
     * @param idx Fitness test history index
     */
    void setPhysicalStatSumHistory(u16 sum, u32 idx);

    /**
     * @brief Gets the specified fitness test completion date from the test
     * history
     *
     * @param idx Fitness test history index
     */
    RPTime16 getPhysicalDateHistory(u32 idx) const;
    /**
     * @brief Sets the specified fitness test completion date in the test
     * history
     *
     * @param date Date of test completion
     * @param idx Fitness test history index
     */
    void setPhysicalDateHistory(RPTime16 date, u32 idx);

    /**
     * @brief Gets the date of the most recently started fitness test
     */
    RPTime16 getPhysicalBeginLastDate() const;
    /**
     * @brief Sets the date of the most recently started fitness test
     *
     * @param date Start date of the last test
     */
    void setPhysicalBeginLastDate(RPTime16 date);
    /**@}*/

    /**
     * @name Player list
     */
    /**@{*/
    /**
     * @brief Tests whether this player has been registered with the player list
     */
    bool isRegistered() const;
    /**
     * @brief Sets whether this player has been registered with the player list
     *
     * @param registered Registration status
     */
    void setRegistered(bool registered);

    /**
     * @brief Gets this player's Mii create ID
     *
     * @param[out] pCreateID Mii create ID
     */
    void getCreateID(RFLCreateID* pCreateID) const;
    /**
     * @brief Set this player's Mii create ID
     *
     * @param pCreateID Mii create ID
     */
    void setCreateID(const RFLCreateID* pCreateID);

    /**
     * @brief Gets the time this player was registered with the player list
     */
    RPTime32 getDebutTime() const;
    /**
     * @brief Sets the time this player was registered with the player list
     *
     * @param time Debut time
     */
    void setDebutTime(RPTime32 time);
    /**@}*/

    /**
     * @brief Deserializes this object from the specified stream
     *
     * @param rStrm Memory stream
     */
    void read(EGG::RamStream& rStrm);
    /**
     * @brief Serializes this object to the specified stream
     *
     * @param rStrm Memory stream
     */
    void write(EGG::RamStream& rStrm);

private:
    /**
     * @brief Player data flags
     */
    enum {
        EFlag_Registered = 1,            //!< Registered with the player list
        EFlag_FirstPlay = 2,             //!< Completed first round of any sport
        EFlag_Champion = 27 /* 27-31 */, //!< Defeated the sport champion
    };

private:
    //! Length of the skill graph history (previous 49)
    static const int SKILL_HISTORY_LENGTH = 50 - 1;

    //! Number of events in a fitness test
    static const int PHYSICAL_EVENT_NUM = 3;
    //! Length of the fitness results history (previous 90)
    static const int PHYSICAL_HISTORY_LENGTH = 90 + 1;

private:
    /**
     * @name Common data
     */
    /**@{*/
    //! Player data flags
    EGG::TBitFlag<u32> mPlayerFlags; // at 0x0
    //! Mii create/unique ID
    RFLCreateID mCreateID; // at 0x4
    //! Time the player was registered
    RPTime32 mDebutTime; // at 0xC

    //! Handedness flags (primary, secondary)
    EGG::TBitFlag<u8> mHandFlags; // at 0x10

    //! Player skill levels
    f32 mSkillLevels[ESport_Max]; // at 0x14
    //! Skill graph history (displacement)
    s16 mSkillGraphDelta[ESport_Max][SKILL_HISTORY_LENGTH]; // at 0x28

    //! First date playing each sport's standard mode
    RPTime16 mStandardFirstDates[ESport_Max]; // at 0x212
    //! First date playing each training game
    RPTime16 mTrainingFirstDates[ESport_Max][EGame_Max]; // at 0x21C

    //! Play count of each sport (measured in holes for Golf)
    u16 mPlayCounts[ESport_Max]; // at 0x23A
    //! Play count of each training game
    u16 mTrainingPlayCounts[ESport_Max][EGame_Max]; // at 0x244

    //! Medal earned in each training game
    u8 mTrainingMedals[ESport_Max][EGame_Max]; // at 0x262
    /**@}*/

    /**
     * @name Tennis data
     */
    /**@{*/
    u16 unk272;

    //! CPU difficulty
    f32 mTnsDifficulty; // at 0x274
    //! Player success coefficient (accelerates the increase in difficulty)
    f32 mTnsSuccess; // at 0x278

    //! Tennis training best scores
    u8 mTnsTrainingBests[EGame_Max]; // at 0x27C
    /**@}*/

    /**
     * @name Baseball data
     */
    /**@{*/
    //! Best home run count in Hitting Home Runs
    u8 mBsbHomerunRunsBest; // at 0x27F
    //! Best total distance in Hitting Home Runs
    u16 mBsbHomerunDistBest; // at 0x280

    //! Swing Control best score
    u8 mBsbUchiwakeBest; // at 0x282
    //! Batting Practice best score
    u8 mBsbRenzokuBest; // at 0x283
    /**@}*/

    /**
     * @name Bowling data
     */
    /**@{*/
    u16 unk284;

    //! Bowling best score
    u16 mBowStandardBest; // at 0x286
    //! Number of perfect games bowled
    u8 mBowPerfectCount; // at 0x288
    //! Best scores in Bowling training games
    u16 mBowTrainingBests[EGame_Max]; // at 0x28A
    /**@}*/

    /**
     * @name Golf data
     */
    /**@{*/
    //! Best scores on each difficulty
    s8 mGolStandardBests[ECourse_Max]; // at 0x290
    //! Number of aces hit
    u8 mGolAceCount; // at 0x294
    //! Best scores in Golf training games
    u16 mGolTrainingBests[EGame_Max]; // at 0x296
    /**@}*/

    /**
     * @name Boxing data
     */
    /**@{*/
    //! Best scores in Boxing training games
    u16 mBoxTrainingBests[EGame_Max]; // at 0x29C
    /**@}*/

    /**
     * @name Wii Fitness data
     */
    /**@{*/
    //! Date of the first completed fitness test
    RPTime16 mPhysicalEndFirstDate; // at 0x2A2
    //! Number of completed fitness tests
    u16 mPhysicalEndCount; // at 0x2A4

    //! Previous fitness test stat ratings
    u16 mPhysicalLastStats[EStat_Max]; // at 0x2A6
    //! Previous fitness test event IDs
    u8 mPhysicalLastEvents[PHYSICAL_EVENT_NUM]; // at 0x2AC

    //! Best fitness stat sum in all training games
    u16 mPhysicalStatSumBests[ESport_Max][EGame_Max]; // at 0x2B0

    //! Date of the last completed fitness test
    RPTime16 mPhysicalEndLastDate; // at 0x2CE
    //! Fitness stat sums of the most recent fitness test, and the previous 90
    u16 mPhysicalStatSumHistory[PHYSICAL_HISTORY_LENGTH]; // at 0x2D0
    //! Dates of the most recent fitness test, and the previous 90
    RPTime16 mPhysicalDateHistory[PHYSICAL_HISTORY_LENGTH]; // at 0x386

    //! Date of the last started fitness test
    RPTime16 mPhysicalBeginLastDate; // at 0x43C

    u16 unk43E[15];
    /**@}*/
};

//! @}

#endif
