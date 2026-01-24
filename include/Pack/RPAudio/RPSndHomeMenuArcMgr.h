#ifndef RP_AUDIO_SND_HOME_MENU_ARC_MGR_H
#define RP_AUDIO_SND_HOME_MENU_ARC_MGR_H
#include <Pack/types_pack.h>

#include <egg/audio.h>

//! @addtogroup rp_audio
//! @{

/**
 * @brief Home menu sound archive manager
 */
class RPSndHomeMenuArcMgr : public EGG::SoundHeapMgr, public EGG::ArcPlayer {
public:
    /**
     * @brief Constructor
     */
    RPSndHomeMenuArcMgr();

    /**
     * @brief Destructor
     */
    virtual ~RPSndHomeMenuArcMgr(); // at 0x8

    /**
     * @brief Updates the state of the sound player
     */
    virtual void calc(); // at 0x34

    /**
     * @brief Mounts the provided sound archive
     *
     * @param pBinary Binary sound archive
     * @return Success
     */
    bool setupArchive(const void* pBinary);

private:
    //! Active sound handle
    nw4r::snd::SoundHandle mSoundHandle; // at 0x6A4
    //! Whether the sound archive has been setup
    bool mIsInitialized; // at 0x6A8
};

//! @}

#endif
