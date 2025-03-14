#ifndef RVL_SDK_SO_SOCOMMON_H
#define RVL_SDK_SO_SOCOMMON_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

//! @addtogroup rvl_so
//! @{

#define SO_O_NONBLOCK 0x4

#define SO_INADDR_ANY 0

#define SO_POLLRDNORM 0x1
#define SO_POLLWRNORM 0x8
#define SO_POLLERR 0x20
#define SO_POLLHUP 0x40

#define SOMAXCONN 5

typedef s32 SOSocket;

typedef enum {
    SO_SUCCESS = 0,
    SO_EWOULDBLOCK = -6,
    SO_EALREADY = -7,
    SO_ECONNRESET = -15,
    SO_EHOSTUNREACH = -23,
    SO_EINPROGRESS = -26,
    SO_EINVAL = -28,
    SO_EISCONN = -30,
    SO_EMSGSIZE = -35,
    SO_ENOBUFS = -42,
    SO_ENOMEM = -49,
    SO_ENOTCONN = -56,
    SO_ETIMEDOUT = -76,
} SOResult;

typedef enum {
    SO_PF_INET = 2,
    SO_PF_INET6 = 23,
} SOProtoFamily;

typedef enum {
    SO_AF_INET = 2,
    SO_AF_INET6 = 23,
} SOAddrFamily;

typedef enum {
    SO_SOCK_STREAM = 1,
    SO_SOCK_DGRAM = 2,
} SOSockType;

typedef enum {
    SO_IPPROTO_IP = 0,
    SO_IPPROTO_TCP = 6,
    SO_IPPROTO_UDP = 17,
} SOIPProtocol;

typedef enum { SO_F_GETFL = 3, SO_F_SETFL = 4 } SOFcntlCmd;

typedef enum {
    SO_MSG_OOB = (1 << 0),
    SO_MSG_PEEK = (1 << 1),
    SO_MSG_WAITALL = (1 << 2),
} SOMsgFlag;

typedef enum {
    SO_SOL_SOCKET = 0xFFFF,
} SOSockOptLevel;

typedef enum {
    SO_SO_REUSEADDR = 0x0004,
    SO_SO_SNDBUF = 0x1002,
    SO_SO_RCVBUF = 0x1003,
} SOSockOpt;

typedef enum { SO_SHUT_RD, SO_SHUT_WR, SO_SHUT_RDWR } SOShutdownType;

typedef struct SOInAddr {
    union {
        u32 raw;
        u8 octets[4];
    }; // at 0x0
} SOInAddr;

typedef struct SOInAddr6 {
    union {
        u8 bytes[16];
        u16 groups[8];
    }; // at 0x0
} SOInAddr6;

typedef struct SOSockAddrIn {
    u8 len;        // at 0x0
    u8 family;     // at 0x1
    u16 port;      // at 0x2
    SOInAddr addr; // at 0x4
} SOSockAddrIn;

typedef struct SOSockAddrIn6 {
    u8 len;         // at 0x0
    u8 family;      // at 0x1
    u16 port;       // at 0x2
    u32 flowinfo;   // at 0x4
    SOInAddr6 addr; // at 0x8
    u32 scope;      // at 0x18
} SOSockAddrIn6;

typedef struct SOSockAddr {
    union {
        struct {
            u8 len;    // at 0x0
            u8 family; // at 0x1
            u16 port;  // at 0x2
        };
        SOSockAddrIn in;   // at 0x0
        SOSockAddrIn6 in6; // at 0x0
    };
} SOSockAddr;

typedef struct SOHostEnt {
    char* name;     // at 0x0
    char** aliases; // at 0x4
    s16 addrType;   // at 0x8
    s16 length;     // at 0xA
    u8** addrList;  // at 0xC
} SOHostEnt;

typedef struct SOAddrInfo {
    s32 flags;               // at 0x0
    s32 family;              // at 0x4
    s32 type;                // at 0x8
    s32 protocol;            // at 0xC
    s32 len;                 // at 0x10
    SOSockAddr* addr;        // at 0x14
    char* name;              // at 0x18
    struct SOAddrInfo* next; // at 0x1C
} SOAddrInfo;

typedef struct SOPollFD {
    s32 fd;      // at 0x0
    s32 events;  // at 0x4
    s32 revents; // at 0x8
} SOPollFD;

//! @}

#ifdef __cplusplus
}
#endif
#endif
