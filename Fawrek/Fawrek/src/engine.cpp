#include "engine.h"

Engine::Engine()
{
	startTime = GetCurrentTimeMillis();
}

float Engine::GetRunningTime()
{
    float RunningTime = (float)((double)GetCurrentTimeMillis() - (double)startTime) / 1000.0f;
    return RunningTime;
}