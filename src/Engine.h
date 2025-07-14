/**
 *  @author David Gonzalez Ledesma
 **/

#pragma once
#include <string>
#include "tigr.h"
#include "SpawnSystem.h"
#include "Entity.h"
#include "Input.h"

/**
 * Callback to get the player initial position in the game.
 * @param int& -> XPosition.
 * @param int& -> YPosition.
 */
typedef void (*PlayerPosition)(int&, int&);
/**
 * Callback to render text in the menu (Welcome screen and game over screen)
 * @param std::string -> Text to render.
 * @param int& -> Xposition.
 * @param int& -> YPosition.
 * @param uint32_t& -> Scale for the text.
 */
typedef void (*MenuGameText)(std::string&, int&, int&, uint32_t&);
/**
 * Callback to take the decision when the game is finished.
 * @return bool -> true if the game should be finished.
 */
typedef bool (*GameLoopCondition)();
/**
 * Callback to create the UI in the game.
 */
typedef void (*CreateGameUI)();

class Engine
{
public:

  /**
   * It returns the Engine instance.
   */
  static Engine& GetInstance();
  /**
   * It removes the Engine instance.
   */
  static void Destroy();
  /**
   * It inits the engine and tigr library.
   * @param _iWidth -> Window width.
   * @param _iHeight -> Window height.
   * @param _sTitle -> Window title to show.
   * @return true -> if tigr was initialized.
   */
  bool Init(int _iWidth, int _iHeight, const char* _sTitle);
  /**
   * It returns if the engine and tigr is currently running.
   */
  bool IsRunning();
  /**
   * It processes de user inputs.
   */
  bool ProcessInput();
  /**
   * It updates the game.
   * @param _dDeltatime -> period to update.
   */
  void Update(double _dDeltatime);
  /**
   * It clears the screen.
   */
  void Clear();
  /**
   * It renders the scene and update the tigr library.
   * @param _bDebugDraw -> if true, it will render the entity colliders.
   */
  void Render(bool _bDebugDraw = false);
  /**
   * It unloads the engine and tigr.
   */
  bool Quit();
  /**
   * It returns the time since the engine was initialized.
   */
  double Time();
  /**
   * It waits the specified milliseconds.
   * @param _dTime -> milliseconds to wait.
   */
  void Wait(double _dTime);
  /**
   * It returns if the game has started.
   */
  bool IsGameStarted() const;
  /**
   * It sets the level map url to load.
   * @param _sLevelMap -> Map URL (TMX file).
   * @param _sBackground -> Background URL image.
   */
  void SetLevelMap(const std::string& _sLevelMap, const std::string& _sBackground = "");
  /**
   * It sets the spawn period in the spawner system.
   * @param _iX -> Spawner horizontal point.
   * @param _iY -> Spawner vertical point.
   * @param _dSpawnPeriod -> spawn enemies period.
   */
  void SetupSpawner(int _iX, int _iY, double _dSpawnPeriod);
  /**
   * It adds an enemy type to the spawner.
   * @param _sTEnemy -> Enemy umage URL.
   * @param _dHorizontalVelocity -> Enemy horizontal velocity.
   * @param _dBounceForce -> Force applies when the enemy bounce.
   * @param _pEnemyVelocity -> Callback to change the enemy velocity when collision or bouncing.
   */
  void AddEnemyType(std::string _sTEnemy, double _dHorizontalVelocity, double _dBounceForce, EnemyVelocity _pEnemyVelocity = nullptr);
  /**
   * It creates the player for the game in the position (0, 0). To change the position, use the function SetInitPlayerPosition.
   */
  Entity& CreatePlayerEntity();
  /**
   * It sets the function to set the initial player position in the game.
   * @param _pPlayerPosition -> Player position function;
   */
  void SetInitPlayerPosition(PlayerPosition _pPlayerPosition);
  /**
   * It creates a new input for the game.
   * @param _eType -> Input type (START_GAME, QUIT_GAME, PLAYER_MOVEMENT)
   * @param _iKey -> Key Id in tigr.
   * @param _dValue -> Value to apply when the key is pressed (optional)
   */
  void CreateInput(Input::EType _eType, int _iKey, double _dValue = 0);
  /**
   * It creates a new component in the game UI.
   * @param _eUIComponentType -> Text, image or text plus timer.
   * @param _sValue -> Text to show or image URL.
   * @param _iX -> horizontal position in the screen.
   * @param _iY -> vertical position in the screen.
   * @param _uScale -> UI component scale.
   */
  void CreateIUComponent(Entity::EUIComponentType _eUIComponentType, const std::string& _sValue, int _iX, int _iY, uint32_t _uScale = 1);
  /**
   * It sets the function to assign the start text in the game. 
   * @param _pEndGameText -> End game text.
   */
  void SetStartGameText(MenuGameText _pStartGameText);
  /**
   * It sets the function to assign the text when the player looses. 
   * @param _pEndGameText -> End game text.
   */
  void SetEndGameText(MenuGameText _pEndGameText);
  /**
   * It sets the function to make actions when the game is finished.
   * @param _pGameLoop -> Game loop function.
   */
  void SetGameLoopCondition(GameLoopCondition _pGameLoop);
  /**
   * It sets the function tocreate the UI in the game.
   */
  void SetGameUICreation(CreateGameUI _pGameUI);
  /**
   * It returns the seconds since the game has started.
   */
  double GetGameTime();
  /**
   * It checks the player-enemies collisions.
   */
  bool CheckPlayerCollisions();
  /**
   * It plays the sound in the file parameter.
   * @param _sSoundFile -> Sound to reproduce.
   */
  void PlayAudio(const std::string& _sSoundFile);

private:

  /**
   * Private constructor and destructor
   */
  Engine();
  virtual ~Engine();
  /**
   * Copy constructor and asign methods removed. 
   */
  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) = delete;

  /**
   * It prints the specified text as log in the console.
   * @param _sText -> text to print in console.
   */
  void Log(std::string _sText);

  static Engine* oEngineInstance;

  double m_dTime;
  bool m_bIsRunning;
  bool m_bIsGameStarted;
  bool m_bIsGameEnded;
  bool m_bQuitGame;
  PlayerPosition m_pPlayerPosition;
  MenuGameText m_pStartGameText;
  MenuGameText m_pEndGameText;
  GameLoopCondition m_pGameLoop;
  CreateGameUI m_pGameUI;
  Tigr* m_oScreen;
};