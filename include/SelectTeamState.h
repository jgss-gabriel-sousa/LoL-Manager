#pragma once

#include "State.h"
#include "Game.h"

using namespace std;

class SelectTeamState : public State{
public:
    SelectTeamState(GameDataRef data);

    void Init();

    void HandleInput();
    void Update(float dt);
    void Draw(float dt);

    void TeamButton();
    void LeagueButton();

private:
    GameDataRef _data;

    sf::Sprite _playButton;
    sf::Sprite _leftArrowTeam;
    sf::Sprite _rightArrowTeam;
    sf::Sprite _leftArrowLeague;
    sf::Sprite _rightArrowLeague;
    sf::Sprite _leagueLogo;
    sf::RectangleShape _countryFlag;
    sf::Sprite _teamLogo;
    sf::Sprite _teamLogoBackground;
    sf::Text _teamName;
    sf::Text _leagueName;
    sf::Text _countryName;
    sf::Text teamCash;
    sf::Text teamHability;

    std::map<std::string,std::vector<std::string>> leaguesTeams;
    std::vector<std::string>aux;
    std::string team;
    std::string league;
    std::string country;

    int teamButton;
    int leagueButton;
    bool isTeamButtonChanged;
    bool isLeagueButtonChanged;
};
