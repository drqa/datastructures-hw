#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// Set range for min and max size of type int
const int INT_MIN = -2147483648;
const int INT_MAX = 2147483647;

// G: This function as stated in the HW should return void and decrypt by changing a reference to 
// the char c instead of returning a char

// Create a function to convert encrypted chars to decrypted chars
char decryptChar(char c, int key) {
    int decryptKey;
    
    // G: I stated that the file would not overflow so you did not have to check for overflow here.
    // G: Watch your spaces, there should be a space between ) and {, and on the following line there
    // should be a space between - and (. There are other instances but you can apply this comment to
    // all of them
    if (key >= INT_MIN && key <= INT_MAX){
        decryptKey = 26 -(key % 26);
    }
    else{
        // G: You should output an error message with cerr before you return an exit status code 1
        return 1;
    }
    
    // G: For loop is unnecessary, can be done with O(1) operations entirely. Additionally, this will
    // make the math on line 21 very slightly less complicated
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
        /* G:
           Use the character codes here instead of the numbers when doing comparisons
           I.e. encryptedStr[i] >= 'a' && encryptedStr[i] <= 'z'
           Easier to read and understand
        */
        if((encryptedStr[i] >= 97 && encryptedStr[i] <= 122)){
            encryptedStr[i] = decryptChar(encryptedStr[i], key);
        }
    }
}

// G: We talked about prototyping - your functions should be defined after main() with prototypes given beforehand
int main() {
    // G: Declare variables, generally, as close to where you first use them as possible - you use this on line 74
    // first it should be down there with your vector<string> lines; instialization
    string decryptedStr;
    
    // G: Nitpick but file name should be encrypted.txt as per assignment specifications
    ifstream file("test1.txt");
    
    /* G: 
       This is fine but I would prefer you avoid the cast from string -> int by reading
       the step value as an int directly from the stream
       E.g. int x; file >> x;
    */
    
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
    
    // G: You can close the file sooner than this, you're done with it after your while loop
    file.close();
}

/* G:
   Overall you did well, particularly I'm happy with the printing of the vector in reverse and your understanding 
   of the C++ naming conventions when it comes to function names, variable names, etc. Your program works and that 
   is the more important part but there are, as my comments should make clear, some places for improvement.
   
   I'll go over my version with you on Friday and we can talk about why I think there are certain choices in mine 
   that make it faster and more easily maintainable. If I were to grade this, I would give it a B+.
