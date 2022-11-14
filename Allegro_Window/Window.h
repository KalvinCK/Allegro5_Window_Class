#pragma once

#include <iostream>
#include <string>

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_opengl.h>


#include <glm/glm.hpp>

#include "Error.h"
#include "ColorsAllegro.h"
#include "Keys.h"


enum Wheel { BACK = -1, STOPPED = 0, FRONT = 1};

class Window
{
private:
    
    ALLEGRO_EVENT_QUEUE* queue;

    ALLEGRO_EVENT event;

    bool game_loop_state = true;

    bool keys[ALLEGRO_KEY_MAX] { false };
    bool ctrl[ALLEGRO_KEY_MAX] { false };

    bool buttons_mouse[ALLEGRO_MOUSE_KEY_MAX] { false };
    bool ctrl_mouse[ALLEGRO_MOUSE_KEY_MAX] { false };

    int _wheel = 0;

    static ALLEGRO_DISPLAY* Display;
    static ALLEGRO_FONT* Fonte;
    static ALLEGRO_TIMER* timer;

    glm::ivec2 Size;
    glm::ivec2 MousePosition;
public:

    bool IsMouseEnterWindow = true;
    bool IsFocus = true;
    bool setCursorCenter = false;

    Wheel MouseWheel = STOPPED;

    ~Window();
    Window(glm::ivec2 size, const std::string& title);

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
    inline void SetTitle(const std::string& title) { al_set_window_title(Display, title.c_str()); }
    void SetIconWindow(const std::string& iconPath);
    void SetCursorWindow(const std::string& cursorPath);
    //---------------------------------------------------------------------------------

    //gets
    inline glm::ivec2 getSize() { return Size; }
    inline glm::ivec2 getCursorPosition(){ return MousePosition; }

    static inline ALLEGRO_DISPLAY* GetDisplay() { return Display; }
    static inline ALLEGRO_FONT* getFont() { return Fonte; }
    static inline ALLEGRO_TIMER* getTimer() { return timer; }

    inline void Close() { game_loop_state = false; }
    inline void FlipDisplay() { al_flip_display(); }
    // verifica se a fila de eventos esta vazia
    inline bool EventQueueEmpty() { return ((al_is_event_queue_empty(queue) && IsFocus) ? true : false); }

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