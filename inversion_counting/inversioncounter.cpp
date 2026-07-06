/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Arjun Patel
 * Version     : 1.0
 * Date        : 11/22/24
 * Description : Counts the number of inversions in an array.
 * Pledge      : "I pledge my honor that I have abided by the Stevens Honor System"
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

class MyInversionCounter {
public:
    MyInversionCounter(int array_[], int length_) : array(array_), length(length_) {}
    ~MyInversionCounter() {}

    /**
    * Counts the number of inversions in an array in Theta(n^2) time.
    */
    long quadratic_time_counter(int array[], int length) {
        // TODO
        long ret = 0; // Initialize a counter for the inversions 
        for (int i = 0; i < length; i++){ // Loop through the array starting at first element 
            for(int j = i + 1; j < length; j++){ // Loop though array starting at second element 
                if (array[i] > array[j]){ // Compare elements in the array to determine if inversion
                    ret ++; // if array[i] > array[j], count this as an inversion within array
                }
            }
        }
        return ret; // return the number of inversions given the array 
    }

    /**
    * Counts the number of inversions in an array in Theta(n lg n) time.
    */
    unsigned long linearithmic_time_counter(int array[], int length) {
        // TODO
        // Hint: Use mergesort!
        int * scratch = new int [length]; // Dynamically allocate a new array 'scratch' for merging 
        long count = m_e_r_g_e_s_o_r_t(array, scratch, 0, length - 1); // Use mergesort
        delete[] scratch; // De-allocate memory for the array 
        return count; // Return the number of inversions counted
    }

private:
    unsigned long m_e_r_g_e_s_o_r_t(int array[], int scratch[], int low, int high) {
        // Psudocode for merge and mergesort implemented below (slide 2 Recitation 10)
        long ret = 0;
        if (low < high){
            int mid = low + (high - low) / 2;
            ret += m_e_r_g_e_s_o_r_t(array, scratch, low, mid);
            ret += m_e_r_g_e_s_o_r_t(array, scratch, mid + 1, high);
            // Implement merge function within m_e_r_g_e_s_o_r_t
            int x = mid + 1;
            int y = low;
            int z = low;
            while ((y <= mid) && (x <= high)){
                if (array[y] <= array[x]){ 
                    // When we copy from the low/left subarray A[i1] to B[i], no inversions are fixed (slide 8 Recitation 10)
                    scratch[z++] = array[y++];
                } else{
                    // When we copy from the high/right subarray A[i2] to B[i] 
                    scratch[z++] = array[x++];
                    // # of inversions fixed = # of elements left in low/left subarray (aka midpoint - i1 + 1)
                    ret += (mid - y + 1);
                }
            }
            for (; y <= mid; y++){
                scratch[z++] = array[y]; 
            }
            for (; x <= high; x++){
                scratch[z++] = array[x]; 
            }
            for (int k = low; k <= high; k++){
                array[k] = scratch[k];
            }
        }
        return ret;
    }
    int *array;
    int length;
};

int main(int argc, char *argv[]) {
    // TODO: parse command-line argument
    string option = "fast";
    if (argc > 2) { // Handle command-line argument where user enters more than 2 inputs
        cerr << "Usage: " << argv[0] << " [slow]" << endl;
        return 1;
    } else if (argc == 2){ // Handle command-line argument where user sepcifies slow apprach for inversion counting 
        string input = argv[1];
        if (input == "slow"){
            option = "slow";
        } else{ // If something other than 'slow' is entered, error message 
            cerr << "Error: Unrecognized option " << "'" << input << "'" << "." << endl;
            return 1;
        }
    }
    // Given 
    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }
    // Given END 
    // TODO: produce output
    if (values.empty()){ // If no sequence of integers are recieved, throw error message 
        cerr << "Error: Sequence of integers not received." << endl;
        return 1;
    }
    int length = values.size();
    MyInversionCounter counter(&values[0], length); /* Use MyInversionCounter function to count the inversions 
                                                       and &values[0] to store input in vector and pass the internal
                                                       array to the function*/
    long inversions;
    if (option  == "slow"){ // Using the theat(n^2) approach to count the inversions if user eneters slow 
        inversions = counter.quadratic_time_counter(&values[0], length);
    } else { // Using the theta (n lg n) approach to count the inversions if the user does not specify 'slow'
        inversions = counter.linearithmic_time_counter(&values[0], length);
    }
    // Fast approach will be used by default unless the user specifies 'slow'
    cout << "Number of inversions: " << inversions << endl; // Print the number of inversions 
}