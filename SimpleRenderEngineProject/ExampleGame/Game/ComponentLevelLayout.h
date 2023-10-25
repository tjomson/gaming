#include "Engine/Component.h"

class ComponentLevelLayout : public MyEngine::Component {
public:
    void Init(rapidjson::Value& serializedData) override;
    void Update(float deltaTime) override;
    void Render(sre::RenderPass &renderPass) override;
};
