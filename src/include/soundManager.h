#pragma once
#include <SDL2/SDL_mixer.h>
#include <string>
#include <map>
#include <iostream>
#include <fstream>

enum SoundType {
    SOUND_MUSIC = 0,
    SOUND_SFX = 1
};

class SoundManager {
private:
    // Singleton Instance
    static SoundManager* instance;

    std::map<std::string, Mix_Music*> musicMap;
    std::map<std::string, Mix_Chunk*> sfxMap;

    SoundManager();
public:
    ~SoundManager();
    static SoundManager* Instance();

    // Load 1 file(sound, sfx)
    bool load(std::string fileName, std::string id, SoundType type);

    // Load all sounds from a file
    bool loadFromList(std::string path);

    // play background music (-1 for loop)
    void playMusic(std::string id, int loop = -1);
    
    // play sfx
    void playSFX(std::string id, int loop = 0);

    // Adjust the volume
    void setMusicVolume(int volume);
    void setSFXVolume(int volume);

    void stopMusic();
    void clean();
};