#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct Warrior {
    string name;
    int strength;
};

void createWarrior(string name, int strength, vector<Warrior>& warriors);
void doBattle(Warrior& warrior1, Warrior& warrior2);
Warrior& searchWarriors(string name, vector<Warrior>& warriors);
void status(vector<Warrior>& warriors);
 


int main(){
    vector<Warrior> warriors;

    ifstream file("warriors.txt");

    string current;
    string warriorName;
    int warriorStrength;
    string warriorName1, warriorName2;
    
    while(file >> current){

        if(current == "Warrior"){
            file >> warriorName >> warriorStrength;
            createWarrior(warriorName, warriorStrength, warriors);
        }
        else if(current == "Battle"){
            file >> warriorName1 >> warriorName2;
            Warrior& warrior1 = searchWarriors(warriorName1, warriors);
            Warrior& warrior2 = searchWarriors(warriorName2, warriors);
            doBattle(warrior1, warrior2);
        }
        else{
            status(warriors);
        }
    }
}

void createWarrior(string name, int strength, vector<Warrior>& warriors){
    Warrior warrior{name, strength};
    warriors.push_back(warrior);
}

void doBattle(Warrior& warrior1, Warrior& warrior2){
    
    cout << warrior1.name << " battles " << warrior2.name << endl;
    
    if(warrior1.strength == 0 && warrior2.strength == 0){
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
    }
    else if(warrior1.strength == 0){
        cout << "He's dead, " << warrior2.name << endl;
    }
    else if(warrior2.strength == 0){
        cout << "He's dead, " << warrior1.name << endl;
    }
    else if(warrior1.strength == warrior2.strength){
            cout << "Mutual Annihilation: " << warrior1.name << " and " << warrior2.name << " die at each other's hands" << endl;
            warrior1.strength = 0;
            warrior2.strength = 0;
    }
    else if(warrior1.strength > warrior2.strength){
            cout << warrior1.name << " defeats " << warrior2.name << endl;
            warrior1.strength -= warrior2.strength;
            warrior2.strength = 0;
    }
    else if(warrior2.strength > warrior1.strength){
            cout << warrior2.name << " defeats " << warrior1.name << endl;
            warrior2.strength -= warrior1.strength;
            warrior1.strength = 0;
    }
}

Warrior& searchWarriors(string name, vector<Warrior>& warriors){
    //This is my great shame
    //I have to return a reference to a Warrior struct, but I've no clue how to do that if no match is found
    //I look fotward to learning why this is dumb and how to do it better
    Warrior nobody{"", 0};
    for(Warrior& i : warriors){
        if(i.name == name){
            return(i);
        }
    }

    Warrior& nobodyRef = nobody;
    return(nobodyRef);
}

void status(vector<Warrior>& warriors){
    cout << "There are: " << warriors.size() << " warriors" << endl;
    for(size_t i = 0; i < warriors.size(); i++){
        cout << warriors[i].name << ", strength: " << warriors[i].strength << endl;
    }
}
