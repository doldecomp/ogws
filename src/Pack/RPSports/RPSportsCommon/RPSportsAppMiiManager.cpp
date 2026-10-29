#include <RPSports/RPSportsCommon/RPSportsAppMiiManager.h>
#include <Pack/RPSystem.h>

/**
 * @brief Constructor
 *
 * @param pHeap Heap to use for allocations
 */
RPSportsAppMiiManager::RPSportsAppMiiManager(EGG::Heap *pHeap) : RPSysAppMiiManager(60, pHeap)
{
}

/**
 * @brief Destructor
 */
RPSportsAppMiiManager::~RPSportsAppMiiManager()
{
}
