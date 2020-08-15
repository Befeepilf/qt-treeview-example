#include "store.hpp"

#include <lager/util.hpp>

#include <iostream>


namespace store {
    model update(model current, action action)
    {
        std::cout << "reduce" << std::endl;

        return std::visit(lager::visitor{
            [&](addMesh_action payload) {
                current.meshes.push_back(payload.mesh);
                current.sceneTree.push_back(&payload.mesh);
                return current;
            },
            [&](reset_action payload) {
                current.value = payload.value;
                return current;
            }
        }, action);
    }
}