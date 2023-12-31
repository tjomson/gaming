#pragma once

#include "Component.h"

class ComponentController : public MyEngine::Component
{
public:
	void Init(rapidjson::Value &) override;
	void Update(float deltaTime) override;
	void KeyEvent(SDL_Event &) override;
private:
	float mov_speed;
	float rot_speed;
	bool w_clicked = false;
	bool s_clicked = false;
	bool a_clicked = false;
	bool d_clicked = false;
    bool q_clicked = false;
    bool e_clicked = false;
};
