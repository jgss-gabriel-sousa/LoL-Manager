#include "TeamMenuState.h"
#include "SelectTeamState.h"
#include "ClassificationState.h"


TeamMenuState::TeamMenuState(GameDataRef data,string teamName) : _data(data){
    actualTeam = &_data->database._teams.at(teamName);
}

PlayerIcons::PlayerIcons(GameDataRef data, string playerName, Team* team) : _data(data){
    pos = 0;
    actualTeam = team;

    player = _data->database.getPlayer(playerName);

    face.setTexture(&_data->assets.GetTexture(playerName+"Face"),true);

    //country.setTexture(&_data->assets.GetTexture(_data->database.getPlayerByName(name).nationality),true);

    if(actualTeam->getPlayerStatus(playerName).find("inLoan") != string::npos)
        name.setFillColor(DARK_GREEN);
    else
        name.setFillColor(sf::Color::Black);

    name.setCharacterSize(18);
    name.setString(playerName);
    name.setFont(_data->assets.GetFont("Arial"));
    name.setOrigin(0,name.getGlobalBounds().height/2);

    lane.setSize(sf::Vector2f(30,30));
    lane.setTexture(&_data->assets.GetTexture(player.lane),true);
    lane.setOutlineThickness(2);
    lane.setOutlineColor(sf::Color::White);
}

void PlayerIcons::UpdateAndDraw(){
    lane.setPosition(SCREEN_WIDTH-(SCREEN_WIDTH*0.75),SCREEN_HEIGHT-(SCREEN_HEIGHT*0.8)+(pos*32));
    name.setPosition(lane.getPosition().x+lane.getGlobalBounds().width+5,
                     lane.getPosition().y+(lane.getGlobalBounds().height/2));

    //_data->window.draw(face);
    _data->window.draw(name);
    _data->window.draw(hability);
    _data->window.draw(age);
    _data->window.draw(lane);
}


void TeamMenuState::Init(){
    LogPush("\t TeamMenuState");
    teamLogo.setSize(sf::Vector2f(SCREEN_WIDTH*0.125,SCREEN_WIDTH*0.125));
    teamLogo.setOutlineColor(sf::Color::White);
    teamLogo.setOutlineThickness(1);
    teamLogo.setTexture(&_data->assets.GetTexture(actualTeam->name),true);
    teamLogo.setPosition(5,5);

    calendarIcon.setPosition(teamLogo.getPosition().x+teamLogo.getGlobalBounds().width+(SCREEN_WIDTH*0.025),0);
    calendarIcon.setSize(sf::Vector2f(SCREEN_HEIGHT*0.083,SCREEN_HEIGHT*0.083));
    calendarIcon.setTexture(&_data->assets.GetTexture("calendarIcon"),true);
    standingsIcon.setPosition(calendarIcon.getPosition().x+calendarIcon.getGlobalBounds().width+(SCREEN_WIDTH*0.025),0);
    standingsIcon.setSize(sf::Vector2f(SCREEN_HEIGHT*0.083,SCREEN_HEIGHT*0.083));
    standingsIcon.setTexture(&_data->assets.GetTexture("standingsIcon"),true);
    financesIcon.setPosition(standingsIcon.getPosition().x+standingsIcon.getGlobalBounds().width+(SCREEN_WIDTH*0.025),0);
    financesIcon.setSize(sf::Vector2f(SCREEN_HEIGHT*0.083,SCREEN_HEIGHT*0.083));
    financesIcon.setTexture(&_data->assets.GetTexture("financesIcon"),true);
    marketIcon.setPosition(financesIcon.getPosition().x+financesIcon.getGlobalBounds().width+(SCREEN_WIDTH*0.025),0);
    marketIcon.setSize(sf::Vector2f(SCREEN_HEIGHT*0.083,SCREEN_HEIGHT*0.083));
    marketIcon.setTexture(&_data->assets.GetTexture("marketIcon"),true);
    saveIcon.setSize(sf::Vector2f(SCREEN_HEIGHT*0.083,SCREEN_HEIGHT*0.083));
    saveIcon.setPosition(SCREEN_WIDTH-saveIcon.getGlobalBounds().width-(SCREEN_WIDTH*0.025),0);
    saveIcon.setTexture(&_data->assets.GetTexture("saveIcon"),true);
    exitIcon.setSize(sf::Vector2f(SCREEN_HEIGHT*0.083,SCREEN_HEIGHT*0.083));
    exitIcon.setPosition(saveIcon.getPosition().x-exitIcon.getGlobalBounds().width-(SCREEN_WIDTH*0.025),0);
    exitIcon.setTexture(&_data->assets.GetTexture("exitIcon"),true);
    playIcon.setSize(sf::Vector2f(SCREEN_HEIGHT*0.166,SCREEN_HEIGHT*0.083));
    playIcon.setPosition((SCREEN_WIDTH*0.025),SCREEN_HEIGHT-(playIcon.getSize().y)-(SCREEN_WIDTH*0.025));
    playIcon.setTexture(&_data->assets.GetTexture("button"),true);

    playText.setFillColor(sf::Color::Black);
    playText.setPosition(playIcon.getPosition().x-(playText.getGlobalBounds().width/2)+(playIcon.getGlobalBounds().width/2),
                         playIcon.getPosition().y-(playText.getGlobalBounds().height/2)+(playIcon.getGlobalBounds().height/2));

    playerBoxBackground.setPosition(SCREEN_WIDTH-(SCREEN_WIDTH*0.75)-10,SCREEN_HEIGHT-(SCREEN_HEIGHT*0.8)-10);
    playerBoxBackground.setSize(sf::Vector2f(SCREEN_WIDTH*0.75,SCREEN_HEIGHT*0.8));
    playerBoxBackground.setFillColor(MAIN_COLOR);
    playerBoxBackground.setOutlineColor(GREY_COLOR);
    playerBoxBackground.setOutlineThickness(2);

    float initialX = SCREEN_WIDTH*0.2375, y = SCREEN_HEIGHT*0.13;
    string tabsStrings[] = {"Active","Substitute","In Loan","Loaned","Inactive"};

    for(int i = 0; i < 5; i++){
        tabs.push_back(sf::RectangleShape());
        tabsText.push_back(sf::Text());
        tabs[i].setFillColor(GREY_COLOR);
        tabs[i].setSize(sf::Vector2f(SCREEN_WIDTH*0.125,SCREEN_HEIGHT*0.05));
        tabs[i].setOutlineColor(GREY_COLOR);
        tabs[i].setOutlineThickness(2);

        if(i == 0)
            tabs[0].setPosition(initialX,y);
        else
            tabs[i].setPosition(tabs[i-1].getPosition().x+tabs[i-1].getGlobalBounds().width,y);

        tabsText[i].setString(tabsStrings[i]);
        tabsText[i].setCharacterSize((SCREEN_WIDTH/SCREEN_HEIGHT)*15);
        tabsText[i].setFont(_data->assets.GetFont("Arial"));
        tabsText[i].setOrigin(tabsText[i].getGlobalBounds().width/2,tabsText[i].getGlobalBounds().height/2);
        tabsText[i].setPosition(tabs[i].getPosition().x+tabs[i].getGlobalBounds().width/2,
                                tabs[i].getPosition().y+tabs[i].getGlobalBounds().height/3);
    }

    tabAux.setSize(sf::Vector2f(10,10));
    tabAux.setFillColor(sf::Color::Red);
    debugObj = &tabAux;

    floatingHelpBox.setFillColor(sf::Color::White);
    floatingHelpBox.setOutlineColor(sf::Color::Black);
    floatingHelpBox.setSize(sf::Vector2f(1,2));

    floatingHelpText.setFont(_data->assets.GetFont("Arial"));
    floatingHelpText.setFillColor(sf::Color::Black);
    floatingHelpText.setCharacterSize(SCREEN_HEIGHT*0.026);
}


void TeamMenuState::HandleInput(){
    sf::Event event;

    while(_data->window.pollEvent(event)){
        if(sf::Event::Closed == event.type){
            _data->window.close();
        }

        if(_data->input.IsSpriteClicked(tabs[0].getGlobalBounds(), sf::Mouse::Button::Left, _data->window)){
            actualTab = 0;
            tabChanged = true;
        }
        else if(_data->input.IsSpriteClicked(tabs[1].getGlobalBounds(), sf::Mouse::Button::Left, _data->window)){
            actualTab = 1;
            tabChanged = true;
        }
        else if(_data->input.IsSpriteClicked(tabs[2].getGlobalBounds(), sf::Mouse::Button::Left, _data->window)){
            actualTab = 2;
            tabChanged = true;
        }
        else if(_data->input.IsSpriteClicked(tabs[3].getGlobalBounds(), sf::Mouse::Button::Left, _data->window)){
            actualTab = 3;
            tabChanged = true;
        }
        else if(_data->input.IsSpriteClicked(tabs[4].getGlobalBounds(), sf::Mouse::Button::Left, _data->window)){
            actualTab = 4;
            tabChanged = true;
        }
        else if(_data->input.IsSpriteClicked(standingsIcon.getGlobalBounds(), sf::Mouse::Button::Left, _data->window)){
            _data->machine.AddState(
                StateRef(new ClassificationState(_data,actualTeam->name,
                                                 _data->database.getActualLeague(actualTeam->name))),false);
        }
        else if(_data->input.IsSpriteClicked(saveIcon.getGlobalBounds(), sf::Mouse::Button::Left, _data->window)){
            Save();
        }
        else if(_data->input.IsSpriteClicked(exitIcon.getGlobalBounds(), sf::Mouse::Button::Left, _data->window)){
            Exit();
        }

        //Floating Help
        if(_data->input.IsOverSprite(calendarIcon.getGlobalBounds(),_data->window)){
            UpdateFloatingHelp(calendarIcon.getPosition(),calendarIcon.getGlobalBounds(),"Calendar");
        }
        else if(_data->input.IsOverSprite(standingsIcon.getGlobalBounds(),_data->window)){
            UpdateFloatingHelp(standingsIcon.getPosition(),standingsIcon.getGlobalBounds(),"Standings");
        }
        else if(_data->input.IsOverSprite(financesIcon.getGlobalBounds(),_data->window)){
            UpdateFloatingHelp(financesIcon.getPosition(),financesIcon.getGlobalBounds(),"Finances");
        }
        else if(_data->input.IsOverSprite(marketIcon.getGlobalBounds(),_data->window)){
            UpdateFloatingHelp(marketIcon.getPosition(),marketIcon.getGlobalBounds(),"Market");
        }
        else{
            showingHelp = false;
        }

        //Set Obj Pos
        if(showDebugObj){
            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Left){
                    debugObj->setPosition(debugObj->getPosition().x-1,debugObj->getPosition().y);
                }
                else if(event.key.code == sf::Keyboard::Right){
                    debugObj->setPosition(debugObj->getPosition().x+1,debugObj->getPosition().y);
                }
                else if(event.key.code == sf::Keyboard::Up){
                    debugObj->setPosition(debugObj->getPosition().x,debugObj->getPosition().y-1);
                }
                else if(event.key.code == sf::Keyboard::Down){
                    debugObj->setPosition(debugObj->getPosition().x,debugObj->getPosition().y+1);
                }
                else if(event.key.code == sf::Keyboard::Add){
                    debugObj->setSize(sf::Vector2f(debugObj->getSize().x+1,debugObj->getSize().y+1));
                }
                else if(event.key.code == sf::Keyboard::Subtract){
                    debugObj->setSize(sf::Vector2f(debugObj->getSize().x-1,debugObj->getSize().y-1));
                }
                else if(event.key.code == sf::Keyboard::Numpad6){
                    debugObj->setSize(sf::Vector2f(debugObj->getSize().x+1,debugObj->getSize().y));
                }
                else if(event.key.code == sf::Keyboard::Numpad4){
                    debugObj->setSize(sf::Vector2f(debugObj->getSize().x-1,debugObj->getSize().y));
                }
                else if(event.key.code == sf::Keyboard::Numpad8){
                    debugObj->setSize(sf::Vector2f(debugObj->getSize().x,debugObj->getSize().y+1));
                }
                else if(event.key.code == sf::Keyboard::Numpad2){
                    debugObj->setSize(sf::Vector2f(debugObj->getSize().x,debugObj->getSize().y-1));
                }
                else if(event.key.code == sf::Keyboard::A){
                    debugObj->setOutlineThickness(debugObj->getOutlineThickness()+1);
                }
                else if(event.key.code == sf::Keyboard::Z){
                    debugObj->setOutlineThickness(debugObj->getOutlineThickness()-1);
                }
                else if(event.key.code == sf::Keyboard::Space && int(stateTime.getElapsedTime().asSeconds())%1 == 0){
                    if(showDebugObj)
                        showDebugObj = false;
                    else
                        showDebugObj = true;
                }

                cout<<endl;
                cout<<"          Position: "<<debugObj->getPosition().x<<","<<debugObj->getPosition().y<<endl;
                cout<<"Position by Screen: "<<debugObj->getPosition().x/SCREEN_WIDTH<<","<<debugObj->getPosition().y/SCREEN_HEIGHT<<endl;
                cout<<"              Size: "<<debugObj->getSize().x<<","<<debugObj->getSize().y<<endl;
                cout<<"    Size by Screen: "<<debugObj->getSize().x/SCREEN_WIDTH<<","<<debugObj->getSize().y/SCREEN_HEIGHT<<endl;
                cout<<" Outline Thickness: "<<debugObj->getOutlineThickness()<<endl;
                cout<<"Thickness by Width: "<<debugObj->getOutlineThickness()/SCREEN_WIDTH<<endl;
                cout<<"Thicknes by Height: "<<debugObj->getOutlineThickness()/SCREEN_HEIGHT<<endl;
                cout<<" Thickness by Prop: "<<debugObj->getOutlineThickness()/(SCREEN_WIDTH/SCREEN_HEIGHT)<<endl;
                cout<<endl;
            }
        }
    }
}


void TeamMenuState::Update(float dt){
    if(tabChanged){
        tabChanged = false;

        if(actualTab > 4){
            actualTab = 0;
        }
        else if(actualTab < 0){
            actualTab = 0;
        }

        for(int i = 0; i < tabs.size(); i++){
            if(i == actualTab)
                tabs[actualTab].setFillColor(HALF_GREY_COLOR);
            else
                tabs[i].setFillColor(LIGHT_GREY_COLOR);
        }

        players.clear();

        if(actualTab == 0){
            for(int i = 0; i<actualTeam->playersActive.size(); i++){
                players.push_back(PlayerIcons(_data,actualTeam->playersActive[i]->name,actualTeam));
            }
            for(int i = 0; i<actualTeam->coachStaff.size(); i++){
                players.push_back(PlayerIcons(_data,actualTeam->coachStaff[i]->name,actualTeam));
            }
        }
        else if(actualTab == 1){
            for(int i = 0; i<actualTeam->playersSubstitute.size(); i++){
                players.push_back(PlayerIcons(_data,actualTeam->playersSubstitute[i]->name,actualTeam));
            }
        }
        else if(actualTab == 2){
            for(int i = 0; i<actualTeam->playersInLoan.size(); i++){
                players.push_back(PlayerIcons(_data,actualTeam->playersInLoan[i]->name,actualTeam));
            }
        }
        else if(actualTab == 3){
            string name;
            for(int i = 0; i<actualTeam->playersLoaned.size(); i++){
                name = actualTeam->playersLoaned[i]->name;
                players.push_back(PlayerIcons(_data,name,actualTeam));
            }
        }
        else if(actualTab == 4){
            for(int i = 0; i<actualTeam->playersInactive.size(); i++){
                players.push_back(PlayerIcons(_data,actualTeam->playersInactive[i]->name,actualTeam));
            }
        }

        if(actualTab == 0){
            for(int i = 0; i<players.size(); i++){
                if(players[i].player.lane == "top"){
                    players[i].pos = 0;
                }
                else if(players[i].player.lane == "jg"){
                    players[i].pos = 1;
                }
                else if(players[i].player.lane == "mid"){
                    players[i].pos = 2;
                }
                else if(players[i].player.lane == "adc"){
                    players[i].pos = 3;
                }
                else if(players[i].player.lane == "sup"){
                    players[i].pos = 4;
                }
                else{
                    players[i].pos = i+2;
                }
            }
        }
        else{
            for(int i = 0; i<players.size(); i++){
                players[i].pos = i;
            }
        }
    }

    if(!showingHelp){
        floatingHelpBox.setPosition(-1000,-1000);
        floatingHelpText.setPosition(-1000,-1000);
        floatingHelpText.setString("");
    }
}


void TeamMenuState::UpdateFloatingHelp(sf::Vector2f objPos, sf::FloatRect objRect,string text){
    showingHelp = true;
    floatingHelpText.setString(text);
    floatingHelpText.setPosition(objPos.x+objRect.width+5,objPos.y+(objRect.height/2)+5);
    floatingHelpBox.setPosition(floatingHelpText.getPosition().x-5,floatingHelpText.getPosition().y-5);
    floatingHelpBox.setScale(floatingHelpText.getGlobalBounds().width+10,floatingHelpText.getGlobalBounds().height+5);
}


void TeamMenuState::Save(){
    ofstream file;

    file.open("savegames/"+actualTeam->name+".sav",fstream::out);

    file<<actualTeam->name<<endl;
    file<<actualTeam->cash<<endl;
}


void TeamMenuState::Exit(){
    //Add Message to Save Game
    _data->machine.AddState(StateRef(new SelectTeamState(_data)),true);
}


void TeamMenuState::Draw(float dt){
    _data->window.clear(BACKGROUND_COLOR);

    _data->window.draw(teamLogo);
    _data->window.draw(playerBoxBackground);
    _data->window.draw(calendarIcon);
    _data->window.draw(standingsIcon);
    _data->window.draw(financesIcon);
    _data->window.draw(marketIcon);
    _data->window.draw(saveIcon);
    _data->window.draw(exitIcon);
    _data->window.draw(playIcon);

    _data->window.draw(playText);

    _data->window.draw(floatingHelpBox);
    _data->window.draw(floatingHelpText);

    for(int i = 0; i<players.size(); i++)
        players[i].UpdateAndDraw();
    for(int i = 0; i<tabs.size(); i++)
        _data->window.draw(tabs[i]);
    for(int i = 0; i<tabsText.size(); i++)
        _data->window.draw(tabsText[i]);

    if(showDebugObj)
        _data->window.draw(*debugObj);

    _data->window.display();
}







