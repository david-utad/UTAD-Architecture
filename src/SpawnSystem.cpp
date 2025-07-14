#include "SpawnSystem.h"
#include "EntityManager.h"

double SpawnSystem::dSpawnPeriod = 0;
double SpawnSystem::dSpawnTimer = 0;
Vec2 SpawnSystem::vSpawnPoint = Vec2();
std::vector<SpawnSystem::TEnemyType> SpawnSystem::lEnemyType;

void SpawnSystem::ClearEnemyTypes()
{
  lEnemyType.clear();
}

void SpawnSystem::SetupSpawner(const Vec2& _vSpawnPoint, double _dSpawnPeriod)
{
  vSpawnPoint = _vSpawnPoint;
  dSpawnPeriod = _dSpawnPeriod;
}

void SpawnSystem::ResetSpawnTimer()
{
  dSpawnTimer = 0;
}

void SpawnSystem::AddEnemyType(std::string _sTEnemy, double _dHorizontalVelocity, double _dBounceForce, EnemyVelocity _pEnemyVelocity)
{
  lEnemyType.push_back({ _sTEnemy , _dHorizontalVelocity, _dBounceForce, _pEnemyVelocity });
}

EnemyVelocity SpawnSystem::GetEnemyVelocity(int _iEnemyType)
{
  return lEnemyType[_iEnemyType].m_pEnemyVelocity;
}

void SpawnSystem::Update(double _dDeltatime)
{
  if (dSpawnPeriod > 0)
  {
    if (dSpawnTimer == 0)
    {
      SpawnEnemy();
    }
    dSpawnTimer = (dSpawnTimer < dSpawnPeriod) ? (dSpawnTimer + _dDeltatime) : 0;
  }
}

void SpawnSystem::SpawnEnemy()
{
  EntityManager* oEntityManager = EntityManager::GetInstance();
  if (oEntityManager != nullptr)
  {
    int iEnemyType = rand() % lEnemyType.size();
    Vec2 oVelocity(lEnemyType[iEnemyType].m_dHorizontalVelocity, 0);
    Entity oEnemy = oEntityManager->CreateEnemyEntity(iEnemyType, vSpawnPoint, oVelocity, lEnemyType[iEnemyType].m_dBounceForce);
    oEnemy.SetSprite(lEnemyType[iEnemyType].m_sTEnemy);
  }
}