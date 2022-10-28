
#include "Window.h"

double Window::ProcessFps::GetCountFrames()
{
    double currentTime = al_get_time();

    frameCount++;
    if (currentTime - previousTime >= 1.0)
    {
        Fps = frameCount;
        frameCount = 0.0;
        previousTime = currentTime;
    }
    return Fps;

}



Window::~Window()
{
    al_destroy_font(Fonte);
    al_destroy_display(Display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

}
Window::Window(ivec2 size, const string& title)
{
    Size = size;
    MousePosition = ivec2(size / 2);

    Error::Test_Entity(al_init(), "allegro");
    Error::Test_Entity(al_install_keyboard(), "keyboard");
    Error::Test_Entity(al_install_mouse(), "Mouse");

    al_set_new_display_flags(ALLEGRO_RESIZABLE);

    timer = al_create_timer(1.0 / 60.0);
    Error::Test_Entity(timer, "timer");

    queue = al_create_event_queue();
    Error::Test_Entity(queue, "queue");

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    Display = al_create_display(Size.x, Size.y);
    Error::Test_Entity(Display, "display");

    Fonte = al_create_builtin_font();
    Error::Test_Entity(Fonte, "font");

    Error::Test_Entity(al_init_primitives_addon(), "primitives");
    Error::Test_Entity(al_init_image_addon(), "image addon");

    Error::Test_Entity(al_install_audio(), "audio");
    Error::Test_Entity(al_init_acodec_addon(), "audio codecs");
    Error::Test_Entity(al_reserve_samples(16), "reserve samples");

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(Display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());

    al_set_window_title(Display, title.c_str());


    al_start_timer(timer);
}

// Inicilaiza o loop e processa os eventos
bool Window::Run()
{


    Time = al_get_time();
    ElapsedTime = al_get_timer_speed(timer);
    Frames = process_fps.GetCountFrames();

    ProcessEvents();

    MouseWheel = ProcessMouseWheel();

    if (CursorCenter)
    {
        al_set_mouse_xy(Display, Size.x / 2, Size.y / 2);

    }

    return game_loop_state;
}
void Window::SetMouseHidden(bool value)
{
    if (value)
    {
        al_hide_mouse_cursor(Display);
    }
    else
    {
        al_show_mouse_cursor(Display);
    }
}
Wheel Window::ProcessMouseWheel()
{
    auto temp = _wheel;
    _wheel = 0;
    switch (temp)
    {
    case -1:
        return BACK;

    case 1:
        return FRONT;

    default:
        return STOPPED;
    }
}
// aqui iniciamos o processo de eventos
void Window::ProcessEvents()
{
    al_wait_for_event(queue, &event);

    switch (event.type)
    {
    case ALLEGRO_EVENT_TIMER:
        break;

        // display Events
        //-------------------------------------------
    case ALLEGRO_EVENT_DISPLAY_CLOSE:
        game_loop_state = false;
        break;

    case ALLEGRO_EVENT_DISPLAY_SWITCH_IN:
        IsFocus = true;
        al_start_timer(timer);
        break;

    case ALLEGRO_EVENT_DISPLAY_SWITCH_OUT:
        IsFocus = false;
        al_stop_timer(timer);
        break;

    case ALLEGRO_EVENT_DISPLAY_RESIZE:
        al_resize_display(Display, event.display.width, event.display.height);
        Size = ivec2(event.display.width, event.display.height);
        break;

        // Keyboard Events
        //-------------------------------------------
    case ALLEGRO_EVENT_KEY_DOWN:
        keys[event.keyboard.keycode] = true;
        break;

    case ALLEGRO_EVENT_KEY_UP:
        keys[event.keyboard.keycode] = false;
        break;
        // mouse events
        //-------------------------------------------
    case ALLEGRO_EVENT_MOUSE_AXES:
        MousePosition = ivec2(event.mouse.x, event.mouse.y);
        _wheel = event.mouse.dz;
        break;

    case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
        buttons_mouse[event.mouse.button] = true;
        break;

    case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
        buttons_mouse[event.mouse.button] = false;
        break;

    case ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY:
        IsMouseEnterWindow = true;
        break;
    case ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY:
        IsMouseEnterWindow = false;
        break;
        //-------------------------------------------
    }
}
// set window details
//---------------------------------------------------------------------------------
void Window::SetTitle(const string& title)
{
    al_set_window_title(Display, title.c_str());
}
void Window::SetIconWindow(const string& iconPath)
{
    ALLEGRO_BITMAP* icon = al_load_bitmap(iconPath.c_str());
    Error::Test_Entity(icon, "icon Window");
    al_set_display_icon(Display, icon);
}
void Window::SetCursorWindow(const string& cursorPath)
{
    ALLEGRO_BITMAP* Cursor = al_load_bitmap(cursorPath.c_str());
    Error::Test_Entity(Cursor, "Cursor Window");
    al_create_mouse_cursor(Cursor, Size.x / 2, Size.y / 2);
}
//---------------------------------------------------------------------------------

void Window::Close()
{
    game_loop_state = false;
}
void Window::SwapBuffers()
{
    al_flip_display();
}

//---------------------------------------------------------------------------------
// teclado inputs
bool Window::IsKeyPress(Keys_Keyboard key)
{
    if (ctrl[key])
    {
        if (IskeyDown(key))
        {
            ctrl[key] = false;
            return true;
        }
    }
    else if (IsKeyUp(key))
    {
        ctrl[key] = true;
    }
    return false;
}

//---------------------------------------------------------------------------------
// mouse Inputs
bool Window::IsMousePress(Keys_Mouse Mos_key)
{
    if (ctrl_mouse[Mos_key])
    {
        if (IsMouseDown(Mos_key))
        {
            ctrl_mouse[Mos_key] = false;
            return true;
        }
    }
    else if (IsMouseUp(Mos_key))
    {
        ctrl_mouse[Mos_key] = true;
    }
    return false;
}
