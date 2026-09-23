#ifndef NW4R_EF_MEMORY_MANAGER_CONFIG_H
#define NW4R_EF_MEMORY_MANAGER_CONFIG_H
#include <nw4r/types_nw4r.h>

// clang-format off
//
// Effect memory management in nw4r::ef involves watching the lifetime of four object types: 
//   - Effects created by the system (nw4r::ef::Effect)
//   - Emitters created by their effects (nw4r::ef::Emitter)
//   - Particle managers (nw4r::ef::ParticleManager)
//   - Particles created by their managers (nw4r::ef::Particle)
//
// NW4R provides the MemoryManagerBase interface to allow the implementation to be swapped out.
// Register a memory manager with the effect system, and it will be used for all memory allocations.
//
// The default concrete implementation is MemoryManager, which leverages MemoryManagerTmp for object pooling.
// However, MemoryManagerTmp requires explicit template specializations for its GarbageCollection method.
//
// Customizing the default MemoryManager becomes difficult for developers because they would need to
// dig into nw4r::ef internals to understand MemoryManagerTmp and implement GarbageCollection for their object types.
//
// As such, the only way to reasonably support derived object types in these two classes
// is to allow developers to configure the basic MemoryManager through the use of preprocessor macros.
//
// There exists some information we can gather that gives this theory some merit.
//
// nw4r::ef::MemoryManager contains very large functions defined in-header, despite inlining them being impossible.
//
// In New Super Mario Bros. Wii, debugging symbols reveal that a modified MemoryManager exists for EGG types.
// Additionally, the classes keep their original names (MemoryManager, MemoryManagerTmp) but are strangely in the global namespace.
//
// Stringitized expressions leftover in debug NW4R assertions reveal that MemoryManagerTmp accesses members
// of the nw4r::ef namespace using "::nw4r::ef::".
//
// clang-format on

// Opening namespace declarations
#if !defined(NW4R_EF_MEMORY_MANAGER_NAMESPACE_OPEN)
#if defined(NW4R_EF_MEMORY_MANAGER_CONFIGURED)
#define NW4R_EF_MEMORY_MANAGER_NAMESPACE_OPEN
#else
#define NW4R_EF_MEMORY_MANAGER_NAMESPACE_OPEN                                  \
    namespace nw4r {                                                           \
    namespace ef {
#endif
#endif

// Closing namespace declarations
#if !defined(NW4R_EF_MEMORY_MANAGER_NAMESPACE_CLOSE)
#if defined(NW4R_EF_MEMORY_MANAGER_CONFIGURED)
#define NW4R_EF_MEMORY_MANAGER_NAMESPACE_CLOSE
#else
#define NW4R_EF_MEMORY_MANAGER_NAMESPACE_CLOSE                                 \
    }                                                                          \
    }
#endif
#endif

// Memory manager class name
#if !defined(NW4R_EF_MEMORY_MANAGER_CLASS)
#define NW4R_EF_MEMORY_MANAGER_CLASS MemoryManager
#endif

// Temp memory manager class name
#if !defined(NW4R_EF_MEMORY_MANAGER_TMP_CLASS)
#define NW4R_EF_MEMORY_MANAGER_TMP_CLASS MemoryManagerTmp
#endif

// Effect object class type
#if !defined(NW4R_EF_MEMORY_MANAGER_TEFFECT)
#define NW4R_EF_MEMORY_MANAGER_TEFFECT ::nw4r::ef::Effect
#endif

// Emitter object class type
#if !defined(NW4R_EF_MEMORY_MANAGER_TEMITTER)
#define NW4R_EF_MEMORY_MANAGER_TEMITTER ::nw4r::ef::Emitter
#endif

// Particle manager object class type
#if !defined(NW4R_EF_MEMORY_MANAGER_TPARTICLEMANAGER)
#define NW4R_EF_MEMORY_MANAGER_TPARTICLEMANAGER ::nw4r::ef::ParticleManager
#endif

// Particle object class type
#if !defined(NW4R_EF_MEMORY_MANAGER_TPARTICLE)
#define NW4R_EF_MEMORY_MANAGER_TPARTICLE ::nw4r::ef::Particle
#endif

#if defined(NW4R_EF_MEMORY_MANAGER_CONFIGURED)
#define NW4R_EF_MEMORY_MANAGER_MEMBER_ACCESS public:
#else
#define NW4R_EF_MEMORY_MANAGER_MEMBER_ACCESS private:
#endif

NW4R_EF_MEMORY_MANAGER_NAMESPACE_OPEN;

// Expose user object types
typedef NW4R_EF_MEMORY_MANAGER_TEFFECT TEffect;
typedef NW4R_EF_MEMORY_MANAGER_TEMITTER TEmitter;
typedef NW4R_EF_MEMORY_MANAGER_TPARTICLEMANAGER TParticleManager;
typedef NW4R_EF_MEMORY_MANAGER_TPARTICLE TParticle;

NW4R_EF_MEMORY_MANAGER_NAMESPACE_CLOSE;

#endif
