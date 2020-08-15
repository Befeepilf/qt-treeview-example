#ifndef MESH_H
#define MESH_H

#include "scene/item.hpp"

#include <string>
#include <tuple>

namespace Scene
{
    class Mesh : public Item
    {
        public:
            Mesh(std::string name, std::pair<int, int> pos = {0, 0}, int rot = 0);
    };
}

#endif // MESH_H