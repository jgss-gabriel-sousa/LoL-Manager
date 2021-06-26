#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

using namespace std;


class ClassificationState : public State{
    typedef struct tableRow{
        sf::RectangleShape nameBox;
        sf::RectangleShape ptsBox;
        sf::Text textName;
        sf::Text textPts;
    }tableRow;

public:
    ClassificationState(GameDataRef data,string team,string league);

    void Init();

    void HandleInput();
    void Update(float dt);
    void Draw(float dt);

    void RoundRobinTable();
    void PlayoffTable();

private:
    GameDataRef _data;

    League* league;
    string actualTeam;

    bool leagueChanged = true;

    vector<tableRow> slot;
};
