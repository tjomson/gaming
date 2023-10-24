#include "ComponentLevelLayout.h"
#include "ComponentRendererMesh.h"
#include "MyEngine.h"

void ComponentLevelLayout::Init(rapidjson::Value& serializedData) {
    auto& ints = serializedData["layout"];
    auto count = serializedData["layoutCount"].GetInt();
    auto engine = MyEngine::Engine::GetInstance();
    auto gameObj = engine->CreateGameObject("lay");
    for (int i = 0; i < count; i++) {
        auto renderer = std::make_shared<ComponentRendererMesh>();
        renderer->Init(serializedData);
        renderer->uvs = CalculateUVs(ints[i].GetInt());
        gameObj.lock()->AddComponent(renderer);
    }
}

std::vector<glm::vec4> ComponentLevelLayout::CalculateUVs(int spriteIndex) {
    // Calculate the number of rows and columns in the sprite sheet
    int numRows = 6;
    int numCols = 16;

    // Calculate the width and height of each sprite in UV space
    float spriteWidth = 1.0f / numCols;
    float spriteHeight = 1.0f / numRows;

    // Calculate the row and column of the sprite based on the index
    int row = spriteIndex / numCols;
    int col = spriteIndex % numCols;

    // Calculate the UV coordinates for the sprite's four corners
    float uMin = col * spriteWidth;
    float uMax = (col + 1) * spriteWidth;
    float vMin = row * spriteHeight;
    float vMax = (row + 1) * spriteHeight;

    // Define the UV coordinates for the four corners
    std::vector<glm::vec4> uvCoordinates = {
            glm::vec4(uMin, vMin, 0, 0),
            glm::vec4(uMin, vMax, 0, 0),
            glm::vec4(uMax, vMax, 0, 0),
            glm::vec4(uMax, vMin, 0, 0)
    };

    return uvCoordinates;
}

void ComponentLevelLayout::Update(float deltaTime) {

}

void ComponentLevelLayout::Render(sre::RenderPass &renderPass) {

//    gameObject->Render(renderPass);
}
