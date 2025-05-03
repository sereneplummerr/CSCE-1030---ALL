#ifndef SP3155PROJECT3_HEADER_H
#define SP3155PROJECT3_HEADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

const int MAX = 5; // global int const Number of tests

enum MenuChoice {Add = 1, Remove = 2, Display = 3, Search = 4, Results = 5, Quit =6};

struct Student{
    string studentName; // last name, first name
    string studentID; // student ID
    int testsTaken; // number of tests taken
    int* testScores; // array of test scores
    double averageScore; // average score
};

int getNumber(const string& studentRecords); // function to get number of students
void add_Student(); // function to add student
void remove_Student(const string& studentIDRemove);
void display();
void search(const string& studentIDSearch);
void exportResults();
int findMinimum(int* scores, int size); // function to find minimum score

#endif // SP3155PROJECT3_HEADER_H