#include "Team.h"

Team::Team(){
    name = "NULL TEAM";
    cash = 0;
}

Team::Team(std::string name,std::string country,float cash){
    this->cash = cash;
    this->name = name;
    this->country = country;
}

std::string Team::getCash(){
    std::string aux;
    aux = std::to_string((int)cash);

    for(int i = aux.size()-1; i > 0; i--){
        if(i%3 == 0){
            aux.insert(aux.end()-i,'.');
        }
    }
    return aux;
}

int Team::getTeamHability(){
    LogPush("Team::getTeamHability()");
    int sum = 0;
    int i = 0;

    for(; i < playersActive.size(); i++){
        sum += playersActive[i]->getSkill();
        LogPush(playersActive[i]->getName()+" = "+to_string(playersActive[i]->getSkill()));
        //cout<<playersActive[i]->getName()<<"=";
        //cout<<playersActive[i]->getSkill()<<endl;
    }

    return sum/playersActive.size();
}

string Team::getPlayerStatus(string player){
    string status = "";
    Player* p;

    for(int i = 0; i<playersActive.size(); i++){
        p = playersActive[i];
        if(p->name == player){
            status += "active;";
        }
    }
    for(int i = 0; i<playersSubstitute.size(); i++){
        p = playersSubstitute[i];
        if(p->name == player){
            status += "substitute;";
        }
    }
    for(int i = 0; i<playersInLoan.size(); i++){
        p = playersInLoan[i];
        if(p->name == player){
            status += "inLoan;";
        }
    }
    for(int i = 0; i<playersLoaned.size(); i++){
        p = playersLoaned[i];
        if(p->name == player){
            status += "loaned;";
        }
    }
    for(int i = 0; i<playersInactive.size(); i++){
        p = playersInactive[i];
        if(p->name == player){
            status += "inactive;";
        }
    }
    for(int i = 0; i<coachStaff.size(); i++){
        p = coachStaff[i];
        if(p->name == player){
            status += "coachStaff;";
        }
    }

    return status;
}

void Team::addPlayer(Player* player,std::string type){
    if(type == "active"){
        playersActive.push_back(player);
    }
    else if(type == "substitute"){
        playersSubstitute.push_back(player);
    }
    else if(type == "loaned"){
        playersLoaned.push_back(player);
    }
    else if(type == "in loan"){
        playersInLoan.push_back(player);
    }
    else if(type == "inactive"){
        playersInactive.push_back(player);
    }
    else if(type == "coach"){
        coachStaff.push_back(player);
    }
    else{
        LogPush("Team::addPlayer failure: Incorrect Type Argument");
    }
}

void Team::removePlayer(std::string name){
    Player* p;

    for(int i = 0; i<playersActive.size(); i++){
        p = playersActive[i];
        if(p->name == name){
            //playersActive[i].();
            return;
        }
    }

    for(int i = 0; i<playersSubstitute.size(); i++){
        p = playersSubstitute[i];
        if(p->name == name){
            //playersSubstitute[i].();
            return;
        }
    }

    for(int i = 0; i<playersInLoan.size(); i++){
        p = playersInLoan[i];
        if(p->name == name){
            //playersInLoan[i].();
            return;
        }
    }

    for(int i = 0; i<playersLoaned.size(); i++){
        p = playersLoaned[i];
        if(p->name == name){
            //playersLoaned[i].();
            return;
        }
    }

    for(int i = 0; i<playersInactive.size(); i++){
        p = playersInactive[i];
        if(p->name == name){
            //playersInactive[i].();
            return;
        }
    }

    for(int i = 0; i<coachStaff.size(); i++){
        p = coachStaff[i];
        if(p->name == name){
            //coachStaff[i].();
            return;
        }
    }
}

void Team::changePlayerStatus(std::string name, std::string newStatus){
    ;
}
