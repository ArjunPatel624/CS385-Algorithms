/*******************************************************************************
 * Name          : quickselect.cpp
 * Author        : Arjun Patel 
 * Pledge        : "I pledge my honor that I have abided by the Stevens Honor System"
 * Date          : 11/15/2024
 * Description   : Implements the quickselect algorithm.
 ******************************************************************************/
#include <iostream>
#include<sstream>
#include <algorithm>
#include <vector> 

using namespace std;

class Selector {
private:
    int *a;
    size_t length;
    size_t k;

    size_t the_lomuto_partitioner(int array[], size_t left, size_t right) {
        // TODO
        // DO NOT change the function header in any way, otherwise you will lose points.
        // The pivot is chosen as the first element in the current partition [left..right].
        int pivot = array[left]; // Assign the initial pivot to the leftmost (first) element in the array 
        int current = left; // 'current' will mark the end of the segment with elements < pivot
        // Iterate over the rest of the array to partition around the pivot
        for (size_t i = left + 1; i <= right; i++) {
            // If the current element is less than the pivot, expand the segment of elements < pivot
            if (array[i] < pivot){
                current++; // Move 'current' forward to extend the segment of elements < pivot
                swap(array[current], array[i]); // Swap element at 'current' with 'i' to maintain partitioninsg
            }
            // If array[i] >= pivot, we simply move to the next element without swapping
        }
        // After processing all elements, swap the pivot element with the element at 'current'
        // This places the pivot in its correct position between segments < pivot and >= pivot
        swap(array[left], array[current]);
        return current;  // Return the final position of the pivot
    }

    int capital_Q_uickselect(int array[], size_t left, size_t right, size_t k) {
        // TODO
        // DO NOT change the function header in any way, otherwise you will lose points.
        // Use Lomuto partitioning to partition the array and get the pivot's position
        size_t s = the_lomuto_partitioner(array, left, right);
        // Check if the pivot is the k-th smallest element
        // (Remember that k-th smallest element corresponds to index k-1 because arrays are 0-indexed)
        if (s == k - 1){
            return array[s]; // If the pivot's position matches k-1, we've found the k-th smallest element
        }
        // If the k-th smallest element lies in the left segment
        else if(s > + k - 1){
            // Recur on the left segment [left .. s-1]
            return capital_Q_uickselect(array, left, s - 1, k);
        }
        // If the k-th smallest element lies in the right segment
        else{
            // Recur on the right segment [s+1 .. right]
            return capital_Q_uickselect(array, s + 1, right, k);
        }
    }

public:
    Selector(int *a_,const size_t length_, size_t k_) : a(a_), length(length_), k(k_) {}
    ~Selector() {}
    
    int do_k_select() {
        // TODO
        // DO NOT change the function header in any way, otherwise you will lose points.
        return capital_Q_uickselect(a, 0, length - 1, k);
    }
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <k>" << endl;
        return 1;
    }
    int k;
    istringstream iss;
    iss.str(argv[1]);
    if ( !(iss >> k) || k <= 0 ) {
        cerr << "Error: Invalid value '" << argv[1] << "' for k." << endl;
        return 1;
    }
    cout << "Enter sequence of integers, each followed by a space: " << flush;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    iss.clear();
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
    int num_values = values.size();
    if (num_values == 0) {
        cerr << "Error: Sequence of integers not received." << endl;
        return 1;
    }
    // TODO - error checking k against the size of the input
    if (num_values < k) {
    cerr << "Error: Cannot find smallest element " << k << " with only " << num_values << " value" << (num_values == 1 ? "." : "s.") << endl;
    return 1; 
    }
    // TODO - instantiate a Selector object and call the do_k_select function and display the result
    Selector selector(&values[0],values.size(),k);
    cout << "Smallest element " << k << ": " << selector.do_k_select() << endl;
    return 0;
}