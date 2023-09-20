#include "GraphicLib/Logger.h"

#include "InternalLogger.h"
#include <cassert>

namespace GraphicLib {
void Logger::SetCallback(MessageCallback callback, const void* userData) {
    assert(callback != nullptr);
    InternalLogger::Get().SetCallback(callback, userData);
}

void Logger::SetSeverity(Severity severity) {
    InternalLogger::Get().SetSeverity(severity);
}
} // namespace GraphicLib
