#include "MainMenuState.h"

#include "LoadingState.h"

MainMenuState::MainMenuState(GameDataRef data) : _data(data){

}


void MainMenuState::Init(){
    _data->assets.LoadTexture("Game Title","resources/textures/game title.png");
    _data->assets.LoadTexture("button");
    _data->assets.LoadFont("Arial","resources/fonts/arial.ttf");
    _data->assets.LoadFont("Marker Felt","resources/fonts/Marker Felt.ttf");

    title.setTexture(_data->assets.GetTexture("Game Title"));
    title.setPosition((SCREEN_WIDTH/2)-(title.getGlobalBounds().width/2),title.getGlobalBounds().height * 0.1);

    AddMenuButton("New Game");
    AddMenuButton("Load Game");
    AddMenuButton("Credits");
    AddMenuButton("Quit");
}


void MainMenuState::HandleInput(){
    sf::Event event;

    while(_data->window.pollEvent(event)){
        if(sf::Event::Closed == event.type){
            _data->window.close();
        }

        if(_data->input.IsSpriteClicked(buttons[0].getGlobalBounds(),sf::Mouse::Left,_data->window)){
            _data->machine.AddState(StateRef(new LoadingState(_data)),true);
        }
        if(_data->input.IsSpriteClicked(buttons[buttons.size()-1].getGlobalBounds(),sf::Mouse::Left,_data->window)){
            exit(0);
        }
    }
}


void MainMenuState::Update(float dt){
    ;
}


void MainMenuState::AddMenuButton(string textString){
    sf::RectangleShape button;

    button.setSize(sf::Vector2f(BUTTON_SIZE));
    button.setTexture(&_data->assets.GetTexture("button"),true);
    if(buttons.size() > 0){
        if(buttons.size() == 1)
            button.setPosition(buttons[0].getPosition().x,buttons[0].getPosition().y+buttons[0].getGlobalBounds().height+BUTTONS_SPACING);
        else
            button.setPosition(buttons[buttons.size()-1].getPosition().x,
                               buttons[buttons.size()-1].getPosition().y+buttons[buttons.size()-1].getGlobalBounds().height+BUTTONS_SPACING);
    }
    else{
        button.setPosition((SCREEN_WIDTH/2)-(button.getGlobalBounds().width/2),
                           FIRST_BUTTON_POSITION-(button.getGlobalBounds().height/2));
    }

    //#################

    sf::Text text;

    text.setFont(_data->assets.GetFont("Arial"));
    text.setFillColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);
    text.setString(textString);

    int aux = text.getCharacterSize();
    while(text.getPosition().x+text.getGlobalBounds().width+10 > button.getPosition().x+button.getGlobalBounds().width){
        text.setCharacterSize(aux);
        aux -= 2;
    }

    text.setOrigin(text.getGlobalBounds().width/2,button.getGlobalBounds().height/4);
    text.setPosition(button.getPosition().x+(button.getGlobalBounds().width/2),
                     button.getPosition().y+(button.getGlobalBounds().height/2));

    buttons.push_back(button);
    buttonsText.push_back(text);
}


void MainMenuState::Draw(float dt){
    _data->window.clear(BACKGROUND_COLOR);

    _data->window.draw(title);

    for(int i = 0; i<buttons.size(); i++){
        _data->window.draw(buttons[i]);
        _data->window.draw(buttonsText[i]);
    }

    _data->window.display();
}



