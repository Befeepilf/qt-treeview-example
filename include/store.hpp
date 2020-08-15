#ifndef STORE_H
#define STORE_H

#include "scene/camera.hpp"
#include "scene/group.hpp"
#include "scene/itemVariant.hpp"
#include "scene/light.hpp"
#include "scene/mesh.hpp"

#include <variant>
#include <vector>

namespace store {
    struct model {
        std::vector<Scene::Mesh> meshes;
        std::vector<Scene::Camera> cameras;
        std::vector<Scene::Light> lights;

        std::vector<Scene::ItemVariant> sceneTree;

        int value = 0;
    };

    struct addMesh_action {
        Scene::Mesh mesh;
    };

    struct reset_action {
        int value = 0;
    };

    using action = std::variant<addMesh_action, reset_action>;

    model update(model current, action action);
}

#endif // STORE_H