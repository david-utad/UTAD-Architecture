#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite() :
  m_oIdle(),
  m_oRight(),
  m_oLeft(),
  m_eCurrentImage(AnimatedSprite::ECurrentImage::IDLE),
  m_uFrames(0),
  m_dCurrentFrame(0)
{

}

AnimatedSprite::AnimatedSprite(const std::string& _sTIdle, const std::string& _sTRight, const std::string& _sTLeft, uint32_t _uFrames) :
  m_oIdle(_sTIdle),
  m_oRight(_sTRight),
  m_oLeft(_sTLeft),
  m_eCurrentImage(AnimatedSprite::ECurrentImage::IDLE),
  m_uFrames(_uFrames),
  m_dCurrentFrame(0)
{

}

AnimatedSprite::~AnimatedSprite()
{

}

AnimatedSprite& AnimatedSprite::operator=(const AnimatedSprite& _oOther)
{
  m_oIdle = _oOther.GetIdleSprite();
  m_oRight = _oOther.GetRightSprite();
  m_oLeft = _oOther.GetLeftSprite();
  m_eCurrentImage = _oOther.GetCurrentImageEnum();
  m_uFrames = _oOther.GetAnimationFrames();
  m_dCurrentFrame = _oOther.GetCurrentFrame();
  return *this;
}

const Sprite& AnimatedSprite::GetIdleSprite() const
{
  return m_oIdle;
}

const Sprite& AnimatedSprite::GetRightSprite() const
{
  return m_oRight;
}

const Sprite& AnimatedSprite::GetLeftSprite() const
{
  return m_oLeft;
}

void* AnimatedSprite::GetCurrentImage() const
{
  switch (m_eCurrentImage)
  {
    case AnimatedSprite::ECurrentImage::IDLE:
      return m_oIdle.GetImage();
    case AnimatedSprite::ECurrentImage::RIGHT:
      return m_oRight.GetImage();
    case AnimatedSprite::ECurrentImage::LEFT:
      return m_oLeft.GetImage();
    default:
      return nullptr;
  }
}

AnimatedSprite::ECurrentImage AnimatedSprite::GetCurrentImageEnum() const
{
  return m_eCurrentImage;
}

uint32_t AnimatedSprite::GetAnimationFrames() const
{
  return m_uFrames;
}

uint32_t AnimatedSprite::GetCurrentImageFrames() const
{
  return (m_eCurrentImage != AnimatedSprite::ECurrentImage::IDLE) ? m_uFrames : 1;
}

double AnimatedSprite::GetCurrentFrame() const
{
  return (m_eCurrentImage != AnimatedSprite::ECurrentImage::IDLE) ? m_dCurrentFrame : 0;
}

void AnimatedSprite::Update(double _dDeltatime, AnimatedSprite::ECurrentImage _eCurrentImage)
{
  m_dCurrentFrame = fmod(m_uFrames + m_dCurrentFrame + (m_uFrames * _dDeltatime), static_cast<double>(m_uFrames));
  m_eCurrentImage = _eCurrentImage;
}