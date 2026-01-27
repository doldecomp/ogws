#ifndef RP_AUDIO_SND_AUDIO_MGR_H
#define RP_AUDIO_SND_AUDIO_MGR_H
#include <Pack/types_pack.h>

#include <Pack/RPAssert.h>
#include <Pack/RPAudio/RPSndMoveParam.h>
#include <Pack/RPAudio/RPSndStaticMgr.h>
#include <Pack/RPSingleton.h>

#include <egg/audio.h>

#include <nw4r/math.h>
#include <nw4r/snd.h>

#include <cstring>

//! @addtogroup rp_audio
//! @{

/**
 * @brief Audio manager
 */
class RPSndAudioMgr : public EGG::ExpAudioMgr {
    RP_SINGLETON_DECL_EX(RPSndAudioMgr);

public:
    /**
     * @brief Callback for configuring audio effects
     */
    typedef void (*SetFxCallback)();

public:
    /**
     * @brief Initializes the audio manager state
     *
     * @param pArg Audio system configuration
     */
    virtual void initialize(Arg* pArg); // at 0x8

    /**
     * @brief Attempts to open the specified sound archive, using storage
     * settings from the project locale
     *
     * @param pPath Sound archive path
     * @param pHeap Sound heap
     * @param pMultiHandle Multi handle for special storage types
     * @return Archive player
     */
    virtual nw4r::snd::SoundArchivePlayer*
    openArchiveRP(const char* pPath, nw4r::snd::SoundHeap* pHeap,
                  void* pMultiHandle); // at 0xB0

    /**
     * @brief Updates the state of the audio manager
     */
    virtual void calc(); // at 0xC

    /**
     * @brief Attempts to restore the specified sound heap state
     *
     * @param id State ID
     * @return Success
     */
    virtual bool loadState(s32 id); // at 0x18

    /**
     * @brief Attempts to load the specified sound group
     *
     * @param id Group ID
     * @param pHeap Sound heap to use for allocations
     * @param blockSize Read block size (zero tries to read it all at once)
     * @return Success
     */
    virtual bool loadGroup(unsigned int id, nw4r::snd::SoundHeap* pHeap = NULL,
                           u32 blockSize = 0); // at 0x28

    /**
     * @brief Attempts to load the specified sound group
     *
     * @param id Group ID
     * @param pHeap Sound heap to use for allocations
     * @param blockSize Read block size (zero tries to read it all at once)
     * @return Success
     */
    virtual bool loadGroup(int id, nw4r::snd::SoundHeap* pHeap = NULL,
                           u32 blockSize = 0); // at 0x2C

    /**
     * @brief Attempts to load the specified sound group
     *
     * @param pName Group name
     * @param pHeap Sound heap to use for allocations
     * @param blockSize Read block size (zero tries to read it all at once)
     * @return Success
     */
    virtual bool loadGroup(const char* pName,
                           nw4r::snd::SoundHeap* pHeap = NULL,
                           u32 blockSize = 0); // at 0x30

    /**
     * @brief Attempts to start the specified sound
     *
     * @param pHandle Sound handle
     * @param id Sound ID
     * @return Success
     */
    virtual bool startSound(nw4r::snd::SoundHandle* pHandle, u32 id); // at 0x38

    /**
     * @brief Attempts to start the specified sound
     *
     * @param pHandle Sound handle
     * @param id Sound ID
     * @return Success
     */
    virtual bool startSound(nw4r::snd::SoundHandle* pHandle,
                            unsigned int id); // at 0x3C

    /**
     * @brief Attempts to start the specified sound
     *
     * @param pHandle Sound handle
     * @param pName Sound name
     * @return Success
     */
    virtual bool startSound(nw4r::snd::SoundHandle* pHandle,
                            const char* pName); // at 0x40

    /**
     * @brief Attempts to open and prepare the specified sound archive
     *
     * @param pPath Sound archive path
     * @param staticPath Whether the archive path is relative to the static
     * resource directory
     * @param pHeap Sound heap
     * @return Archive player
     */
    nw4r::snd::SoundArchivePlayer* attachArchive(const char* pPath,
                                                 bool staticPath,
                                                 nw4r::snd::SoundHeap* pHeap);

    /**
     * @brief Attempts to start the specified BGM ("BGM_") sound
     *
     * @param id Sound ID
     * @return Success
     */
    bool startBgm(u32 id) {
        return startSound(&mHandleBgm, id);
    }
    /**
     * @brief Attempts to start the specified BGM ("BGM_") sound
     *
     * @param pName Sound name
     * @return Success
     */
    bool startBgm(const char* pName) {
        return startBgm(changeNameToIdRP(pName));
    }

    /**
     * @brief Attempts to start the specified stream ("STRM_") sound
     *
     * @param id Sound ID
     * @return Success
     */
    bool startStream(u32 id) {
        return startSound(&mHandleStream, id);
    }
    /**
     * @brief Attempts to start the specified stream ("STRM_") sound
     *
     * @param pName Sound name
     * @return Success
     */
    bool startStream(const char* pName) {
        return startStream(changeNameToIdRP(pName));
    }

    /**
     * @brief Attempts to start the specified system sound effect
     *
     * @param id Sound ID
     * @return Success
     */
    bool startSystemSe(u32 id) {
        return startSystemSe(getSoundArchive().GetSoundLabelString(id));
    }
    /**
     * @brief Attempts to start the specified system sound effect
     *
     * @param pName Sound name
     * @return Success
     */
    bool startSystemSe(const char* pName) {
        if (mIsDisableFanfare) {
            if (pName[7] == 'B' && pName[8] == 'G' && pName[9] == 'M') {
                return false;
            }
        }

        return startSound(&mHandleSystemSe, pName);
    }

    /**
     * @brief Attempts to start the specified system sound effect through the
     * remote speaker(s)
     *
     * @param id Sound ID
     * @param playerFlag Player output line flags
     * @return Success
     */
    bool startSystemSeWithRemote(u32 id, u32 playerFlag) {
        bool success = startSound(&mHandleSystemSe, id);
        if (success) {
            setRemote(playerFlag);
        }

        return success;
    }
    /**
     * @brief Attempts to start the specified system sound effect through the
     * remote speaker(s)
     *
     * @param pName Sound name
     * @param playerFlag Player output line flags
     * @return Success
     */
    bool startSystemSeWithRemote(const char* pName, u32 playerFlag) {
        return startSystemSeWithRemote(changeNameToIdRP(pName), playerFlag);
    }

    /**
     * @brief Attempts to start the specified wave sound
     *
     * @param id Sound ID
     * @return Success
     */
    bool startWaveSound(u32 id) {
        return startWaveSound(getSoundArchive().GetSoundLabelString(id));
    }
    /**
     * @brief Attempts to start the specified wave sound
     *
     * @param pName Sound name
     * @return Success
     */
    bool startWaveSound(const char* pName) {
        if (pName[0] == 'B' && pName[1] == 'g' && pName[2] == 'm') {
            return false;
        }

        return startSound(&mHandleWaveSound, pName);
    }

    /**
     * @brief Converts a sound effect name to its corresponding ID
     *
     * @param pName Sound effect name
     * @return Sound effect ID
     */
    u32 changeNameToIdRP(const char* pName) {
        u32 id = mArchive->ConvertLabelStringToSoundId(pName);

#line 206
        RP_ASSERT_MSG(id != nw4r::snd::SoundArchive::INVALID_ID, "Wrong Sound Name < %s >\n", pName);
        return id;
    }

    /**
     * @brief Configures the audio system for title scenes
     */
    void configureTitle();

    /**
     * @brief Configures the audio system for scenes without BGM
     */
    void configureNoBgm();

    /**
     * @brief Configures the audio system for game scenes
     *
     * @param cameraNum 3D audio camera count
     */
    void configureMiniGame(s32 cameraNum);

    /**
     * @brief Fades out all audio in the specified number of frames
     *
     * @param frames Fade out length
     */
    void fadeOutAllSound(u16 frames);

    /**
     * @brief Applies the fade out for game Retry buttons
     */
    void setAutoFadeOnRetry();

    /**
     * @brief Prepares the audio system for a scene change
     */
    void changeScene();

    /**
     * @brief Resets the audio system configuration
     */
    void exitAudio();

    /**
     * @brief Sets the volume of all sound players
     *
     * @param volume New volume
     * @param frames Interpolation time
     */
    void setArcVolume(f32 volume, u32 frames);

    /**
     * @brief Resets the volume of all sound players
     */
    void resetArcVolume();

    /**
     * @brief Sets the volume of the current BGM
     *
     * @param volume New volume
     * @param frames Interpolation time
     */
    void setBgmVolume(f32 volume, int frames);

    /**
     * @brief Sets the volume of the current stream
     *
     * @param volume New volume
     * @param frames Interpolation time
     */
    void setStreamVolume(f32 volume, int frames);

    /**
     * @brief Gets the position of the current stream, in seconds
     */
    u32 getStreamPlaySecond();

    /**
     * @brief Attempts to start a cursor sound effect
     *
     * @param pName Sound name
     * @param rDpdPos Cursor DPD/IR position
     * @param pan Sound pan
     * @param playerFlag Player output line flag
     * @return Success
     */
    bool startPointCursorSe(const char* pName, const nw4r::math::VEC2& rDpdPos,
                            f32 pan, u32 playerFlag);

    /**
     * @brief Attempts to start a pause sound effect
     *
     * @param pNameRemote Remote speaker sound name
     * @param pNameTV TV speaker sound name
     * @param waitForDpd Whether to wait until the controller reconnects
     * @param player Player whose remote speaker should be used
     */
    void startPauseSe(const char* pNameRemote, const char* pNameTV,
                      bool waitForDpd, s32 player);

    /**
     * @brief Applies the default audio effect configuration
     */
    void setDefaultFx();

    /**
     * @brief Configures the specified remote speaker(s) for the current system
     * sound effect
     *
     * @param playerFlag Player output line flags
     */
    void setRemote(u32 playerFlag);

    /**
     * @brief Prepares the audio system for entering the home button menu
     */
    void enterMenu();
    /**
     * @brief Prepares the audio system for returning from the home button menu
     */
    void exitMenu();

    /**
     * @brief Prepares the audio system for entering the pause menu
     */
    void enterPause();
    /**
     * @brief Prepares the audio system for returning from the pause menu
     */
    void exitPause();

    /**
     * @brief Pauses the audio system when a DVD error occurs
     */
    void onDvdError();
    /**
     * @brief Resumes the audio system after a DVD error
     */
    void exitDvdError();

    /**
     * @brief Stops all sounds when exiting the scene from the pause menu
     */
    void stopAllSoundOnPauseOff();

    /**
     * @brief Requests the audio system to shutdown
     *
     * @param frames Time to fade out the master volume
     */
    void shutdownSystem(int frames);

    /**
     * @brief Requests the audio system to reset
     *
     * @param frames Time to fade out the archive volume
     */
    void resetSystem(int frames);

    /**
     * @brief Attempts to start the specified fanfare sound effect
     *
     * @param id Sound ID
     * @return Success
     */
    bool startFanfare(u32 id);
    /**
     * @brief Attempts to start the specified fanfare sound effect
     *
     * @param pName Sound name
     * @return Success
     */
    bool startFanfare(const char* pName);

    /**
     * @brief Gets the user parameters attached to the specified sound
     *
     * @param rArchive Sound archive
     * @param id Sound ID
     */
    u32 getUserParam(const nw4r::snd::SoundArchive& rArchive, u32 id);

    /**
     * @brief Sets the output mode of the audio system
     *
     * @param confMode Sound mode from the SYSCONF
     */
    void setOutputMode(u8 confMode);

    /**
     * @brief Gets the number of game players
     */
    u32 getPlayerNum() const {
        return mPlayerNum;
    }

private:
    /**
     * @brief Audio manager flags
     */
    enum {
        EFlag_IsPause = 1 << 0,    //!< Pause state was entered
        EFlag_IsMenu = 1 << 1,     //!< Menu state was entered
        EFlag_IsDvdError = 1 << 2, //!< DVD error state was entered
    };

    /**
     * @brief Audio manager state
     */
    enum EState {
        EState_Exited,   //!< Needs configuration for the current scene
        EState_Title,    //!< Configured for a title scene
        EState_MiniGame, //!< Configured for a minigame scene
        EState_NoBgm,    //!< Configured for a scene without BGM
    };

    //! Maximum file path length
    static const u32 PATH_MAX = 128;

    //! Time to fadeout all sounds
    static const u32 RETRY_FADE_TIME = 60;
    //! Time to fade in when exiting the pause/HBM menu
    static const u32 EXIT_FADE_TIME = 20;

    //! Time to clear audio bus effects
    static const u32 MENU_FX_CLEAR_TIME = 15;

    //! Stream sound tickrate
    static const u32 STREAM_TICKRATE = 60;

private:
    /**
     * @brief Sets the specified bitflags
     *
     * @param flag Bitflags
     */
    void setFlag(u8 flag) {
        mFlags |= flag;
    }
    /**
     * @brief Clears the specified bitflags
     *
     * @param flag Bitflags
     */
    void clearFlag(u8 flag) {
        mFlags &= static_cast<u8>(~flag);
    }
    /**
     * @brief Tests whether the specified bitflags are set
     *
     * @param flag Bitflags
     */
    bool testFlag(u8 flag) {
        return mFlags & flag;
    }

    /**
     * @brief Gets the playtime of the specified fanfare sound effect, in
     * milliseconds
     *
     * @param pName Fanfare sound effect name
     */
    u32 getFanfareLength(const char* pName) {
        if (std::strcmp("RP_COM_BGM_GET_COPPER", pName) == 0) {
            return 1900;
        }
        if (std::strcmp("RP_COM_BGM_GET_SILVER", pName) == 0) {
            return 3400;
        }
        if (std::strcmp("RP_COM_BGM_GET_GOLD", pName) == 0) {
            return 3100;
        }
        if (std::strcmp("RP_COM_BGM_GET_PLATINA", pName) == 0) {
            return 4900;
        }

        if (std::strcmp("RP_COMMON_BGM_RANK_COMPLETE", pName) == 0) {
            return 3300;
        }

        if (std::strcmp("RP_PNP_BGM_FANFARE_WIN", pName) == 0) {
            return 3000;
        }

        if (std::strcmp("FANFARE_HomeRun", pName) == 0) {
            return 1736;
        }
        if (std::strcmp("FANFARE_OutOfTheParkHomer", pName) == 0) {
            return 2576;
        }

        if (std::strcmp("FANFARE_Strike", pName) == 0) {
            return 1760;
        }
        if (std::strcmp("FANFARE_SpareGet", pName) == 0) {
            return 2192;
        }

        // @bug Max value will be used as a timer
#if defined(BUG_FIX)
        return 0;
#else
        return -1;
#endif
    }

private:
    //! Sound archive file path
    char mArchivePath[PATH_MAX]; // at 0x8A0

    //! BGM sound handle
    nw4r::snd::SoundHandle mHandleBgm; // at 0x920
    //! Stream sound handle
    nw4r::snd::SoundHandle mHandleStream; // at 0x924
    //! System sound effect handle
    nw4r::snd::SoundHandle mHandleSystemSe; // at 0x928
    //! Wave sound handle
    nw4r::snd::SoundHandle mHandleWaveSound; // at 0x92C
    //! Fanfare sound handle
    nw4r::snd::SoundHandle mHandleFanfare; // at 0x930

    //! Current sound heap level
    s32 mSoundHeapLevel; // at 0x934
    //! Shutdown status
    EShutDownStatus mShutDownStatusRP; // at 0x938

    //! Audio manager flags
    u8 mFlags; // at 0x93C
    u32 unk940;

    //! Current stream sound tick
    u32 mStreamPlayTick; // at 0x944
    u32 unk948;

    //! Sound archive volume
    RPSndMoveValueF32 mArcVolume; // at 0x94C

    //! Number of game players
    u32 mPlayerNum; // at 0x968

    //! Time until the audio system is reset
    u32 mResetTimer; // at 0x96C

    //! Whether fanfare sounds are disabled
    bool mIsDisableFanfare; // at 0x970

    //! Static sound manager
    RPSndStaticMgr mStaticMgr; // at 0x974

    //! Whether a pause sound effect task is queued
    bool mIsPauseSe; // at 0xF7C
    //! Whether the pause sound effect should wait for the controller
    bool mPauseSeWaitForDpd; // at 0xF7D
    //! Whether a DVD error has just occurred
    bool mIsNewDvdError; // at 0xF7E
    //! Previous DPD enable state when the pause sound effect was requested
    bool mPauseSePrevDpdEnable; // at 0xF7F
    //! Remote speaker pause sound effect name
    const char* mpPauseSeNameRemote; // at 0xF80
    //! TV speaker pause sound effect name
    const char* mpPauseSeName; // at 0xF84

    //! Fanfare start time
    u32 mFanfareStart; // at 0xF88
    //! Pause sound effect player output line flags
    u32 mPauseSePlayerFlag; // at 0xF8C
    //! Pause sound effect channel
    u32 mPauseSeChan; // at 0xF90
    //! Fanfare sound effect length, in milliseconds
    u32 mFanfareLength; // at 0xF94

    //! User-set fade time to use instead of the default
    u32 mMenuPauseFrame; // at 0xF98
    //! Time until an exit fade in is triggered
    u32 mMenuPauseFadeInTimer; // at 0xF9C

    //! Callback for re-configuring audio effects
    SetFxCallback mpSetFxCallback; // at 0xFA0

    //! BGM volume control
    RPSndMoveParam* mpBgmVolume; // at 0xFA4

    //! Audio system state
    EState mState; // at 0xFA8
};

//! @}

#endif
