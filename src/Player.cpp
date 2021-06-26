#include "Player.h"

Player::Player(){
    name = "";
    nationality = "";
    age = 0;
    skill = 0;
    lane = "";
    experience = 0;
    fanBase = 0;
    salary = 0;
    value = 0;
}

Player::Player(string name,std::string nationality,std::string lane,int age,int skill,int experience,int fanBase){
    this->name = name;
    this->nationality = nationality;
    this->age = age;
    this->skill = skill;
    this->lane = lane;
    this->experience = experience;
    this->fanBase = fanBase;

    salary = (skill*skill*(skill/2)*(20/age))+(fanBase*5);
    value = (skill*skill)+(salary*6);
}

void Player::UpdateSalaryAndValue(){
    salary = (skill*skill*(skill/2)*(20/age))+(fanBase*5);
    value = (skill*skill)+(salary*6);
}

void Player::YearSkillEvolution(){
    notesOfGames.clear();
}
