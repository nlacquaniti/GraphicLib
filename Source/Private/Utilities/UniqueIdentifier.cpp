#include "GraphicLib/Utilities/UniqueIdentifier.h"

namespace GraphicLib {
UniqueIdentifier::UniqueIdentifier(UniqueIdentifier&& other) noexcept
    : Value(other.Value)
    , IsInitialised(other.IsInitialised) {
    other.Value = 0;
    other.IsInitialised = false;
}

UniqueIdentifier& UniqueIdentifier::operator=(UniqueIdentifier&& other) noexcept {
    this->Value = other.Value;
    this->IsInitialised = other.IsInitialised;
    other.Value = 0;
    other.IsInitialised = false;
    return *this;
}
} // namespace GraphicLib
