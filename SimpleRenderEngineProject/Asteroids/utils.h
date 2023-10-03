#pragma once

#include <cstdlib>
#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"
#include <cmath>

#define GAMEWIDTH 1800
#define GAMEHEIGHT 1000

float floatMod(float a, float b);
int randInRange(int a, int b);
float distanceBetweenLineAndPoint(glm::vec2 A, glm::vec2 B, glm::vec2 C);
