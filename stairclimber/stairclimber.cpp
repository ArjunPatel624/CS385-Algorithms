/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Arjun Patel  
 * Date        : 10/25/24
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : "I pledge my honor that I have abided by the Stevens Honor System"
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<unsigned long> > way_getter(unsigned long stairs_count) {
    // TODO: Return a vector of vectors of unsigned long representing
    // the different combinations of ways to climb stairs_count
    // stairs, moving up either 1, 2, 3, 4, ..., stairs_count stairs at a time.
    // Base case since there are no ways to climb 0 stairs; should return empty list
    if (stairs_count == 0){
        return {{}}; // Return vector of vector with nothing in it
    } else {
        vector<vector<unsigned long>> result;
        for (unsigned long i = 1; i <= stairs_count; i++){
            // Recursive call to get the ways to climb the remaining stairs
            vector< vector<unsigned long> > inner_vect = way_getter(stairs_count - i);
            for (unsigned long j = 0; j < inner_vect.size(); j++){
                // Add the current stair to the result
                inner_vect[j].insert(inner_vect[j].begin(), i);
                // Add the updated combination to the result 
                result.push_back(inner_vect[j]);
            }
        }
        return result;
    }
}

void print_ways_to_screen(const vector<vector<unsigned long>> &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.

    int total_ways = (int)ways.size();

    // Calculate the total number of stairs by summing the first combination.
    // Every combination adds up to the same number of stairs.
    unsigned long stairs = 0;
    if (!ways.empty()) {
        for (unsigned long step : ways[0]) {
            stairs += step;
        }
    }

    // Print the appropriate message depending on the number of ways.
    if (stairs == 0) {
        cout << "1 way to climb 0 stairs." << endl;
    } else if (total_ways == 1) {
        cout << "1 way to climb " << stairs << " stair." << endl;
    } else {
        cout << total_ways << " ways to climb " << stairs << " stairs." << endl;
    }

    // Determine the width needed to align the numbering.
    int width = to_string(total_ways).length();

    // Iterate through each way and print its corresponding sequence of steps.
    for (int i = 0; i < total_ways; i++) {
        cout << setw(width) << (i + 1) << ". [";

        // Print each step in the current combination, separated by commas.
        for (size_t j = 0; j < ways[i].size(); j++) {
            if (j > 0) {
                cout << ", ";
            }
            cout << ways[i][j];
        }
        cout << "]" << endl;
    }
}

int main(int argc, char * const argv[]) {
    int n;
    istringstream iss;      // Used to check if input is an integer later
    // Makes sure that the input is a single number for n stairs to climb
    if (argc != 2){
        cerr << "Usage: " << argv[0] << " <number of stairs>" << endl;
        return 1;
    }
    iss.str(argv[1]);
    if(!(iss >> n)) { // Read integer from iss and check to see if it is a valid integer  
        cerr << "Error: Number of stairs must be a positive integer." << endl; // Error message if n is not an integer 
        return 1;
    }
    // Handles an input that is a negative number for n stairs to climb 
    if (n < 0){
        cerr << "Error: Number of stairs must be a positive integer." << endl;
        return 1;
    }
    vector<vector<unsigned long>> example = way_getter(n); // Initial call to the recursive function
    print_ways_to_screen(example);                         // Prints the vector of vectors as we want
    return 0; 
}