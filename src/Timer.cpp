#include "Timer.h"

void Timer::onAttach()
{
    _currTime = glfwGetTime();
    ++_frames;
}

TimerCalculation Timer::onUpdate()
{
    TimerCalculation result;
    double deltaTime = GetDeltaTime();

    result.FPS = ( 1.0/  deltaTime ) * _frames;
    result.TimePerFrame = (deltaTime * 1000 / _frames );


    //Update time and reset frames
    _prevTime = _currTime;
    _frames = 0;

    return result;
}

void UpdateTitleFPS(GLFWwindow* window,const std::string& oldTitle, TimerCalculation calc)
{
    std::string FPS = std::to_string(calc.FPS);
    std::string TimePerFrame = std::to_string(calc.TimePerFrame);

    std::string NewTitle = oldTitle + " - " + FPS + " FPS / " + TimePerFrame + " ms";
    glfwSetWindowTitle(window,NewTitle.c_str());
}