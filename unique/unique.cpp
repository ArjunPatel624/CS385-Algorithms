/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Arjun Patel 
 * Date        : 10/4/2024
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : "I pledge my honor that I have abided by the Stevens Honor System"
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool are_letters_uppercase(const string &s) {
    // TODO: returns true if all characters in string are uppercase
    // letters in the English alphabet; false otherwise.
    for (unsigned int i = 0; i < s.length(); i++){ /* create an unsigned int and loop through each character 
                                                      in the string all the way to the end of the string */
       if (!(s[i] >= 'A' && s[i] <= 'Z')) /* if letter(s) in the input string does not fall within the range  
                                             of uppercase letters from A-Z, return false; else return true */
       return false;
    }
    return true;
   }

bool are_letters_unique(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.
    unsigned int vector = 0;  // create an unsigned int to act as a bit vector 
    unsigned int setter; // create an unsigned int to act as a setter
    for (unsigned int i = 0; i < s.length(); i++){ /* loop through each character in the string all the way to 
                                                      the end of the string */
        if(s[i] >= 'A' && s[i] <= 'Z'){ /* if letter(s) in the input string do fall within the range  
                                           of uppercase letters from A-Z, set corresponding bit for uppercase
                                           letter in bitmask*/
            setter = 1 << (s[i] - 'A'); 
        }
        if ((vector & setter) > 0){ // to check if a letter has been seen before, if the and operation returns 1 return flase 
            return false; 
        }
        vector = vector | setter; // to add onto the letters that have been seen before, use the or operation 
    }
    return true;
    // You MUST use only single unsigned integers and work with bitwise
    // and bitshifting operators only. Using any other kind of solution
    // will automatically result in a grade of ZERO for the whole assignment.
}   
int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.
    if(argc != 2) { // checks to see if the number of arguments exceed the program name and string input
        cerr << "Usage: " << argv[0] << " <string>" << endl;
            return 1;
    }
    if(!are_letters_uppercase(argv[1])){ // throws an error if letters are not uppercase within string
        cerr  << "Error: String must contain only uppercase letters." << endl;
    } 
    else{
        if(are_letters_unique(argv[1])){// lets the user know that all letters are unique uppercase letter 
            cout << "All letters are unique." << endl;
            }
            else { //lets the user know that there are repeat uppercase letters within input string 
                cout << "Duplicate letters found." << endl;
            } 
    }
}