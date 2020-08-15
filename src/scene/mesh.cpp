#include "scene/mesh.hpp"
#include "scene/item.hpp"

#include <string>
#include <tuple>

namespace Scene
{
    Mesh::Mesh(std::string name, std::pair<int, int> pos, int rot) : Item(name, pos, rot)
    {}
}