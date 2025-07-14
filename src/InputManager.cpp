#include "InputManager.h"
#include "tigr.h"
#include "Components.h"

InputManager* InputManager::oInputmanagerInstance = nullptr;

InputManager::InputManager()
{

}

InputManager::~InputManager()
{
  m_lInput.clear();
}

void InputManager::CreateInstance()
{
  if (oInputmanagerInstance == nullptr) {
    oInputmanagerInstance = new InputManager();
  }
}

InputManager* InputManager::GetInstance()
{
  return oInputmanagerInstance;
}

void InputManager::Destroy()
{
  if (oInputmanagerInstance == nullptr) {
    delete oInputmanagerInstance;
    oInputmanagerInstance = nullptr;
  }
}

void InputManager::CreateInput(Input::EType _eType, int _iKey, double _dValue)
{
  m_lInput.push_back(Input(_eType, _iKey, _dValue));
}

bool InputManager::ProcessInput(void* _oScreen, Input::EType _eType)
{
  bool bPressed = false;
  Tigr* oTScreen = static_cast<Tigr*>(_oScreen);
  for (Input& oInput : m_lInput)
  {
    if ((_eType == oInput.GetType()) && (tigrKeyHeld(oTScreen, oInput.GetKey())))
    {
      if (_eType == Input::EType::PLAYER_MOVEMENT)
      {
        // It joins the components with player and velocity.
        for (uint32_t uId : join<CPlayer, CVelocity>())
        {
          get<CVelocity>(uId).SetX(oInput.GetValue());
        }
      }
      bPressed = true;
      break;
    }
  }
  return bPressed;
}

bool InputManager::RestoreInput(Input::EType _eType)
{
  bool bFound = false;
  for (Input& oInput : m_lInput)
  {
    if ((oInput.GetType() == _eType) && (_eType == Input::EType::PLAYER_MOVEMENT))
    {
      // It joins the components with player and velocity.
      for (uint32_t uId : join<CPlayer, CVelocity>())
      {
        get<CVelocity>(uId).SetX(0);
      }
    }
  }
  return bFound;
}