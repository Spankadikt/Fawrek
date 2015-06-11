#include "animation.h"

Clip::Clip()
{
}

Clip::Clip(Clip&& clip)
{
	*this = clip;
}

Clip::Clip(Animation* _pAnimation, int _iId, float _fStartTime, float _fEndTime, bool _bLoop,float _fBaseSpeed)
{
    m_pAnimation = _pAnimation;

	m_iId = _iId;
    m_fClipStartTime = _fStartTime;
    m_fClipEndTime = _fEndTime;
    m_bLoop = _bLoop;

    SetClipSpeed(_fBaseSpeed);
    Stop();

	
	m_fStampLastStartTime = 0.0f;
	m_fStampStartTime = -1.0f;
}

bool Clip::operator==(const Clip& _clip)
{
    return m_iId == _clip.m_iId;
}

void Clip::SetClipSpeed(float _fSpeed)
{
    m_fClipSpeed = _fSpeed;
}

float Clip::GetClipSpeed()
{
    return m_fClipSpeed;
}

void Clip::SetClipCurrentTime(float _fTimeInSeconds)
{
    //if(m_fStampStartTime < 0)
    //    m_fStampStartTime = _fTimeInSeconds + m_fStampLastStartTime;

    float TicksPerSecond = (float)(m_pAnimation->m_pScene->mAnimations[0]->mTicksPerSecond != 0 ? m_pAnimation->m_pScene->mAnimations[0]->mTicksPerSecond * m_fClipSpeed : 30.0f * m_fClipSpeed);
    //float stampTime = _fTimeInSeconds - m_fStampStartTime;
	//float TimeInTicks = stampTime + TicksPerSecond * stampTime ;
	float TimeInTicks = _fTimeInSeconds * TicksPerSecond;

    float AnimationTime = fmod(TimeInTicks, (float)(m_pAnimation->m_pScene->mAnimations[0]->mTicksPerSecond != 0 ?GetClipLengthInSec():GetClipLength()));

    if(m_bLoop)
    {
        m_fClipCurrentTime = m_fClipStartTime + AnimationTime;
    }
    else
    {
		if(TimeInTicks < GetClipLength())
            m_fClipCurrentTime = m_fClipStartTime + AnimationTime;
		else if (m_state != ClipState::STOP)
			Stop();
    }
}

float Clip::GetClipCurrentTime()
{
    return m_fClipCurrentTime;
}

void Clip::Init()
{
    m_fStampStartTime = -1.0f;
	m_fStampLastStartTime = 0.0f;
}

void Clip::Play()
{
    m_state = PLAY;
}

void Clip::Pause()
{
    m_state = PAUSE;
    m_fStampLastStartTime = m_fStampStartTime;
    m_fStampStartTime = -1.0f;
}

void Clip::Stop()
{
    m_state = STOP;
}