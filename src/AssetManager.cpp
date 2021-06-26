#include "AssetManager.h"

//################## TEXTURES #################################

void AssetManager::LoadTexture(std::string name, std::string filePath){
    sf::Texture tex;

    if(tex.loadFromFile(filePath)){
        LogPush("\""+name+"\" Loaded to Asset Manager from: \""+filePath+"\"");
        tex.setSmooth(true);
        this->_textures[name] = tex;
    }else{
        tex.loadFromFile(MISSING_ICON_FILEPATH);
        tex.setSmooth(true);
        this->_textures[name] = tex;
        LogPush("\""+name+"\" NOT loaded to Asset Manager from: \""+filePath+"\" (Missing Texture applied)");
    }
}

void AssetManager::LoadTexture(std::string name){
    sf::Texture tex;

    std::string filePath = TEXTURES_FOLDER_FILEPATH+name+".png";

    if(tex.loadFromFile(filePath)){
        LogPush("\""+name+"\" Loaded to Asset Manager from: \""+filePath+"\"");
        tex.setSmooth(true);
        this->_textures[name] = tex;
    }else{
        tex.loadFromFile(MISSING_ICON_FILEPATH);
        tex.setSmooth(true);
        this->_textures[name] = tex;
        LogPush("\""+name+"\" NOT loaded to Asset Manager from: \""+filePath+"\" (Missing Texture applied)");
    }
}

sf::Texture &AssetManager::GetTexture(std::string name){
    auto found = _textures.find(name);

    if(found != _textures.end()){
        LogPush("\""+name+"\" request: Returned");
        return this->_textures.at(name);
    }else{
        LogPush("\""+name+"\" request: Missing");
        return this->_textures.at("Missing");
    }
}

//################## FONTS ####################################

void AssetManager::LoadFont(std::string name, std::string fileName){
    sf::Font font;

    if(font.loadFromFile(fileName)){
        this->_fonts[name] = font;
        LogPush("Font Loaded to Asset Manager with tag: \""+name+"\" from: \""+fileName+"\"");
    }else{
        LogPush("Font not Loaded correctly to Asset Manager with tag: \""+name+"\" from: \""+fileName+"\" (Default Font (Arial) applied)");
        font.loadFromFile(FONT_ARIAL_FILEPATH);
        this->_fonts[name] = font;
    }
}

sf::Font &AssetManager::GetFont(std::string name){
    return this->_fonts.at(name);
}

//################## AUDIO ####################################

void AssetManager::LoadAudio(std::string name, std::string fileName){
    sf::SoundBuffer sound;

    if(sound.loadFromFile(fileName)){
        this->_audios[name] = sound;
        LogPush("Audio Loaded to Asset Manager with tag: \""+name+"\" from: \""+fileName+"\"");
    }else{
        LogPush("Audio not Loaded correctly to Asset Manager with tag: \""+name+"\" from: \""+fileName+"\" (Missing Audio applied)");
        sound.loadFromFile(MISSING_AUDIO_FILEPATH);
        this->_audios[name] = sound;
    }
}

sf::SoundBuffer &AssetManager::GetAudio(std::string name){
    return this->_audios.at(name);
}








