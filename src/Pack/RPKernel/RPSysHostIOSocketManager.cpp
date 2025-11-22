#include <Pack/RPKernel.h>

RP_SINGLETON_IMPL(RPSysHostIOSocketManager);

/**
 * @brief Constructor
 */
RPSysHostIOSocketManager::RPSysHostIOSocketManager() {
    // Stubbed for release
}

/**
 * @brief Destructor
 */
RPSysHostIOSocketManager::~RPSysHostIOSocketManager() {
    // Stubbed for release
}

/**
 * @brief Adds a new host I/O socket to the node tree
 *
 * @param pChild New child socket
 * @param pParent Parent socket
 */
void RPSysHostIOSocketManager::AddHostIOSocket(
    IRPSysHostIOSocket* /* pChild */, IRPSysHostIOSocket* /* pParent */) {
    // Stubbed for release
}

/**
 * @brief Updates the state of the host I/O sockets
 */
void RPSysHostIOSocketManager::Update() {
    // Stubbed for release
}
