#include <iostream>
#include <string>

#include <glm/glm.hpp>

#include "ColorsAllegro.h"
#include "Window.h"
#include "Timer.h"

void UseMatrixIdenty()
{
    ALLEGRO_TRANSFORM matrix_identy;
    al_identity_transform(&matrix_identy);
    al_use_transform(&matrix_identy);
}
int main()
{
    Window* window = new Window(glm::ivec2(1600, 900), "Allegro Game");

    window->SetIconWindow("allegro_icon.png");

    bool hidden = false;
    while (window->Run())
    {
        window->SetTitle(std::string("Allegro5 " + std::to_string(Timer::Frames)));
        if(window->IsKeyPress(KEY_ESCAPE))
        {
            window->Close();
        }

        if (window->IsMousePress(MOUSE_BUTTON_2))
        {
            hidden = hidden ? false : true;
            window->SetMouseHidden(hidden);
        }


        if (window->EventQueueEmpty())
        {
            al_clear_to_color(Colors::Quantum);
            al_draw_textf(window->getFont(), Colors::AliceBlue, 10, 10, 0, "Time: %f FPS: %2.f ElapsedTime: %f", Timer::Time, Timer::Frames, Timer::ElapsedTime);

            glm::ivec2 m_pos = window->getCursorPosition();


            al_draw_filled_rectangle(m_pos.x - 10, m_pos.y - 10, m_pos.x + 10, m_pos.y + 10, Colors::Coral);


            window->FlipDisplay();
        }
    }
    // delete

    return 0;
}