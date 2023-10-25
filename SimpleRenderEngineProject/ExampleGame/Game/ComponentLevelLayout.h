#include "Engine/Component.h"

class ComponentLevelLayout : public MyEngine::Component {
public:
    void Init(rapidjson::Value& serializedData) override;
};
