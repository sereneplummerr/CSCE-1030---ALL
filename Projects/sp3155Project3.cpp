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


int getNumber(const string& studentRecords) { // used clyde AI to help bc I kept getting errors
    ifstream inFile(studentRecords);
    if (!inFile) {
        cout << "Error opening file." << endl;
        return 0;
    }
    
    int count = 0;
    string line;
    
    // Count the number of lines in the file
    while (getline(inFile, line)) {
        count++;
    }
    
    inFile.close();
    return count;
}

void add_Student() {
    Student newStudent;
    string firstName, lastName;

    cout << "Enter student last name: ";
    cin >> lastName;
    cout << "Enter student first name: ";
    cin >> firstName;
    newStudent.studentName = firstName + " " + lastName; // Concatenate first and last name

    cout << "Enter student ID: ";
    cin >> newStudent.studentID;

    cout << "How many tests did this student take? (1-5): ";
    cin >> newStudent.testsTaken;

    if (newStudent.testsTaken < 1 || newStudent.testsTaken > MAX) {
        cout << "Invalid number of tests. Please enter a number between 1 and 5." << endl;
        return;
    }

    newStudent.testScores = new int[newStudent.testsTaken];
    for (int i = 0; i < newStudent.testsTaken; i++) {
        cout << "Enter score " << i + 1 << ": ";
        cin >> newStudent.testScores[i];
    }

    ofstream outputFile("student.dat", ios::app);
    if (!outputFile) {
        cout << "Error opening file." << endl;
        delete[] newStudent.testScores;
        return;
    }

    outputFile << lastName << "," << firstName << "," << newStudent.studentID << "," << newStudent.testsTaken << ",";
    for (int i = 0; i < newStudent.testsTaken; i++) {
        outputFile << newStudent.testScores[i] << ",";
    }
    outputFile << endl;
    outputFile.close();

    cout << "Student record added successfully." << endl;
    delete[] newStudent.testScores;
}

void remove_Student(const string& studentIDRemove) { // used gemini AI, code was not functioning correctly
    ifstream inFile("student.dat");
    if (!inFile) {
        cout << "Error opening file." << endl;
        return;
    }

    int numStudents = getNumber("student.dat");
    Student* students = new Student[numStudents];

    string line;
    int studentCount = 0;
    bool foundMatch = false;

    while (getline(inFile, line) && studentCount < numStudents) {
        stringstream ss(line);
        string lastName, firstName, item;

        getline(ss, lastName, ',');
        getline(ss, firstName, ',');
        students[studentCount].studentName = firstName + " " + lastName;
        getline(ss, students[studentCount].studentID, ',');

        getline(ss, item, ',');
        students[studentCount].testsTaken = stoi(item);
        students[studentCount].testScores = new int[students[studentCount].testsTaken];

        for (int i = 0; i < students[studentCount].testsTaken; i++) {
            getline(ss, item, ',');
            students[studentCount].testScores[i] = stoi(item);
        }

        if (students[studentCount].studentID == studentIDRemove) {
            cout << "Removing student: " << students[studentCount].studentName << endl;
            foundMatch = true;
        }

        studentCount++;
    }
    inFile.close();

    if (foundMatch) {
        ofstream outFile("student.dat");
        if (!outFile) {
            cout << "Error opening file." << endl;
            for (int i = 0; i < studentCount; i++) {
                delete[] students[i].testScores;
            }
            delete[] students;
            return;
        }

        for (int i = 0; i < studentCount; i++) {
            if (students[i].studentID != studentIDRemove) {
                stringstream nameSS(students[i].studentName);
                string firstName, lastName;
                nameSS >> firstName >> lastName;
                outFile << lastName << "," << firstName << "," << students[i].studentID << "," << students[i].testsTaken;
                for (int j = 0; j < students[i].testsTaken; j++) {
                    outFile << "," << students[i].testScores[j];
                }
                outFile << endl;
            }
        }

        outFile.close();
        cout << "Student with ID " << studentIDRemove << " removed successfully." << endl;
    } else {
        cout << "Student with ID " << studentIDRemove << " not found." << endl;
    }

    for (int i = 0; i < studentCount; i++) {
        delete[] students[i].testScores;
    }
    delete[] students;
}

void display(){
    ifstream inputFile("student.dat");
    if (!inputFile) {
        cout << "Error opening file." << endl;
        return;
    }

    //get the number of students in the file
    int numStudents = getNumber("student.dat");
    if (numStudents <= 0){
        cout << "No students found." << endl;
        inputFile.close();
        return;
    }
    //create dynamic array 
    Student* students = new Student[numStudents];
    //read content of file into the array
    string line;
    int Num = 0; 
    while (getline(inputFile, line) && Num < numStudents){
        stringstream ss(line); // full line for each student
        string lastName, firstName, item; 

        getline(ss, lastName, ','); // get last name
        getline(ss, firstName, ','); // get first name
        students[Num].studentName = firstName + " " + lastName; // concatenate first and last name
        getline(ss, students[Num].studentID, ','); // get student ID
        getline(ss, item, ','); // get number of tests taken, reads string stream until comma
        students[Num].testsTaken = stoi(item); // convert string to int

        students[Num].testScores = new int[students[Num].testsTaken]; // create dynamic array for test scores
        //read test scores into the array
        for (int i = 0; i < students[Num].testsTaken; i++){
            getline(ss, item, ',');
            students[Num].testScores[i] = stoi(item); // convert string to int
        }
        Num++; // increment number of students
    }
    inputFile.close(); // close the file
    //display the students
    cout << "Student Records:" << endl;
    cout << left << setw(30) << "Name" << setw(15) << "Student ID" << "Test Score" << endl;
    cout << string(70, '-') << endl; 

    for (int i = 0; i < Num; i++){
        cout << left << setw(30) << students[i].studentName 
        << setw(15) << students[i].studentID;

    for (int j = 0; j < students[i].testsTaken; j++){
        cout << setw(5) << students[i].testScores[j];
    }
    cout << endl;
    delete[] students[i].testScores; // free memory
    }

    delete[] students; // free memory
    cout << string(70, '-') << endl; // print line
}

void search(const string& studentIDSearch){
    ifstream inputFile("student.dat");
    if (!inputFile) {
        cout << "Error opening file." << endl;
        return;
    }

    Student* studentPtr = new Student;
    string line;
    bool found = false;
    while (getline(inputFile, line)){
        stringstream ss(line); // full line for each student
        string lastName, firstName, item; 
        getline(ss, lastName, ','); // get last name
        getline(ss, firstName, ','); // get first name
        (*studentPtr).studentName = firstName + " " + lastName; // used GEMINI TO HELP, concatenate first and last name
        getline(ss, (*studentPtr).studentID, ','); // get student ID

        getline(ss, item, ',');
        (*studentPtr).testsTaken = stoi(item); // convert string to int
        (*studentPtr).testScores = new int[(*studentPtr).testsTaken]; 
        for (int i = 0; i < (*studentPtr).testsTaken; i++){
            getline(ss, item, ',');
            (*studentPtr).testScores[i] = stoi(item);
        }

        //check if student ID matches
        if ((*studentPtr).studentID == studentIDSearch){
            found = true;
            cout << left << setw(30) << "Name" << setw(15) << "Student ID" << "Test Score" << endl;
            cout << string(70, '-') << endl; 
            cout << left << setw(30) << (*studentPtr).studentName << setw(15) << (*studentPtr).studentID;

            for (int j = 0; j < (*studentPtr).testsTaken; j++){
                cout << setw(5) << (*studentPtr).testScores[j];
            }
            cout << endl;
            cout << string(70, '-') << endl; // print line
            delete[] (*studentPtr).testScores;
            break; // exit loop if found
        }
        delete[] (*studentPtr).testScores;
    }

    inputFile.close(); // close the file
    if (!found){
        cout << "No student found with ID: " << studentIDSearch << endl;
    }
    
    delete studentPtr; // free memory

}

int findMinimum(int* scores, int size){
    int minScore = scores[0]; // initialize minScore to the first score
    for (int i = 1; i < size; i++){
        if (scores[i]< minScore){
            minScore = scores[i];
        }
    }
    return minScore;
}


void exportResults(){
    //open file for writing
    ofstream outputFile("average.dat");
    if (!outputFile) {
        cout << "Error opening file." << endl;
        return;
    }

    //open file for reading
    ifstream inputFile("student.dat");
    if (!inputFile) {
        cout << "Error opening file." << endl;
        return;
    }

    int numStudents = getNumber("student.dat");
    if (numStudents <= 0){
        cout << "No students found." << endl;
        inputFile.close();
        return;
    }

    //dynamic array for students struct
    Student* students = new Student[numStudents];
    string line;
    int Num = 0; // current number of students
    while (getline(inputFile, line) && Num < numStudents){
        stringstream ss(line); // full line for each student
        string lastname, firstName, item;
        getline(ss, lastname, ','); // get last name
        getline(ss, firstName, ','); // get first name
        students[Num].studentName = firstName + " " + lastname; // concatenate first and last name
        getline(ss, students[Num].studentID, ','); // get student ID
        getline(ss, item, ','); // get number of tests taken
        students[Num].testsTaken = stoi(item); // convert string to int
        students[Num].testScores = new int[students[Num].testsTaken]; // create dynamic array for test scores
        //read test scores into the array
        for (int i = 0; i < students[Num].testsTaken; i++){
            getline(ss, item, ',');
            students[Num].testScores[i] = stoi(item); // convert string to int
        }
        Num++; // increment number of students
    }
        //calculate average score
        for (int i = 0; i < numStudents; i++){
        int sum = 0;
        for (int j = 0; j < students[i].testsTaken; j++){
            sum += students[i].testScores[j];
        }
        int minScore = findMinimum(students[i].testScores, students[i].testsTaken);
        sum -= minScore; // subtract minimum score from sum
        //divide the sum by the number of tests taken 
        double average = static_cast<double>(sum) / (students[i].testsTaken - 1);
        outputFile << students[i].studentID << " " << fixed << setprecision(1) << average << endl; 
        delete[] students[i].testScores;  
    }

    delete[] students;
    //close both files
    inputFile.close();
    outputFile.close();
    cout << "Results exported successfully." << endl;
}



int main() {
    int choice;
    MenuChoice menuOption;
    //game loop
    while(true){
        cout << "1. Add" << endl;
                cout << "2. Remove" << endl;
                cout << "3. Display" << endl;
                cout << "4. Search" << endl;
                cout << "5. Results" << endl;
                cout << "6. Quit" << endl;
                cout << "What would you like to do? (1-6): ";
                cin >> choice;

                //validate input 
                if (choice < 1 || choice > 6){
                    cout << "Invalid input. Please enter a number between 1 and 6." << endl;
                    continue; //continue to the next iteration of the loop
                } 

                choice = static_cast<MenuChoice>(choice);
	            switch (choice) {
	            case 1: { // Add a new student record
                    add_Student();
                    break;
                }
                case 2: { // Remove an existing student record
                    cout << "Enter ID of student to remove: ";
                    string studentIDRemove;
                    cin >> studentIDRemove;
                    remove_Student(studentIDRemove);
                    break;
                }
                case 3: { // Display all records
                    display();
                    break;
                }
                case 4: { // Search for a particular student record using student ID
                    cout << "Enter ID of student to search: ";
                    string studentIDSearch;
                    cin >> studentIDSearch;
                    search(studentIDSearch);
                    break;
                }
                case 5: { // Export the results to a disk file
                    exportResults();
                    break;
                }
                case 6: { //Quit the program
                    cout << "Goodbye!" << endl;
                    break;
                }

                default: { // Invalid choice
                    cout << "Invalid choice. Please eneter a number between 1 and 6." << endl;
                    break;
                }
                
                
    }


    }
}