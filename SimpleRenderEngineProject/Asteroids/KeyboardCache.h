#pragma once

#include "sre/SDLRenderer.hpp"

class KeyboardCache
{
public:
    static bool w_clicked;
    static bool s_clicked;
    static bool a_clicked;
    static bool d_clicked;
    static bool space_clicked;
    static void HandleEvent(SDL_Event &event);
};
