#ifndef ENGINE__H
#define	ENGINE_COMMON_H

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

class Engine
{
protected:
	Engine();

	float GetRunningTime();

private:

	long long startTime;
};

#endif	//ENGINE_H