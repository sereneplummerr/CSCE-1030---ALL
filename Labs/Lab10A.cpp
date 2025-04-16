#include <iostream> 
#include <cmath>
#include <string> 
using namespace std;

bool checkBMI(float weight, int feet, int inches);

struct Patient{
    string name; 
    float weight;
    int feet;
    int inches;
};

int main(){
    //string name;
    //float weight;
    //int feet;
    //int inches;
    Patient person; // create a Patient object

    cout << "Enter the person's name: ";
    getline(cin, person.name);

    cout << "Enter the person's weight in pounds: ";
    cin >> person.weight;

    cout << "Enter the person's height in feet and inches: ";
    cin >> person.feet >> person.inches;

    if (checkBMI(person.weight, person.feet, person.inches)){
        cout << "The BMI of "<< person.name << " is within range." << endl;
    }
    else{
        cout << "The BMI of "<< person.name << " is not within range."<< endl;
    }
    return 0;
}

bool checkBMI(float weight, int feet, int inches){
    int totalHeight = feet * 12 + inches;
    float bmi = (703 * weight )/pow (totalHeight, 2); 

    return (bmi >= 18.5 && bmi <= 24.9); 
}