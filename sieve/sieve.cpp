/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Arjun Patel
 * Date        : 10/11/24
 * Description : Sieve of Eratosthenes
 * Pledge      : "I pledge my honor that I have abided by the Stevens Honor System"
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class MyPrimeSieve {
private:

    // Method declarations
    int get_primes_count() const;
    void sieve_runner();
    static int max_prime_width(int num);

    // Instance variables
    bool* primes_;
    const int lower_limit_, upper_limit_, bad_digit_;
    int num_primes_, max_prime_;
public:
    MyPrimeSieve(int lower_limit, int upper_limit, int bad_digit);

    ~MyPrimeSieve() {
        //TODO: free any dynamically allocated memory
        delete[]primes_; // Deallocate memory to prevent valgrind / memory leaks 
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;
};

MyPrimeSieve::MyPrimeSieve(int lower_limit, int upper_limit, int bad_digit) :
          primes_{nullptr}, lower_limit_{lower_limit}, 
          upper_limit_{upper_limit}, bad_digit_{bad_digit} {
    // TODO: dynamically allocate primes_
    primes_ = new bool[upper_limit_ + 1]; // +1 to accomidate for all numbers between 0 and upper_limit_
    // Assume all elements in primes_ array to be true boolean value, meaning all of the values in primes_ are actually prime numbers 
    for (int i = 0; i <= upper_limit_; ++i) {
        primes_[i] = true;
    }
    // run the sieve
    sieve_runner();
}

void MyPrimeSieve::display_primes() const {
    // TODO: write code to display the primes in the format specified in the
    // requirements document.
    // Print number of good primes and the range
    cout << "Number of good primes found: " << get_primes_count() << endl;
    cout << "Good primes between " << lower_limit_ << " and " << upper_limit_ << ":" << endl;
    // Get the width of the largest prime for formatting purposes
    // Determine the width for formatting based on the largest prime
    int maxWidth = max_prime_width(max_prime_);
    int primesPerRow = 80 / (maxWidth + 1);  // Maximum number of primes that can fit in a row
    int printedCount = 0;  // Counter for printed primes

    // Loop through the primes array and print the primes within the specified range
    for (int i = lower_limit_; i <= upper_limit_; ++i) {
        if (primes_[i]) {
            cout << setw(maxWidth) << i;  // Right-align prime numbers using setw
            printedCount++;  // Increment the printed primes count
            // Control formatting for output
            if (printedCount % primesPerRow == 0) {
                cout << endl;  // Start a new line after reaching the maximum number of primes per row
            } else if (i < upper_limit_ && printedCount < get_primes_count()) {
                cout << " ";  // Insert space between primes
            }
        }
    }
    // If the last row isn't full, we add a new line at the end
    if (printedCount % primesPerRow != 0) {
        cout << endl;
    }
}

int MyPrimeSieve::get_primes_count() const {
    // TODO: write code to count the number of primes found
    int count = 0; // Initialize counter variable to count  the number of primes
    // Loop through  the primes array and count the number of primes
    for (int i = lower_limit_; i <= upper_limit_; ++i) {
        if (primes_[i]) {
            count++;
        }
    }   
    return count;
}

void MyPrimeSieve::sieve_runner() {
    // TODO: write sieve algorithm
    // Set the numbers 0 and 1 to false since they are not prime numbers given any case
    primes_[0] = primes_[1] = false;
    // We only need to run up to the square root of the upper_limit_
    int sqrt_upper_limit = static_cast<int>(sqrt(upper_limit_));
    for (int i = 2; i <= sqrt_upper_limit; ++i) {
        if (primes_[i]) {
            // Mark multiples of i as not prime, starting from i^2
            for (int j = i * i; j <= upper_limit_; j += i) {
                primes_[j] = false;
            }
        }
    }
    // Filter out primes that contain the bad digit
    // Iterate through the range and filter primes that contain the bad digit
    for (int i = lower_limit_; i <= upper_limit_; ++i) {
        if (primes_[i]) {
            int number = i;
            while (number > 0) {
            // Check if any digit of the number matches the bad digit
            if (number % 10 == bad_digit_) {
                primes_[i] = false;  // Immediately mark as non-prime
                break;  // Exit loop once a bad digit is found
            }
            number /= 10;  // Continue checking the next digit
        }
    }
}
// Set max_prime_ to the largest prime in the given range
max_prime_ = -1;  // Default to -1 if no primes are found
for (int i = upper_limit_; i >= lower_limit_; --i) {
    if (primes_[i]) {
        max_prime_ = i;  // Capture the largest prime
        break;  // No need to continue once the largest prime is found
    }
    }
}

int MyPrimeSieve::max_prime_width(int num) {   
    // TODO: write code to determine the maximum prime width
    // Hint: get how many digits are in the maximum prime number.
    // Check if the number is zero, as it has a single digit.
    if(num == 0){
        return 1;
    } else {
        // Initialize a counter for the number of digits
        int digits = 1;
        // Loop to divide the number by 10 until it's less than or equal to 10,
        // incrementing the digit count for each division
        while (num > 10) {
            num /= 10;
            digits++;
        }
        return digits; // Return total count of digits
    }
}

int main() {
    cout << "*********************** " <<  "Sieve of Eratosthenes (MODIFIED)" <<
            " ***********************" << endl;
    cout << "Search for good primes between: ";
    string lower_limit_str;
    cin >> lower_limit_str;
    int lower_limit;
    
    string upper_limit_str;
    cin >> upper_limit_str;
    int upper_limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(lower_limit_str);

    // Check for error.
    if ( !(iss >> lower_limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (lower_limit < 0) {
        cerr << "Error: Input must be an integer >= 0." << endl;
        return 1;
    }

    iss.clear();
    iss.str(upper_limit_str);

    // Check for error.
    if ( !(iss >> upper_limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
        if (upper_limit < lower_limit) {
        cerr << "Error: Input must be an integer >= lower limit." << endl;
        return 1;
    }

    string bad_digit_str;
    cin >> bad_digit_str;
    int bad_digit;

    iss.clear();
    iss.str(bad_digit_str);

    // Check for error
    if ( !(iss >> bad_digit)) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (bad_digit < 0 || bad_digit > 9) {
        cerr << "Error: Input must be a digit." << endl;
        return 1;
    }

    cout << endl << "Bad digit: " << bad_digit << endl;

    // TODO: write code that uses your class to produce the desired output. 
    // Create an instance of MyPrimeSieve class with specified lower_limit, upper_limit, and bad_digit
    MyPrimeSieve sieve(lower_limit, upper_limit, bad_digit);
    // Call the display_primes method to print all prime numbers within the range that do not contain the bad_digit
    sieve.display_primes();
    return 0;   
}