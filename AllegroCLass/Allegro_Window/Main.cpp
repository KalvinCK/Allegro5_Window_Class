#include <iostream>
#include <string>
using namespace std;

#include <glm/glm.hpp>
using namespace glm;

#include "ColorsAllegro.h"
#include "Window.h"


void UseMatrixIdenty()
{
    ALLEGRO_TRANSFORM matrix_identy;
    al_identity_transform(&matrix_identy);
    al_use_transform(&matrix_identy);
}
int main()
{
    Window window(ivec2(1600, 900), "Allegro Game");

    window.SetIconWindow("allegro_icon.png");

    bool hidden = false;
    while (window.Run())
    {
        window.SetTitle(string("Allegro5 " + std::to_string(window.Frames)));
        if(window.IsKeyPress(KEY_ESCAPE))
        {
            window.Close();
        }

        if (window.IsMousePress(MOUSE_BUTTON_2))
        {
            hidden = hidden ? false : true;
            window.SetMouseHidden(hidden);
        }


        if (window.EventQueueEmpty())
        {
            al_clear_to_color(Colors::Quantum);
            al_draw_textf(window.Fonte, Colors::AliceBlue, 10, 10, 0, "Time: %f FPS: %2.f ElpasedTime: %f", window.Time, window.Frames, window.ElapsedTime);

            ivec2 m_pos = window.MousePosition;


            al_draw_filled_rectangle(m_pos.x - 10, m_pos.y - 10, m_pos.x + 10, m_pos.y + 10, Colors::Coral);


            window.SwapBuffers();
        }
    }
    // delete

    return 0;
}