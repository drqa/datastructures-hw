#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

//Warrior struct with a name and strength
struct Warrior {
    string name;
    int strength;
};

//function prototypes
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

        //if the Warrior command is found, create a new Warrior and add him to the vector
        if(current == "Warrior"){
            file >> warriorName >> warriorStrength;
            createWarrior(warriorName, warriorStrength, warriors);
        }
        //if the Battle command is found, first search the vector for the given Warriors
        //If found, have those Warriors engage in glorious battle
        else if(current == "Battle"){
            file >> warriorName1 >> warriorName2;
            Warrior& warrior1 = searchWarriors(warriorName1, warriors);
            Warrior& warrior2 = searchWarriors(warriorName2, warriors);
            doBattle(warrior1, warrior2);
        }
        //Status is our last and only remaining command, thus if we reach this far we know the command is Status
        //display each Warriors current status
        else{
            status(warriors);
        }
    }
}

//Create an new Warrior and push it to the vector
void createWarrior(string name, int strength, vector<Warrior>& warriors){
    Warrior warrior{name, strength};
    warriors.push_back(warrior);
}

void doBattle(Warrior& warrior1, Warrior& warrior2){
    
    cout << warrior1.name << " battles " << warrior2.name << endl;
    
    //Check if either one or both warriors are already dead
    if(warrior1.strength == 0 && warrior2.strength == 0){
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
    }
    else if(warrior1.strength == 0){
        cout << "He's dead, " << warrior2.name << endl;
    }
    else if(warrior2.strength == 0){
        cout << "He's dead, " << warrior1.name << endl;
    }
    //Compare strengths and calculate results of battle
    //Set losing warriors strength to 0 to avoid negative ints
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
    //I look forward to learning why this is dumb and how to do it better
    Warrior nobody{"", 0};

    //search the vector of Warriors for a Warrior with a given name
    //once found return a reference to that Warrior
    for(Warrior& i : warriors){
        if(i.name == name){
            return(i);
        }
    }

    //im a dumb guy
    Warrior& nobodyRef = nobody;
    return(nobodyRef);
}

//Iterate through the vector and display the names and strengths of each warrior within it
void status(vector<Warrior>& warriors){
    cout << "There are: " << warriors.size() << " warriors" << endl;
    for(size_t i = 0; i < warriors.size(); i++){
        cout << warriors[i].name << ", strength: " << warriors[i].strength << endl;
    }
}
