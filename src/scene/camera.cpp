#include "scene/camera.hpp"
#include "scene/item.hpp"

namespace Scene
{
    Camera::Camera(std::string name, int fov, std::pair<int, int> pos, int rot) : Item(name, pos, rot), fov(fov)
    {}
}