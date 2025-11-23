# Contributing

Thank you for your interest in the project!

We ask that you please follow these contribution guidelines to ensure consistency across the codebase and its documentation.

## Project Structure

```text
└── src / include:
    ├── egg: Nintendo EAD middleware
    ├── MetroTRK: Metrowerks Target Resident Kernel (TRK) Debugger
    ├── MSL: Metrowerks Standard Library
    ├── nw4r: NintendoWare for Revolution (NW4R) SDK
    ├── Pack: Revolution Pack Project (RP)
    ├── revolution: Revolution (RVL) SDK
    ├── runtime: CodeWarrior compiler runtime
    └── RVLFaceLib: Revolution Face Library (RFL)
```

## File Formats

Please use the following file extensions for code:

| File Extension | Usage                                                |
| -------------- | ---------------------------------------------------- |
| `*.c`          | C function definition(s)                             |
| `*.cpp`        | C++ function/class definition(s)                     |
| `*.h`          | C/C++ function/class declaration(s)                  |

## Style Guide

This repository contains a `.clang-format` configuration file which handles most of the code formatting automatically.

Even then, there are some important style elements to manually conform to:

### Header Guards

Although this project will likely always use the CodeWarrior compiler, which supports the `#pragma once` directive, please use standard include guards instead.

This is done both for readability purposes and to provide context about the file inside the guard:

- `#ifndef EGG_CORE_ARCHIVE_H` -> `include/egg/core/eggArchive.h`
- `#ifndef NW4R_UT_LIST_H` -> `include/nw4r/ut/ut_list.h`

#### Guard syntax

Please use the following format:

```cpp
#ifndef {library}_{module}_{filename}_H
#define {library}_{module}_{filename}_H

// . . .

#endif
```

Identifier terms separated by case/underscores should be converted to underscores in the guard name:

- `myClass` -> `MY_CLASS`
- `MyClass` -> `MY_CLASS`
- `My_Class` -> `MY_CLASS`
- `MYClass` -> `MY_CLASS`

> [!IMPORTANT]
> The only exception is for Pack Project (RP) files. The classes exist in the global namespace, and as such often include the module name in *both the directory and filename*:
>
> - `include/Pack/RPAudio/RPSndAudioMgr.h` -> `#ifndef RP_AUDIO_SND_AUDIO_MGR_H`
> - `include/Pack/RPGraphics/RPGrpRenderer.h` -> `#ifndef RP_GRAPHICS_RENDERER_H`
> - `include/Pack/RPUtility/RPUtlBaseFsm.h` -> `#ifndef RP_UTILITY_BASE_FSM_H`

### Include Directives

*Include-what-you-use.* Unnecessary `#include` directives only increase the duration of compilation.

#### Include syntax

Please use the `<>` characters over `""` when writing include paths, and use filepaths relative to `include/` or `lib/`:

```cpp
#include "include/Pack/RPGraphics.h" // ❌ Don't do this!!!
#include <include/Pack/RPGraphics.h> // ❌ Don't do this!!!
#include "Pack/RPGraphics.h"         // ❌ Don't do this!!!
#include <Pack/RPGraphics.h>         // ✅ Do this!!!
```

#### Vs. forward declarations

If a forward declaration can resolve the dependency, favor that over `#include`'ing the corresponding file:

```cpp
#include <Pack/RPGraphics.h> // ❌ Don't do this!!!

class RPGrpRenderer {
public:
    void AppendDrawObject(IRPGrpDrawObject* pDrawObject);
```

```cpp
// Forward declarations
class IRPGrpDrawObject; // ✅ Do this!!!

class RPGrpRenderer {
public:
    void AppendDrawObject(IRPGrpDrawObject* pDrawObject);
```

The only exception is when dealing with symbols from other libraries:

```cpp
#include <egg/core.h>   // ✅ From different library, so #include is OK.

// Forward declarations
class IRPGrpDrawObject; // ✅ From same library, so forward declare it.
namespace EGG {
class Heap; // ❌ Don't do this!!! Heap is from the EGG library, not RP!
}

class RPGrpRenderer {
public:
    static void SetEfbClearColor(const EGG::Color& rColor);
    void AppendDrawObject(IRPGrpDrawObject* pDrawObject);
```

If you do need to write forward declarations, please write a comment as follows:

```cpp
// Forward declarations
class IRPGrpDrawObject;
class IRPGrpModelCallback;
class IRPGrpHostIOSocket;
```

#### Public header files

Many libraries/modules have a "public" or "external" header file which will, in-turn, `#include` all of its internal files.

For example, `include/revolution/NAND.h` is the public header file for the NAND library:

```cpp
#ifndef RVL_SDK_PUBLIC_NAND_H
#define RVL_SDK_PUBLIC_NAND_H
#ifdef __cplusplus
extern "C" {
#endif

#include <revolution/NAND/NANDCheck.h>
#include <revolution/NAND/NANDCore.h>
#include <revolution/NAND/NANDOpenClose.h>
#include <revolution/NAND/nand.h>

#ifdef __cplusplus
}
#endif
#endif
```

> [!CAUTION]
> Using public headers is OK as long as:
>
> - They are from another library
> - You are writing the `#include` directive in an implementation file (`*.c`/`*.cpp`)
>
Otherwise, it is very easy to form a circular dependency. Here's an example!

`egg/core/eggDvdFile.h`:

```cpp
#include <egg/core.h>         // ❌ It will cause a circular dependency!
#include <egg/core/eggFile.h> // ✅ Include only what you use.
#include <revolution/DVD.h>   // ✅ DVD is in another library (RVL SDK).
```

`egg/core/eggDvdFile.cpp`:

```cpp
#include <egg/core.h>         // ✅ OK because this is the implementation file!
#include <egg/core/eggFile.h> // ✅ Also OK.
#include <revolution/DVD.h>   // ✅ DVD is in another library (RVL SDK).
```

#### Types headers

All header files must at least include the types header file:

| Library    | Types header                 |
| ---------- | ---------------------------- |
| NW4R       | `<nw4r/types_nw4r.h>`        |
| EGG        | `<egg/types_egg.h>`          |
| RP         | `<Pack/types_pack.h>`        |
| All others | `<types.h>`                  |

### Naming Scheme

> [!IMPORTANT]
> The only exceptions to the rules below are identifiers that must be named otherwise for the sake of decompilation accuracy.
>
> This includes functions/data with known symbols, and any identifiers whose names are revealed by assertions and other strings in the binary.

#### Function naming

Please write function names in PascalCase:

```cpp
void myFunction();  // ❌ Don't do this!!!
void my_function(); // ❌ Don't do this!!!
void MyFunction();  // ✅ Do this!!!
```

#### Data naming

Please use the following prefixes for data members/function parameters:

| Prefix | Meaning                                 |
| ------ | --------------------------------------- |
| `m`    | C++ class private member                |
| `s`    | C/C++ static, private member            |
| `p`    | C/C++ pointer-typed member or variable  |
| `r`    | C++ reference-typed member or variable |

If no prefix is required, write the name in camelCase.

These can be combined/stacked in the same order as the table; however, **the member (`m`) and static (`s`) prefixes are mutually exclusive**:

```cpp
class X {
public:
    int var;  // ✅ Do this!!!
    int mVar; // ❌ Don't do this!!! This is a public member!

private:
    int id;  // ❌ Don't do this!!! This is a private member!
    int mID; // ✅ Do this!!!

    int* mNum;    // ❌ Don't do this!!! This is a pointer!
    int* mpNum;   // ✅ Do this!!!
    int** mppNum; // ✅ Do this!!!

    int& mHandle;  // ❌ Don't do this!!! This is a reference!
    int& mrHandle; // ✅ Do this!!!

    static void* mpBuffer;  // ❌ Don't do this!!! This is a static member!
    static void* mspBuffer; // ❌ Don't do this!!! Don't combine 'm' and 's'!
    static void* spBuffer;  // ✅ Do this!!!
};

int MemCopy(void* buffer, u32 size);  // ❌ Don't do this!!! 'buffer' is a pointer!
int MemCopy(void* pBuffer, u32 size); // ✅ Do this!!!

bool GetHandle(int& handle);  // ❌ Don't do this!!! 'handle' is a reference!
bool GetHandle(int& rHandle); // ✅ Do this!!!
```

#### Macro naming

Please write macros in uppercase SNAKE_CASE.

### Declaration Order

Please use the following order when writing C++ classes:

1. Public members
2. Protected members
3. Private members

#### Order per section

In each section (public/protected/private), use the following order of declarations:

- Type aliases (`friend`, `typedef`, `using`)
- Nested types
- Literal constants

**Re-declare the access specifier at this point!**

- Constructor(s) and assignment operator(s)
- Destructor
- Virtual functions
- All other functions

**Re-declare the access specifier at this point!**

- Constant, static members
- Non-constant, static members
- All other data members

```cpp
class FruitBasket : public IBasket {
// 1. PUBLIC ACCESS
public:
    // 1. Type aliases (`friend`, `typedef`, `using`)
    friend class BasketMgr;
    
    typedef TList<FruitBasket> FruitBasketList;
    using IBasket::Foo;

    // 2. Nested types
    struct Fruit : public IObject {
        String name;
        Color color;
    };

    // 3. Literal constants
    static const int FRUIT_MAX = 10;

// Re-declare access specifier
public:
    // 4. Constructor(s) and assignment operator(s)
    FruitBasket();
    FruitBasket& operator=(const FruitBasket& rOther);
    // 5. Destructor
    virtual ~FruitBasket();

    // 6. Static functions
    static String GetName() {
        return "FruitBasket";
    }

    // 7. Non-static functions
    void AddFruit(const Fruit& rFruit) {
        mFruits.PushBack(rFruit);
    }

// 2. PROTECTED ACCESS
protected:
    // 7. Non-static functions
    const Fruit& GetFruit(int i) const {
        return mFruits[i];
    }

// 3. PRIVATE ACCESS
private:
    // 7. Non-static functions
    void Clear();

    // 8. Constant, static members
    static const IBasket::Profile PROFILE;

    // 9. Non-constant, static members
    static TList<FruitBasket> sInstances;

    // 10. All other data members
    TList<Fruit> mFruits;
};
```

### Doxygen

This repository uses [Doxygen](https://www.doxygen.nl) as the standard format for documentation.

#### Doxygen syntax

- Use the `@` prefix to issue Doxygen commands, rather than `\`.
- Use `//!` for single-line Doxygen comments, rather than  `///`.

#### Doxygen groups

The only required Doxygen grouping is for modules that are not distinguished by namespaces. This is especially true for C code where there is no such construct as a "namespace".

For example, the Doxygen group hierarchy `NW4R` -> `ut` is represented by the contents of the namespace `nw4r::ut`.

For some libraries, this relation does not occur. EGG has many modules but only one namespace. To get around this, the contents of their header files are divided into Doxygen groups depending on the directory the file is in.

Below is the outline of `egg/core/eggDvdFile.h`. It exists in the `core` module of EGG, but must be explicitly placed into a Doxygen group because it only uses the root `EGG` namespace:

```cpp
#ifndef EGG_CORE_DVD_FILE_H
#define EGG_CORE_DVD_FILE_H
#include <egg/types_egg.h>

namespace EGG {
//! @addtogroup egg_core
//! @{

    // File contents . . .

//! @}
} // namespace EGG

#endif
```

> [!NOTE]
> Due to this repository being in the early stages, it is not important to include documentation in files outside of the Pack Project modules (the "game code").

**To see a list of all Doxygen groups, please see `include/__doxygen.hpp`.**

#### Comments

Comments do not have heavy restrictions, but they should follow a consistent format to generate readable Doxygen pages:

##### Function comments

When documenting functions, write the `@brief` description such that it could be prefixed with "This function" and still make sense:

```cpp
// ❌ [This function] **CLEAR** the memory buffer
/**
 * @brief Clear the memory buffer
 */
void Clear();

// ✅ [This function] **CLEARS** the memory buffer
/**
 * @brief Clears the memory buffer
 */
void Clear();
```

If the function is a simple check that returns a boolean result, start the description with "Tests whether":

```cpp
/**
 * @brief Tests whether the buffer is empty
 */
bool Empty() const;
```

Functions should document all parameters with the `@param` command:

```cpp
/**
 * @brief Advances this stream's position
 *
 * @param dir Seek direction
 * @param offset Seek offset
 */
void Seek(ESeekDir dir, s32 offset);
```

If the return value is not obvious, explain its purpose with the `@return` command:

> [!WARNING]
> It is easy to accidentally use `@returns` (with the "s") instead of `@return`.
>
> Please use `@return` in your documentation.

```cpp
/**
 * @brief Writes data to this stream (internal implementation)
 *
 * @param pSrc Source buffer
 * @param size Number of bytes to write
 * @return Number of bytes written, or DVD error code
 */
s32 WriteImpl(const void* pSrc, u32 size);
```

If a pointer/reference typed parameter is meant to be given an initial value through the function, mark it as an ***out*** parameter, like so:

```cpp
/**
 * @brief Gets the console's IP address
 *
 * @param rAddr[out] IPv4 address
 */
void GetHostAddr(SockAddr4& rAddr)
```

Doxygen also provides the `[in]` tag to mark input parameters.

However, please only use this tag if the parameter is both an in **and** out parameter. This is common with "in-place" algorithms:

```cpp
/**
 * @brief Performs the Fisher-Yates shuffle algorithm to generate a random
 * permutation of the specified values
 *
 * @param[in,out] rArray Input array (shuffled in-place)
 * @param size Length of input array
 */
void Shuffle(int* pArray, size_t size) {
```

##### Structure comments

Structures (`struct`/`class`) should at least provide a `@brief` description:

```cpp
/**
 * @brief Interface for binary file serialization/deserialization
 */
class IBinary {
public:
```

##### Enumeration comments

Enumerations (`enum`) should at least provide a `@brief` description:

```cpp
/**
 * @brief Stream seek origin
 */
enum ESeekDir { ESeekDir_Begin, ESeekDir_Current, ESeekDir_End };
```

##### Macro comments

Macros can be documented like functions, but also a single-line comment will suffice when there are no parameters, or their purpose is obvious:

```cpp
/**
 * @brief Helper for creating version numbers
 * 
 * @param major Major version number
 * @param minor Minor version number
 */
#define K_VERSION(major, minor) ((major << 8) | minor)

//! Helper for creating version numbers
#define K_VERSION(major, minor) ((major << 8) | minor)
```

##### Data comments

Data members should provide a single-line brief description. It does not matter whether this is a comment above or after the declaration:

```cpp
//! Stream open flag
bool mIsOpen; 
//! Position in data 
u32 mPosition;

bool mIsOpen;  //!< Stream open flag
u32 mPosition; //!< Position in data
```

> [!NOTE]
> Please do not mix these types of comments in the same scope!

##### Constructor/Destructor comments

The brief description for constructors should be "Constructor", and the brief description for destructors should be "Destructor":

```cpp
/**
 * @brief Constructor
 */
IStream();

/**
 * @brief Destructor
 */
virtual ~IStream();
```

If there are many constructor overloads for purposes such as moving/copying, feel free to specify the constructor "type" in the Doxygen detailed description:

```cpp
/**
 * @brief Constructor
 */
Optional();

/**
 * @brief Constructor
 * @details Null constructor
 */
Optional(NullOpt);

/**
 * @brief Constructor
 * @details Copy constructor
 *
 * @param rOther Optional value
 */
Optional(const Optional& rOther);

/**
 * @brief Constructor
 * @details Copy constructor
 *
 * @param rValue Value
 */
Optional(const T& rValue);
```
