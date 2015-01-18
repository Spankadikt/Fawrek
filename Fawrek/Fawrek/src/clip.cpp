#include "animation.h"

Clip::Clip()
{
}

Clip::Clip(Clip &&clip)
{
	*this = clip;
}

Clip::Clip(Animation *_animation, int _id, float _startTime, float _endTime, bool _loop)
{
    animation = _animation;

	id = _id;
    clipStartTime = _startTime;
    clipEndTime = _endTime;
    loop = _loop;

    SetClipSpeed(1.0f);
    Stop();

	
	stamp_lastStartTime = 0.0f;
	stamp_startTime = -1.0f;
}

void Clip::SetClipSpeed(float speed)
{
    clipSpeed = speed;
}

float Clip::GetClipSpeed()
{
    return clipSpeed;
}

void Clip::SetClipCurrentTime(float _timeInSeconds)
{
    if(stamp_startTime < 0)
        stamp_startTime = _timeInSeconds + stamp_lastStartTime;

    float TicksPerSecond = (float)(animation->pScene->mAnimations[0]->mTicksPerSecond != 0 ? animation->pScene->mAnimations[0]->mTicksPerSecond * clipSpeed : 25.0f * clipSpeed);
    float stampTime = _timeInSeconds - stamp_startTime;
	float TimeInTicks = stampTime + TicksPerSecond * stampTime ;
    float AnimationTime = fmod(TimeInTicks, GetClipLength());

    if(loop)
    {
        clipCurrentTime = clipStartTime + AnimationTime;
    }
    else
    {
		if(TimeInTicks < GetClipLength())
            clipCurrentTime = clipStartTime + AnimationTime;
		else if (state != ClipState::STOP)
			Stop();
    }
}

float Clip::GetClipCurrentTime()
{
    return clipCurrentTime;
}

void Clip::Play()
{
	if(state != ClipState::PAUSE)
	{
		stamp_startTime = -1.0f;
		stamp_lastStartTime = 0.0f;
		clipCurrentTime = 0.0f;
	}
    state = PLAY;
}

void Clip::Pause()
{
    state = PAUSE;
    stamp_lastStartTime = stamp_startTime;
    stamp_startTime = -1.0f;
}

void Clip::Stop()
{
    state = STOP;
}