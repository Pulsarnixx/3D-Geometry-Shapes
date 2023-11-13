#pragma once

#include "GLFW/glfw3.h"
#include <string>

struct TimerCalculation
{
    double FPS;
    double TimePerFrame;
};

class Timer
{
    private:
        double _prevTime;
        double _currTime;
        unsigned int _frames;


    public:
    Timer():_prevTime(0.0f),_currTime(0.0f),_frames(0){}

   void onAttach();
   double GetDeltaTime(){return _currTime - _prevTime;}

   TimerCalculation onUpdate();
};

void UpdateTitleFPS(GLFWwindow* window,const std::string& oldTitle,TimerCalculation calc);

