#pragma once

namespace GraphicLib {
struct UniqueIdentifier {
public:
    UniqueIdentifier() noexcept = default;
    UniqueIdentifier(UniqueIdentifier&&) noexcept;
    UniqueIdentifier& operator=(UniqueIdentifier&&) noexcept;
    UniqueIdentifier(const UniqueIdentifier&) = delete;
    UniqueIdentifier& operator=(const UniqueIdentifier&) = delete;
    ~UniqueIdentifier() noexcept = default;
    unsigned int Value{};
    bool IsInitialised{};
};
} // namespace GraphicLib
