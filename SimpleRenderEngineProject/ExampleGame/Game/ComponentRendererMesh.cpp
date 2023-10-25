#include "ComponentRendererMesh.h"

#include "glm/gtx/transform.hpp"

void ComponentRendererMesh::Init(rapidjson::Value &serializedData)
{
    auto uvIndex = serializedData.GetInt();
    auto uvs = CalculateUVs(uvIndex);
    _mesh = sre::Mesh::create()
                .withPositions(positions)                           // define which points are possible
                .withUVs(uvs)                                       // mapping of texture onto face, between 0 and 1, where the sprite is in the sprite atlas
                .withIndices(idxs, sre::MeshTopology::Triangles, 0) // indeces of the points to define the shape
                .build();
    _material = sre::Shader::getUnlit()->createMaterial();

    _texture = sre::Texture::create().withFile("data/level0.png").withGenerateMipmaps(false).withFilterSampling(false).build();
    _material->setTexture(_texture);
}

void ComponentRendererMesh::Render(sre::RenderPass &renderPass)
{
    for (int i = 0; i < 4; i++)
    {
        // vec3(0,1,0) to rotate around y axis
        auto r = glm::rotate(GetGameObject()->transform, (glm::pi<float>() / 2.0f) * i, glm::vec3(0, 1, 0));
        auto t = glm::translate(r, glm::vec3(0,0,0.5));
        renderPass.draw(_mesh, t, _material);
    }
}


std::vector<glm::vec4> ComponentRendererMesh::CalculateUVs(int spriteIndex) {
    int numRows = 6;
    int numCols = 16;

    float spriteWidth = 1.0f / numCols;
    float spriteHeight = 1.0f / numRows;

    int row = spriteIndex / numCols;
    int col = spriteIndex % numCols;

    float uMin = col * spriteWidth;
    float uMax = (col + 1) * spriteWidth;
    float vMin = row * spriteHeight;
    float vMax = (row + 1) * spriteHeight;

    std::vector<glm::vec4> uvCoordinates = {
            glm::vec4(uMin, vMin, 0, 0),
            glm::vec4(uMin, vMax, 0, 0),
            glm::vec4(uMax, vMax, 0, 0),
            glm::vec4(uMax, vMin, 0, 0)
    };
    return uvCoordinates;
}
