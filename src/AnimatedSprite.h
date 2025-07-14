/**
 *  @author David Gonzalez Ledesma
 **/

#pragma once
#include "Sprite.h"

class AnimatedSprite
{
public:

  enum ECurrentImage
  {
    IDLE,
    RIGHT,
    LEFT
  };

  AnimatedSprite();
  AnimatedSprite(const std::string& _sTIdle, const std::string& _sTRight, const std::string& _sTLeft, uint32_t _uFrames = 1);
  virtual ~AnimatedSprite();

  AnimatedSprite& operator=(const AnimatedSprite& _oOther);
  /**
   * It returns the idle sprite.
   */
  const Sprite& GetIdleSprite() const;
  /**
   * It returns the right sprite.
   */
  const Sprite& GetRightSprite() const;
  /**
   * It returns the left sprite.
   */
  const Sprite& GetLeftSprite() const;
  /**
   * It returns the current image to render acording to _eCurrentImage setted.
   */
  void* GetCurrentImage() const;
  /**
   * It returns the current image enum selected.
   */
  AnimatedSprite::ECurrentImage GetCurrentImageEnum() const;
  /**
   * It return the total frames in the animation.
   */
  uint32_t GetAnimationFrames() const;
  /**
   * It return the current image frames in the animation. For idle animation it will return always 1.
   */
  uint32_t GetCurrentImageFrames() const;
  /**
   * It returns the current frame in the animation. For idle animation it will return always 0.
   */
  double GetCurrentFrame() const;
  /**
   * It updates the current frame and the image to show in the animation.
   * @param _dDeltatime -> time to update the frame. 
   * @param _eCurrentImage -> Current image.
   */
  void Update(double _dDeltatime, AnimatedSprite::ECurrentImage _eCurrentImage);

private:

  Sprite m_oIdle, m_oRight, m_oLeft;
  AnimatedSprite::ECurrentImage m_eCurrentImage;
  uint32_t m_uFrames;
  double m_dCurrentFrame;
};