#include "soundManager.h"

SoundManager* SoundManager::instance = 0;


SoundManager::SoundManager() {
    // Mixer: 44.1kHz, default format, 2 channels, 2048 chunk size
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "SDL_mixer could not initialize! Error: " << Mix_GetError() << std::endl;
    }
}


SoundManager::~SoundManager() {
    clean();
}

SoundManager* SoundManager::Instance() {
    if (instance == 0) {
        instance = new SoundManager();
    }
    return instance;
}


bool SoundManager::load(std::string fileName, std::string id, SoundType type) {
    if (type == SOUND_MUSIC) {
        Mix_Music* music = Mix_LoadMUS(fileName.c_str());
        if (music == 0) {
            std::cout << "Could not load music: " << Mix_GetError() << std::endl;
            return false;
        }
        musicMap[id] = music;
    } else if (type == SOUND_SFX) {
        Mix_Chunk* chunk = Mix_LoadWAV(fileName.c_str());
        if (chunk == 0) {
            std::cout << "Could not load SFX: " << Mix_GetError() << std::endl;
            return false;
        }
        sfxMap[id] = chunk;
    }

    return true;
}


bool SoundManager::loadFromList(std::string path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cout << "Failed to open file: " << path << std::endl;
        return false;
    }

    std::string id, typeStr, filePath;

    while (file >> id >> typeStr >> filePath) {
        SoundType type = (typeStr == "music") ? SOUND_MUSIC : SOUND_SFX;
        load(filePath, id, type);
        std::cout << "Loaded Sound: " << id << std::endl;
    }

    file.close();
    return true;
}


void SoundManager::playMusic(std::string id, int loop) {
    if (musicMap[id] != NULL) {
        Mix_PlayMusic(musicMap[id], loop);
    }
}


void SoundManager::playSFX(std::string id, int loop) {
    if (sfxMap[id] != NULL) {
        // Channel -1: Select the nearest empty channel
        Mix_PlayChannel(-1, sfxMap[id], loop);
    }
}


void SoundManager::setMusicVolume(int volume) {
    Mix_VolumeMusic(volume);
}


void SoundManager::setSFXVolume(int volume) {
    // -1 to set all channels
    Mix_Volume(-1, volume);
}


void SoundManager::stopMusic() {
    Mix_HaltMusic();
}


void SoundManager::clean() {
    for (const auto& [key, val] : sfxMap) {
        Mix_FreeChunk(val);
    }
    sfxMap.clear();

    for (const auto& [key, val] : musicMap) {
        Mix_FreeMusic(val);
    }
    musicMap.clear();

    Mix_CloseAudio();
}