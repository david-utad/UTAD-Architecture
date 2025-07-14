#include "EntityManager.h"
#include "Components.h"

EntityManager* EntityManager::oEntitymanagerInstance = nullptr;

EntityManager::EntityManager() : m_uNextEntityId(0)
{

}

EntityManager::~EntityManager()
{
  m_lEntity.clear();
}

void EntityManager::CreateInstance()
{
  if (oEntitymanagerInstance == nullptr) {
    oEntitymanagerInstance = new EntityManager();
  }
}

EntityManager* EntityManager::GetInstance()
{
  return oEntitymanagerInstance;
}

void EntityManager::Destroy()
{
  if (oEntitymanagerInstance == nullptr) {
    delete oEntitymanagerInstance;
    oEntitymanagerInstance = nullptr;
  }
}

Entity& EntityManager::CreatePlayerEntity(const Vec2& _vPosition)
{
  m_lEntity.push_back(Entity(m_uNextEntityId, _vPosition));
  m_uNextEntityId++;
  return m_lEntity.back();
}

Entity& EntityManager::CreateEnemyEntity(int _iEnemyType, const Vec2& _vPosition, const Vec2& _vVelocity, double _dBounceForce)
{
  m_lEntity.push_back(Entity(m_uNextEntityId, _iEnemyType, _vPosition, _vVelocity, _dBounceForce));
  m_uNextEntityId++;
  return m_lEntity.back();
}

Entity& EntityManager::CreateTileEntity(uint32_t _uTileId, const Vec2& _vPosition, const Vec2& _vSize)
{
  m_lEntity.push_back(Entity(m_uNextEntityId, _uTileId, _vPosition, _vSize));
  m_uNextEntityId++;
  return m_lEntity.back();
}

Entity& EntityManager::CreateUIEntity(Entity::EUIComponentType _eUIComponentType, const std::string& _sValue, const Vec2& _vPosition, uint32_t _uScale)
{
  m_lEntity.push_back(Entity(m_uNextEntityId, _eUIComponentType, _sValue, _vPosition, _uScale));
  m_uNextEntityId++;
  return m_lEntity.back();
}

void EntityManager::RemoveEnemies()
{
  for (std::vector<Entity>::iterator it = m_lEntity.begin(); it != m_lEntity.end();)
  {
    if ((*it).IsEnemyEntity())
    {
      (*it).DestroyEntity();
      it = m_lEntity.erase(it);
    }
    else
    {
      ++it;
    }
  }
}

void EntityManager::RemoveUI()
{
  for (std::vector<Entity>::iterator it = m_lEntity.begin(); it != m_lEntity.end();)
  {
    if ((*it).IsUIEntity())
    {
      (*it).DestroyEntity();
      it = m_lEntity.erase(it);
    }
    else
    {
      ++it;
    }
  }
}

void EntityManager::SetPlayerPosition(const Vec2& _vPosition)
{
  for (Entity oEntity : m_lEntity)
  {
    if (oEntity.IsPlayerEntity())
    {
      oEntity.SetEntityPosition(_vPosition);
    }
  }
}