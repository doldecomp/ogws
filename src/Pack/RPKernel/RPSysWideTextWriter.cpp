#include <Pack/RPKernel.h>

/**
 * @brief Work buffer for string formatting
 */
wchar_t* RPSysWideTextWriter::spTextBuffer = NULL;

/**
 * @brief Creates the text buffer
 */
void RPSysWideTextWriter::Initialize() {
    spTextBuffer = new wchar_t[TEXT_BUFFER_SIZE];
}
