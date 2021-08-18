#pragma once

#include "player.h"
#include "Log.h"

using namespace std;

class Team{
public:
    Team();
    Team(std::string name,std::string country,float cash);
    ~Team(){}

    std::string getName(){return name;}
    std::string getLeague(){return league;}
    std::string getCountry(){return country;}
    std::string getCash();
    string getPlayerStatus(string player);
    int getTeamHability();
    void setCountry(std::string name){country = name;}
    void setLeague(std::string name){league = name;}

    void addPlayer(Player* player,std::string type);
    void removePlayer(std::string name);
    void changePlayerStatus(std::string name,std::string newStatus);

    std::string name;
    std::string country;
    std::string league;
    float cash;
    std::vector<Player*> coachStaff;
    std::vector<Player*> playersActive;
    std::vector<Player*> playersSubstitute;
    std::vector<Player*> playersInLoan;
    std::vector<Player*> playersLoaned;
    std::vector<Player*> playersInactive;
};
