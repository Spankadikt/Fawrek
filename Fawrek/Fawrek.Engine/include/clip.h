#include "api.h"

#ifndef CLIP_H
#define CLIP_H

class FAWREK_API Animation;

class FAWREK_API Clip
{
public:
	
	Clip();
	Clip(Clip&& _clip);

    enum ClipState
    {
        PLAY,
        PAUSE,
        STOP
    };


    Animation* m_pAnimation;

    bool operator==(const Clip& _clip);

	int m_iId;
    float m_fFps;
	float m_fClipStartTime;
	float m_fClipEndTime;
    float m_fClipCurrentTime;

    bool m_bLoop;
    ClipState m_state;
    float m_fClipSpeed;

	Clip(Animation* _pAnimation, int _iId, float _fStartTime, float _fEndTime, bool _bLoop, float _bBaseSpeed);

    float GetClipLength()
    {
        return m_fClipEndTime - m_fClipStartTime;
    }

	float GetClipLengthInSec()
    {
        return (m_fClipEndTime - m_fClipStartTime)/30.0f;
    }

    void SetClipSpeed(float _fSpeed);
    float GetClipSpeed();

    void SetClipCurrentTime(float _fTime);
    float GetClipCurrentTime();

    void Init();
    void Play();
    void Pause();
    void Stop();

private:
	
	float m_fStampLastStartTime;
	float m_fStampStartTime;
};

#endif // CLIP_H