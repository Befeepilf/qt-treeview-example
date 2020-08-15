#include "scene/item.hpp"

#include <string>

namespace Scene
{
    Item::Item(std::string name, std::pair<int, int> pos, int rot) : m_name(name), pos(pos), rot(rot)
    {}

    std::string Item::name(void) const
    {
        return "test";
    }
}