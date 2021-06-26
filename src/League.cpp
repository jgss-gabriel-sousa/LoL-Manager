#include "League.h"

League::League(std::string name,std::string region,bool franchise,bool twoSplits,std::string tier,std::string format){
    this->name = name;
    this->region = region;
    isFranchise = franchise;
    haveTwoSplits = twoSplits;
    this->tier = tier;

    if(format.find("RR") != string::npos){
        hasRoundRobin = true;
    }
    if(format.find("D") != string::npos){
        haveTwoSplits = true;
    }
    if(format.find("P") != string::npos){
        hasPlayoff = true;
    }
    if(format.find("-") != string::npos){
        teamsInPlayoff = stoi(format.substr(format.find("-")+1));
    }
}

void League::addTeam(std::string name, Team* team){
    teams.push_back(name);
    teamsPtr[name] = team;
    table.push_back(make_pair(0,team));
}

void League::sortTable(){
    sort(table.begin(), table.end(), greater<pair<int,Team*>>());
}

void League::resetTable(){
    for(int i = 0; i<table.size(); i++)
        table[i].first = 0;
}

void League::generateCalendar(){
    //Provisory Algorithm
    string line[2][table.size()/2];
    vector<string> round;

    for(int i = 0; i<table.size(); i++){
        if(i>=table.size()/2)
            line[0][i] = table[i].second->name;
        else
            line[1][i-table.size()/2] = table[i].second->name;
    }

    if(hasRoundRobin){
        for(int i = 0; i<table.size()/2; i++){
            round.push_back(line[0][i]+"x"+line[1][i]);
        }
    }

    calendar.push_back(round);

    /*
    vector<string> round;
    string original,line[2][table.size()/2],aux,prev;
    int turns = 0, nextPos = -1;


    for(int i = 0; i<table.size(); i++){
        if(i>=table.size()/2)
            line[0][i] = table[i].second->name;
        else
            line[1][i-table.size()/2] = table[i].second->name;
    }

    original = line[0][0];

    aux = line[1][0];

    while(turns<2){
        if(line[1][0] == original)
            turns++;


        for(int i = 0; i<2; i++){
            for(int j = 0; j<table.size()/2; j++){
                if(i == 0 && j == 0){
                    //Save Rounds
                    continue;
                }

                if(j < ((table.size()/2)-2))
                    nextPos = j;
                else if(j == (table.size()/2)-1)
                    nextPos = ;


                prev = line[i][j];
                line[i][j] = aux;
                line[i][nextPos] = prev;
                aux = line[i][nextPos];
            }
        }
    }
    */
}


void League::generatePlayoff(int numberOfTeams){
    string teams[numberOfTeams];
    int generatedNumbers[numberOfTeams] = {};
    vector<string> round;

    for(int i = 0; i<numberOfTeams; i++){
        teams[i] = table[i].second->name;
    }

    bool aux = false;
    int generated;

    for(int i = 0; i<numberOfTeams; i++){
        for(int j = 0; j<numberOfTeams; j++){
            generated = rand()%numberOfTeams;
            if(generated == generatedNumbers[j]);
        }
        generatedNumbers[i] = generated;
        cout<<generatedNumbers[i]<<"-";
    }
    cout<<endl;

    calendar.push_back(round);
}



int League::playMatch(string match, int bestOf){
    string team[2];
    int teamHability[2];
    int chance[2];
    int team1Wins = 0;
    int team2Wins = 0;
    int matches = bestOf;

    team[0] = match.substr(0,match.find("x"));
    team[1] = match.substr(match.find("x")+1);
    teamHability[0] = teamsPtr.at(team[0])->getTeamHability();
    teamHability[1] = teamsPtr.at(team[1])->getTeamHability();

    while(matches--){
        chance[0] = (1/(teamHability[0]/(teamHability[0]+teamHability[1])));
        chance[1] = (1/(teamHability[1]/(teamHability[0]+teamHability[1])));

        chance[0] = 100-((chance[0]/(chance[0]+chance[1]))*100);
        chance[1] = 100-((chance[1]/(chance[0]+chance[1]))*100);


        if(rand()%100 < (100-chance[0])){
            team2Wins++;
        }else{
            team1Wins++;
        }

        if(team1Wins == bestOf/2 || team2Wins == bestOf/2){
            break;
        }
    }

    if(team1Wins > team2Wins){
        return 1;
    }
    else if(team2Wins > team1Wins){
        return 2;
    }
    else{
        return 3;
    }
}


void League::playRound(){
    string team[2];
    string aux;
    int winner;

    if(calendar.size() > 0){ //Round Robin Games
        for(int j = 0; j<calendar[0].size(); j++){
            team[0] = calendar[0][j].substr(0,calendar[0][j].find("x"));
            team[1] = calendar[0][j].substr(calendar[0][j].find("x")+1);

            winner = playMatch(calendar[0][j],3);

            for(int k = 0; k<table.size(); k++){
                if(table[k].second->name == team[winner])
                    table[k].first += 3;
            }
        }
        sortTable();

        if(calendar.size() > 0){
            reverse(calendar.begin(),calendar.end());
            calendar.pop_back();
            reverse(calendar.begin(),calendar.end());
        }

        if(calendar.size() == 0){
            if(hasPlayoff){
                generatePlayoff(teamsInPlayoff);
            }
            else{
                running = false;
            }

            if(!isFranchise){
                Relegation();
            }
        }
    }
    else if(0){ //Playoff Games
        ;
    }
}


void League::Relegation(){
    ;
}
