#include <Pack/RPGraphics.h>

#include <egg/core.h>

/**
 * @brief File extension for RPGrpModelMisc binaries
 */
template <> const char* EGG::IBinary<RPGrpModelMisc>::spExtension = "pmmisc";

/**
 * @brief Gets the binary signature of this object
 */
const char* RPGrpModelMisc::GetBinaryType() const override {
    return "MMSC";
}
