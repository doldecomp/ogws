#ifndef RP_AUDIO_SND_SPEAKER_MGR_H
#define RP_AUDIO_SND_SPEAKER_MGR_H
#include <Pack/types_pack.h>

#include <Pack/RPSingleton.h>

#include <egg/core.h>

#include <nw4r/snd.h>

//! @addtogroup rp_audio
//! @{

/**
 * @brief Remote speaker manager
 */
class RPSndSpeakerMgr : public EGG::Disposer {
    RP_SINGLETON_DECL_EX(RPSndSpeakerMgr);

public:
    /**
     * @brief Resets the state of each remote speaker
     */
    void reset();

    /**
     * @brief Updates the state of each remote speaker
     */
    void calc();

    /**
     * @brief Finalizes the state of each remote speaker
     */
    void exit();

    /**
     * @brief Fetches the latest WPAD master volume
     */
    void updateMasterVolume();

    /**
     * @brief Toggles enabling output of the specified remote speaker
     *
     * @param chan Remote speaker channel
     * @param enable Whether to enable the speaker output
     * @return Previous enable status
     */
    bool setEnableSw(s32 chan, bool enable);

    /**
     * @brief Configures the main and remote output volumes of the specified
     * sound handle
     *
     * @param pHandle Sound handle
     * @param playerFlag Player output line flags
     * @param mainOut Main output volume
     * @param remoteOut Remote output volume
     * @param muteOut Main output volume when the remote speaker is muted
     */
    void setRemoteSend(nw4r::snd::SoundHandle* pHandle, u32 playerFlag,
                       f32 mainOut, f32 remoteOut, f32 muteOut);

    /**
     * @brief Callback for new remote connections
     *
     * @param chan Remote channel
     * @param result WPAD library result
     */
    static void setSpeakerOnCallback(s32 chan, s32 result);

    /**
     * @brief Callback for remote disconnections
     *
     * @param chan Remote channel
     * @param result WPAD library result
     */
    static void setSpeakerOffCallback(s32 chan, s32 result);

    /**
     * @brief Callback for initializing remote speaker connections
     *
     * @param chan Remote channel
     * @param result WPAD library result
     */
    static void setSpeakerSetupCallback(s32 chan, s32 result);

    /**
     * @brief Callback for finalizing remote speaker connections
     *
     * @param chan Remote channel
     * @param result WPAD library result
     */
    static void setSpeakerShutdownCallback(s32 chan, s32 result);

    /**
     * @brief Attempts to connect to all remote speakers
     */
    void connectAll();

    /**
     * @brief Attempts to disconnect from all remote speakers
     */
    void disconnectAll();

    /**
     * @brief Tests whether the manager has no connections and is in an idle
     * state
     */
    bool isDisconnectAllFinished();

private:
    /**
     * @brief Speaker connection task
     */
    struct ConnectTask {
        //! Whether to turn the speakers on
        bool on; // at 0x0
        //! Whether this command has finished
        bool finish; // at 0x1
        //! Time-out threshold
        u16 timeOut; // at 0x2
        //! Remote channel index
        s32 chan; // at 0x4
    };

    //! Task queue size
    static const int QUEUE_SIZE = 20;
    //! Task time-out threshold
    static const int TIMEOUT = 180;

private:
    /**
     * @brief Converts player-indexed bitflags to remote channel output flags
     *
     * @param playerFlag Player flags
     * @return Remote channel output line flags
     */
    u32 changeBitPlayerToChannel(u32 playerFlag);

    /**
     * @brief Requests a change in the specified remote speaker's state
     *
     * @param chan Remote speaker channel
     * @param on Whether to turn the speaker on
     */
    static void setSpeakerSw(s32 chan, bool on);

    /**
     * @brief Processes the specified remote speaker connection
     *
     * @param chan Remote speaker channel
     * @param on Whether to turn the speaker on
     */
    void taskSpeakerSw(s32 chan, bool on);

    /**
     * @brief Tests whether the specified connection task has completed
     *
     * @param chan Remote speaker channel
     */
    static bool isTaskFinished(s32 chan);

private:
    s32 unk14;
    u8 unk18;

    //! Whether a connect task is currently ongoing
    bool mIsBusy; // at 0x19
    //! Whether all speakers have been disconnected
    bool mIsDisconnected; // at 0x1A

    //! Master speaker volume
    u8 mMasterVolume; // at 0x1B

    u32 unk1C[WPAD_MAX_CONTROLLERS];
    u32 unk2C[WPAD_MAX_CONTROLLERS];
    u32 unk3C[WPAD_MAX_CONTROLLERS];
    u32 unk4C[WPAD_MAX_CONTROLLERS];

    //! Whether each speaker has been initialized
    bool mIsSpeakerSetUp[WPAD_MAX_CONTROLLERS]; // at 0x5C
    //! Whether each speaker is currently turned on
    bool mIsSpeakerOn[WPAD_MAX_CONTROLLERS]; // at 0x60
    //! Whether each speaker has audio output enabled
    bool mIsEnabledOutput[WPAD_MAX_CONTROLLERS]; // at 0x64

    u8 unk68[WPAD_MAX_CONTROLLERS];

    //! Speaker connection task queue
    ConnectTask mTaskQueue[QUEUE_SIZE]; // at 0x6C
    //! Number of finished tasks
    u32 mTaskFinishCount; // at 0x10C
    //! Number of requested tasks
    u32 mTaskRequestCount; // at 0x110

    u32 unk114; // at 0x114
};

//! @}

#endif
