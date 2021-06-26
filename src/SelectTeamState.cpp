#include "SelectTeamState.h"

#include "SplashState.h"
#include "MainMenuState.h"
#include "TeamMenuState.h"
#include "EditorState.h"

SelectTeamState::SelectTeamState(GameDataRef data) : _data(data){
    teamButton = 100;
    leagueButton = 98;

    for(int i = 0;; i++){
        league = this->_data->database.getLeaguesToLoading(i);
        if(league == "end"){
            break;
        }

        leaguesTeams[league] = this->_data->database.getTeamsinLeague(league);
        aux = leaguesTeams[league];
    }
    aux = leaguesTeams[league];

    LeagueButton();
    TeamButton();
}

void SelectTeamState::Init(){
    LogPush("\t Select Team State");

    this->_data->assets.LoadTexture("Right Arrow",LOADING_RIGHT_ARROW_FILEPATH);
    this->_data->assets.LoadTexture("Left Arrow",LOADING_LEFT_ARROW_FILEPATH);
    this->_data->assets.LoadTexture("Team Logo Background",LOADING_TEAM_LOGO_BACKGROUND_FILEPATH);

    //_background.setTexture(this->_data->assets.GetTexture("Background"));
    _leftArrowTeam.setTexture(this->_data->assets.GetTexture("Left Arrow"));
    _rightArrowTeam.setTexture(this->_data->assets.GetTexture("Right Arrow"));
    _leftArrowLeague.setTexture(this->_data->assets.GetTexture("Left Arrow"));
    _rightArrowLeague.setTexture(this->_data->assets.GetTexture("Right Arrow"));
    _playButton.setTexture(this->_data->assets.GetTexture("Play Button"));
    _teamLogo.setTexture(this->_data->assets.GetTexture(team));
    _teamLogoBackground.setTexture(this->_data->assets.GetTexture("Team Logo Background"));
    _leagueLogo.setTexture(this->_data->assets.GetTexture(league));

    _teamName.setFont(this->_data->assets.GetFont("Arial"));
    _leagueName.setFont(this->_data->assets.GetFont("Arial"));
    _countryName.setFont(this->_data->assets.GetFont("Arial"));
    teamCash.setFont(this->_data->assets.GetFont("Arial"));
    teamHability.setFont(this->_data->assets.GetFont("Arial"));

    _teamName.setString(team);
    _leagueName.setString(league);
    _countryName.setString(country);


    _countryFlag.setSize(sf::Vector2f(120,80));

    _teamName.setPosition((SCREEN_WIDTH/2)-(_teamName.getGlobalBounds().width/2),(SCREEN_HEIGHT/1.075)-(_teamName.getGlobalBounds().height/2));
    _leagueName.setPosition((SCREEN_WIDTH/2)-(_leagueName.getGlobalBounds().width/2),(SCREEN_HEIGHT/2.75)-(_leagueName.getGlobalBounds().height/2));
    _countryName.setPosition((SCREEN_WIDTH/2)-(_countryName.getGlobalBounds().width/2),(SCREEN_HEIGHT/1.625)-(_countryName.getGlobalBounds().height/2));
    teamHability.setPosition((SCREEN_WIDTH/1.125)-(teamHability.getGlobalBounds().width/2),(SCREEN_HEIGHT/2)-(teamHability.getGlobalBounds().height/2));
    teamCash.setPosition((SCREEN_WIDTH/6)-(teamCash.getGlobalBounds().width/2),(SCREEN_HEIGHT/2)-(teamCash.getGlobalBounds().height/2));

    _leagueLogo.setPosition((SCREEN_WIDTH/2)-(_leagueLogo.getGlobalBounds().width/2),(SCREEN_HEIGHT/4)-(_leagueLogo.getGlobalBounds().height/2));
    _countryFlag.setPosition((SCREEN_WIDTH/2)-(_countryFlag.getGlobalBounds().width/2),(SCREEN_HEIGHT/2)-(_countryFlag.getGlobalBounds().height/2));
    _teamLogo.setPosition((SCREEN_WIDTH/2)-(_teamLogo.getGlobalBounds().width/2),(SCREEN_HEIGHT/1.25)-(_teamLogo.getGlobalBounds().height/2));
    _teamLogoBackground.setPosition((SCREEN_WIDTH/2)-(_teamLogoBackground.getGlobalBounds().width/2),(SCREEN_HEIGHT/1.25)-(_teamLogoBackground.getGlobalBounds().height/2));
    _playButton.setPosition(SCREEN_WIDTH-_playButton.getGlobalBounds().width-10,SCREEN_HEIGHT-_playButton.getGlobalBounds().height-10);

    _leftArrowTeam.setPosition((SCREEN_WIDTH/3)-(this->_leftArrowTeam.getGlobalBounds().width/2),(SCREEN_HEIGHT/1.25)-(this->_leftArrowTeam.getGlobalBounds().height/2));
    _rightArrowTeam.setPosition((SCREEN_WIDTH/1.5)-(this->_rightArrowTeam.getGlobalBounds().width/2),(SCREEN_HEIGHT/1.25)-(this->_rightArrowTeam.getGlobalBounds().height/2));

    _leftArrowLeague.setPosition((SCREEN_WIDTH/3)-(this->_leftArrowLeague.getGlobalBounds().width/2),(SCREEN_HEIGHT/4)-(this->_leftArrowLeague.getGlobalBounds().height/2));
    _rightArrowLeague.setPosition((SCREEN_WIDTH/1.5)-(this->_rightArrowLeague.getGlobalBounds().width/2),(SCREEN_HEIGHT/4)-(this->_rightArrowLeague.getGlobalBounds().height/2));

}

void SelectTeamState::HandleInput(){
    sf::Event event;

    while(this->_data->window.pollEvent(event)){
        if(event.type == sf::Event::Closed){
            this->_data->window.close();
        }
        if(event.type == sf::Event::KeyPressed){
            if(event.key.code == sf::Keyboard::Left){
                teamButton--;
                isTeamButtonChanged = true;
            }
            if(event.key.code == sf::Keyboard::Right){
                teamButton++;
                isTeamButtonChanged = true;
            }
            if(event.key.code == sf::Keyboard::Up){
                leagueButton--;
                isLeagueButtonChanged = true;
            }
            if(event.key.code == sf::Keyboard::Down){
                leagueButton++;
                isLeagueButtonChanged = true;
            }
            if(event.key.code == sf::Keyboard::F10){
                this->_data->machine.AddState(StateRef(new EditorState(_data)),true);
            }
        }
        if(event.type == sf::Event::MouseButtonPressed){
            if(this->_data->input.IsSpriteClicked(_leftArrowTeam, sf::Mouse::Button::Left, this->_data->window)){
                teamButton--;
                isTeamButtonChanged = true;
            }
            if(this->_data->input.IsSpriteClicked(_rightArrowTeam, sf::Mouse::Button::Left, this->_data->window)){
                teamButton++;
                isTeamButtonChanged = true;
            }
            if(this->_data->input.IsSpriteClicked(_leftArrowLeague, sf::Mouse::Button::Left, this->_data->window)){
                leagueButton--;
                isLeagueButtonChanged = true;
            }
            if(this->_data->input.IsSpriteClicked(_rightArrowLeague, sf::Mouse::Button::Left, this->_data->window)){
                leagueButton++;
                isLeagueButtonChanged = true;
            }
            if(this->_data->input.IsSpriteClicked(_playButton, sf::Mouse::Button::Left, this->_data->window)){
                //Go to Start Settings State
                this->_data->machine.AddState(StateRef(new TeamMenuState(_data,_teamName.getString())),true);
            }
        }
        if(teamButton > 10000 || teamButton < -10000){
            teamButton = 0;
        }
        if(leagueButton > 10000 || leagueButton < -10000){
            leagueButton = 0;
        }
    }
}

void SelectTeamState::Update(float dt){
    if(isTeamButtonChanged){
        TeamButton();
    }if(isLeagueButtonChanged){
        LeagueButton();
    }
}

void SelectTeamState::Draw(float dt){
    this->_data->window.clear(BACKGROUND_COLOR);
    this->_data->window.draw(this->_leftArrowTeam);
    this->_data->window.draw(this->_rightArrowTeam);
    this->_data->window.draw(this->_leftArrowLeague);
    this->_data->window.draw(this->_rightArrowLeague);
    this->_data->window.draw(this->_teamLogoBackground);
    this->_data->window.draw(this->_leagueLogo);
    this->_data->window.draw(this->_countryFlag);
    this->_data->window.draw(this->_teamLogo);
    this->_data->window.draw(this->_playButton);
    this->_data->window.draw(this->_countryName);
    this->_data->window.draw(this->_leagueName);
    this->_data->window.draw(this->_teamName);
    this->_data->window.draw(this->teamCash);
    this->_data->window.draw(this->teamHability);
    this->_data->window.display();
}

void SelectTeamState::TeamButton(){
    Team t;

    team = aux[teamButton%aux.size()];

    _teamName.setString(team);
    _teamName.setPosition((SCREEN_WIDTH/2)-(_teamName.getGlobalBounds().width/2),(SCREEN_HEIGHT/1.075)-(_teamName.getGlobalBounds().height/2));

    country = _data->database.getCountryByTeam(team);
    _countryName.setString(country);
    _countryName.setPosition((SCREEN_WIDTH/2)-(_countryName.getGlobalBounds().width/2),(SCREEN_HEIGHT/1.625)-(_countryName.getGlobalBounds().height/2));

    _teamLogo.setTexture(_data->assets.GetTexture(team));
    _countryFlag.setTexture(&(_data->assets.GetTexture(country)),true);

    t = _data->database.getTeam(team);
    teamCash.setString("Cash: $ "+t.getCash());
    teamCash.setPosition((SCREEN_WIDTH/6)-(teamCash.getGlobalBounds().width/2),(SCREEN_HEIGHT/2)-(teamCash.getGlobalBounds().height/2));
    teamHability.setString(std::to_string(t.getTeamHability()));
    teamHability.setPosition((SCREEN_WIDTH/1.125)-(teamHability.getGlobalBounds().width/2),(SCREEN_HEIGHT/2)-(teamHability.getGlobalBounds().height/2));

    isTeamButtonChanged = false;
}

void SelectTeamState::LeagueButton(){
    league = _data->database.getLeague(leagueButton);
    aux = leaguesTeams[league];

    _leagueName.setString(league);
    _leagueName.setPosition((SCREEN_WIDTH/2)-(_leagueName.getGlobalBounds().width/2),(SCREEN_HEIGHT/2.75)-(_leagueName.getGlobalBounds().height/2));

    _leagueLogo.setTexture(this->_data->assets.GetTexture(league));

    isLeagueButtonChanged = false;
    TeamButton();
}


