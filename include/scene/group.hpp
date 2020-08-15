#ifndef GROUP_H
#define GROUP_H

#include "scene/camera.hpp"
#include "scene/item.hpp"
#include "scene/light.hpp"
#include "scene/mesh.hpp"

#include <string>
#include <variant>
#include <vector>

namespace Scene
{
    struct Group
    {
        std::string name;
        std::vector<std::variant<Group, Mesh*, Camera*, Light*>> children;
    };
}

#endif // GORUP_H