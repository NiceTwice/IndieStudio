//
// SoundManager.hh for  in /home/hugo/rendu_tek2/CPP/cpp_indie_studio/src/Drafts/Sound
// 
// Made by walbecq
// Login   <hugo@epitech.net>
// 
// Started on  Wed May 11 16:55:53 2016 walbecq
// Last update Thu May 26 13:24:21 2016 walbecq
//

#ifndef		SOUNDMANAGER_H
# define	SOUNDMANAGER_H

#include <iostream>
#include <fmodex/fmod.h>
#include <string>
#include <list>

class SoundManager
{
public:
    static SoundManager &getSingleton();

    void			playSound(const std::string &);
    bool            createSound(const std::string &, const std::string &);
    bool            setAmbiance(const std::string &);
    void            playAmbiance();
    void            setEffectVolume(float);
    void            setGeneralVolume(float);
    void            setAmbianceVolume(float);
    float           getEffectVolume() const;
    float           getGeneralVolume() const;
    float           getAmbianceVolume() const;
    void            stopAmbiance();

private:
    static SoundManager	m_instance;
    FMOD_SYSTEM		*m_system;
    std::list<std::pair<std::string, FMOD_SOUND *> > m_sounds;
    FMOD_CHANNEL        *m_channeleffect;
    FMOD_CHANNEL        *m_channelambiance;
    FMOD_SOUND          *m_ambiance;
    FMOD_CHANNELGROUP   *m_music;
    FMOD_CHANNELGROUP   *m_effect;
    float               m_volume;
    float               m_effectsVolume;
    float               m_ambianceVolume;

    SoundManager();
    ~SoundManager();
};

#endif		// SOUNDMANAGER_H
