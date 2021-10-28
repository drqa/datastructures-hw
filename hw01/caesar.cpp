// Seen by Graeme
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// Set range for min and max size of type int
const int INT_MIN = -2147483648;
const int INT_MAX = 2147483647;

// Create a function to convert encrypted chars to decrypted chars
char decryptChar(char c, int key) {
    int decryptKey;
    
    if (key >= INT_MIN && key <= INT_MAX){
        decryptKey = 26 -(key % 26);
    }
    else{
        return 1;
    }

    for(int i = 0; i < decryptKey; i++){
        if(c != 'z') {
            c++; 
        } 
        else {
            c = 'a';
        }
    }
    return c;
}
// Create a function that uses decryptChar to decrypt an entire string
void decryptString(string& encryptedStr, int key) {
    for(size_t i = 0; i < encryptedStr.size(); i++){
        if((encryptedStr[i] >= 97 && encryptedStr[i] <= 122)){
            encryptedStr[i] = decryptChar(encryptedStr[i], key);
        }
    }
}

int main() {
    string decryptedStr;

    ifstream file("test1.txt");

    // Read first line of file to retrieve the key value, convert key from type string to int
    string keyStr;
    getline(file, keyStr);
    int key = stoi(keyStr);

    vector<string> lines;

    // Use while loop / getline function to read from the file line by line
    while(getline(file, decryptedStr)) {

        // Decrypt lines using decryptString, add decrypted strings to the vector
        decryptString(decryptedStr, key);
        lines.push_back(decryptedStr);
    }

    // Print decrypted lines in reverse order
    for(int i = lines.size() - 1; i >= 0; i--){
        cout << lines[i] << endl;
    }

    file.close();
}
