#ifndef RP_KERNEL_EFFECT_BASE_H
#define RP_KERNEL_EFFECT_BASE_H
#include <Pack/types_pack.h>

#include <egg/core.h>

#include <nw4r/ef.h>
#include <nw4r/math.h>

//! @addtogroup rp_kernel
//! @{

/**
 * @brief Effect wrapper
 */
class RPSysEffect {
public:
    /**
     * @brief Constructor
     *
     * @param pName Effect name
     * @param drawGroup Effect draw group
     * @param drawScene Effect draw scene
     */
    RPSysEffect(const char* pName, u32 drawGroup, u32 drawScene);

    /**
     * @brief Destructor
     */
    virtual ~RPSysEffect(); // at 0x8

    /**
     * @brief Creates this effect if it does not yet exist
     *
     * @return Success
     */
    virtual bool create(); // at 0xC

    /**
     * @brief Fades away and destroys this effect
     */
    virtual void fade(); // at 0x10

    /**
     * @brief Fades away this effect without destroying the handle
     */
    virtual void followFade(); // at 0x14

    /**
     * @brief Destroys this effect and all of its particles
     */
    virtual void forceKill(); // at 0x18

    /**
     * @brief Toggles whether this effect will update
     *
     * @param disable Whether to disable updating
     */
    virtual void setDisableCalc(bool disable); // at 0x1C

    /**
     * @brief Toggles whether this effect will draw
     *
     * @param disable Whether to disable drawing
     */
    virtual void setDisableDraw(bool disable); // at 0x20

    /**
     * @brief Toggles whether this effect will update and draw
     *
     * @param disable Whether to disable both updating and drawing
     */
    virtual void setDisableCalcDraw(bool disable); // at 0x24

    /**
     * @brief Sets the lifetime of all particles
     *
     * @param life Lifetime, in ticks
     */
    virtual void setLife(u16 life); // at 0x28

    /**
     * @brief Sets the emission ratio of all emitters
     *
     * @param ratio Emission ratio
     */
    virtual void setEmitRatio(f32 ratio); // at 0x2C

    /**
     * @brief Sets the emission interval of all emitters
     *
     * @param interval Emission interval
     */
    virtual void setEmitInterval(u16 interval); // at 0x30

    /**
     * @brief Sets the number of circular divisions of all emitters
     *
     * @param emitDiv Number of emitter divisions
     */
    virtual void setEmitEmitDiv(u16 emitDiv); // at 0x34

    /**
     * @brief Sets the emission power in the radiation direction
     *
     * @param power Emission power
     */
    virtual void setPowerRadiationDir(f32 power); // at 0x38

    /**
     * @brief Sets the emission power in the specified direction
     *
     * @param power Emission power
     */
    virtual void setPowerSpecDir(f32 power); // at 0x3C

    /**
     * @brief Adds emission power in the specified direction
     *
     * @param add Emission power addend
     */
    virtual void setPowerSpecDirAdd(f32 add); // at 0x40

    /**
     * @brief Sets the specified direction of emission
     *
     * @param rDir Specified direction
     */
    virtual void setSpecDir(const nw4r::math::VEC3& rDir); // at 0x44

    /**
     * @brief Adds to the specified direction of emission
     *
     * @param rDir Specified direction addend
     */
    virtual void setSpecDirAdd(const nw4r::math::VEC3& rAdd); // at 0x48

    /**
     * @brief Sets this effect's velocity
     *
     * @param rVelocity Velocity
     */
    virtual void setVelocity(const nw4r::math::VEC3& rVelocity); // at 0x4C

    /**
     * @brief Sets the color of all particles
     *
     * @param r Color red component
     * @param g Color green component
     * @param b Color blue component
     * @param a Color alpha component
     */
    virtual void setColor(u8 r, u8 g, u8 b, u8 a); // at 0x50

    /**
     * @brief Sets the color of all particles
     * @details This function assumes full alpha
     *
     * @param r Color red component
     * @param g Color green component
     * @param b Color blue component
     */
    virtual void setColor(u8 r, u8 g, u8 b); // at 0x54

    /**
     * @brief Sets the color alpha component of all particles
     * @details This function assumes a white color
     *
     * @param a Color alpha component
     */
    virtual void setColor(u8 a); // at 0x58

    /**
     * @brief Sets the default size of all particles
     *
     * @param rSize Default particle size
     */
    virtual void
    setDefaultParticleSize(const nw4r::math::VEC2& rSize); // at 0x5C

    /**
     * @brief Sets the scale of all particles
     *
     * @param rSize Particle scale
     */
    virtual void setParticleScale(nw4r::math::VEC2& rScale); // at 0x60

    /**
     * @brief Sets the default rotation of all particles
     *
     * @param rRotate Default particle rotation
     */
    virtual void
    setDefaultParticleRotate(const nw4r::math::VEC3& rRotate); // at 0x64

    /**
     * @brief Sets the rotation of all particles
     *
     * @param rRotate Particle rotation
     */
    virtual void setParticleRotate(const nw4r::math::VEC3& rRotate); // at 0x68

    /**
     * @brief Sets the scale of all emitters
     *
     * @param rScale Emitter scale
     */
    virtual void setLocalScale(const nw4r::math::VEC3& rScale); // at 0x6C

    /**
     * @brief Sets this effect's scale without also indirectly scaling particles
     *
     * @param rScale New effect scale
     * @param pParticleScale Current particle scale (optional)
     */
    virtual void
    setDynamicsScale(const nw4r::math::VEC3& rScale,
                     const nw4r::math::VEC2* pParticleScale); // at 0x70

    /**
     * @brief Sets this effect's scale
     *
     * @param scale Effect scale (uniform)
     */
    virtual void setScale(f32 scale); // at 0x74

    /**
     * @brief Sets this effect's scale
     *
     * @param rScale Effect scale
     */
    virtual void setScale(const nw4r::math::VEC3& rScale); // at 0x78

    /**
     * @brief Sets this effect's position
     *
     * @param rPosition Effect position
     */
    virtual void setPos(const nw4r::math::VEC3& rPosition); // at 0x7C

    /**
     * @brief Sets this effect's transformation matrix
     *
     * @param rTransform Effect transformation matrix
     */
    virtual void setMtx(const nw4r::math::MTX34& rTransform); // at 0x80

    /**
     * @brief Toggles whether a particle animation is enabled
     *
     * @param idx Particle animation index
     * @param enable Whether to enable the animation
     */
    virtual void setPtclAnim(int idx, bool enable); // at 0x84

    /**
     * @brief Flushes this effect's configuration
     */
    virtual void update(); // at 0x88

    /**
     * @brief Tests whether the specified flag in emitter userdata is set
     *
     * @param idx Userdata bitflag index
     */
    virtual bool getUserFlag(int idx) const; // at 0x8C

    virtual u8 fn_801941BC(int idx) const; // at 0x90

    /**
     * @brief Clears this effect's configuration
     */
    virtual void reset(); // at 0x94

    /**
     * @brief Tests whether this effect is attached to an instance
     */
    bool isValid() const {
        return mHandle.IsValid();
    }

    /**
     * @brief Tests whether this effect's instance is alive
     */
    bool isAlive() const {
        return mHandle.IsAlive();
    }

private:
    /**
     * @brief Effect state flags
     */
    enum {
        EFlag_PositionDirty,  //!< Effect position should be flushed
        EFlag_TransformDirty, //!< Effect transform should be flushed
        EFlag_ScaleDirty,     //!< Effect scale should be flushed
    };

    //! Maximum effect name length
    static const u32 NAME_LENGTH = 32;

private:
    //! Dummy effect handle
    static const nw4r::ef::Handle<nw4r::ef::Effect> INVALID_HANDLE;

    //! Effect name
    char mName[NAME_LENGTH]; // at 0x4

    //! Effect draw group
    u32 mDrawGroup; // at 0x24
    //! Effect draw scene
    u32 mDrawScene; // at 0x28

    //! Effect state flags
    EGG::TBitFlag<u32> mFlags; // at 0x2C

    //! Effect scale
    nw4r::math::VEC3 mScale; // at 0x30
    //! Effect position
    nw4r::math::VEC3 mPosition; // at 0x3C
    //! Effect transformation matrix
    nw4r::math::MTX34 mTransform; // at 0x48

    //! Effect handle
    nw4r::ef::Handle<nw4r::ef::Effect> mHandle; // at 0x78
};

//! @}

#endif
