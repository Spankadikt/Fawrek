#include "api.h"

#ifndef ENGINE_H
#define	ENGINE_H

#define COLOR_TEXTURE_UNIT              GL_TEXTURE0
#define COLOR_TEXTURE_UNIT_INDEX        0
#define SHADOW_TEXTURE_UNIT             GL_TEXTURE1
#define SHADOW_TEXTURE_UNIT_INDEX       1
#define NORMAL_TEXTURE_UNIT             GL_TEXTURE2
#define NORMAL_TEXTURE_UNIT_INDEX       2
#define RANDOM_TEXTURE_UNIT             GL_TEXTURE3
#define RANDOM_TEXTURE_UNIT_INDEX       3
#define DISPLACEMENT_TEXTURE_UNIT       GL_TEXTURE4
#define DISPLACEMENT_TEXTURE_UNIT_INDEX 4

#include "utils.h"

class FAWREK_API Engine
{
public:
	enum EngineState
	{
		Play,
		Pause,
		Stop
	};

	EngineState GetEngineState();
	void PlayEngine();
	void PauseEngine();
	void StopEngine();

protected:
	Engine();

	float GetRunningTime();

private:
	EngineState m_engineState;
	long long m_lStartTime;
};

#endif	//ENGINE_H