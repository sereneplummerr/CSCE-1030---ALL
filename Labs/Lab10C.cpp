#include <iostream> 
#include <cmath>
#include <string> 
#include <fstream>
#include <iomanip>
using namespace std;

double findMinimum(double* arr, int size){
    double* min = arr;

    for(double* ptr = arr + 1; ptr < arr + size; ptr++){
        if(*ptr < *min){
            min = ptr;
        }
    }
    //returning the minimum value
    return *min;
}

int main(){
    int SIZE;
    cout << "Enter the size of the array: ";
    cin >> SIZE;

    //create dynamic array using new operator
    double* numlist = new double[SIZE];
    
    for(int i = 0; i < SIZE; i++){
        cout << "Enter value #" << i + 1 << ": ";
        cin >> *(numlist + i);
    }
    double minimum = findMinimum(numlist, SIZE);
    cout << fixed << setprecision(2);
    cout << "Minimum: " << minimum << endl;

    delete[] numlist; 

    return 0;
}
    