/**
 *  @author David Gonzalez Ledesma
 **/

#pragma once
#include <vector>
#include "Input.h"

class InputManager
{
public:

  /**
   * It creates the InputManager instance.
   */
  static void CreateInstance();
  /**
   * It returns the InputManager instance.
   */
  static InputManager* GetInstance();
  /**
   * It removes the InputManager instance.
   */
  static void Destroy();
  /**
   * It creates a new input for the game.
   */
  void CreateInput(Input::EType _eType, int _iKey, double _dValue = 0);
  /**
   * It checks the key with a specific type pressed.
   * @param _eType -> Key type to process. 
   */
  bool ProcessInput(void* _oScreen, Input::EType _eType);
  /**
   * It restores the key held functionality.
   * @param _eType -> Specific key type to restore.
   */
  bool RestoreInput(Input::EType _eType);

private:

  /**
   * Private constructor and destructor
   */
  InputManager();
  virtual ~InputManager();
  /**
   * Copy constructor and asign methods removed.
   */
  InputManager(const InputManager&) = delete;
  InputManager& operator=(const InputManager&) = delete;

  static InputManager* oInputmanagerInstance;

  std::vector<Input> m_lInput;
};