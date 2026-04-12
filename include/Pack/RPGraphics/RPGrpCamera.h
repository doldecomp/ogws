#ifndef RP_GRAPHICS_CAMERA_H
#define RP_GRAPHICS_CAMERA_H
#include <Pack/types_pack.h>

#include <nw4r/g3d.h>
#include <nw4r/math.h>

//! @addtogroup rp_graphics
//! @{

// Forward declarations
class RPGrpScreen;

/**
 * @brief Camera controller
 */
class RPGrpCamera {
public:
    /**
     * @brief Camera behavior type
     */
    enum ECameraType {
        //! Use the G3D camera animation result
        ECameraType_Anm,
        //! World matrix is supplied directly
        ECameraType_Direct,
        //! Look at the target position
        ECameraType_LookAt,
        //! Rotate around the target point
        ECameraType_Orbit,
        //! Camera is placed in the scene
        ECameraType_Free,
    };

private:
    //! Default camera
    static RPGrpCamera sDefaultCamera;

    //! Camera view matrix (world -> cam)
    nw4r::math::MTX34 mViewMtx; // at 0x0
    //! Inverse of the view matrix (cam -> world)
    nw4r::math::MTX34 mWorldMtx; // at 0x30
    //! View matrix controlled by a G3D camera animation
    nw4r::math::MTX34 mAnmViewMtx; // at 0x60
    //! World matrix supplied for direct type cameras
    nw4r::math::MTX34 mDirectWorldMtx; // at 0x90

    //! World position of the camera
    nw4r::math::VEC3 mPosition; // at 0xC0
    //! World position of the camera's target
    nw4r::math::VEC3 mTarget; // at 0xCC
    //! Rotation of the camera, in degrees
    nw4r::math::VEC3 mRotation; // at 0xD8

    //! Distance to the camera target
    f32 mDistance; // at 0xE4

    //! Right vector (+X)
    nw4r::math::VEC3 mRight; // at 0xE8
    //! Up vector (+Y)
    nw4r::math::VEC3 mUp; // at 0xF4
    //! Forward vector (+Z)
    nw4r::math::VEC3 mForward; // at 0x100

    //! Camera behavior type
    ECameraType mCameraType; // at 0x10C
    //! Camera state flags
    u16 mFlags; // at 0x110

    //! World matrix during the previous frame
    nw4r::math::MTX34 mWorldMtxOld; // at 0x114

    //! Saved state of the view matrix
    nw4r::math::MTX34 mSavedViewMtx; // at 0x144

public:
    /**
     * @brief Initializes the camera system
     */
    static void Initialize();

    /**
     * @brief Constructor
     */
    RPGrpCamera();

    /**
     * @brief Destructor
     */
    virtual ~RPGrpCamera() {} // at 0x8

    /**
     * @brief Copies the state from another camera
     *
     * @param rOther Camera from which to copy
     */
    virtual void CopyFromAnother(const RPGrpCamera& rOther); // at 0xC

    /**
     * @brief Resets the camera transformation
     */
    void Identity();

    /**
     * @brief Updates the camera state based on the camera type
     */
    void CalcMatrix();

    /**
     * @brief Saves the current state of the view matrix
     */
    void SaveCameraMatrix();

    /**
     * @brief Converts a position from world-space to screen-space
     *
     * @param[out] pScreenPos Position in screen-space
     * @param rWorldPos Position in world-space
     * @param pScreen Screen
     */
    void GetWorldToScreen(nw4r::math::VEC3* pScreenPos,
                          const nw4r::math::VEC3& rWorldPos,
                          const RPGrpScreen* pScreen) const;

    /**
     * @brief Converts a position from screen-space to world-space
     *
     * @param[out] pWorldPos Position in world-space
     * @param rScreenPos Position in screen-space
     * @param pScreen Screen
     */
    void GetScreenToWorld(nw4r::math::VEC3* pWorldPos,
                          const nw4r::math::VEC3& rScreenPos,
                          const RPGrpScreen* pScreen) const;

    /**
     * @brief Converts a position from screen-space to world-space
     *
     * @param[out] pWorldPos Position in world-space
     * @param rScreenPos Position in screen-space
     * @param pScreen Screen
     */
    void GetScreenToWorld(nw4r::math::VEC3* pWorldPos,
                          const nw4r::math::VEC2& rScreenPos,
                          const RPGrpScreen* pScreen) const;

    /**
     * @brief Applies camera settings from the specified scene resource
     *
     * @param scn Scene resource
     * @param refNumber Camera reference number
     * @param frame Animation frame (defaults to the first frame)
     */
    void LoadScnCameraMatrix(const nw4r::g3d::ResAnmScn scn, u8 refNumber,
                             f32 frame = 0.0f);

    /**
     * @brief Sets the type of this camera
     *
     * @param type New camera type
     */
    void SetCameraType(ECameraType type) {
        mCameraType = type;
    }

    /**
     * @brief Accesses the saved state of the view matrix
     */
    const nw4r::math::MTX34& GetSavedCameraMatrix() const {
        return mSavedViewMtx;
    }

    /**
     * @brief Accesses the default camera object
     */
    static RPGrpCamera& GetDefaultCamera() {
        return sDefaultCamera;
    }

private:
    /**
     * @brief Bit flags to control SyncFromMatrix behavior
     */
    enum ESyncFlag {
        //! Derive position using the world matrix
        ESyncFlag_Position = 1 << 0,

        //! Derive the up vector using the world matrix
        ESyncFlag_Up = 1 << 1,
        //! Derive the target position using the world matrix
        ESyncFlag_Target = 1 << 2,
        //! Derive rotation using the world matrix
        ESyncFlag_Rotation = 1 << 3,
        //! Calculate distance to the target position
        ESyncFlag_Distance = 1 << 4,

        //! Derive the view matrix from the world matrix
        ESyncFlag_ViewMtx = 1 << 5,
        //! Derive the world matrix from the view matrix
        ESyncFlag_WorldMtx = 1 << 6,

        //! Save the view matrix to the G3D animation matrix
        ESyncFlag_AnmViewMtx = 1 << 7,
        //! Save the world matrix to the direct world matrix
        ESyncFlag_DirectWorldMtx = 1 << 8,

        // Sync flag presets
        ESyncFlag_ForAnmCamera = ESyncFlag_Position | ESyncFlag_Up |
                                 ESyncFlag_Target | ESyncFlag_Rotation |
                                 ESyncFlag_WorldMtx | ESyncFlag_DirectWorldMtx,

        ESyncFlag_ForDirectCamera = ESyncFlag_Position | ESyncFlag_Up |
                                    ESyncFlag_Target | ESyncFlag_Rotation |
                                    ESyncFlag_ViewMtx | ESyncFlag_AnmViewMtx,

        ESyncFlag_ForLookAtCamera = ESyncFlag_Rotation | ESyncFlag_Distance |
                                    ESyncFlag_WorldMtx | ESyncFlag_AnmViewMtx |
                                    ESyncFlag_DirectWorldMtx,

        ESyncFlag_ForOrbitCamera = ESyncFlag_Position | ESyncFlag_Up |
                                   ESyncFlag_WorldMtx | ESyncFlag_AnmViewMtx |
                                   ESyncFlag_DirectWorldMtx,

        ESyncFlag_ForFreeCamera = ESyncFlag_Up | ESyncFlag_Target |
                                  ESyncFlag_ViewMtx | ESyncFlag_AnmViewMtx |
                                  ESyncFlag_DirectWorldMtx,
    };

    /**
     * @brief Camera state flags
     */
    enum {
        EFlag_5 = 1 << 5,
        EFlag_7 = 1 << 7,
    };

private:
    /**
     * @brief Derives components of the camera state from the world matrix
     *
     * @param flags Flags controlling which components to update
     */
    void SyncFromMatrix(u16 flags);
};

//! @}

#endif
