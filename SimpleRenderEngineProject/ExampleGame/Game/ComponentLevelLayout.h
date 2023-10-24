#include "Engine/Component.h"

class ComponentLevelLayout : public MyEngine::Component {
public:
    void Init(rapidjson::Value& serializedData) override;
    void Update(float deltaTime) override;
    void Render(sre::RenderPass &renderPass) override;
    std::vector<glm::vec4> CalculateUVs(int spriteIndex);
//    std::shared_ptr<MyEngine::GameObject> gameObject;
};
