#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

#define SPLASH_STATE_SHOW_TIME 2    //In Seconds
#define SPLASH_STATE_FADE_IN 1      //In Seconds
#define SPLASH_STATE_FADE_OUT 1     //In Seconds
#define SPLASH_BACKGROUND_FILEPATH "resources/textures/Splash Background.png"

class SplashState : public State{
public:
    SplashState(GameDataRef data);

    void Init();

    void HandleInput();
    void Update(float dt);
    void Draw(float dt);

private:
    GameDataRef _data;
    sf::Clock _clock;

    int _fadeAlpha;

    sf::RectangleShape _background;
    sf::RectangleShape _fade;
};
