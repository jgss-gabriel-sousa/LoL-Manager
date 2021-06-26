#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

#define FIRST_BUTTON_POSITION (SCREEN_HEIGHT*0.5)
#define BUTTONS_SPACING (SCREEN_HEIGHT*0.033)
#define BUTTON_SIZE sf::Vector2f(SCREEN_WIDTH*0.32,SCREEN_HEIGHT*0.108)

class MainMenuState : public State{
public:
    MainMenuState(GameDataRef data);

    void Init();

    void HandleInput();
    void Update(float dt);
    void Draw(float dt);

    void AddMenuButton(string text);

private:
    GameDataRef _data;

    vector<sf::RectangleShape> buttons;
    vector<sf::Text> buttonsText;
    sf::Sprite title;
};
