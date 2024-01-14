#pragma once

#ifdef __clang__
#pragma warning(push)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#endif

#ifdef _MSC_VER
#pragma warning(push, 0)
#endif

#include <fmt/format.h>

#ifdef __clang__
#pragma clang diagnostic pop
#pragma warning(pop)
#endif

#ifdef _MSC_VER
#pragma warning(pop)
#endif
