#pragma once

#include "Engine/Component.h"

class ComponentRendererMesh : public MyEngine::Component
{
public:
	void Init(rapidjson::Value &serializedData) override;
	void Update(float deltaTime) override;
	void Render(sre::RenderPass &renderPass) override;
	std::shared_ptr<sre::Mesh> _mesh;
	std::shared_ptr<sre::Material> _material;
	std::shared_ptr<sre::Texture> _texture;

	// this should be metadata of the texture, but we are keeping them here for simplicity
	// challenge: associate a json to each texture, with their metadata?
	// const glm::vec2 textureSize = glm::vec2(1039, 389);
	// const glm::vec2 tileSize = glm::vec2(64, 64);
	const std::vector<glm::vec3> positions = {
		glm::vec3(-0.5, -0.5, 0.0), // Lower-left
		glm::vec3(-0.5, 0.5, 0.0),	// Upper-left
		glm::vec3(0.5, 0.5, 0.0),	// Upper-right
		glm::vec3(0.5, -0.5, 0.0)	// Lower-right
	};

	std::vector<glm::vec4> uvs = {
		glm::vec4(0.0, 0.0, 0, 0),			// Lower-left
		glm::vec4(0.0, 1.0 / 6, 0, 0),		// Upper-left
		glm::vec4(1.0 / 16, 1.0 / 6, 0, 0), // Upper-right
		glm::vec4(1.0 / 16, 0.0, 0, 0)		// Lower-right
	};

    const std::vector<uint16_t> idxs = {3, 1, 0, 3, 2, 1};
};
