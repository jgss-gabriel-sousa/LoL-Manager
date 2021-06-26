#pragma once

#include <SFML/Graphics.hpp>
#include "DEFINITIONS.h"

using namespace std;

class Player{
public:
    Player();
    Player(string name,string nationality,string lane,int age,int skill,int experience,int fanBase);
    ~Player(){}

    int getSkill(){return skill;}
    std::string getName(){return name;}
    std::string getNationality(){return nationality;}
    std::string getLane(){return lane;}
    int getAge(){return age;}
    int getExperience(){return experience;}
    int getFanBase(){return fanBase;}

    void UpdateSalaryAndValue();
    void YearSkillEvolution();

    string name;
    string nationality;
    string lane;
    int skill;
    int age;
    int experience;
    int fanBase;
    float salary;
    float value;
    vector<int> notesOfGames; //All match go generate a note of each player, this vector reset each year
};
