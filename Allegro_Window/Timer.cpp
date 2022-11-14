#include "Timer.h"

#include <allegro5/allegro5.h>

#include "Window.h"

double Timer::ElapsedTime = 0.0;
double Timer::Time = 0.0;
double Timer::Frames = 0.0;

static double previousTime = 0.0;
static double frameCount = 0.0;

void Timer::GetCountFrames()
{
    double Time = al_get_time();
    ElapsedTime = al_get_timer_speed(Window::timer);

    frameCount++;
    if (Time - previousTime >= 1.0)
    {
        Frames = frameCount;
        frameCount = 0.0;
        previousTime = Time;
    }
}