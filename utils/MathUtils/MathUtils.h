// =============================================================================
// Utils | MathUtils
// =============================================================================

#ifndef UTILS_MATHUTILS_
#define UTILS_MATHUTILS_

// create macro for counting elements in array
#define ARR_ELEMENT_COUNT(a) (sizeof(a) / sizeof(*a))

// create to_underlying macro for enums
#define to_underlying(x) uint8_t(x)

#endif