#include "EditorState.h"
#include "MainMenuState.h"

EditorState::EditorState(GameDataRef data) : _data(data){
    stateButton = EditingPlayers;
    objectButton = 0;
    objectChanged = true;
    stateChanged = true;
}


void EditorState::Init(){
    LogPush("#########################");
    LogPush("\t EditorState");

    title.setFont(_data->assets.GetFont("Arial"));
    title.setFillColor(MAIN_COLOR);
    title.setOutlineColor(sf::Color::Black);
    title.setOutlineThickness(1);

    textName.setFont(_data->assets.GetFont("Arial"));

    textNationality.setFont(_data->assets.GetFont("Arial"));

    textLane.setFont(_data->assets.GetFont("Arial"));

    textAge.setFont(_data->assets.GetFont("Arial"));

    textSkill.setFont(_data->assets.GetFont("Arial"));

    textExperience.setFont(_data->assets.GetFont("Arial"));

    textFanBase.setFont(_data->assets.GetFont("Arial"));

    textCash.setFont(_data->assets.GetFont("Arial"));

    closeButton.setTexture(_data->assets.GetTexture("Close Button"));
    closeButton.setScale(sf::Vector2f(0.5,0.5));
    closeButton.setPosition(SCREEN_WIDTH-closeButton.getGlobalBounds().width-10,SCREEN_HEIGHT-closeButton.getGlobalBounds().height-10);

    faceIcon.setSize(sf::Vector2f(SCREEN_WIDTH*0.125,SCREEN_WIDTH*0.125));
    faceIcon.setOutlineColor(sf::Color::White);
    faceIcon.setOutlineThickness(1);
    faceIcon.setPosition(10,10);

    floatingHelpBox.setFillColor(sf::Color::White);
    floatingHelpBox.setOutlineColor(sf::Color::Black);
    floatingHelpBox.setSize(sf::Vector2f(1,2));

    floatingHelpText.setFont(_data->assets.GetFont("Arial"));
    floatingHelpText.setFillColor(sf::Color::Black);
    floatingHelpText.setCharacterSize(SCREEN_HEIGHT*0.026);

    sf::Text aux;
    aux.setFont(_data->assets.GetFont("Arial"));
    for(int i = 0; i < _data->database._countryStrings.size(); i++){
        aux.setString(_data->database._countryStrings[i]);
        countriesList.push_back(aux);
    }

    blackBox.setSize(sf::Vector2f(1,1));
    blackBox.setFillColor(sf::Color(64,64,64,255));
}


void EditorState::HandleInput(){
    sf::Event event;

    while(_data->window.pollEvent(event)){
        if(sf::Event::Closed == event.type){
            _data->window.close();
        }
        if(event.type == sf::Event::MouseButtonPressed){
            if(_data->input.IsSpriteClicked(closeButton, sf::Mouse::Button::Left, _data->window)){
                _data->machine.AddState(StateRef(new MainMenuState(_data)),true);
            }
        }
        if(event.type == sf::Event::KeyPressed){
            if(event.key.code == sf::Keyboard::Left){
                objectButton--;
                objectChanged = true;
            }
            if(event.key.code == sf::Keyboard::Right){
                objectButton++;
                objectChanged = true;
            }
            if(event.key.code == sf::Keyboard::Up){
                stateButton++;
                stateChanged = true;
            }
            if(event.key.code == sf::Keyboard::Down){
                stateButton--;
                stateChanged = true;
            }
        }

        if(event.type == sf::Event::MouseWheelScrolled){
            if(event.mouseWheelScroll.delta > 0){
                mouseScroll++;
            }
            if(event.mouseWheelScroll.delta < 0){
                mouseScroll--;
            }
        }


        if(_data->input.IsSpriteClicked(faceIcon.getGlobalBounds(),sf::Mouse::Left,_data->window)){
            _data->assets.LoadTexture(name+"Face","resources/icons/faces/"+name+".png");
            faceIcon.setTexture(&_data->assets.GetTexture(name+"Face"),true);
        }
        if(_data->input.IsSpriteClicked(textNationality.getGlobalBounds(),sf::Mouse::Left,_data->window)){
            mouseScroll = 0;
            showCountries = true;
        }

        if(_data->input.IsOverSprite(faceIcon.getGlobalBounds(),_data->window)){
            UpdateFloatingHelp(faceIcon.getPosition(),faceIcon.getGlobalBounds(),"Click to reload face texture");
        }
        else{
            showingHelp = false;
        }
    }
}


void EditorState::Update(float dt){
    if(objectChanged){
        UpdateObject();
    }
    if(stateChanged){
        UpdateState();
    }

    if(!showingHelp){
        floatingHelpBox.setPosition(-1000,-1000);
        floatingHelpText.setPosition(-1000,-1000);
        floatingHelpText.setString("");
    }

    if(showCountries){
        blackBox.setPosition(0,0);
        int aux = 10;
        for(int i = mouseScroll; i<countriesList.size(); i++){
            countriesList[i].setPosition(SCREEN_WIDTH/2 - countriesList[i].getGlobalBounds().width/2,
                                         aux);
            aux += 40;
        }
        blackBox.setScale(SCREEN_WIDTH,SCREEN_HEIGHT);
    }
    else{
        for(int i = 0; i<countriesList.size(); i++){
            countriesList[i].setPosition(-1000,-1000);
        }
    }
}


void EditorState::UpdateInfos(){
    if(stateButton == EditingPlayers){
        textName.setString(name);
        textNationality.setString(nationality);
        textLane.setString(playerLane);
        textAge.setString("Age: " + std::to_string(playerAge));
        textSkill.setString("Skill: " + std::to_string(playerSkill));
        textExperience.setString("Exp: " + std::to_string(playerExperience));
        textFanBase.setString("Fan Base: " + std::to_string(playerFanBase));

        textName.setCharacterSize(16);
        textNationality.setCharacterSize(16);
        textLane.setCharacterSize(16);
        textAge.setCharacterSize(16);
        textSkill.setCharacterSize(16);
        textExperience.setCharacterSize(16);
        textFanBase.setCharacterSize(16);

        textName.setPosition((SCREEN_WIDTH/2)-(textName.getGlobalBounds().width/2),(SCREEN_HEIGHT/10)-(textName.getGlobalBounds().height/2));
        textNationality.setPosition((SCREEN_WIDTH/2)-(textNationality.getGlobalBounds().width/2),(SCREEN_HEIGHT/6)-(textNationality.getGlobalBounds().height/2));
        textLane.setPosition((SCREEN_WIDTH/2)-(textLane.getGlobalBounds().width/2),(SCREEN_HEIGHT/4)-(textLane.getGlobalBounds().height/2));
        textAge.setPosition((SCREEN_WIDTH/2)-(textAge.getGlobalBounds().width/2),(SCREEN_HEIGHT/2)-(textAge.getGlobalBounds().height/2));
        textSkill.setPosition((SCREEN_WIDTH/2)-(textSkill.getGlobalBounds().width/2),(SCREEN_HEIGHT/1.75)-(textSkill.getGlobalBounds().height/2));
        textExperience.setPosition((SCREEN_WIDTH/2)-(textExperience.getGlobalBounds().width/2),(SCREEN_HEIGHT/1.5)-(textExperience.getGlobalBounds().height/2));
        textFanBase.setPosition((SCREEN_WIDTH/2)-(textFanBase.getGlobalBounds().width/2),(SCREEN_HEIGHT/1.3)-(textFanBase.getGlobalBounds().height/2));
    }
    if(stateButton == EditingTeams){
        textName.setString(name);
        textNationality.setString(nationality);
        textLane.setString(playerLane);

        textName.setPosition((SCREEN_WIDTH/2)-(textName.getGlobalBounds().width/2),(SCREEN_HEIGHT/10)-(textName.getGlobalBounds().height/2));
        textNationality.setPosition((SCREEN_WIDTH/2)-(textNationality.getGlobalBounds().width/2),(SCREEN_HEIGHT/6)-(textNationality.getGlobalBounds().height/2));
        textSkill.setPosition((SCREEN_WIDTH/2)-(textSkill.getGlobalBounds().width/2),(SCREEN_HEIGHT/1.75)-(textSkill.getGlobalBounds().height/2));
    }
}


void EditorState::UpdateObject(){
    string objectName;

    if(stateButton == EditingPlayers){
        objectName = _data->database._playersStrings[objectButton%_data->database._playersStrings.size()];
        Player p = _data->database.getPlayer(objectName);

        name = p.getName();
        nationality = p.getNationality();
        nationality = _data->database.getCountry(nationality);
        playerLane = p.getLane();
        playerAge = p.getAge();
        playerSkill = p.skill;
        playerExperience = p.getExperience();
        playerFanBase = p.getFanBase();

        faceIcon.setTexture(&_data->assets.GetTexture(name+"Face"),true);
    }else{
        textLane.setPosition(-1000,-1000);
        textAge.setPosition(-1000,-1000);
        textExperience.setPosition(-1000,-1000);
        textFanBase.setPosition(-1000,-1000);
    }
    if(stateButton == EditingTeams){
        objectName = _data->database._teamsStrings[objectButton%_data->database._teamsStrings.size()];
        Team t = _data->database.getTeam(objectName);

        name = t.getName();
        nationality = t.getCountry();
        faceIcon.setTexture(&_data->assets.GetTexture(name),true);
    }

    UpdateInfos();
    objectChanged = false;
}


void EditorState::UpdateState(){
    switch(stateButton){
        case EditingPlayers:
            title.setString("Editing Players");
            break;
        case CreatingPlayer:
            title.setString("Creating Player");
            break;
        case EditingTeams:
            title.setString("Editing Teams");
            break;
        case CreatingTeam:
            title.setString("Creating Team");
            break;
        case EditingLeagues:
            title.setString("Editing Leagues");
            break;
        case CreatingLeague:
            title.setString("Creating League");
            break;
        default:
            if(stateButton < EditingPlayers){
                stateButton = CreatingLeague;
                title.setString("Creating League");
            }
            else if(stateButton > CreatingLeague){
                stateButton = EditingPlayers;
                title.setString("Editing Players");
            }
            break;
    }
    title.setPosition((SCREEN_WIDTH/2)-(title.getGlobalBounds().width/2),(SCREEN_HEIGHT/40)-(title.getGlobalBounds().height/2));
    UpdateObject();
    stateChanged = false;
}


void EditorState::Save(){
    LogPush("EditorState::Save");

    if(stateButton == EditingPlayers){
        std::ifstream file;
        std::string read, aux;
        std::vector<std::string> originalFile;
        int pos;

        file.open(PLAYERS_DATABASE_FILEPATH,std::ios::in);

        if(file.is_open()){
            while(!file.eof() && !file.bad()){
                getline(file,read);
                pos = read.find(";");
                aux = read.substr(0,pos);
                if(aux == name){
                    continue;
                }
                originalFile.push_back(read);
            }
        }
        //Merging Old File with new player line

        std::ofstream file2;
        std::string line;

        file2.open(PLAYERS_DATABASE_FILEPATH);

        for(int i = 0; i < originalFile.size(); i++){
            if(originalFile[i].substr(0,originalFile[i].find(";")) == name)
                continue;
            file2<<originalFile[i];
        }

        line = name+";";
        line += std::to_string(playerAge)+";";
        line += nationality+";";
        line += playerLane+";";
        line += std::to_string(playerSkill)+";";
        line += std::to_string(playerExperience)+";";
        line += std::to_string(playerFanBase)+";";

        file2<<line;

        file2.close();

    }else if(stateButton == CreatingPlayer){
        ofstream file;
        string line;

        file.open(PLAYERS_DATABASE_FILEPATH, std::ios_base::app);

        line = name+";";
        line += to_string(playerAge)+";";
        line += nationality+";";
        line += playerLane+";";
        line += to_string(playerSkill)+";";
        line += to_string(playerExperience)+";";
        line += to_string(playerFanBase)+";";

        file<<line;
        file.close();
    }
}


void EditorState::UpdateFloatingHelp(sf::Vector2f objPos, sf::FloatRect objRect,string text){
    showingHelp = true;
    floatingHelpText.setString(text);
    floatingHelpText.setPosition(objPos.x+objRect.width+5,objPos.y+(objRect.height/2)+5);
    floatingHelpBox.setPosition(floatingHelpText.getPosition().x-5,floatingHelpText.getPosition().y-5);
    floatingHelpBox.setScale(floatingHelpText.getGlobalBounds().width+10,floatingHelpText.getGlobalBounds().height+5);
}


void EditorState::Draw(float dt){
    _data->window.clear(BACKGROUND_COLOR);
    _data->window.draw(title);
    _data->window.draw(closeButton);

    _data->window.draw(textName);
    _data->window.draw(textNationality);
    _data->window.draw(textSkill);
    _data->window.draw(faceIcon);

    _data->window.draw(textLane);
    _data->window.draw(textAge);
    _data->window.draw(textExperience);
    _data->window.draw(textFanBase);

    _data->window.draw(textCash);

    _data->window.draw(blackBox);
    for(int i = 0; i<countriesList.size(); i++){
        _data->window.draw(countriesList[i]);
    }

    //if(stateButton == EditingPlayers || stateButton == CreatingPlayer)
    //if(stateButton == EditingTeams || stateButton == CreatingTeam)

    _data->window.draw(floatingHelpBox);
    _data->window.draw(floatingHelpText);

    _data->window.display();
}







