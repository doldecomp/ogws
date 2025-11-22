#ifndef RP_KERNEL_HOST_IO_SOCKET_MANAGER_H
#define RP_KERNEL_HOST_IO_SOCKET_MANAGER_H
#include <Pack/types_pack.h>

#include <Pack/RPSingleton.h>

//! @addtogroup rp_kernel
//! @{

// Forward declarations
class IRPSysHostIOSocket;

/**
 * @brief Host I/O socket manager
 */
class RPSysHostIOSocketManager {
    RP_SINGLETON_DECL(RPSysHostIOSocketManager);

public:
    /**
     * @brief Adds a new host I/O socket to the node tree
     *
     * @param pChild New child socket
     * @param pParent Parent socket
     */
    static void AddHostIOSocket(IRPSysHostIOSocket* pChild,
                                IRPSysHostIOSocket* pParent = NULL);

    /**
     * @brief Updates the state of the host I/O sockets
     */
    void Update();
};

//! @}

#endif
