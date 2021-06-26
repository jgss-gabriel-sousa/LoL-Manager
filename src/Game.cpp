#include "Game.h"
#include "SplashState.h"

Game::Game(int width, int height, std::string title){
    _data->window.create(sf::VideoMode(width,height),title,sf::Style::Close | sf::Style::Titlebar);
    _data->machine.AddState(StateRef(new SplashState(this->_data)));

    sf::Image icon;
    icon.loadFromFile("resources/textures/icon.png");
    _data->window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    this->Run();
}

void Game::Run(){
    float newTime, frameTime, interpolation;

    float currentTime = this->_clock.getElapsedTime().asSeconds();
    float accumulator = 0.0f;

    while(this->_data->window.isOpen()){
        if(!_data->window.hasFocus()){
            _data->window.setFramerateLimit(1);
        }
        else{
            _data->window.setFramerateLimit(GAME_FRAMERATE);
        }

        this->_data->machine.ProcessStateChanges();

        newTime = this->_clock.getElapsedTime().asSeconds();
        frameTime = newTime - currentTime;

        if(frameTime > 0.25f){
            frameTime = 0.25f;
        }

        currentTime = newTime;
        accumulator += frameTime;

        while(accumulator >= dt){
            this->_data->machine.GetActiveState()->HandleInput();
            this->_data->machine.GetActiveState()->Update(dt);

            accumulator -= dt;
        }
        interpolation = accumulator / dt;
        this->_data->machine.GetActiveState()->Draw(interpolation);
    }
}
