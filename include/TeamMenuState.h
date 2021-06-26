#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

using namespace std;


class PlayerIcons{
public:
    PlayerIcons(GameDataRef data, string name, Team* team);

    void UpdateAndDraw();

    GameDataRef _data;

    int pos;
    Player player;
    Team* actualTeam;
    sf::RectangleShape face;
    sf::RectangleShape country;
    sf::RectangleShape lane;
    sf::Text name;
    sf::Text hability;
    sf::Text age;
};


class TeamMenuState : public State{
public:
    TeamMenuState(GameDataRef data,string teamName);

    void Init();

    void HandleInput();
    void Update(float dt);
    void Draw(float dt);

    void UpdateFloatingHelp(sf::Vector2f objPos, sf::FloatRect objRect,string text);

    void Save();
    void Exit();

private:
    GameDataRef _data;

    sf::Clock stateTime;

    bool showingHelp = 0;
    sf::RectangleShape floatingHelpBox;
    sf::Text floatingHelpText;

    bool showDebugObj = 1;
    sf::RectangleShape* debugObj;
    sf::RectangleShape tabAux;

    Team* actualTeam;

    sf::RectangleShape teamLogo;

    sf::RectangleShape calendarIcon;
    sf::RectangleShape standingsIcon;
    sf::RectangleShape financesIcon;
    sf::RectangleShape marketIcon;
    sf::RectangleShape saveIcon;
    sf::RectangleShape exitIcon;
    sf::RectangleShape playIcon;

    sf::Text playText = sf::Text("Play",_data->assets.GetFont("Arial"),30);

    sf::RectangleShape playerBoxBackground;
    sf::RectangleShape playerBoxFace;
    sf::Text playerBoxInfo;

    vector<PlayerIcons> players;

    int actualTab = 0;
    bool tabChanged = true;
    vector<sf::RectangleShape> tabs;
    vector<sf::Text> tabsText;
};
