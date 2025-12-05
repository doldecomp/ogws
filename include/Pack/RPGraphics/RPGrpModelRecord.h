#ifndef RP_GRAPHICS_MODEL_RECORD_H
#define RP_GRAPHICS_MODEL_RECORD_H
#include <Pack/types_pack.h>

//! @addtogroup rp_graphics
//! @{

// Forward declarations
class RPGrpModel;

/**
 * @brief Model transformation recorder
 */
class RPGrpModelRecord {
public:
    /**
     * @brief Constructor
     *
     * @param flags Bound type flags
     * @param pModel Owner model
     */
    RPGrpModelRecord(u16 frames, RPGrpModel* pModel);

    /**
     * @brief Destructor
     */
    virtual ~RPGrpModelRecord() {} // at 0x8

    /**
     * @brief Clears the recorded data
     */
    void Clear();

    /**
     * @brief Records the current frame
     *
     * @param pModel Model to record
     */
    void Calc(RPGrpModel* pModel);

private:
    char unk4[0x48 - 0x4];
};

//! @}

#endif
