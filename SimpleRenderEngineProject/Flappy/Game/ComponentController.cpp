#include "ComponentController.h"

#include "glm/glm.hpp"
#include "SDL.h"

#include "Engine/Components/ComponentPhysicsBody.h"

void ComponentController::Init(rapidjson::Value& serializedData) {
    mov_speed = serializedData["movSpeed"].GetInt();
    upwards_impulse = serializedData["impulse"].GetInt();
	// TODO load necessary data (linear velocity, inpulse strenght, etc) and add the to `scene.json`
}

void ComponentController::Update(float deltaTime) {
    auto bird = GetGameObject().lock()->FindComponent<ComponentPhysicsBody>().lock();
    auto vel = bird->getLinearVelocity();
    bird->setLinearVelocity(glm::vec2(mov_speed * deltaTime, vel.y));
	// TODO, if you need to do anything here
}

void ComponentController::KeyEvent(SDL_Event& event)
{
	// TODO listen for spacebar
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
        auto bird = GetGameObject().lock()->FindComponent<ComponentPhysicsBody>().lock();
        bird->addImpulse(glm::vec2(0, upwards_impulse));
    }
}

void ComponentController::OnCollisionStart(ComponentPhysicsBody* other) {
	// TODO gameOver on touching pipes, despawn coins
}