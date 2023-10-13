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
	auto game = GetGameObject();
	float turn = 0;
	if (a_clicked)
		turn = 1.0;
	else if (d_clicked)
		turn = -1.0;
	game->transform = glm::rotate(game->transform, turn * deltaTime, glm::vec3(0, 1, 0));

	float move = 0;
	if (w_clicked)
		move = -1;
	else if (s_clicked)
		move = 1;
	game->transform = glm::translate(game->transform, glm::vec3(0, 0, move * deltaTime));
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
