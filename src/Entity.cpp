#include "Entity.h"
#include "Components.h"

Entity::Entity(uint32_t _uId, const Vec2& _vPosition) : m_uId(_uId)
{
  m_eType = Entity::EType::PLAYER;
  add<CPlayer>(_uId);
  add<CPosition>(_uId) = _vPosition;
  add<CVelocity>(_uId) = Vec2();
}

Entity::Entity(uint32_t _uId, int _iEnemyType, const Vec2& _vPosition, const Vec2& _vVelocity, double _dBounceForce) : m_uId(_uId)
{
  m_eType = Entity::EType::ENEMY;
  add<CEnemy>(_uId) = Enemy(_iEnemyType, _dBounceForce);
  add<CPosition>(_uId) = _vPosition;
  add<CVelocity>(_uId) = _vVelocity;
}

Entity::Entity(uint32_t _uId, uint32_t _uTileId, const Vec2& _vPosition, const Vec2& _vSize) : m_uId(_uId)
{
  m_eType = Entity::EType::TILE;
  add<CTile>(_uId) = _uTileId;
  add<CPosition>(_uId) = _vPosition;
  add<CRCollider>(_uId) = _vSize;
}

Entity::Entity(uint32_t _uId, Entity::EUIComponentType _eUIComponentType, const std::string& _sValue, const Vec2& _vPosition, uint32_t _uScale) : m_uId(_uId)
{
  m_eType = Entity::EType::UI_COMPONENT;
  add<CPosition>(_uId) = _vPosition;
  add<CUI>(_uId).m_uScale = _uScale;
  add<CText>(_uId) = _sValue;
  if (_eUIComponentType == Entity::EUIComponentType::TIMER)
  {
    add<CTimer>(_uId);
  }
}

Entity::~Entity()
{

}

Vec2 Entity::GetSpriteSize()
{
  Vec2 vSize(0, 0);
  if (has<CSprite>(m_uId))
  {
    vSize = get<CSprite>(m_uId).GetSize();
  }
  else if (has<CAnimatedSprite>(m_uId))
  {
    vSize = get<CAnimatedSprite>(m_uId).GetIdleSprite().GetSize();
  }
  return vSize;
}

bool Entity::IsPlayerEntity()
{
  return (m_eType == Entity::EType::PLAYER);
}

bool Entity::IsEnemyEntity()
{
  return (m_eType == Entity::EType::ENEMY);
}

bool Entity::IsUIEntity()
{
  return (m_eType == Entity::EType::UI_COMPONENT);
}

void Entity::SetEntityPosition(const Vec2& _vPosition)
{
  add<CPosition>(m_uId) = _vPosition;
}

void Entity::SetSprite(const std::string& _sTFile)
{
  if (has<CAnimatedSprite>(m_uId))
  {
    del<CAnimatedSprite>(m_uId);
  }
  Sprite oSprite(_sTFile);
  add<CSprite>(m_uId) = oSprite;
  add<CCCollider>(m_uId) = static_cast<uint32_t>(oSprite.GetSize().GetX() / 2);
}

void Entity::SetAnimatedSprite(const std::string& _sIdle, const std::string& _sRight, const std::string& _sLeft, uint32_t _uFrames)
{
  if (has<CSprite>(m_uId))
  {
    del<CSprite>(m_uId);
  }
  AnimatedSprite oAnimatedSprite(_sIdle, _sRight, _sLeft, _uFrames);
  add<CAnimatedSprite>(m_uId) = oAnimatedSprite;
  add<CCCollider>(m_uId) = static_cast<uint32_t>(oAnimatedSprite.GetIdleSprite().GetSize().GetX() / 2);
}

void Entity::DestroyEntity()
{
  del<CPosition>(m_uId);
  del<CVelocity>(m_uId);
  del<CSprite>(m_uId);
  del<CRCollider>(m_uId);
  del<CCCollider>(m_uId);
  del<CEnemy>(m_uId);
  del<CPlayer>(m_uId);
  del<CTile>(m_uId);
  del<CUI>(m_uId);
  del<CTimer>(m_uId);
  del<CText>(m_uId);
  del<CAnimatedSprite>(m_uId);
}