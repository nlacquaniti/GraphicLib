#pragma once

#include "DLL_API.h"

namespace GraphicLib {
class DLL_API Logger {
public:
    enum class Severity
    {
        HIGH,
        MEDIUM,
        LOW,
        NOTIFICATION,
    };
    struct Message {
        Severity severity{};
        const char* source{};
        const char* type{};
        const char* text{};
        const void* userData{};
    };
    using MessageCallback = void (*)(const Message& message);
    static void SetCallback(MessageCallback callback, const void* userData);
    static void SetSeverity(Severity severity);
};
} // namespace GraphicLib
