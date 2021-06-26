#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

using namespace std;

class EditorState : public State{
enum{
    EditingPlayers,
    CreatingPlayer,
    EditingTeams,
    CreatingTeam,
    EditingLeagues,
    CreatingLeague
};

public:
    EditorState(GameDataRef data);

    void Init();

    void HandleInput();
    void Update(float dt);
    void Draw(float dt);

    void Save();
    void UpdateInfos();
    void UpdateObject();
    void UpdateState();
    void UpdateFloatingHelp(sf::Vector2f objPos, sf::FloatRect objRect,string text);

private:
    GameDataRef _data;

    int objectButton;
    int stateButton;
    bool objectChanged;
    bool stateChanged;
    int mouseScroll = 0;

    bool showingHelp = false;
    bool showCountries = false;
    sf::RectangleShape floatingHelpBox;
    sf::Text floatingHelpText;

    sf::Sprite closeButton;
    sf::Sprite saveButton;
    sf::RectangleShape faceIcon;

    sf::Text title;
    sf::Text textName;
    sf::Text textNationality;
    sf::Text textLane;
    sf::Text textAge;
    sf::Text textSkill;
    sf::Text textExperience;
    sf::Text textFanBase;
    sf::Text textCash;

    sf::Sprite checkBox;
    sf::RectangleShape blackBox;

    vector<sf::Text> countriesList;

    //-----------------

    std::string name;
    std::string nationality;

    std::string playerLane;
    int playerAge;
    int playerSkill;
    int playerExperience;
    int playerFanBase;

    float teamCash;
};
