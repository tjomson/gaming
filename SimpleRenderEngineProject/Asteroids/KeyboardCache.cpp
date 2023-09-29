#include "KeyboardCache.h"

bool KeyboardCache::w_clicked = false;
bool KeyboardCache::s_clicked = false;
bool KeyboardCache::a_clicked = false;
bool KeyboardCache::d_clicked = false;
bool KeyboardCache::space_clicked = false;

void KeyboardCache::HandleEvent(SDL_Event &event)
{
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_w:
            KeyboardCache::w_clicked = true;
            break;
        case SDLK_s:
            KeyboardCache::s_clicked = true;
            break;
        case SDLK_a:
            KeyboardCache::a_clicked = true;
            break;
        case SDLK_d:
            KeyboardCache::d_clicked = true;
            break;
        case SDLK_SPACE:
            KeyboardCache::space_clicked = true;
            break;
        }
    }
    else if (event.type == SDL_KEYUP)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_w:
            KeyboardCache::w_clicked = false;
            break;
        case SDLK_s:
            KeyboardCache::s_clicked = false;
            break;
        case SDLK_a:
            KeyboardCache::a_clicked = false;
            break;
        case SDLK_d:
            KeyboardCache::d_clicked = false;
            break;
        case SDLK_SPACE:
            KeyboardCache::space_clicked = false;
            break;
        }
    }
}
