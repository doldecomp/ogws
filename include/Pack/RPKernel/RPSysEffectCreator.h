#ifndef RP_KERNEL_EFFECT_CREATOR_H
#define RP_KERNEL_EFFECT_CREATOR_H
#include <Pack/types_pack.h>

#include <Pack/RPKernel/RPSysEffectMemoryManager.h>

#include <egg/core.h>

#include <nw4r/ef.h>

//! @addtogroup rp_kernel
//! @{

/**
 * @brief Effect creator
 */
class RPSysEffectCreator : public EGG::Disposer {
public:
    /**
     * @brief Constructor
     *
     * @param drawScene Effect draw scene
     */
    explicit RPSysEffectCreator(u32 drawScene);

    /**
     * @brief Destructor
     */
    virtual ~RPSysEffectCreator(); // at 0x8

    /**
     * @brief Attaches new effect resource files
     *
     * @param pEffectProject Binary effect data project (.BREFF)
     * @param pTextureProject Binary effect texture project (.BREFT)
     */
    void setEffectResource(void* pEffectProject, void* pTextureProject);

    /**
     * @brief Releases the attached effect resource files
     */
    void resetEffectResource();

    /**
     * @brief Creates the effect system for slow-motion effects
     */
    void createSlowSystem();

    /**
     * @brief Sets the frame rate of the slow-motion system
     *
     * @param frameRate Frame rate (0, 1)
     */
    void setFrameRate(f32 frameRate);

    /**
     * @brief Tests whether the slow-motion effect system exists
     */
    bool isSlowSystem() const;

    /**
     * @brief Tests whether effects are currently updating in slow motion
     */
    bool isSlowEffect() const;

    /**
     * @brief Kills all effects owned by this creator
     */
    void stopAllEffect();

    /**
     * @brief Creates an instance of the specified effect
     *
     * @param pName Effect name
     * @param drawGroup Effect draw group
     */
    nw4r::ef::Effect* createEffect(const char* pName, u32 drawGroup);

    /**
     * @brief Updates all effects owned by this creator
     */
    void update();

    /**
     * @brief Draws the specified set of effects
     *
     * @param rDrawInfo Graphics configuration
     * @param drawGroup Effect draw group
     * @param drawScene Effect draw scene
     */
    void draw(const nw4r::ef::DrawInfo& rDrawInfo, u32 drawGroup,
              u32 drawScene);

    /**
     * @brief Tests whether this creator has resource files attached
     */
    bool isActive() const {
        return mpEffectProject != NULL && mpTextureProject != NULL;
    }

    /**
     * @brief Accesses the attached effect texture project
     */
    nw4r::ef::TextureProject* getTextureProject() const {
        return mpTextureProject;
    }

private:
    /**
     * @brief Save buffer index
     */
    enum ESaveBuffer {
        ESaveBuffer_1st, //!< First of the two alternating buffers
        ESaveBuffer_2nd, //!< Second of the two alternating buffers

        ESaveBuffer_Max
    };

    //! Slow system effect object pool size
    static const u16 SLOW_MAX_EFFECT = 50;
    //! Slow system emitter object pool size
    static const u16 SLOW_MAX_EMITTER = 100;
    //! Slow system particle manager object pool size
    static const u16 SLOW_MAX_PARTICLE_MANAGER = 100;
    //! Slow system particle object pool size
    static const u16 SLOW_MAX_PARTICLE = 500;

private:
    //! Group ID prefix inherited by child effects
    u32 mBaseGroupID; // at 0x10

    //! Effect data project (.BREFF)
    nw4r::ef::EffectProject* mpEffectProject; // at 0x14
    //! Effect texture project (.BREFT)
    nw4r::ef::TextureProject* mpTextureProject; // at 0x18

    //! Parameter save buffer where slow system data will be saved
    u32 mBackSaveBuffer; // at 0x1C
    //! Whether slow-motion effects are about to be processed
    BOOL mIsSlowEffect; // at 0x20

    //! Current frame processing position
    f32 mFrame; // at 0x24
    //! Frame processing rate
    f32 mFrameRate; // at 0x28

    //! Effect system for slow-motion effects
    nw4r::ef::EffectSystem* mpSlowSystem; // at 0x2C
    //! Effect memory manager
    RPSysEffectMemoryManager* mpMemoryManager; // at 0x30

    //! Emitter parameter save buffers
    nw4r::ef::EmitterParameter* mEmitterParamSave[ESaveBuffer_Max]; // at 0x34
    //! Particle parameter save buffers
    nw4r::ef::ParticleParameter* mParticleParamSave[ESaveBuffer_Max]; // at 0x3C
};

//! @}

#endif
