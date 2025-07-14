#include "Game.h"
#include "Engine.h"
#include <sstream>
#include "pugixml.hpp"

double Game::dHiScore = 0;
int Game::iPlayerXPos = 0;
int Game::iPlayerYPos = 0;

Game::Game()
{

}

Game::~Game()
{

}

bool Game::Init()
{
  pugi::xml_document xmlDoc;
  pugi::xml_parse_result xmlParseResult = xmlDoc.load_file("./data/gamedata.xml");
  if (xmlParseResult)
  {
    Engine& oEngine = Engine::GetInstance();
    pugi::xml_node gameData = xmlDoc.child("gamedata");
    // Level map
    pugi::xml_node map = gameData.child("map");
    if (map)
    {
      oEngine.SetLevelMap(map.attribute("file").as_string(), map.attribute("background").as_string());
    }
    // Player creation
    pugi::xml_node player = gameData.child("player");
    Entity& playerEntity = oEngine.CreatePlayerEntity();
    iPlayerXPos = player.attribute("x").as_int();
    iPlayerYPos = player.attribute("y").as_int();
    oEngine.SetInitPlayerPosition(&Game::SetInitPlayerPosition);
    pugi::xml_node animatedSprite = player.child("animatedsprite");
    if (animatedSprite)
    {
      uint32_t uFrames = animatedSprite.attribute("frames").as_uint();
      std::string sIdle = animatedSprite.child("idle").attribute("sprite").as_string();
      std::string sRight = animatedSprite.child("right").attribute("sprite").as_string();
      std::string sLeft = animatedSprite.child("left").attribute("sprite").as_string();
      playerEntity.SetAnimatedSprite(sIdle, sRight, sLeft, uFrames);
    }
    else
    {
      pugi::xml_node sprite = player.child("sprite");
      playerEntity.SetSprite(sprite.attribute("sprite").as_string());
    }
    // Spawner configuration
    pugi::xml_node enemySpawner = gameData.child("enemyspawner");
    oEngine.SetupSpawner(enemySpawner.attribute("x").as_int(), enemySpawner.attribute("y").as_int(), enemySpawner.attribute("period").as_double());
    pugi::xml_node enemyType = enemySpawner.child("enemytype");
    while (enemyType)
    {
      oEngine.AddEnemyType(enemyType.attribute("sprite").as_string(), enemyType.attribute("xvelocity").as_double(),
                           enemyType.attribute("bounceforce").as_double(), &Game::SetEnemyVel);
      enemyType = enemyType.next_sibling("enemytype");
    }
    // Text for the welcome and game over screens
    oEngine.SetStartGameText(&Game::SetStartGameText);
    oEngine.SetEndGameText(&Game::SetEndGameText);
    // Player inputs
    oEngine.CreateInput(Input::EType::START_GAME, TK_SPACE);
    oEngine.CreateInput(Input::EType::QUIT_GAME, TK_ESCAPE);
    oEngine.CreateInput(Input::EType::PLAYER_MOVEMENT, TK_LEFT, -50);
    oEngine.CreateInput(Input::EType::PLAYER_MOVEMENT, TK_RIGHT, 50);
    oEngine.CreateInput(Input::EType::PLAYER_MOVEMENT, 'A', -50);
    oEngine.CreateInput(Input::EType::PLAYER_MOVEMENT, 'D', 50);
    // UI creation
    oEngine.SetGameUICreation(&Game::GameUI);
    // Game loop
    oEngine.SetGameLoopCondition(&Game::GameLoop);
  }
  return xmlParseResult;
}

void Game::SetEnemyVel(Enemy& _oEnemy_, double& _dXVelocity_, double& _dYVelocity_, double _dDeltatime, bool _bRightCollision, bool _bLeftCollision, bool _bTopCollision, bool _bBottomCollision)
{
  double dGravity = 200;
  if ((_bTopCollision && (_dYVelocity_ < 0)) || _bBottomCollision)
  {
    _oEnemy_.SetIsBouncing(_bBottomCollision);
    _dYVelocity_ = (_bBottomCollision ? -_oEnemy_.GetBounceForce() : -_dYVelocity_);
    Engine::GetInstance().PlayAudio("./data/bubble.wav");
  }

  if ((_bRightCollision && (_dXVelocity_ > 0)) || (_bLeftCollision && (_dXVelocity_ < 0)))
  {
    _dXVelocity_ = -_dXVelocity_;
    Engine::GetInstance().PlayAudio("./data/bubble.wav");
  }

  if (_oEnemy_.IsBouncing() && (_dYVelocity_ > 0))
  {
    _oEnemy_.SetIsBouncing(false);
  }
  _dYVelocity_ += dGravity * _dDeltatime;
}

void Game::SetInitPlayerPosition(int& iXPosition_, int& iYPosition_)
{
  iXPosition_ = iPlayerXPos;
  iYPosition_ = iPlayerYPos;
}

void Game::SetStartGameText(std::string& sText_, int& iXPosition_, int& iYPosition_, uint32_t& uScale_)
{
  sText_ = "Press SPACE to start the game";
  iXPosition_ = 175;
  iYPosition_ = 300;
  uScale_ = 3;
}

void Game::SetEndGameText(std::string& sText_, int& iXPosition_, int& iYPosition_, uint32_t& uScale_)
{
  sText_ = "You loose. Your score is: ";
  std::ostringstream sOSText;
  sOSText.precision(2);
  sOSText << std::fixed << Engine::GetInstance().GetGameTime();
  sText_.append(sOSText.str());
  sText_.append("\nPress SPACE to retry");
  iXPosition_ = 175;
  iYPosition_ = 275;
  uScale_ = 3;
}

bool Game::GameLoop()
{
  bool bGameFinished = false;
  // If the player collides with an enemy, the game will be finished.
  if (Engine::GetInstance().CheckPlayerCollisions())
  {
    bGameFinished = true;
    double dCurrentScore = Engine::GetInstance().GetGameTime();
    if (dCurrentScore > dHiScore) {
      dHiScore = dCurrentScore;
      std::ostringstream sHiScore;
      sHiScore.precision(2);
      sHiScore << std::fixed << Engine::GetInstance().GetGameTime();
      pugi::xml_document xmlDoc;
      pugi::xml_node oNode = xmlDoc.append_child("SaveGameData");
      oNode.append_attribute("HiScore").set_value(sHiScore.str());
      xmlDoc.save_file("./save_data/hiscore.xml");
    }
  }
  return bGameFinished;
}

void Game::GameUI()
{
  pugi::xml_document xmlDoc;
  pugi::xml_parse_result xmlParseResult = xmlDoc.load_file("./save_data/hiscore.xml");
  if (xmlParseResult)
  {
    dHiScore = xmlDoc.child("SaveGameData").attribute("HiScore").as_double();
  }
  std::ostringstream sOSText;
  sOSText.precision(2);
  sOSText << "Hi-Score: " << std::fixed << dHiScore;
  Engine& oEngine = Engine::GetInstance();
  oEngine.CreateIUComponent(Entity::EUIComponentType::TEXT, sOSText.str(), 50, 10, 2);
  oEngine.CreateIUComponent(Entity::EUIComponentType::TIMER, "Time: ", 750, 10, 2);
}