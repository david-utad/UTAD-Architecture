#include "AnimationSystem.h"
#include "Components.h"

void AnimationSystem::Update(double _dDeltatime)
{
  // It joins the components with velocity, sprite to draw and animate.
  for (uint32_t uId : join<CAnimatedSprite, CVelocity>())
  {
    AnimatedSprite& oAnimatedSprite = get<CAnimatedSprite>(uId);
    Vec2& vVelocity = get<CVelocity>(uId);
    AnimatedSprite::ECurrentImage eCurrentImage = AnimatedSprite::ECurrentImage::IDLE;
    if (vVelocity.GetX() > 0)
    {
      eCurrentImage = AnimatedSprite::ECurrentImage::RIGHT;
    }
    else if (vVelocity.GetX() < 0)
    {
      eCurrentImage = AnimatedSprite::ECurrentImage::LEFT;
    }
    oAnimatedSprite.Update(_dDeltatime, eCurrentImage);
  }
}