#include "ComponentController.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/matrix_decompose.hpp"
#include "glm/gtx/transform.hpp"
#include "SDL.h"

void ComponentController::Init(rapidjson::Value &serializedData)
{
	mov_speed = serializedData["movSpeed"].GetFloat();
	rot_speed = serializedData["rotSpeed"].GetFloat();
}

void ComponentController::Update(float deltaTime)
{
	auto transform = GetGameObject()->transform;
	glm::vec3 position, scale;
	glm::quat rotation;

	glm::vec3 skew;
	glm::vec4 perspective;

	glm::decompose(transform, scale, rotation, position, skew, perspective);

	glm::vec3 display_rot = glm::degrees(glm::eulerAngles(rotation));
	auto x = (sin(glm::radians(display_rot.y)) * deltaTime);
	auto z = (cos(glm::radians(display_rot.y)) * deltaTime);

	// std::cout << display_rot.x << " " << display_rot.y << " " << display_rot.z << std::endl;

	if (a_clicked)
	{
		display_rot.y += deltaTime * rot_speed * 50;
	}
	else if (d_clicked)
	{
		display_rot.y -= deltaTime * rot_speed * 50;
	}
	if (w_clicked)
	{
		position -= glm::vec3(x, 0, z);
	}
	else if (s_clicked)
	{
		position += glm::vec3(x, 0, z);
	}
	std::cout << position.x << " " << position.y << " " << position.z << std::endl;

	GetGameObject()->transform =
		glm::scale(scale) *
		glm::translate(position) *
		glm::mat4_cast(glm::quat(glm::radians(display_rot)));
}

void ComponentController::KeyEvent(SDL_Event &event)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_w:
			w_clicked = true;
			break;
		case SDLK_s:
			s_clicked = true;
			break;
		case SDLK_a:
			a_clicked = true;
			break;
		case SDLK_d:
			d_clicked = true;
			break;
		}
	}
	else if (event.type == SDL_KEYUP)
	{
		switch (event.key.keysym.sym)
		{
		case SDLK_w:
			w_clicked = false;
			break;
		case SDLK_s:
			s_clicked = false;
			break;
		case SDLK_a:
			a_clicked = false;
			break;
		case SDLK_d:
			d_clicked = false;
			break;
		}
	}
}

void ComponentController::Render(sre::RenderPass &)
{
}
