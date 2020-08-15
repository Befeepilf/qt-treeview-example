#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <tuple>


namespace Scene
{
    class Item
    {
        public:
            Item(std::string name, std::pair<int, int> pos = {0, 0}, int rot = 0);

            std::string name(void) const;

        private:
            std::string m_name;
            std::pair<int, int> pos;
            int rot;
    };
}

#endif // ITEM_H