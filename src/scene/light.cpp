#include "scene/item.hpp"
#include "scene/light.hpp"

#include <string>
#include <tuple>

namespace Scene
{
    Light::Light(std::string name, int brightness, std::pair<int, int> pos) : Item(name, pos), brightness(brightness)
    {}
}