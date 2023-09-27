#include "Score.h"

int Score::score = 0;

void Score::Render()
{
    ImGui::SetNextWindowSize(ImVec2(70, 50), ImGuiCond_Always);
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::Begin("Score");
    ImGui::Text("%i", score);
    ImGui::End();
}
