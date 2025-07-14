/**
 *  @author David Gonzalez Ledesma
 **/

#pragma once
#include <cstdint>
#include "Vec2.h"

class CollisionSystem
{
public:

  struct TCollisionDetection
  {
    bool m_bRightCollision, m_bLeftCollision, m_bTopCollision, m_bBottomCollision;
  };

  /**
   * It checks the collisions between player and enemies in the game.
   */
  static bool CheckPlayerEnemies();
  /**
   * It checks the entity collisions with the level bounds and tiles.
   * @param _uId -> Entity Id.
   */
  static CollisionSystem::TCollisionDetection CheckEntityLevel(uint32_t _uId);

private:

  /**
   * It checks the entity collisions with the level bounds and tiles.
   * @param _vCentre -> Entity collider centre.
   * @param _uRadius -> Enitty collider radius.
   */
  static CollisionSystem::TCollisionDetection CheckLevelCollisions(const Vec2& _vCentre, uint32_t _uRadius);
  /**
   * It will check the collision between two circle colliders.
   */
  static CollisionSystem::TCollisionDetection CheckCircleCircle(const Vec2& _vCentre1, uint32_t _uRadius1, const Vec2& _vCentre2, uint32_t _uRadius2);
  /**
   * It will check the collision between one circle and one rectangle colliders.
   */
  static CollisionSystem::TCollisionDetection CheckCircleRect(const Vec2& _oCirclePos, uint32_t _uCircleRadius, const Vec2& _oRectPos, const Vec2& _oRectSize);
};