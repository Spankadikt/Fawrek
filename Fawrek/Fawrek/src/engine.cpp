#include "engine.h"

Engine::Engine()
{
}

float Engine::GetRunningTime()
{
    float RunningTime = (float)((double)GetCurrentTimeMillis() - (double)startTime) / 1000.0f;
    return RunningTime;
}