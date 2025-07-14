#include "Enemy.h"

Enemy::Enemy() : m_iEnemyType(-1), m_dBounceForce(0), m_bIsBouncing(false)
{

}

Enemy::Enemy(int _iEnemyType, double _dBounceForce) : m_iEnemyType(_iEnemyType), m_dBounceForce(_dBounceForce), m_bIsBouncing(false)
{

}

Enemy::~Enemy()
{

}

int Enemy::GetEnemyType()
{
    return m_iEnemyType;
}

double Enemy::GetBounceForce()
{
    return m_dBounceForce;
}

bool Enemy::IsBouncing()
{
    return m_bIsBouncing;
}

void Enemy::SetIsBouncing(bool _bIsBouncing)
{
  m_bIsBouncing = _bIsBouncing;
}