#include "ComponentRendererMesh.h"

#include "glm/gtx/transform.hpp"

void ComponentRendererMesh::Init(rapidjson::Value &serializedData)
{
    _mesh = sre::Mesh::create()
                .withPositions(positions)                           // define which points are possible
                .withUVs(uvs)                                       // mapping of texture onto face, between 0 and 1, where the sprite is in the sprite atlas
                .withIndices(idxs, sre::MeshTopology::Triangles, 0) // indeces of the points to define the
                .build();
    _material = sre::Shader::getUnlit()->createMaterial();

    _texture = sre::Texture::create().withFile("data/level0.png").withGenerateMipmaps(false).withFilterSampling(false).build();
    _material->setTexture(_texture);
    // _material->setColor({0, 1, 0, 1});
}

void ComponentRendererMesh::Update(float deltaTime)
{
    // GetGameObject()->transform = glm::rotate(GetGameObject()->transform, glm::pi<float>() * deltaTime, glm::vec3(0, 1, 0));
}

void ComponentRendererMesh::Render(sre::RenderPass &renderPass)
{
    renderPass.draw(_mesh, GetGameObject()->transform, _material);
}
