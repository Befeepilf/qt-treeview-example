#ifndef LIGHT_H
#define LIGHT_H

#include "scene/item.hpp"

#include <string>
#include <tuple>

namespace Scene
{
    class Light : public Item
    {
        public:
            Light(std::string name, int brightness, std::pair<int, int> pos = {0, 0});
        
        private:
            int brightness;

    };
}

#endif // LIGHT_H