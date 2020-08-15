#ifndef ITEM_VARIANT_H
#define ITEM_VARIANT_H

#include "scene/camera.hpp"
#include "scene/group.hpp"
#include "scene/light.hpp"
#include "scene/mesh.hpp"

#include <variant>

namespace Scene
{
    using ItemVariant = std::variant<Group, Mesh*, Camera*, Light*>;
}

#endif // ITEM_VARIANT_H