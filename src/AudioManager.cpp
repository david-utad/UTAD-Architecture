#include "AudioManager.h"

AudioManager* AudioManager::oAudiomanagerInstance = nullptr;

AudioManager::AudioManager(bool& _bSuccess_)
{
  _bSuccess_ = ma_engine_init(nullptr, &m_oEngine);
}

AudioManager::~AudioManager()
{
  ma_engine_uninit(&m_oEngine);
}

void AudioManager::CreateInstance()
{
  if (oAudiomanagerInstance == nullptr) {
    bool bSuccess = false;
    oAudiomanagerInstance = new AudioManager(bSuccess);
    if (bSuccess != MA_SUCCESS)
    {
      delete oAudiomanagerInstance;
      oAudiomanagerInstance = nullptr;
    }
  }
}

AudioManager* AudioManager::GetInstance()
{
  return oAudiomanagerInstance;
}

void AudioManager::Destroy()
{
  if (oAudiomanagerInstance == nullptr) {
    delete oAudiomanagerInstance;
    oAudiomanagerInstance = nullptr;
  }
}

void AudioManager::PlayAudio(const std::string& _sSoundFile)
{
  ma_engine_play_sound(&m_oEngine, _sSoundFile.c_str(), nullptr);
}
