#include "ComponentLevelLayout.h"
#include "ComponentRendererMesh.h"
#include "MyEngine.h"
#include <glm/glm.hpp>
#include "glm/gtx/transform.hpp"
#include <glm/gtc/quaternion.hpp>

void ComponentLevelLayout::Init(rapidjson::Value& serializedData) {
    auto& ints = serializedData["layout"];
    auto count = serializedData["layoutCount"].GetInt();
    auto engine = MyEngine::Engine::GetInstance();
    for (int i = 0; i < count; i++) {
        char name[100];
        sprintf(name, "cube%i", i);
        auto gameObj = engine->CreateGameObject(name);
        auto renderer = std::make_shared<ComponentRendererMesh>();
        renderer->Init(ints[i]);
        gameObj.lock()->AddComponent(renderer);
        auto pos = glm::vec3(i, 0, i);
        auto rot = glm::vec3(0, 0, 0);
        auto scl = glm::vec3(1, 1, 1);
        gameObj.lock()->transform =
                glm::translate(pos) *
                glm::mat4_cast(glm::quat(glm::radians(rot))) *
                glm::scale(scl);
    }
}

