/**
 *  @author David Gonzalez Ledesma
 **/

#pragma once

class Enemy
{
public:

  Enemy();
  Enemy(int _iEnemyType, double _dBounceForce);
  virtual ~Enemy();

  /**
   * It returns the enemy type id.
   */
  int GetEnemyType();
  /**
   * It returns the enemy bounce force.
   */
  double GetBounceForce();
  /**
   * It returns if the enemy is bouncing.
   */
  bool IsBouncing();
  /**
   * It sets the enemy bouncing parameter.
   */
  void SetIsBouncing(bool _bIsBouncing);

private:

  int m_iEnemyType;
  double m_dBounceForce;
  bool m_bIsBouncing;
};