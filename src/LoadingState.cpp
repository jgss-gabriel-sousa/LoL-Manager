#include "LoadingState.h"

#include "SelectTeamState.h"

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

LoadingState::LoadingState(GameDataRef data) : _data(data){
    _loadingStage = 0;
}

void LoadingState::Init(){
    LogPush("\t Loading State");

    this->_data->assets.LoadTexture("Loading Bar",LOADING_LOADING_BAR_FILEPATH);
    this->_data->assets.LoadTexture("Detail Rect",LOADING_DETAIL_RECT_FILEPATH);
    this->_data->assets.LoadFont("Arial",FONT_ARIAL_FILEPATH);

    this->_loadingBar.setTexture(this->_data->assets.GetTexture("Loading Bar"));
    this->_detailRect.setTexture(this->_data->assets.GetTexture("Detail Rect"));
    this->_loadingText.setFont(this->_data->assets.GetFont("Arial"));

    this->_loadingBar.setPosition((SCREEN_WIDTH/4)-(this->_loadingBar.getGlobalBounds().width/2),(SCREEN_HEIGHT/1.25)-(this->_loadingBar.getGlobalBounds().height/2));
    this->_detailRect.setPosition((SCREEN_WIDTH/2)-(this->_detailRect.getGlobalBounds().width/2),(SCREEN_HEIGHT/2)-(this->_detailRect.getGlobalBounds().height/2));

    _loadingText.setPosition((SCREEN_WIDTH/2),(SCREEN_HEIGHT/2));
    _loadingText.setString("Loading Players Database");
}

void LoadingState::HandleInput(){
    sf::Event event;

    while(this->_data->window.pollEvent(event)){
        if(sf::Event::Closed == event.type){
            this->_data->window.close();
        }
    }
}

void LoadingState::Update(float dt){

    //Loading Bar Animation
    if(this->_clock.getElapsedTime().asSeconds() > 0.25){
        if(_loadingStage == LoadingPlayers){
            if(!this->_data->database.IsAvailableToLoading()){
                this->_data->database.resetDatabase();
            }
            _loadingText.setString("Loading Players Database");
            _loadingBar.setScale(1.5,1);
            LoadPlayers();
        }else if(_loadingStage == LoadingTeams){
            _loadingText.setString("Loading Team Database");
            _loadingBar.setScale(0.75,1);
            LoadTeams();
        }else if(_loadingStage == LoadingLeagues){
            _loadingText.setString("Loading Leagues Database");
            _loadingBar.setScale(2.25,1);
            LoadLeagues();
        }else if(_loadingStage == LoadingTextures){
            _loadingText.setString("Loading Textures");
            _loadingBar.setScale(3,1);
            LoadTextures();
        }else{
            //Switch to Select Team
            this->_data->machine.AddState(StateRef(new SelectTeamState(_data)),true);
        }
    }

    //Align Loading Text to center
    _loadingText.setPosition((SCREEN_WIDTH/2)-(_loadingText.getGlobalBounds().width/2),(SCREEN_HEIGHT/2)-(_loadingText.getGlobalBounds().height/2));
}

void LoadingState::Draw(float dt){
    this->_data->window.clear(BACKGROUND_COLOR);

    this->_data->window.draw(this->_detailRect);
    this->_data->window.draw(this->_loadingText);
    this->_data->window.draw(this->_loadingBar);

    this->_data->window.display();
}

void LoadingState::LoadPlayers(){
    std::ifstream file;
    std::string read;
    int nPlayers = 0;
    bool commentary;

    file.open(PLAYERS_DATABASE_FILEPATH,std::ios::in);

    if(file.is_open()){
        _loadingText.setString("Loading Team Database"); // Print the next Stage

        while(!file.eof() && !file.bad()){
            getline(file,read);

            if(read.find("<<") != std::string::npos){
                commentary = true;
            }
            if(read.find(">>") != std::string::npos){
                commentary = false;
                continue;
            }
            if(read.size() == 0){
                continue;
            }
            if(commentary == true){
                continue;
            }

            if(this->_data->database.addPlayerFromFile(read) == true){
                nPlayers++;
            }
        }
    }else{
        LogPush("\"data/players.txt\" not found");
    }

    LogPush(std::to_string(nPlayers)+" Players loaded");
    _loadingStage++;
}

void LoadingState::LoadTeams(){
    LogPush("LoadingState::LoadTeams");
    _loadingText.setString("Loading League Database"); // Print the next Stage
    this->_data->database.addTeamFromFile(TEAMS_DATABASE_FILEPATH);

    _loadingStage++;
}

void LoadingState::LoadLeagues(){
    LogPush("LoadingState::LoadLeagues");
    _loadingText.setString("Loading Textures"); // Print the next Stage
    this->_data->database.addLeagueFromFile(LEAGUES_DATABASE_FILEPATH);
    _loadingStage++;
}

void LoadingState::LoadTextures(){
    //Load Country Flags Textures
    std::ifstream file1, file2;
    std::string read, tag, countryName, address;
    int pos;

    file1.open(COUNTRY_TAGS_FILEPATH,std::ios::in);

    if(file1.is_open()){
        while(!file1.eof() && !file1.bad()){
            getline(file1,read);

            if(read.size() == 0)
                continue;

            pos = read.find("=");
            tag = read.substr(0,pos);
            countryName = read.substr(pos+1);

            this->_data->database.addCountry(countryName);
            this->_data->database.addCountryTag(tag,countryName);

            address = COUNTRY_ICON_FILEPATH+countryName+".png";
            this->_data->assets.LoadTexture(countryName,address);

            LogPush("Country added: ("+tag+") "+countryName);
        }
    }else{
        LogPush("\"data/country tags.txt\" not found");
    }
    //Overwriting Country Tag with correct Strings

    this->_data->database.setCountryOfTeams();

    //-------------------------------------------
    //Load League Logos
    std::string name;
    int i = 0;

    while(this->_data->database.getLeaguesToLoading(i) != "end"){
        name = this->_data->database.getLeaguesToLoading(i);

        address = LEAGUE_LOGO_ICON_FILEPATH+name+".png";
        this->_data->assets.LoadTexture(name,address);

        i++;
    }
    //-------------------------------------------
    //Load Teams Logo
    file2.open("data/teamsTemp.txt",std::ios::in);

    if(file2.is_open()){
        while(!file2.eof() && !file2.bad()){
            getline(file2,read);

            if(read.size() == 0)
                continue;

            address = TEAM_LOGO_ICON_FILEPATH+read+".png";
            this->_data->assets.LoadTexture(read,address);
        }
        remove("data/teamsTemp.txt");
    }else{
        LogPush("\"data/teamsTemp.txt\" not found");
    }
    //-------------------------------------------
    //Load Player Faces

    std::string auxx;
    for(int i = 0; i<_data->database._playersStrings.size(); i++){
        auxx = _data->database._playersStrings[i];
        _data->assets.LoadTexture(auxx+"Face","resources/icons/faces/"+auxx+".png");
    }

    //-------------------------------------------
    //Other Textures

    _data->assets.LoadTexture("Close Button");
    _data->assets.LoadTexture("Play Button");
    _data->assets.LoadTexture("coach","resources/icons/coach.png");
    _data->assets.LoadTexture("top","resources/icons/top.png");
    _data->assets.LoadTexture("jg","resources/icons/jg.png");
    _data->assets.LoadTexture("mid","resources/icons/mid.png");
    _data->assets.LoadTexture("adc","resources/icons/adc.png");
    _data->assets.LoadTexture("sup","resources/icons/sup.png");
    _data->assets.LoadTexture("calendarIcon","resources/icons/calendarIcon.png");
    _data->assets.LoadTexture("standingsIcon","resources/icons/standingsIcon.png");
    _data->assets.LoadTexture("financesIcon","resources/icons/financesIcon.png");
    _data->assets.LoadTexture("marketIcon","resources/icons/marketIcon.png");
    _data->assets.LoadTexture("saveIcon","resources/icons/saveIcon.png");
    _data->assets.LoadTexture("exitIcon","resources/icons/exitIcon.png");

    //-------------------------------------------
    _loadingStage++;
}





