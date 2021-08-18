#pragma once

#include <iostream>
#include <algorithm>

#include "team.h"
#include "Log.h"

using namespace std;


class League{
    struct tableElement{
        int points;
        Team* team;
    };

public:
    League(){};
    League(std::string name,std::string region,bool franchise,bool twoSplits,std::string tier,std::string format);
    ~League(){};

    void addTeam(std::string name, Team* team);
    void sortTable();
    void resetTable();
    void generateCalendar();
    void generatePlayoff(int numberOfTeams);
    void playRound();
    int playMatch(string match, int bestOf);
    void Relegation();


    std::string name;
    std::string region;
    vector<std::string> teams;
    map<string,Team*> teamsPtr;
    std::vector<std::string> champions;
    std::string tier;

    vector<pair<int,Team*>> table;
    vector<vector<string>> calendar;

    vector<pair<Team*,Team*>> playoff;


    bool hasPlayoff = false;
    bool hasRoundRobin = false;
    bool haveTwoSplits = false;
    bool isFranchise = false;
    bool running = false;

    int teamsInPlayoff = 0;
};
