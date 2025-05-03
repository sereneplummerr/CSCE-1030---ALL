#include "sp3155Project3_header.h"

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