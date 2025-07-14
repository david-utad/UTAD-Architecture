/**
 *  @author David Gonzalez Ledesma
 **/

#pragma once
#include <string>

class Enemy;

class Game
{
public:

  /**
   * It initialice the entities in the game. 
   */
  static bool Init();
  
private:

  Game();
  virtual ~Game();

  /**
   * Function to provide the enemies velocity to the engine.
   * @param _oEnemy_ -> Enemy entity.
   * @param _dXVelocity_ -> Enemy horizontal velocity.
   * @param _dYVelocity_ -> Enemy vertical velocity.
   * @param _dDeltatime -> Time to update the velocity.
   * @param _bRightCollision -> If the enemy collides with something in its right position.
   * @param _bLeftCollision -> If the enemy collides with something in its left position.
   * @param _bTopCollision -> If the enemy collides with something in its top position.
   * @param _bBottomCollision -> If the enemy collides with something in its bottom position.
   */
  static void SetEnemyVel(Enemy& _oEnemy_, double& _dXVelocity_, double& _dYVelocity_, double _dDeltatime,
                          bool _bRightCollision, bool _bLeftCollision, bool _bTopCollision, bool _bBottomCollision);
  /**
   * Function to set the player initial position.
   * @param iXPosition_ -> Player horizontal position.
   * @param iYPosition_ -> Player vertical position.
   */
  static void SetInitPlayerPosition(int& iXPosition_, int& iYPosition_);
  /**
   * Function to set the welcome text in the game.
   * @param sText_ -> Text to show.
   * @param iXPosition_ -> Horizontal position in the screen.
   * @param iYPosition_ -> Vertical position in the screen.
   * @param uScale_ -> Text scale.
   */
  static void SetStartGameText(std::string& sText_, int& iXPosition_, int& iYPosition_, uint32_t& uScale_);
  /**
   * Function to set the text when the game finishes.
   * @param sText_ -> Text to show.
   * @param iXPosition_ -> Horizontal position in the screen.
   * @param iYPosition_ -> Vertical position in the screen.
   * @param uScale_ -> Text scale.
   */
  static void SetEndGameText(std::string& sText_, int& iXPosition_, int& iYPosition_, uint32_t& uScale_);
  /**
   * function to set the game loop.
   */
  static bool GameLoop();
  /**
   * Function to create the UI in the game.
   */
  static void GameUI();

  static double dHiScore;
  static int iPlayerXPos;
  static int iPlayerYPos;
};