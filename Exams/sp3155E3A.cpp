
#include <iomanip>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <fstream>
using namespace std;

struct Student{
    string firstName;
    string lastName;
    double GPA;
};

int main(){

    ifstream inputFile("sp3155Adata.dat");
    if (!inputFile){
        cout << "Error: Could not open file." << endl;
        return 1; 
    }

    Student myStudent;
    double maxGPA = 0;
    string fullName;

    while (inputFile >> myStudent.firstName >> myStudent.lastName >> myStudent.GPA){
        //cout << myStudent.firstName << " " << myStudent.lastName << " " << myStudent.GPA << endl;
        if (myStudent.GPA > maxGPA){
            maxGPA = myStudent.GPA;
            fullName = myStudent.firstName + " " + myStudent.lastName;
        }
    }

    //close the file
    inputFile.close();

    cout << fullName << " obtained the highest GPA of " << maxGPA << endl;
    return 0;
}