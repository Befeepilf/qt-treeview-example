#ifndef CAMERA_H
#define CAMERA_H

#include "scene/item.hpp"

#include <string>
#include <tuple>

namespace Scene
{
    class Camera : public Item
    {
        public:
            Camera(std::string name, int fov, std::pair<int, int> pos = {0, 0}, int rot = 0);

        private:
            int fov;
    };
}

#endif // CAMERA_H