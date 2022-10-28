#pragma once

#include <iostream>
#include <string>
using namespace std;

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_opengl.h>


#include <glm/glm.hpp>
using namespace glm;

#include "Error.h"
#include "ColorsAllegro.h"
#include "Keys.h"


enum Wheel { BACK = -1, STOPPED = 0, FRONT = 1};

class Window
{
private:
    struct ProcessFps
    {
    private:
        double previousTime = 0.0;
        double frameCount = 0.0;
        double Fps = 0.0;
    public:
        double GetCountFrames();
    };

    ProcessFps process_fps;

    ALLEGRO_EVENT_QUEUE* queue;

    ALLEGRO_EVENT event;

    bool game_loop_state = true;

    bool keys[ALLEGRO_KEY_MAX] = { 0 };
    bool ctrl[ALLEGRO_KEY_MAX] = { 0 };

    bool buttons_mouse[ALLEGRO_MOUSE_KEY_MAX] = { 0 };
    bool ctrl_mouse[ALLEGRO_MOUSE_KEY_MAX] = { 0 };

    ALLEGRO_TIMER* timer;
    int _wheel = 0;
public:

    ALLEGRO_DISPLAY* Display;
    ALLEGRO_FONT* Fonte;

    double ElapsedTime = 0;
    double Frames = 0;
    double Time = 0;

    ivec2 Size;

    ivec2 MousePosition;

    bool IsMouseEnterWindow = true;
    bool IsFocus = true;
    bool CursorCenter = false;

    Wheel MouseWheel = STOPPED;

    ~Window();
    Window(ivec2 size, const string& title);

    // Inicilaiza o loop e processa os eventos
    bool Run();
    void SetMouseHidden(bool value);
private:
    Wheel ProcessMouseWheel();
    // aqui iniciamos o processo de eventos
    void ProcessEvents();
public:
    // set window details
    //---------------------------------------------------------------------------------
    void SetTitle(const string& title);
    void SetIconWindow(const string& iconPath);
    void SetCursorWindow(const string& cursorPath);
    //---------------------------------------------------------------------------------

    void Close();
    void SwapBuffers();
    // verifica se a fila de eventos esta vazia
    inline bool EventQueueEmpty();

    //---------------------------------------------------------------------------------
    // teclado inputs
    inline bool IskeyDown(Keys_Keyboard key);
    inline bool IsKeyUp(Keys_Keyboard key);
    bool IsKeyPress(Keys_Keyboard key);

    //---------------------------------------------------------------------------------
    // mouse Inputs
    inline bool IsMouseDown(Keys_Mouse Mos_key);
    inline bool IsMouseUp(Keys_Mouse Mos_key);
    bool IsMousePress(Keys_Mouse Mos_key);
};

// verifica se a fila de eventos esta vazia
bool Window::EventQueueEmpty()
{
    return (al_is_event_queue_empty(queue) && IsFocus) ? true : false;
}

//---------------------------------------------------------------------------------
// teclado inputs
bool Window::IskeyDown(Keys_Keyboard key)
{
    return keys[key];
}

bool Window::IsKeyUp(Keys_Keyboard key)
{
    return !(keys[key]);
}

//---------------------------------------------------------------------------------
// mouse Inputs
bool Window::IsMouseDown(Keys_Mouse Mos_key)
{
    return buttons_mouse[Mos_key];
}

bool Window::IsMouseUp(Keys_Mouse Mos_key)
{
    return !(buttons_mouse[Mos_key]);
}