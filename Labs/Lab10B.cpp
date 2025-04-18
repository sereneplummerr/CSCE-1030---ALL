#include <iostream> 
#include <cmath>
#include <string> 
#include <fstream>
using namespace std;

//structure called Point 
struct Point {
    int x;
    int y;
    int z;
    double distance;
};

//function to read the data in an array of structures
void readPoints(Point points[], int& count, ifstream& inputFile){
    count = 0;
    while (inputFile >> points[count].x >> points[count].y >> points[count].z){
        points[count].distance = 0; // distance to 0
        count++;
    }
}

Point findClosestPoint(Point points[], int count, Point userPoint){
    double minDistance = -1;
    Point closestPoint;
    for (int i = 0; i < count; i++){
    points[i].distance = sqrt(pow(points[i].x - userPoint.x,2)+
                              pow(points[i].y - userPoint.y,2)+
                               pow(points[i].z - userPoint.z,2));

    //update 
    if (minDistance == -1 || points[i].distance < minDistance){
        minDistance = points[i].distance;
        closestPoint = points[i];
    }
    }

    return closestPoint;
}


int main() {

    int count = 0;
    const int SIZE = 100;
    Point points[SIZE]; // Declare an array of Point structures

    //open files
    ifstream inputFile("data1.dat");
    if (!inputFile){
        cout << "Error: Could not open file." << endl;
        return 1;
    }

    readPoints(points, count, inputFile);
    inputFile.close();

    Point userPoint;
    cout << "Enter point (x, y, z): ";
    cin >> userPoint.x >> userPoint.y >> userPoint.z;

    //find the closest point
    Point closestPoint = findClosestPoint(points, count, userPoint);

    cout << "The closest point is " << closestPoint.x << ", " << closestPoint.y << ", " << closestPoint.z << endl;
    cout << "Minimum distance = " << closestPoint.distance << endl;
    return 0;

}