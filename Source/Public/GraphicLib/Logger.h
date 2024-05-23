#pragma once

#include "DLL_API.h"

namespace GraphicLib {
class DLL_API Logger {
public:
    enum class Severity : unsigned char {
        HIGH,
        MEDIUM,
        LOW,
        NOTIFICATION,
    };

    enum class Category : unsigned char {
        INTERNAL,
        GRAPHIC_API,
    };

    struct Message {
        Category category{};
        Severity severity{};
        const char* source{};
        const char* text{};
        const void* userData{};
    };

    using MessageCallback = void (*)(const Message& message);
    static void SetCallback(MessageCallback callback, const void* userData);
    static void SetSeverity(Severity severity);
};
} // namespace GraphicLib
