/**
 *  @author David Gonzalez Ledesma
 **/

#pragma once
#include <string>
#include <vector>
#include "Enemy.h"
#include "Vec2.h"

/**
 * Callback to get the enemy velocity.
 * @param Entity& -> Enemy entity (in/out)
 * @param double& -> XVelocity (in/out)
 * @param double& -> YVelocity (in/out)
 * @param bool -> RightCollision with the level tiles.
 * @param bool -> LeftCollision with the level tiles.
 * @param bool -> TopCollision with the level tiles.
 * @param bool -> BottomCollision with the level tiles.
 */
typedef void (*EnemyVelocity)(Enemy&, double&, double&, double, bool, bool, bool, bool);

class SpawnSystem
{
public:

  /**
   * It restores the enemy type list.
   */
  static void ClearEnemyTypes();
  /**
   * It sets the enemy spwan period.
   * @param _vSpawnPoint -> Point where the enemies are spapwned.
   * @param _dSpawnPeriod -> period.
   */
  static void SetupSpawner(const Vec2& _vSpawnPoint, double _dSpawnPeriod);
  /**
   * It rests the spawn timer.
   */
  static void ResetSpawnTimer();
  /**
   * It adds a new enemy type in the spwaner.
   * @param _sTEnemy -> Enemy texture file URL.
   * @param _dHorizontalVelocity -> Enemy horizontal velocity.
   * @param _dBounceForce -> Enemy bounce force.
   */
  static void AddEnemyType(std::string _sTEnemy, double _dHorizontalVelocity, double _dBounceForce, EnemyVelocity _pEnemyVelocity);
  /**
   * It returns the behavior function when the enemy type collide with the level.
   * @param _iEnemyType -> Enemy type.
   */
  static EnemyVelocity GetEnemyVelocity(int _iEnemyType);
  /**
   * It updates the enemies in the game.
   * @param _dDeltatime -> time to update.
   */
  static void Update(double _dDeltatime);

private:

  struct TEnemyType
  {
    std::string m_sTEnemy;
    double m_dHorizontalVelocity, m_dBounceForce;
    EnemyVelocity m_pEnemyVelocity;
  };

  /**
   * It spawns a new enemy in the game.
   */
  static void SpawnEnemy();

  static double dSpawnPeriod;
  static double dSpawnTimer;
  static Vec2 vSpawnPoint;
  static std::vector<TEnemyType> lEnemyType;
};