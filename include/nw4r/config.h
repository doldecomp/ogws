#ifndef NW4R_CONFIG_H
#define NW4R_CONFIG_H

#if !defined(NW4R_VERSION)
#error Please provide a value for NW4R_VERSION!
#endif

// Binary file byteorder marks
#define NW4R_BYTEORDER_LITTLE 0xFFFE
#define NW4R_BYTEORDER_BIG 0xFEFF

// Native byteorder mark
#if defined(NW4R_LITTLE_ENDIAN)
#define NW4R_BYTEORDER_NATIVE NW4R_BYTEORDER_LITTLE

#elif defined(NW4R_BIG_ENDIAN)
#define NW4R_BYTEORDER_NATIVE NW4R_BYTEORDER_BIG

#else
#error Please define either NW4R_LITTLE_ENDIAN, or NW4R_BIG_ENDIAN!
#endif

// Debug configuration enables assertions, exception handler
#if defined(NW4R_DEBUG)
#define NW4R_FEATURE_ASSERT
#define NW4R_FEATURE_EXCEPTION

#if !defined(NW4R_DISABLE_MAPFILE)
#define NW4R_FEATURE_MAPFILE
#endif

// Release configuration enables exception handler
#elif defined(NW4R_RELEASE)
#define NW4R_FEATURE_EXCEPTION

#if !defined(NW4R_DISABLE_MAPFILE)
#define NW4R_FEATURE_MAPFILE
#endif

// Product configuration disables everything
#elif defined(NW4R_PRODUCT)

#else
#error Please define either NW4R_DEBUG, NW4R_RELEASE, or NW4R_PRODUCT!
#endif

#endif
