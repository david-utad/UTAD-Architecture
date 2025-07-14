#include "Engine.h"
#include <time.h>
#include "EntityManager.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "MovementSystem.h"
#include "RenderSystem.h"
#include "CollisionSystem.h"
#include "TimeSystem.h"
#include "LevelSystem.h"
#include "AnimationSystem.h"

Engine* Engine::oEngineInstance = nullptr;

Engine::Engine()
{
  m_dTime = 0;
  m_bIsRunning = false;
  m_bIsGameStarted = false;
  m_bIsGameEnded = false;
  m_bQuitGame = false;
  m_oScreen = nullptr;
  m_pPlayerPosition = nullptr;
  m_pStartGameText = nullptr;
  m_pEndGameText = nullptr;
  m_pGameLoop = nullptr;
  m_pGameUI = nullptr;
  srand(static_cast<unsigned int>(time(nullptr)));
  EntityManager::CreateInstance();
  InputManager::CreateInstance();
  AudioManager::CreateInstance();
}

Engine::~Engine()
{
  EntityManager::Destroy();
  InputManager::Destroy();
  AudioManager::Destroy();
  SpawnSystem::ClearEnemyTypes();
}

Engine& Engine::GetInstance()
{
  if (oEngineInstance == nullptr) {
    oEngineInstance = new Engine();
  }
  return *oEngineInstance;
}

void Engine::Destroy()
{
  if (oEngineInstance == nullptr) {
    delete oEngineInstance;
    oEngineInstance = nullptr;
  }
}

bool Engine::Init(int _iWidth, int _iHeight, const char* _sTitle)
{
  m_oScreen = tigrWindow(_iWidth, _iHeight, _sTitle, 0);
  if (m_oScreen != nullptr)
  {
    m_bIsRunning = true;
    m_bIsGameStarted = false;
    m_bIsGameEnded = false;
    m_bQuitGame = false;
  }
  LevelSystem::InitLevel(_iWidth, _iHeight);

  return m_bIsRunning;
}

bool Engine::IsRunning()
{
  m_bIsRunning = (!tigrClosed(m_oScreen)) && (!m_bQuitGame);
  return m_bIsRunning;
}

bool Engine::ProcessInput()
{
  InputManager* oInputManager = InputManager::GetInstance();
  bool bProcessed = false;
  if (oInputManager != nullptr)
  {
    if (m_bIsGameStarted)
    {
      oInputManager->RestoreInput(Input::EType::PLAYER_MOVEMENT);
      bProcessed = oInputManager->ProcessInput(m_oScreen, Input::EType::PLAYER_MOVEMENT);
    }
    else
    {
      m_bIsGameStarted = oInputManager->ProcessInput(m_oScreen, Input::EType::START_GAME);
      if (m_bIsGameStarted)
      {
        EntityManager::GetInstance()->RemoveEnemies();
        if (m_pPlayerPosition != nullptr)
        {
          int iXPosition, iYPosition;
          (*m_pPlayerPosition)(iXPosition, iYPosition);
          EntityManager::GetInstance()->SetPlayerPosition(Vec2(static_cast<double>(iXPosition), static_cast<double>(iYPosition)));
        }
        if (m_pGameUI != nullptr)
        {
          EntityManager::GetInstance()->RemoveUI();
          (*m_pGameUI)();
        }
        SpawnSystem::ResetSpawnTimer();
        TimeSystem::RestartTime();
      }
    }
    m_bQuitGame = oInputManager->ProcessInput(m_oScreen, Input::EType::QUIT_GAME);
  }
  return bProcessed;
}

void Engine::Update(double _dDeltatime)
{
  if (m_bIsGameStarted)
  {
    TimeSystem::Update(_dDeltatime);
    SpawnSystem::Update(_dDeltatime);
    MovementSystem::Update(_dDeltatime);
    AnimationSystem::Update(_dDeltatime);
    if (m_pGameLoop != nullptr)
    {
      if ((*m_pGameLoop)())
      {
        m_bIsGameStarted = false;
        m_bIsGameEnded = true;
      }
    }
  }
}

void Engine::Clear()
{
  tigrClear(m_oScreen, tigrRGB(0x80, 0x90, 0xA0));
}

void Engine::Render(bool _bDebugDraw)
{
  if (m_bIsGameStarted)
  {
    RenderSystem::Render(m_oScreen, _bDebugDraw);
  }
  else
  {
    if (m_bIsGameEnded)
    {
      RenderSystem::Render(m_oScreen, _bDebugDraw);
      if (m_pEndGameText != nullptr)
      {
        std::string sText;
        int iXPosition, iYPosition;
        uint32_t uScale;
        (*m_pEndGameText)(sText, iXPosition, iYPosition, uScale);
        RenderSystem::RenderText(m_oScreen, sText, iXPosition, iYPosition, uScale);
      }
    }
    else
    {
      if (m_pStartGameText != nullptr)
      {
        std::string sText;
        int iXPosition, iYPosition;
        uint32_t uScale;
        (*m_pStartGameText)(sText, iXPosition, iYPosition, uScale);
        RenderSystem::RenderText(m_oScreen, sText, iXPosition, iYPosition, uScale);
      }
    }
  }
  tigrUpdate(m_oScreen);
}

bool Engine::Quit()
{
  tigrFree(m_oScreen);
  m_oScreen = nullptr;
  m_bIsRunning = false;
  m_bIsGameStarted = false;
  m_bQuitGame = false;
  return true;
}

double Engine::Time()
{
  m_dTime += tigrTime();
  return m_dTime;
}

void Engine::Wait(double _dTime)
{
  double dLastTime = Time();
  double dElapsedTime = (_dTime / 1000);
  while (dElapsedTime > 0)
  {
    double dNow = Time();
    double dDeltaTime = dNow - dLastTime;
    dLastTime = dNow;
    dElapsedTime -= dDeltaTime;
  }
}

bool Engine::IsGameStarted() const
{
  return m_bIsGameStarted;
}

void Engine::SetLevelMap(const std::string& _sLevelMap, const std::string& _sBackground)
{
  LevelSystem::LoadLevel(_sLevelMap, _sBackground);
}

void Engine::SetupSpawner(int _iX, int _iY, double _dSpawnPeriod)
{
  SpawnSystem::SetupSpawner(Vec2(static_cast<double>(_iX), static_cast<double>(_iY)), _dSpawnPeriod);
}

void Engine::AddEnemyType(std::string _sTEnemy, double _dHorizontalVelocity, double _dBounceForce, EnemyVelocity _pEnemyVelocity)
{
  SpawnSystem::AddEnemyType(_sTEnemy, _dHorizontalVelocity, _dBounceForce, _pEnemyVelocity);
}

Entity& Engine::CreatePlayerEntity()
{
  return EntityManager::GetInstance()->CreatePlayerEntity(Vec2());
}

void Engine::SetInitPlayerPosition(PlayerPosition _pPlayerPosition)
{
  m_pPlayerPosition = _pPlayerPosition;
}

void Engine::CreateInput(Input::EType _eType, int _iKey, double _dValue)
{
  InputManager* oInputManager = InputManager::GetInstance();
  if (oInputManager != nullptr)
  {
    oInputManager->CreateInput(_eType, _iKey, _dValue);
  }
}

void Engine::CreateIUComponent(Entity::EUIComponentType _eUIComponentType, const std::string& _sValue, int _iX, int _iY, uint32_t _uScale)
{
  EntityManager::GetInstance()->CreateUIEntity(_eUIComponentType, _sValue, Vec2(_iX, _iY), _uScale);
}

void Engine::SetStartGameText(MenuGameText _pStartGameText)
{
  m_pStartGameText = _pStartGameText;
}

void Engine::SetEndGameText(MenuGameText _pEndGameText)
{
  m_pEndGameText = _pEndGameText;
}

void Engine::SetGameLoopCondition(GameLoopCondition _pGameLoop)
{
  m_pGameLoop = _pGameLoop;
}

void Engine::SetGameUICreation(CreateGameUI _pGameUI)
{
  m_pGameUI = _pGameUI;
}

double Engine::GetGameTime()
{
  return TimeSystem::GetGameTime();
}

bool Engine::CheckPlayerCollisions()
{
  return CollisionSystem::CheckPlayerEnemies();
}

void Engine::PlayAudio(const std::string& _sSoundFile)
{
  AudioManager::GetInstance()->PlayAudio(_sSoundFile);
}

void Engine::Log(std::string _sText)
{
  puts(_sText.c_str());
}