#include "ClassificationState.h"


ClassificationState::ClassificationState(GameDataRef data,string teams,string league) : _data(data){
    this->league = _data->database.getLeague(league);
    actualTeam = team;
}


void ClassificationState::Init(){
    LogPush("\t ClassificationState");
}


void ClassificationState::HandleInput(){
    sf::Event event;

    while(_data->window.pollEvent(event)){
        if(sf::Event::Closed == event.type){
            _data->window.close();
        }
        if(event.type == sf::Event::KeyPressed){
            if(event.key.code == sf::Keyboard::Escape)
                 _data->machine.RemoveState();
        }
    }
}


void ClassificationState::Update(float dt){
    if(leagueChanged){
        if(league->hasRoundRobin){
            leagueChanged = false;
            RoundRobinTable();
        }
        if(league->hasPlayoff){
            PlayoffTable();
        }
    }
}


void ClassificationState::PlayoffTable(){
    if(league->hasRoundRobin){
        ;
    }
    else{
        ;
    }

    sf::RectangleShape nameBox;
    sf::RectangleShape ptsBox;
    sf::Text name;
    sf::Text pts;
    int initialY = 20;
    int boxHeight = 40;

    ;
}


void ClassificationState::RoundRobinTable(){
    slot.clear();

    sf::RectangleShape nameBox;
    sf::RectangleShape ptsBox;
    sf::Text name;
    sf::Text pts;
    int initialY = SCREEN_HEIGHT*0.25;
    int boxHeight = 30;

    nameBox.setSize(sf::Vector2f(200,boxHeight));
    nameBox.setOutlineColor(HALF_GREY_COLOR);
    nameBox.setOutlineThickness(-2);

    ptsBox.setSize(sf::Vector2f(boxHeight,boxHeight));
    ptsBox.setFillColor(DARK_WHITE);
    ptsBox.setOutlineColor(HALF_GREY_COLOR);
    ptsBox.setOutlineThickness(-2);

    name.setFont(_data->assets.GetFont("Arial"));
    name.setFillColor(sf::Color::Black);
    pts.setFont(_data->assets.GetFont("Arial"));
    pts.setFillColor(sf::Color::Black);


    if(league->table.size() == 0){
        league->generateCalendar();
    }

    for(int i = 0; i<league->table.size(); i++){
        if(league->hasPlayoff && i < league->teamsInPlayoff){
            nameBox.setFillColor(DARK_GREEN);
            ptsBox.setFillColor(DARK_GREEN);
        }
        else if((!league->isFranchise) && i == league->table.size()-1){
            nameBox.setFillColor(DARK_RED);
            ptsBox.setFillColor(DARK_RED);
        }
        else{
            nameBox.setFillColor(DARK_WHITE);
            ptsBox.setFillColor(DARK_WHITE);
        }

        LogPush(league->table[i].second->name);

        nameBox.setPosition(sf::Vector2f(20+(nameBox.getGlobalBounds().width/2),initialY+(i*boxHeight)));

        name.setString(league->table[i].second->name);
        name.setCharacterSize(18);
        name.setOrigin(name.getGlobalBounds().width/2,name.getGlobalBounds().height/2);
        name.setPosition(sf::Vector2f(nameBox.getPosition().x+nameBox.getGlobalBounds().width/2,
                                      nameBox.getPosition().y+nameBox.getGlobalBounds().height/2));


        ptsBox.setSize(sf::Vector2f(boxHeight,boxHeight));
        ptsBox.setPosition(sf::Vector2f(nameBox.getPosition().x-ptsBox.getGlobalBounds().width,initialY+(i*boxHeight)));

        pts.setCharacterSize(18);
        pts.setString(to_string(league->table[i].first));
        pts.setPosition(sf::Vector2f(ptsBox.getPosition().x+ptsBox.getGlobalBounds().width/2-pts.getGlobalBounds().width/2,ptsBox.getPosition().y+ptsBox.getGlobalBounds().height/2-pts.getCharacterSize()/2));

        tableRow tr;
        tr.nameBox = nameBox;
        tr.ptsBox = ptsBox;
        tr.textName = name;
        tr.textPts = pts;
        slot.push_back(tr);
    }
}


void ClassificationState::Draw(float dt){
    _data->window.clear(BACKGROUND_COLOR);

    for(int i = 0; i<slot.size(); i++){
        _data->window.draw(slot[i].nameBox);
        _data->window.draw(slot[i].ptsBox);
        _data->window.draw(slot[i].textName);
        _data->window.draw(slot[i].textPts);
    }

    _data->window.display();
}







