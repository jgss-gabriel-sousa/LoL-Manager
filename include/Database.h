#pragma once

#include "log.h"
#include "DEFINITIONS.h"
#include <vector>
#include <algorithm>
#include <fstream>

#include "player.h"
#include "team.h"
#include "league.h"

using namespace std;

enum teamScope{
    nothing,
    commentary,
    team,
    coach,
    active,
    substitute,
    loaned,
    inLoan,
    inactive
};

class Database{
public:
    Database();
    ~Database(){}

    bool addPlayerFromFile(std::string fileLine);
    void addTeamFromFile(std::string filePath);
    void addLeagueFromFile(std::string fileLine);

    void playerTransfer(std::string player,std::string origin,std::string destiny,float value);
    void addPlayerToTeam(std::string player,std::string type,std::string team);

    void StartSeason();

    void resetDatabase();
    bool IsAvailableToLoading(){return availableToLoading;;}

    void addCountry(std::string country);
    void addCountryTag(std::string tag,std::string country);

    void setCountryOfTeams();
    void setLeagueOfTeam(std::string name,std::string league);

    std::string getLeaguesToLoading(int i);
    std::string getLeague(int i);
    League* getLeague(string league);
    std::vector<std::string> getLeagueNames();
    string getActualLeague(string team);

    std::string getCountry(int i);
    std::string getCountry(std::string code);
    std::string getCountryByTeam(std::string team);

    Team getTeam(std::string name);
    Team* getTeamPtr(std::string name);
    std::vector<std::string> getTeamsinLeague(std::string league);
    std::vector<std::string> getTeamNames();

    std::vector<std::string> getPlayerNames();
    Player getPlayer(std::string name);
    Player* getPlayerPtr(std::string name);
    Team* getPlayerTeam(string playerName);

    std::vector<std::string> _teamsStrings;
    std::vector<std::string> _playersStrings;
    std::vector<std::string> _leaguesStrings;
    std::vector<std::string> _countryStrings;

    bool availableToLoading;

    std::map<std::string,Player> _players;
    std::map<std::string,Team> _teams;
    std::map<std::string,League> _leagues;
    std::map<std::string,std::string> _countries;
};
