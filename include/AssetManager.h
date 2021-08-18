#pragma once

#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "DEFINITIONS.h"
#include "Log.h"

class AssetManager{
public:
    AssetManager(){}
    ~AssetManager(){}

    void LoadTexture(std::string name, std::string fileName);
    void LoadTexture(std::string name);
    sf::Texture &GetTexture(std::string name);

    void LoadFont(std::string name, std::string fileName);
    sf::Font &GetFont(std::string name);

    void LoadAudio(std::string name, std::string fileName);
    sf::SoundBuffer &GetAudio(std::string name);

private:
    std::map<std::string, sf::Texture> _textures;
    std::map<std::string, sf::Font> _fonts;
    std::map<std::string, sf::SoundBuffer> _audios;
};
