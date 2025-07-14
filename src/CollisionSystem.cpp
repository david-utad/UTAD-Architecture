#include "CollisionSystem.h"
#include "Components.h"
#include "LevelSystem.h"

bool CollisionSystem::CheckPlayerEnemies()
{
  bool bCollision = false;
  CollisionSystem::TCollisionDetection tCollision = { false, false, false, false };
  // It joins the components with position and collider.
  for (uint32_t uPlayerId : join<CPosition, CCCollider, CPlayer>())
  {
    uint32_t uPlayerRadius = get<CCCollider>(uPlayerId);
    Vec2 vPlayerCentre = get<CPosition>(uPlayerId) + Vec2(uPlayerRadius, uPlayerRadius);
    for (uint32_t uEnemyId : join<CPosition, CCCollider, CEnemy>())
    {
      uint32_t uEnemyRadius = get<CCCollider>(uEnemyId);
      Vec2 vEnemyCentre = get<CPosition>(uEnemyId) + Vec2(uEnemyRadius, uEnemyRadius);
      tCollision = CheckCircleCircle(vPlayerCentre, uPlayerRadius, vEnemyCentre, uEnemyRadius);
      bCollision = (tCollision.m_bLeftCollision || tCollision.m_bRightCollision || tCollision.m_bBottomCollision || tCollision.m_bTopCollision);
      if (bCollision)
      {
        break;
      }
    }
  }
  return bCollision;
}

CollisionSystem::TCollisionDetection CollisionSystem::CheckEntityLevel(uint32_t _uId)
{
  CollisionSystem::TCollisionDetection tCollision = { false, false, false, false };
  if (has<CPosition>(_uId) && has<CCCollider>(_uId))
  {
    uint32_t uEntityRadius = get<CCCollider>(_uId);
    Vec2 vEntityCentre = get<CPosition>(_uId) + Vec2(uEntityRadius, uEntityRadius);
    tCollision = CheckLevelCollisions(vEntityCentre, uEntityRadius);
  }
  return tCollision;
}

CollisionSystem::TCollisionDetection CollisionSystem::CheckLevelCollisions(const Vec2& _vCentre, uint32_t _uRadius)
{
  CollisionSystem::TCollisionDetection tCollision = { false, false, false, false };
  const Vec2& vLevelSize = LevelSystem::GetSize();
  // It is necesary to check the level bounds before the level tiles.
  tCollision.m_bLeftCollision = ((_vCentre.GetX() - _uRadius) < 0);
  tCollision.m_bRightCollision = ((_vCentre.GetX() + _uRadius) > vLevelSize.GetX());
  tCollision.m_bTopCollision = ((_vCentre.GetY() - _uRadius) < 0);
  tCollision.m_bBottomCollision = ((_vCentre.GetY() + _uRadius) > vLevelSize.GetY());
  if (!tCollision.m_bLeftCollision && !tCollision.m_bRightCollision && !tCollision.m_bTopCollision && !tCollision.m_bBottomCollision)
  {
    double dClosestCentreDistance = INFINITY;
    // It joins the components with position and collider.
    for (uint32_t uTileId : join<CTile, CPosition, CRCollider>())
    {
      const Vec2& vPosition = get<CPosition>(uTileId);
      const Vec2& vSize = get<CRCollider>(uTileId);
      // It is necessary to check the closest tile that is colliding with the entities for a correct collision.
      double dCurrentCentreDistance = std::abs(_vCentre.Distance(Vec2(vPosition.GetX() + (vSize.GetX() / 2), vPosition.GetY() + (vSize.GetY() / 2))));
      if (dClosestCentreDistance > dCurrentCentreDistance)
      {
        tCollision = CheckCircleRect(_vCentre, _uRadius, vPosition, vSize);
        if (tCollision.m_bLeftCollision || tCollision.m_bRightCollision || tCollision.m_bBottomCollision || tCollision.m_bTopCollision)
        {
          dClosestCentreDistance = dCurrentCentreDistance;
        }
      }
    }
  }
  return tCollision;
}

CollisionSystem::TCollisionDetection CollisionSystem::CheckCircleCircle(const Vec2& _vCentre1, uint32_t _uRadius1, const Vec2& _vCentre2, uint32_t _uRadius2)
{
  CollisionSystem::TCollisionDetection tCollision = { false, false, false, false };
  double dCentreDistance = _vCentre1.Distance(_vCentre2);
  if (dCentreDistance < static_cast<double>(_uRadius1 + _uRadius2))
  {
    double dDistanceX = _vCentre1.GetX() - _vCentre2.GetX();
    double dDistanceY = _vCentre1.GetY() - _vCentre2.GetY();
    if (std::abs(dDistanceX) >= std::abs(dDistanceY))
    {
      tCollision.m_bRightCollision = (dDistanceX > 0);
      tCollision.m_bLeftCollision = (dDistanceX <= 0);
    }
    else
    {
      tCollision.m_bBottomCollision = (dDistanceY > 0);
      tCollision.m_bTopCollision = (dDistanceY <= 0);
    }
  }
  return tCollision;
}

CollisionSystem::TCollisionDetection CollisionSystem::CheckCircleRect(const Vec2& _vCircleCentre, uint32_t _uCircleRadius, const Vec2& _vRectPos, const Vec2& _vRectSize)
{
  CollisionSystem::TCollisionDetection tCollision = { false, false, false, false };
  double dClosestX = std::max(_vRectPos.GetX(), std::min(_vCircleCentre.GetX(), _vRectPos.GetX() + _vRectSize.GetX()));
  double dClosestY = std::max(_vRectPos.GetY(), std::min(_vCircleCentre.GetY(), _vRectPos.GetY() + _vRectSize.GetY()));
  double dDistanceX = _vCircleCentre.GetX() - dClosestX;
  double dDistanceY = _vCircleCentre.GetY() - dClosestY;
  if ((dDistanceX * dDistanceX + dDistanceY * dDistanceY) < static_cast<double>(_uCircleRadius * _uCircleRadius))
  {
    if (std::abs(dDistanceX) >= std::abs(dDistanceY))
    {
      tCollision.m_bRightCollision = (dDistanceX <= 0);
      tCollision.m_bLeftCollision = (dDistanceX > 0);
    }
    else
    {
      tCollision.m_bBottomCollision = (dDistanceY <= 0);
      tCollision.m_bTopCollision = (dDistanceY > 0);
    }
  }
  return tCollision;
}