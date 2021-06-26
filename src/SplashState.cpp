#include "SplashState.h"
#include "MainMenuState.h"

SplashState::SplashState(GameDataRef data) : _data(data){
    _fadeAlpha = 255;
}

void SplashState::Init(){
    _data->assets.LoadTexture("Splash Background", SPLASH_BACKGROUND_FILEPATH);
    _background.setSize(sf::Vector2f(SCREEN_WIDTH,SCREEN_HEIGHT));
    _background.setTexture(&_data->assets.GetTexture("Splash Background"),true);

    _fade.setSize(sf::Vector2f(SCREEN_WIDTH,SCREEN_HEIGHT));
}

void SplashState::HandleInput(){
    sf::Event event;

    while(this->_data->window.pollEvent(event)){
        if(sf::Event::Closed == event.type){
            this->_data->window.close();
        }
    }
}

void SplashState::Update(float dt){
    if(this->_clock.getElapsedTime().asSeconds() < SPLASH_STATE_FADE_IN){
        //Fade In
        _fadeAlpha -= 255/(GAME_FRAMERATE*SPLASH_STATE_FADE_IN);
    }else if(this->_clock.getElapsedTime().asSeconds() > (SPLASH_STATE_SHOW_TIME - SPLASH_STATE_FADE_OUT)){
        //Fade Out
        if(_fadeAlpha >= 255)
            _fadeAlpha = 255;
        else
            _fadeAlpha += 255/(GAME_FRAMERATE*SPLASH_STATE_FADE_IN);
    }else{
        //No Fade
        _fadeAlpha = 0;
    }

    this->_fade.setFillColor(sf::Color(0,0,0,_fadeAlpha));

    if(this->_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME){
        //Switch to Main Menu
        this->_data->machine.AddState(StateRef(new MainMenuState(_data)),true);
    }
}

void SplashState::Draw(float dt){
    this->_data->window.clear(BACKGROUND_COLOR);
    this->_data->window.draw(this->_background);
    this->_data->window.draw(this->_fade);
    this->_data->window.display();
}







