#include "Database.h"

Team Database::getTeam(std::string name){
    LogPush("Database::getTeam");
    return _teams[name];
}

Team* Database::getTeamPtr(string name){
    LogPush("Database::getTeamPtr");
    return &_teams[name];
}

std::string Database::getCountry(int i){
    LogPush("Database::getCountry (int)");
    return _countryStrings[i%_countryStrings.size()];
}

std::string Database::getCountry(std::string code){
    LogPush("Database::getCountry (code)");
    return _countries[code];
}

std::string Database::getCountryByTeam(std::string team){
    LogPush("Database::getCountryByTeam");
    Team t;

    t = _teams.at(team);

    return t.getCountry();
}

std::string Database::getLeague(int i){
    LogPush("Database::getLeague");
    return _leaguesStrings[i%_leaguesStrings.size()];
}

std::vector<std::string> Database::getPlayerNames(){
    LogPush("Database::getPlayerNames");
    std::vector<std::string> vectorOfNames;
    std::string name;
    Player p;

    for(std::map<std::string,Player>::iterator it=_players.begin(); it!=_players.end(); ++it){
        p = _players.at(it->first);
        name = p.getName();
        if(name.size() > 0){
            vectorOfNames.push_back(name);
        }
    }
    return vectorOfNames;
}

std::vector<std::string> Database::getTeamNames(){
    LogPush("Database::getTeamNames");
    std::vector<std::string> vectorOfNames;

    for(int i = 0; i < _teamsStrings.size(); i++){
        vectorOfNames.push_back(_teamsStrings[i]);
    }
    return vectorOfNames;
}

Team* Database::getPlayerTeam(string playerName){
    LogPush("Database::getPlayerTeam");
    Team* t;

    for(int i = 0; i<_teamsStrings.size(); i++){
        t = &_teams[_teamsStrings[i]];

        for(int j = 0; j < t->playersInLoan.size(); j++){
            if(t->playersInLoan[j]->name == playerName){
                return t;
            }
        }
    }
}

League* Database::getLeague(string name){
    LogPush("Database::getLeaguePtr");
    return &_leagues[name];
}

std::vector<std::string> Database::getLeagueNames(){
    LogPush("Database::getLeagueNames");
    std::vector<std::string> vectorOfNames;

    for(int i = 0; i < _leaguesStrings.size(); i++){
        vectorOfNames.push_back(_teamsStrings[i]);
    }
    return vectorOfNames;
}

string Database::getActualLeague(string team){
    League* l;

    for(int i = 0; i<_leaguesStrings.size(); i++){
        l = &_leagues[_leaguesStrings[i]];

        for(int j = 0; j<l->teams.size(); j++){
            if(l->teams[j] == team)
                return l->name;
        }
    }
    return "NULL";
}

std::string Database::getLeaguesToLoading(int i){
    LogPush("Database::getLeaguesToLoading");

    if(i >= _leaguesStrings.size() || i < 0){
        return "end";
    }else{
        return _leaguesStrings[i];
    }
}

std::vector<std::string> Database::getTeamsinLeague(std::string league){
    LogPush("Database::getTeamsinLeague ("+league+")");
    std::vector<std::string> vectorOfTeams;
    Team t;

    for(int i = 0; i < _teamsStrings.size(); i++){
        t = _teams[_teamsStrings[i]];
        if(t.getLeague() == league){
            vectorOfTeams.push_back(t.getName());
        }
    }

    return vectorOfTeams;
}

Player Database::getPlayer(std::string name){
    return _players[name];
}

Player* Database::getPlayerPtr(std::string name){
    return &_players[name];
}


