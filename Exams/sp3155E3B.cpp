#include <iomanip>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <fstream>
using namespace std;

int main(){

    const int SIZE = 20;
    char fileName[SIZE];

    cout << "Enter filename: ";
    cin.getline(fileName, SIZE);

    ofstream outputFile(fileName);
    if (!outputFile){
        cout << "Error: Could not open file to writing." << endl;
        return 1;
    }

    int* array = nullptr;
    int size = 0;

    cout << "How many numbers? ";
    cin >> size;

    array = new int[size];
    int max = -1;

    cout << "Enter " << size << " postive integers: " << endl;
    for (int i = 0; i < size; i++){
    do {
        cin >> array[i];
        if (array[i] < 0){
            cout << "Error: Negative number entered." << endl;
        }
     } while (array[i] < 0);
     
     if (array[i] > max){
            max = array[i];
        }

    }
    //cout << "The maximum number is: " << max << endl;

    cout << fileName << endl;
    for (int i = 0; i < size; i++){
        int deviation = abs(max - array[i]);
        cout << array[i] << "\t" << deviation << endl; 
    }

    delete[] array;
    outputFile.close();

    return 0;
}