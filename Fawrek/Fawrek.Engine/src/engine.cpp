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

Engine::EngineState Engine::GetEngineState()
{
	return m_engineState;
}

void Engine::PlayEngine()
{
	m_engineState = EngineState::Play;
}

void Engine::PauseEngine()
{
	m_engineState = EngineState::Pause;
}

void Engine::StopEngine()
{
	m_engineState = EngineState::Stop;
}