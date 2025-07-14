#pragma once
#include <string>
#include "miniaudio.h"

class AudioManager
{
public:

  /**
   * It creates the AudioManager instance.
   */
  static void CreateInstance();
  /**
   * It returns the AudioManager instance.
   */
  static AudioManager* GetInstance();
  /**
   * It removes the AudioManager instance.
   */
  static void Destroy();
  /**
   * It plays the sound in the file parameter.
   * @param _sSoundFile -> Sound to reproduce.
   */
  void PlayAudio(const std::string& _sSoundFile);

private:

  /**
   * Private constructor and destructor
   */
  AudioManager(bool& _bSuccess_);
  virtual ~AudioManager();
  /**
   * Copy constructor and asign methods removed.
   */
  AudioManager(const AudioManager&) = delete;
  AudioManager& operator=(const AudioManager&) = delete;

  static AudioManager* oAudiomanagerInstance;

  ma_engine m_oEngine; 
};