/**
 *  @author David Gonzalez Ledesma
 **/

#pragma once
#include <vector>
#include <cstdint>
#include "Entity.h"

class EntityManager
{
public:

  /**
   * It creates the EntityManagerInstance.
   */
  static void CreateInstance();
  /**
   * It returns the EntityManager instance.
   */
  static EntityManager* GetInstance();
  /**
   * It removes the EntityManager instance.
   */
  static void Destroy();
  /**
   * It creates the player entity.
   * @param _vPosition -> Player position.
   */
  Entity& CreatePlayerEntity(const Vec2& _vPosition = Vec2());
  /**
   * It creates an enemy entity.
   * @param _iEnemyType -> Enemy type Id.
   * @param _vPosition -> Enemy position.
   * @param _vVelocity -> Enemy velocity.
   * @param _dBounceForce -> Force to apple at bounce.
   */
  Entity& CreateEnemyEntity(int _iEnemyType, const Vec2& _vPosition, const Vec2& _vVelocity, double _dBounceForce);
  /**
   * It creates a tile entity.
   * @param _uTileId -> Tile Id.
   * @param _vPosition -> Tile position.
   * @param _vSize -> Tile size.
   */
  Entity& CreateTileEntity(uint32_t _uTileId, const Vec2& _vPosition, const Vec2& _vSize);
  /**
   * It creates an UI entity.
   * @param _eUIComponentType -> Text, image or text plus timer.
   * @param _sValue -> Text to show or image URL.
   * @param _vPosition -> UI component position in the screen.
   * @param _uScale -> UI component scale.
   */
  Entity& CreateUIEntity(Entity::EUIComponentType _eUIComponentType, const std::string& _sValue, const Vec2& _vPosition, uint32_t _uScale = 1);
  /**
   * It removes all the enemies in the game.
   */
  void RemoveEnemies();
  /**
   * It removes all the UI components in the game.
   */
  void RemoveUI();
  /**
   * It sets the player position.
   * @param _vPosition -> Player position.
   */
  void SetPlayerPosition(const Vec2& _vPosition);

private:

  /**
   * Private constructor and destructor
   */
  EntityManager();
  virtual ~EntityManager();
  /**
   * Copy constructor and asign methods removed.
   */
  EntityManager(const EntityManager&) = delete;
  EntityManager& operator=(const EntityManager&) = delete;

  static EntityManager* oEntitymanagerInstance;

  std::vector<Entity> m_lEntity;
  uint32_t m_uNextEntityId;
};