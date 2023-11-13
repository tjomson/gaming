#include "ComponentController.h"

#include "glm/glm.hpp"
#include <glm/gtc/quaternion.hpp>
#include "SDL.h"
#include "Engine/MyEngine.h"

#include "Engine/Components/ComponentPhysicsBody.h"
#include "Engine/Components/ComponentRendererSprite.h"

void ComponentController::Init(rapidjson::Value& serializedData) {
    mov_speed = serializedData["movSpeed"].GetInt();
    upwards_impulse = serializedData["impulse"].GetInt();
    isDead = false;
	// TODO load necessary data (linear velocity, inpulse strenght, etc) and add the to `scene.json`
}

void ComponentController::Update(float deltaTime) {
    if (isDead) return;
    auto bird = GetGameObject().lock()->FindComponent<ComponentPhysicsBody>().lock();
    auto vel = bird->getLinearVelocity();
    bird->setLinearVelocity(glm::vec2(mov_speed * deltaTime, vel.y));
    float angle = glm::degrees(atan2(vel.y, vel.x));
    glm::quat rotationQuaternion = glm::angleAxis(glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::quat currRot = GetGameObject().lock()->GetRotation();
    GetGameObject().lock()->SetRotation(currRot * rotationQuaternion);

	// TODO, if you need to do anything here
}

void ComponentController::KeyEvent(SDL_Event& event)
{
    if (isDead) return;
	// TODO listen for spacebar
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
        auto bird = GetGameObject().lock()->FindComponent<ComponentPhysicsBody>().lock();
        bird->addImpulse(glm::vec2(0, upwards_impulse));
    }
}

void ComponentController::OnCollisionStart(ComponentPhysicsBody* other) {
    if (isDead) return;
    auto otherName = other->GetGameObject().lock()->GetName();
    if (otherName.find("Coin") != std::string::npos) {
        std::cout << "point!" << std::endl;
        other->GetGameObject().lock()->SetPosition({-50, -50, 0});
    } else {
        isDead = true;
        ShowGameOver();
        std::cout << "dead" << std::endl;
    }
	// TODO gameOver on touching pipes, despawn coins
}

void ComponentController::ShowGameOver() {
    auto engine = MyEngine::Engine::GetInstance();
    auto screenHeight = engine->GetScreenSize().y;
    auto gameObject = GetGameObject();
    auto gameover = engine->CreateGameObject("GameOver", gameObject).lock();
    auto renderer = gameover->CreateComponent<ComponentRendererSprite>().lock();
    auto bird = GetGameObject().lock()->GetPosition();
    renderer->SetSprite("bird", "game-over.png");
    gameover->SetPosition({bird.x, screenHeight / 2, 0});
}
