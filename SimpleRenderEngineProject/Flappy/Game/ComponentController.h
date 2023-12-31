#pragma once

#include "Engine/Component.h"

class ComponentController : public MyEngine::Component {
	void Init(rapidjson::Value&) override;
	void Update(float deltaTime) override;
	void KeyEvent(SDL_Event&) override;
	void OnCollisionStart(ComponentPhysicsBody* other) override;
    void ShowGameOver();

private:
	glm::vec3 _mov;
    float upwards_impulse;
	float mov_speed;
	float rot_speed;
    bool isDead;
};