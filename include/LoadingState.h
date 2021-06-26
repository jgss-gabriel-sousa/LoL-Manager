#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>

#include "State.h"
#include "Game.h"

enum{LoadingPlayers,LoadingTeams,LoadingLeagues,LoadingTextures};

class LoadingState : public State{
public:
    LoadingState(GameDataRef data);

    void Init();

    void HandleInput();
    void Update(float dt);
    void Draw(float dt);

    void LoadPlayers();
    void LoadTeams();
    void LoadLeagues();
    void LoadTextures();

private:
    GameDataRef _data;

    sf::Clock _clock;

    int _loadingStage;

    sf::Sprite _loadingBar;
    sf::Sprite _detailRect;

    sf::Text _loadingText;
};
