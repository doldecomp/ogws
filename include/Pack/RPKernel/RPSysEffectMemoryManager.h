#ifndef RP_KERNEL_EFFECT_MEMORY_MANAGER_H
#define RP_KERNEL_EFFECT_MEMORY_MANAGER_H
#include <Pack/types_pack.h>

#include <Pack/RPKernel/RPSysParticleManager.h>

// nw4r::ef::MemoryManager configuration
#define NW4R_EF_MEMORY_MANAGER_CONFIGURED
#define NW4R_EF_MEMORY_MANAGER_TMP_CLASS RPSysEffectMemoryManagerTmp
#define NW4R_EF_MEMORY_MANAGER_CLASS RPSysEffectMemoryManager
#define NW4R_EF_MEMORY_MANAGER_TPARTICLEMANAGER RPSysParticleManager

// Include with NW4R_EF_MEMORY_MANAGER_CONFIGURED to get ef_memorymanagerimpl.h
#include <nw4r/ef.h>

#endif
