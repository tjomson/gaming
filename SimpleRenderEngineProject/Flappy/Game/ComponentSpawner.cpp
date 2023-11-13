#include "ComponentSpawner.h"

#include "Engine/MyEngine.h"
#include "Engine/Components/ComponentRendererSprite.h"

#include "Engine/Components/ComponentPhysicsBody.h"

void ComponentSpawner::Init(rapidjson::Value&) {
	float winHeight = MyEngine::Engine::GetInstance()->GetScreenSize().y;

	// these should probably go in the json file
	// you can tweak these to find a pipe distriv
	float xOffsetStart = 45;
	float curve = 250;
	float heighVariation = 50;
	float xVariation = 5;
	int nWalls = 50;
	
	for (int i = 0; i < nWalls; ++i) {
		float xOffset = xVariation * cos(i * curve * 0.2f) + xOffsetStart;
		glm::vec3 posBot {
			i * 300 + xOffset,
			sin(i* curve)* heighVariation,
			0
		};
		glm::vec3 posTop {
			i * 300 + xOffset,
			winHeight - sin(i* curve)* heighVariation,
			0
		};

		SpawnWall("WallBottom" + std::to_string(i), "column_bottom.png", posBot);
		SpawnWall("WallTop" + std::to_string(i), "column_top.png", posTop);

        auto coinPos = glm::vec3{posBot.x, (posBot.y + posTop.y) / 2, 0};
        SpawnCoin("Coin" + std::to_string(i), coinPos);
	}

    SpawnHorizontalBound(0, "Floor");
    SpawnHorizontalBound(winHeight, "Ceiling");


	// TODO spawn coins
}

void ComponentSpawner::SpawnHorizontalBound(float height, std::string name) {
    auto engine = MyEngine::Engine::GetInstance();
    auto gameObject = GetGameObject();

    auto wall = engine->CreateGameObject(name, gameObject).lock();
    glm::vec3 zero {0,height,0};
    wall->SetPosition(zero);

    auto body = wall->CreateComponent<ComponentPhysicsBody>().lock();

    glm::vec2 s {10000, 0};
    body->CreateBody(b2_staticBody, false, s);
}

void ComponentSpawner::SpawnWall(std::string name, std::string spriteId, glm::vec3 pos) {
	auto engine = MyEngine::Engine::GetInstance();
	auto gameObject = GetGameObject();

	auto wall = engine->CreateGameObject(name, gameObject).lock();
	auto renderer = wall->CreateComponent<ComponentRendererSprite>().lock();
	renderer->SetSprite("bird", spriteId);

	auto sprite = renderer->GetSprite();
	sprite->setScale({ 2, 2 });

	pos.y += sprite->getSpriteSize().y / 2;
	wall->SetPosition(pos);

	// TODO add body
	auto body = wall->CreateComponent<ComponentPhysicsBody>().lock();

	glm::vec2 s { sprite->getSpriteSize().x * sprite->getScale().x / 2, sprite->getSpriteSize().y * sprite->getScale().y / 2};
	body->CreateBody(b2_staticBody, false, s);
}

void ComponentSpawner::SpawnCoin(std::string name, glm::vec3 pos) {
    auto engine = MyEngine::Engine::GetInstance();
    auto gameObject = GetGameObject();

    auto coin = engine->CreateGameObject(name, gameObject).lock();
    auto renderer = coin->CreateComponent<ComponentRendererSprite>().lock();
    renderer->SetSprite("bird", "coin.png");

    auto sprite = renderer->GetSprite();
    sprite->setScale({ 2, 2 });

    pos.y += sprite->getSpriteSize().y / 2;
    coin->SetPosition(pos);

    auto body = coin->CreateComponent<ComponentPhysicsBody>().lock();

    glm::vec2 s { sprite->getSpriteSize().x * sprite->getScale().x / 2, sprite->getSpriteSize().y * sprite->getScale().y / 2};
    body->CreateBody(b2_staticBody, true, s);
}