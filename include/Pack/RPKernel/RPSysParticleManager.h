#ifndef RP_KERNEL_PARTICLE_MANAGER_H
#define RP_KERNEL_PARTICLE_MANAGER_H
#include <Pack/types_pack.h>

#include <nw4r/ef.h>
#include <nw4r/math.h>

//! @addtogroup rp_kernel
//! @{

/**
 * @brief Particle manager
 */
class RPSysParticleManager : public nw4r::ef::ParticleManager {
public:
    /**
     * @brief Constructor
     */
    RPSysParticleManager();

    /**
     * @brief Destructor
     */
    virtual ~RPSysParticleManager() override; // at 0x20

    /**
     * @brief Prepares this particle manager for creation
     *
     * @param pParent Parent emitter
     * @param pResource Emitter resource data
     * @return Success
     */
    virtual bool
    Initialize(nw4r::ef::Emitter* pParent,
               nw4r::ef::EmitterResource* pResource) override; // at 0x10

    /**
     * @brief Updates the particles' state and applies any modifiers
     */
    virtual void Calc() override; // at 0x18

    /**
     * @brief Sets the life of all active particles
     *
     * @param life New life
     */
    virtual void SetParticleLife(u16 life); // at 0x24

    /**
     * @brief Sets the size of all active particles
     *
     * @param rSize New size
     */
    virtual void SetParticleSize(const nw4r::math::VEC2& rSize); // at 0x28

    /**
     * @brief Sets the rotation of all active particles
     *
     * @param rRotate New rotation
     */
    virtual void SetParticleRotate(const nw4r::math::VEC3& rRotate); // at 0x2C

private:
    /**
     * @brief Particle modifier flags
     */
    enum {
        EFlag_ModifyLife = 1 << 0,   //!< Life modifier is set
        EFlag_ModifySize = 1 << 1,   //!< Size modifier is set
        EFlag_ModifyRotate = 1 << 2, //!< Rotate modifier is set
    };

private:
    /**
     * @brief Resets all particle modifiers
     */
    virtual void Reset(); // at 0x30

private:
    //! Which modifiers have been set
    u32 mModifyFlags; // at 0xBC

    //! Particle life modifier
    u16 mModifyLife; // at 0xC0
    //! Particle size modifier
    nw4r::math::VEC2 mModifySize; // at 0xC4
    //! Particle rotation modifier
    nw4r::math::VEC3 mModifyRotate;
};

//! @}

#endif
