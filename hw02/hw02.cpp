#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// G: Document wide nitpicks: always include a space after the comment symbol // and before an opening brace { e.g.
// This is a good comment
// thisIsAGood(function prototype) {};

// G: This comment is useless
//Warrior struct with a name and strength
struct Warrior {
    string name;
    int strength;
};

// G: This comment is useless
//function prototypes
void createWarrior(string name, int strength, vector<Warrior>& warriors);
void doBattle(Warrior& warrior1, Warrior& warrior2);
Warrior& searchWarriors(string name, vector<Warrior>& warriors);
void status(vector<Warrior>& warriors);
// G: Three newlines between your prototypes and main is excessive


int main(){
    vector<Warrior> warriors;

    ifstream file("warriors.txt");

    string current;
    // G: You could substitute "name" and "strength" as the l-values due to the context being understood as warrior
    string warriorName;
    int warriorStrength;
    // G: I never want you to number things like this if you can help it - I would much prefer attacker/defender, challenger/target, or, at least, lhs/rhs
    //    Try to consider the roles these warriors are playing in the battle when naming them
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
        // G: It wasn't specified in the HW so this is perfect, but brownie points if this else had handled the case when the file command is unrecognized
        //Status is our last and only remaining command, thus if we reach this far we know the command is Status
        //display each Warriors current status
        else{
            status(warriors);
        }
    }
}

//Create an new Warrior and push it to the vector
void createWarrior(string name, int strength, vector<Warrior>& warriors){
    // G: You can combine these lines into: warriors.push_back(Warrior{name, strength});
    Warrior warrior{name, strength};
    warriors.push_back(warrior);
}

// G: I stated this above but I would like to reiterate - warrior1/warrior2 are awful names and if you pick names like this in the future, be prepared
//    to explain why it was absolutely necessary

// G: Nitpick: Don't include a newline between your function signature and the first line of the body
void doBattle(Warrior& warrior1, Warrior& warrior2){
    
    cout << warrior1.name << " battles " << warrior2.name << endl;
    
    //Check if either one or both warriors are already dead
    if(warrior1.strength == 0 && warrior2.strength == 0){
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
    }
    // G: This line is not stated behavior within the HW. It is vague so I can understand why you made this assumption but given the wording of the 
    //    assignment, the special "He's dead, ..." message should only be sent when the defender of the battle is dead, not the attacker.
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

// G: name here should be passed by const reference
Warrior& searchWarriors(string name, vector<Warrior>& warriors){
    // G: We'll talk about this in class
    //This is my great shame
    //I have to return a reference to a Warrior struct, but I've no clue how to do that if no match is found
    //I look forward to learning why this is dumb and how to do it better
    Warrior nobody{"", 0};
    
    // G: For your iterator's l-value, I'd prefer either the singular of the mulitple (i.e. warrior) or the first letter of 
    //    that word (i.e. w)
    //search the vector of Warriors for a Warrior with a given name
    //once found return a reference to that Warrior
    for(Warrior& i : warriors){
        // G: These lines could also be: if(i.name == name) return i;
        if(i.name == name){
            // G: The parentheses here are Pythonic, I prefer: return i;
            return(i);
        }
    }

    //im a dumb guy
    Warrior& nobodyRef = nobody;
    return(nobodyRef);
}

// G: This vector should be passed by const reference
//Iterate through the vector and display the names and strengths of each warrior within it
void status(vector<Warrior>& warriors){
    cout << "There are: " << warriors.size() << " warriors" << endl;
    for(size_t i = 0; i < warriors.size(); i++){
        cout << warriors[i].name << ", strength: " << warriors[i].strength << endl;
    }
}

/* G: Overall, great work, Dan. Outside of expected issues with style and the various pass-by's, you've quickly picked up the language
      and these assignments seem easy for you. I'm looking forward to seeing you tackle the harder assignments. If I were to assign a 
      grade, this would be an A.
*/
