#pragma once

#ifdef WD_ENABLE_ASSERTS
#define WD_ASSERT(x, ...)                             \
  {                                                   \
    if (!(x)) {                                       \
      WD_ERROR("Assertion failed: {0}", __VA_ARGS__); \
    }                                                 \
  }
#define WD_CORE_ASSERT(x, ...)                             \
  {                                                        \
    if (!(x)) {                                            \
      WD_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); \
    }                                                      \
  }
#else
#define WD_ASSERT(x, ...)
#define WD_CORE_ASSERT(x, ...)
#endif