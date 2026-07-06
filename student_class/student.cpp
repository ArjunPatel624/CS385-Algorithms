/*******************************************************************************
 * Filename: student.cpp
 * Author  : Arjun Patel
 * Version : 1.0
 * Date    : January 20, 2024
 * Description: Demonstrates the use of classes, methods, vectors, and pointers.
 * Pledge  : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include<iostream>
#include<iomanip>
#include<vector>
using namespace std;

float min_gpa_threshhold = 1.0; //Constant for lowest gpa 

class Student{ 
    //Declare public methods
    public:
        //Student constructor with parameters first, last, gpa, and id using a initializer list within the constructor
        Student(string first, string last, float gpa, int id) : first_{first}, last_{last}, gpa_{gpa}, id_{id} {}
        string full_name() const{ //Public method that returns the full name of the student 
            return first_+" "+last_;
        }
        int id() const{ //Public method that returns the id of the student
            return id_;
        }
        float gpa() const{ //Public method that returns the gpa of the student
            return gpa_;
        }
        void print_info() const{ //Method to print student info with specific format: Bob Smith, GPA: 3.50, ID: 20146
            cout << first_+" "+last_ << ", GPA: " << fixed << setprecision(2) << gpa_ << ", ID: "<< id_;
        }
    //Declare private members
    private:
        string first_ ;
        string last_;
        float gpa_;
        int id_;
};

/**
* Takes a vector of Student objects, and returns a new vector
* with all Students whose GPA is < 1.0.
*/
vector<Student> find_failing_students(const vector<Student> &students){
    vector<Student> failing_students;
    //Iterates through the students vector, appending each student whose gpa is less than 1.0 to the failing_students vector
    /*Loop throught the students vector from the start to the end, and append to the failing students vector for each student whose gpa
      is less than one (threshhold)*/
    for(auto itr = students.cbegin(); itr != students.cend(); itr++){
        if(itr -> gpa() < min_gpa_threshhold){
            failing_students.push_back(*itr);
        }
    }
    return failing_students;
}

/**
* Takes a vector of Student objects and prints them to the screen.
*/
void print_students(const vector<Student> &students){
    // Iterates through the students vector, calling print_info() for each student
    for(auto itr = students.cbegin(); itr != students.cend(); itr++){
        (*itr).print_info();
        cout << endl;
    }
}

/**
* Allows the user to enter information for multiple students, then
* find those students whose GPA is below 1.0 and prints them to the
* screen. */
int main(){
    string first_name, last_name;
    float gpa;
    int id;
    char repeat;
    vector<Student> students;

    do{
        cout << "Enter student's first name: ";
        cin >> first_name;
        cout << "Enter student's last name: ";
        cin >> last_name;
        gpa = -1;
        while(gpa < 0 || gpa > 4){
            cout << "Enter student's GPA (0.0-4.0): ";
            cin >> gpa; 
        }
        cout << "Enter student's ID: ";
        cin >> id;
        students.push_back(Student(first_name, last_name, gpa, id));
        cout << "Add another student to database (Y/N)? ";
        cin >> repeat;
    } while (repeat == 'Y'|| repeat == 'y');
    cout << endl << "All students:" << endl;
    print_students(students);
    cout << endl << "Failing students:";
    vector<Student> failing_students = find_failing_students(students); 
    if(failing_students.empty()){
        cout << " None";
    } else{
        cout << endl;
        //Print a space and the word 'None' on the same line if no students are failing, otherwise print each failing student on a sep line
        for(auto itr = failing_students.cbegin(); itr != failing_students.cend(); itr ++){
            (*itr).print_info();
            cout << endl; 
        }
    }
    return 0;
}