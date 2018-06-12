//
// SoundManager.cpp for  in /home/hugo/rendu_tek2/CPP/cpp_indie_studio/src/Drafts/Sound
// 
// Made by walbecq
// Login   <hugo@epitech.net>
// 
// Started on  Wed May 11 16:55:47 2016 walbecq
// Last update Sun Jun  5 17:00:22 2016 walbecq
//

#include	"SoundManager.hh"

SoundManager SoundManager::m_instance=SoundManager();

SoundManager::SoundManager() : m_sounds(), m_volume(1), m_ambianceVolume(1), m_effectsVolume(1)
{
  FMOD_Channel_SetChannelGroup(m_channeleffect, m_effect);
  FMOD_Channel_SetChannelGroup(m_channelambiance, m_music);
  FMOD_System_Create(&m_system);
  FMOD_System_Init(m_system, 32, FMOD_INIT_NORMAL, NULL);
}

SoundManager::~SoundManager()
{
  for (auto it = m_sounds.begin(); it != m_sounds.end(); it++)
      FMOD_Sound_Release((*it).second);
  FMOD_Sound_Release(m_ambiance);
  FMOD_System_Close(m_system);
  FMOD_System_Release(m_system);
}

SoundManager &SoundManager::getSingleton()
{
  return m_instance;
}

void SoundManager::playSound(const std::string &sound)
{
  for (auto it = m_sounds.begin(); it != m_sounds.end(); it++)
  {
    if (!sound.compare((*it).first)) {
      FMOD_System_PlaySound(m_system, FMOD_CHANNEL_FREE, (*it).second, 0, &m_channeleffect);
    }
  }
  FMOD_System_Update(m_system);
}

bool SoundManager::createSound(const std::string &path, const std::string &name) {
  std::pair<std::string, FMOD_SOUND *>  toto;
  FMOD_RESULT                           res;

  toto.first = name;
  res = FMOD_System_CreateSound(m_system, path.c_str(), FMOD_CREATESAMPLE, 0, &(toto.second));
  if (res != FMOD_OK)
    return false;
  m_sounds.push_back(toto);
  return true;
}

bool SoundManager::setAmbiance(const std::string &path) {
  FMOD_RESULT res;
  if (m_ambiance != NULL)
    FMOD_Sound_Release(m_ambiance);
  res = FMOD_System_CreateSound(m_system, path.c_str(), FMOD_LOOP_NORMAL | FMOD_CREATESAMPLE | FMOD_SOFTWARE | FMOD_2D, 0, &m_ambiance);
  if (res != FMOD_OK)
    return false;
  //  FMOD_Sound_SetLoopCount(m_ambiance, -1);
  return true;
}

void SoundManager::playAmbiance() {
  FMOD_System_PlaySound(m_system, FMOD_CHANNEL_FREE, m_ambiance, 0, &m_channelambiance);
  setAmbianceVolume(m_ambianceVolume);
}

void SoundManager::setEffectVolume(float volume) {
  m_effectsVolume = volume;
  FMOD_Channel_SetVolume(m_channeleffect, m_effectsVolume * m_volume);
}

void SoundManager::setGeneralVolume(float volume) {
  if (volume > 1)
    m_volume = 1;
  else
    m_volume = volume;
  setEffectVolume(getEffectVolume());
  setAmbianceVolume(getAmbianceVolume());
}

void SoundManager::setAmbianceVolume(float volume) {
  m_ambianceVolume = volume;
  FMOD_Channel_SetVolume(m_channelambiance, m_ambianceVolume * m_volume);
}

float SoundManager::getEffectVolume() const {
  return m_effectsVolume;
}

float SoundManager::getGeneralVolume() const {
  return m_volume;
}

float SoundManager::getAmbianceVolume() const {
  return m_ambianceVolume;
}

void SoundManager::stopAmbiance() {
  FMOD_Channel_Stop(m_channelambiance);
}
