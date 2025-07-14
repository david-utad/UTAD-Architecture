#include "MovementSystem.h"
#include "Components.h"
#include "CollisionSystem.h"
#include "SpawnSystem.h"
#include "Enemy.h"

void MovementSystem::Update(double _dDeltatime)
{
  CollisionSystem::TCollisionDetection tCollision = { false, false, false, false };
  // It joins the components with position and velocity.
  for (uint32_t uId : join<CPosition, CVelocity>())
  {
    Vec2& vPosition = get<CPosition>(uId);
    Vec2& vVelocity = get<CVelocity>(uId);
    if (has<CPlayer>(uId))
    {
      tCollision = CollisionSystem::CheckEntityLevel(uId);
      if ((tCollision.m_bRightCollision && (vVelocity.GetX() > 0)) || (tCollision.m_bLeftCollision && (vVelocity.GetX() < 0)))
      {
        continue;
      }
    }
    if (has<CEnemy>(uId))
    {
      Enemy& oEnemy = get<CEnemy>(uId);
      EnemyVelocity pCallback = SpawnSystem::GetEnemyVelocity(oEnemy.GetEnemyType());
      CollisionSystem::TCollisionDetection tCollision = CollisionSystem::CheckEntityLevel(uId);
      double dXVelocity = vVelocity.GetX();
      double dYVelocity = vVelocity.GetY();
      if (pCallback != nullptr) {
        (*pCallback)(oEnemy, dXVelocity, dYVelocity, _dDeltatime,
                     tCollision.m_bRightCollision, tCollision.m_bLeftCollision, tCollision.m_bTopCollision, tCollision.m_bBottomCollision);
        vVelocity = Vec2(dXVelocity, dYVelocity);
      }
    }
    vPosition.SetX(vPosition.GetX() + vVelocity.GetX() * _dDeltatime);
    vPosition.SetY(vPosition.GetY() + vVelocity.GetY() * _dDeltatime);
  }
}