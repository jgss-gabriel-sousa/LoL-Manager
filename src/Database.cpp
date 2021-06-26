#include "Database.h"

Database::Database(){
    availableToLoading = true;
}


void Database::resetDatabase(){
    LogPush("Database::resetDatabase");
    _players.clear();
    _teams.clear();
    _leagues.clear();
    _countries.clear();
    _teamsStrings.clear();
    _leaguesStrings.clear();
    _countryStrings.clear();
    availableToLoading = true;
}


void Database::playerTransfer(std::string player,std::string teamOrigin,std::string teamDestiny,float value){
    LogPush("Database::playerTransfer");
    Team* teamO = &_teams[teamOrigin];
    Team* teamD = &_teams[teamDestiny];

    teamD->addPlayer(&_players[player],"sub");
    teamD->cash -= value;
    teamO->cash += value;
    teamO->removePlayer(player);
}


void Database::addPlayerToTeam(std::string player,std::string type,std::string team){
    LogPush("Database::addPlayerToTeam");
    Team t;
    Player p;

    t = _teams.at(team);
    p = _players.at(player);

    t.addPlayer(&p,type);
}


void Database::addCountry(std::string country){
    LogPush("Database::addCountry = "+country);
    _countryStrings.push_back(country);
}


void Database::addCountryTag(std::string tag,std::string country){
    LogPush("Database::addCountryTag = "+tag+" = "+country);
    _countries[tag] = country;
}


void Database::setCountryOfTeams(){
    Team t;

    for(int i = 0; i < _teamsStrings.size(); i++){
        t = _teams[_teamsStrings[i]];
        t.setCountry(_countries[t.getCountry()]);
        _teams[_teamsStrings[i]] = t;
    }
}


void Database::setLeagueOfTeam(std::string team, std::string league){
    LogPush("Database::setLeagueOfTeam");

    Team t;

    t = _teams[team];
    t.setLeague(league);
    _teams[team] = t;
}


void Database::StartSeason(){
    League* l;

    for(int i = 0; i<_leaguesStrings.size(); i++){
        l = &_leagues.at(_leaguesStrings[i]);
        l->resetTable();
        l->sortTable();
        l->generateCalendar();
    }
}








