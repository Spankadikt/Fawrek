#include "engine.h"

Engine::Engine()
{
	m_lStartTime = GetCurrentTimeMillis();
}

float Engine::GetRunningTime()
{
    float RunningTime = (float)((double)GetCurrentTimeMillis() - (double)m_lStartTime) / 1000.0f;
    return RunningTime;
}