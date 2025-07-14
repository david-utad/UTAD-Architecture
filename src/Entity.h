/**
 *  @author David Gonzalez Ledesma
 **/

#pragma once
#include <cstdint>
#include <string>
#include "Vec2.h"

class Entity
{
public:
  enum EType
  {
    PLAYER,
    ENEMY,
    TILE,
    UI_COMPONENT
  };

  enum EUIComponentType
  {
    TEXT,
    TIMER
  };

  /**
   * It creates the player entity.
   * @param _uId -> New entity id.
   * @param _vPosition -> Enemy position.
   */
  Entity(uint32_t _uId, const Vec2& _vPosition = Vec2());
  /**
   * It creates an enemy entity.
   * @param _uId -> New entity id.
   * @param _iEnemyType -> Enemy type Id.
   * @param _vPosition -> Enemy position.
   * @param _vVelocity -> Enemy velocity.
   * @param _dBounceForce -> Force to apple at bounce.
   */
  Entity(uint32_t _uId, int _iEnemyType, const Vec2& _vPosition, const Vec2& _vVelocity, double _dBounceForce);
  /**
   * It creates a tile entity.
   * @param _uId -> New entity id.
   * @param _uTileId -> Tile Id.
   * @param _vPosition -> Tile position.
   * @param _vSize -> Tile size.
   */
  Entity(uint32_t _uId, uint32_t _uTileId, const Vec2& _vPosition, const Vec2& _vSize);
  /**
   * It creates an UI component entity.
   * @param _uId -> New entity id.
   * @param _eUIComponentType -> Text, image or text plus timer.
   * @param _sValue -> Text to show or image URL.
   * @param _vPosition -> UI component position in the screen.
   * @param _uScale -> UI component scale.
   */
  Entity(uint32_t _uId, Entity::EUIComponentType _eUIComponentType, const std::string& _sValue, const Vec2& _vPosition, uint32_t _uScale = 1);
  virtual ~Entity();

  /**
   * It returns the entity sprite size, If the sprite doesn't exist for this entity, it will return (0, 0). 
   */
  Vec2 GetSpriteSize();
  /**
   * It returns if the entity is the player. 
   */
  bool IsPlayerEntity();
  /**
   * It returns if the entity is an enemy. 
   */
  bool IsEnemyEntity();
  /**
   * It returns if the entity is a UI component. 
   */
  bool IsUIEntity();
  /**
   * It sets the entity position in the game.
   * @param _vPosition -> Position in the game.
   */
  void SetEntityPosition(const Vec2& _vPosition);
  /**
   * It sets the texture in the file as Sprite component.
   * @param _sTFile -> Texture file.
   */
  void SetSprite(const std::string& _sTFile);
  /**
   * It sets the texture in the file as Sprite component.
   * @param _sIdle -> Idle texture file.
   * @param _sRight -> Right animation texture file.
   * @param _sLeft -> Left animation texture file.
   * @param _uHFrames -> The frames in the right and left animations (they should be the same).
   */
  void SetAnimatedSprite(const std::string& _sIdle, const std::string& _sRight, const std::string& _sLeft, uint32_t _uFrames);
  /**
   * It removes all the entity components.
   */
  void DestroyEntity();

private:

  uint32_t m_uId;
  Entity::EType m_eType;
};