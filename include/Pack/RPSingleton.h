#ifndef RP_SINGLETON_H
#define RP_SINGLETON_H
#include <Pack/types_pack.h>

#include <egg/core.h>
#include <egg/prim.h>

/**
 * @brief Declarations for a singleton class
 */
#define RP_SINGLETON_DECL(T)                                                   \
public:                                                                        \
    static T* CreateInstance();                                                \
    static void DestroyInstance();                                             \
    static T* instance() {                                                     \
        return spInstance;                                                     \
    };                                                                         \
                                                                               \
private:                                                                       \
    T();                                                                       \
    virtual ~T();                                                              \
                                                                               \
private:                                                                       \
    /** Class singleton instance */                                            \
    static T* spInstance;

/**
 * @brief Implementation for a singleton class
 */
#define RP_SINGLETON_IMPL(T)                                                   \
    T* T::spInstance = NULL;                                                   \
                                                                               \
    T* T::CreateInstance() {                                                   \
        spInstance = new T();                                                  \
        return spInstance;                                                     \
    }                                                                          \
    void T::DestroyInstance() {                                                \
        delete spInstance;                                                     \
        spInstance = NULL;                                                     \
    }

/**
 * @brief Declarations for a singleton class which uses the specified heap
 */
#define RP_SINGLETON_DECL_EX(T)                                                \
public:                                                                        \
    static T* CreateInstance(EGG::Heap* pHeap);                                \
    static void DestroyInstance();                                             \
    static T* instance() {                                                     \
        return spInstance;                                                     \
    }                                                                          \
                                                                               \
private:                                                                       \
    T(EGG::Heap* pHeap);                                                       \
    virtual ~T();                                                              \
                                                                               \
private:                                                                       \
    /** Heap in which this object was allocated */                             \
    EGG::Heap* mpParentHeap;                                                   \
                                                                               \
private:                                                                       \
    /** Class singleton instance */                                            \
    static T* spInstance;

/**
 * @brief Implementation for a singleton class which uses the specified heap
 */
#define RP_SINGLETON_IMPL_EX(T)                                                \
    T* T::spInstance = NULL;                                                   \
                                                                               \
    T* T::CreateInstance(EGG::Heap* pHeap) {                                   \
        if (spInstance == NULL) {                                              \
            spInstance = new (pHeap) T(pHeap);                                 \
            return spInstance;                                                 \
        }                                                                      \
        return NULL;                                                           \
    }                                                                          \
                                                                               \
    void T::DestroyInstance() {                                                \
        delete spInstance;                                                     \
        spInstance = NULL;                                                     \
    }

/**
 * @brief Accesses a singleton instance by typename
 */
#ifndef RP_GET_INSTANCE
#define RP_GET_INSTANCE(T) T::instance()
#endif

#endif
