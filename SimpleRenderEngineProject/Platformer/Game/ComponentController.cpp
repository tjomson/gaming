#include "ComponentController.h"

#include "glm/glm.hpp"
#include "SDL.h"

#include "Engine/Components/ComponentPhysicsBody.h"
#include "Engine/Components/ComponentRendererSprite.h"
#include "Engine/MyEngine.h"

void ComponentController::Init(rapidjson::Value& serializedData) {
	auto gameObject = GetGameObject().lock();
	if (!gameObject)
		return;

	_body = gameObject->FindComponent<ComponentPhysicsBody>();
}

std::string ComponentController::DetermineSprite(float deltaTime, glm::vec2 linearVelocity) {
    auto velocity = glm::length(linearVelocity);
    if (velocity == 0) return "19.png";
    if (velocity > 0 && _grounded) {
        lastSpriteChange += deltaTime;
        if (lastSpriteChange > 0.3 / glm::abs(linearVelocity.x)) {
            lastSpriteChange = 0;
            currWalkSprite = currWalkSprite == "20.png" ? "21.png" : "20.png";
        }
        return currWalkSprite;
    }
    if (linearVelocity.y > 2) return "26.png";
    if (linearVelocity.y < -2) return "28.png";
    return "27.png";
}

void ComponentController::Update(float deltaTime) {
    auto renderer = GetGameObject().lock()->FindComponent<ComponentRendererSprite>();
	auto body = _body.lock();
	if (!body)
		return;

	auto linearVelocity = body->getLinearVelocity();
    renderer.lock()->SetSprite("platformer-art-deluxe", DetermineSprite(deltaTime, linearVelocity));
    if (linearVelocity.x < 0) renderer.lock()->GetSprite()->setFlip({1, 0});

	linearVelocity.x = _mov.x * _movSpeed;
	body->setLinearVelocity(linearVelocity);
	if (_jump) {
		body->addImpulse(glm::vec2(0, _jumpStrength));
		_jump = false;
	}
}

void ComponentController::KeyEvent(SDL_Event& event) {


	// movement
	switch (event.key.keysym.sym) {
		case SDLK_a: _mov.x = -(event.type == SDL_KEYDOWN); break;
		case SDLK_d: _mov.x = +(event.type == SDL_KEYDOWN); break;
	}

	// jump
	if (_grounded && event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
		_jump = true;

}

void ComponentController::OnCollisionStart(ComponentPhysicsBody* other, b2Manifold* manifold) {
	if (manifold->localNormal.y > .99)
		_grounded = true;
}

void ComponentController::OnCollisionEnd(ComponentPhysicsBody* other, b2Manifold* manifold) {
	if (manifold->localNormal.y > .99)
		_grounded = false;
}