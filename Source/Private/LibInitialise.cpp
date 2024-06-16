#include "GraphicLib/LibInitialise.h"

#include <glad/glad.h>

namespace GraphicLib {
void Initialise() {
    gladLoadGL();
}
} // namespace GraphicLib