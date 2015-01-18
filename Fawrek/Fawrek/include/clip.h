#ifndef CLIP_H
#define CLIP_H

class Animation;

class Clip
{
public:
	
	Clip();
	Clip(Clip &&clip);

    enum ClipState
    {
        PLAY,
        PAUSE,
        STOP
    };


    Animation *animation;

	int id;
    float fps;
	float clipStartTime;
	float clipEndTime;
    float clipCurrentTime;

    bool loop;
    ClipState state;
    float clipSpeed;

	Clip(Animation *_animation, int id, float _startTime, float _endTime, bool _loop);

    float GetClipLength()
    {
        return clipEndTime - clipStartTime;
    }

    void SetClipSpeed(float speed);
    float GetClipSpeed();

    void SetClipCurrentTime(float time);
    float GetClipCurrentTime();

    void Play();
    void Pause();
    void Stop();

private:
	
	float stamp_lastStartTime;
	float stamp_startTime;
};

#endif // CLIP_H