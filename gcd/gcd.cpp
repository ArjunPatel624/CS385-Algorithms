/*******************************************************************************
 * Filename: gcd.cpp
 * Author  : Arjun Patel
 * Version : 1.0
 * Date    : September 17, 2024
 * Description: Computes the GCD of two command-line arguments.
 * Pledge  : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <sstream>
using namespace std;

    int gcd_iterative(int m, int n){
        /* if n = 0 and m is a non- zero integer, then the GCD of the two integer inputs would automatically be m.
           Similarly, if n is a non zero integer and m = 0, the GCD of the two integers would automatically be n.
           The following implementation(s) use Euclid's Algorithm to find the GCD of two integer inputs:
        */
    
        while (n != 0){  // Step 1. Check if n is euqal to 0, and if so return m (go strait to line 27)
            int r = m % n; /* Step 2. Divide m by n, and assign the remiander to variable r,then set the value of m 
                              equal to n, and the value of n equal to r for the next iteration, repeat until n (remainder) = 0 
                           */ 
            m = n;
            n = r;
        }
        return m; // If n was not initially zero, it will eventually reach 0, which is when m (GCD value) should be returned 
    }

    int gcd_recursive(int m, int n){
        if (n == 0){ // Step 1. (Base case) Check if n is equal to 0, and if so return m and stop the program 
            return m;
        }
        return gcd_recursive(n, m % n); /* Step 2. (Function call to itself) if the value of n was not zero, 
                                           assign the value of n in place of m, and divide m by n until n = 0
                                        */
    }

    int main(int argc, char *argv[]){
    int m, n;
    istringstream iss;
    if (argc != 3){ // Check to make sure that number of arguments is 3 [1 for the name of the program and 2 for int inputs]
        cerr << "Usage: " << argv[0] << " <integer m> <integer n>" << endl; /* Error to show user how many inputs are accepted
                                                                               in case the inputs exceed 2 or input is nothing
                                                                            */
        return 1;
    } 
    iss.str(argv[1]);
    if(!(iss >> m)) { // Read integer from iss and check to see if it is a valid integer  
        cerr << "Error: The first argument is not a valid integer." << endl; // Error message if m is not an integer 
        return 1;
    }
    iss.clear(); // Cleared to use for another string
    iss.str(argv[2]);
    if(!(iss >> n)) { // Read integer from iss and check to see if it is a valid integer
        cerr << "Error: The second argument is not a valid integer." << endl; // Error message if n is not an integer
        return 1;
    }
    cout << "Iterative: gcd(" << m << ", " << n <<") = "<<gcd_iterative(abs(m), abs(n)) << endl; // Display result  
    cout << "Recursive: gcd(" << m << ", " << n <<") = "<<gcd_recursive(abs(m), abs(n)) << endl; // Display result 
    return 0;
    }