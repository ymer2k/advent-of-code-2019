#include <iostream>
#include <fstream> //used to read txt files.
#include <string>     /*  insert   */
#include <string.h>   /*  strlen   */
#include <vector>   /* vector */
#include <cstdlib> /* abs()  */
#include <math.h>       /* sqrt */


using namespace std;

struct Point
{
    int x;
    int y;
    int distance;
};

std::vector<string> splitString(string line, string delimiter)
{
    /* Takes in a string and a char[] delimiter to split up the string at those delimiters and return each separated part in a vector<string> */
    vector<string> input;
    size_t old_pos = 0;
    size_t pos = 0;
    string token;
    while((pos = line.find(delimiter,old_pos)) != string::npos)
    {
        token = line.substr(old_pos,pos - old_pos);
        input.push_back(token);
        old_pos = pos + 1;
    }
    //Grab the last element that doesn't end with ","
    token = line.substr(old_pos,pos - old_pos);
    input.push_back(token);
    return input;
}

std::vector<Point> getStructCoordinates(vector<string> input)
{
    int x_pos = 0;
    int y_pos = 0;
    int totalDistance = 0; //Keeps track of total steps taken.
    std::vector<Point> coordinates;
    for(string element : input)
    {
        if(element.compare(0,1,"R") == 0)
        {
            x_pos += stoi(element.substr(1,string::npos));
            totalDistance += stoi(element.substr(1,string::npos));
        }

        if(element.compare(0,1,"D") == 0)
        {
             y_pos -= stoi(element.substr(1,string::npos));
            totalDistance += stoi(element.substr(1,string::npos));
        }

        if(element.compare(0,1,"L") == 0)
        {
            x_pos -= stoi(element.substr(1,string::npos));
            totalDistance += stoi(element.substr(1,string::npos));
        }

        if(element.compare(0,1,"U") == 0)
        {
             y_pos += stoi(element.substr(1,string::npos));
            totalDistance += stoi(element.substr(1,string::npos));
        }



        //Update coordinates for this step.
        coordinates.push_back({x_pos,y_pos,totalDistance});
        cout << coordinates.back().distance << endl;
        //cout << "Current Data: " << element << endl;
    }
    return coordinates;
}

Point getIntersectionPoint(Point p1, Point p2, Point p3, Point p4)
{ /*   get the intersection point of two lines. */
    Point intersectionPoint;
    int D = (p1.x-p2.x)*(p3.y-p4.y)-(p1.y-p2.y)*(p3.x-p4.x);
    intersectionPoint.x = ( (p1.x*p2.y-p1.y*p2.x)*(p3.x-p4.x)-(p1.x-p2.x)*(p3.x*p4.y-p3.y*p4.x) )/D;
    intersectionPoint.y = ( (p1.x*p2.y-p1.y*p2.x)*(p3.y-p4.y)-(p1.y-p2.y)*(p3.x*p4.y-p3.y*p4.x) )/D;
    return intersectionPoint;
}

int orientation(Point p1, Point p2, Point p3)
{
    /*
     To find orientation of ordered triplet (p1, p2, p3).
     The function returns following values
     0 --> p, q and r are colinear
     1 --> Clockwise
     2 --> Counterclockwise
    */

    int val = (p2.y - p1.y) * (p3.x - p2.x) -
              (p2.x - p1.x) * (p3.y - p2.y);

    if (val == 0) return 0;  // colinear

    return (val > 0)? 1: 2; // clock or counterclock wise
}

bool doIntersect(Point p1, Point q1, Point p2, Point q2)
{ /*  check if two lines intersect  */
    // Find the four orientations needed for general and
    // special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // General case
    if (o1 != o2 && o3 != o4)
        return true;

    return false; // Doesn't fall in any of the above cases
}

int Part1()
{
    ifstream inFile;
    inFile.open("C:\\Users\\Jonas\\Cprojects\\advent-of-code-2019\\data\\2019-03\\2019-03-1-data.txt");

    if (!inFile)
    {
        cerr << "Unable to open file datafile.txt";
        exit(1);   // call system to stop
    }
    vector<Point> Pcoords1;
    vector<Point> Pcoords2;
    int counter = 0; //used to save the second lines coordinates
    vector<string> input;
    while(!inFile.eof())
    {
        string line;
        getline(inFile, line); //put a line of inFile into line.
        input = splitString(line,",");
        //To save the two different coordinates as we take data from the txt file.
        if(counter ==0)
        {
            Pcoords1 = getStructCoordinates(input);
        }
        else
        {
            Pcoords2 = getStructCoordinates(input);
        }
        counter++;
    }
    //Next step is to See if each line between two point intersect with a line between two points of the other wire.
    //Use the algorithm. for each pair of coordinates of each wire, test if they intersect. Loop through all lines for both wires. (should be 300*300 tests.)
    int minDistance = 999999;
    vector<Point> intersectingPoints;
    Point previousPoint1 = {0,0,0};
    Point previousPoint2 = {0,0,0};
    //loop through all points.
    for(Point currentPoint1 : Pcoords1)
    {
        for(Point currentPoint2 : Pcoords2)
        {
            if(doIntersect(previousPoint1, currentPoint1, previousPoint2, currentPoint2))
            {
                //1. find intersection point       //2. Save intersecting point in the intersectingPoints vector.
                intersectingPoints.push_back(getIntersectionPoint(previousPoint1, currentPoint1, previousPoint2, currentPoint2));
                cout << "Intersecting Point: (" << intersectingPoints.back().x << ", " << intersectingPoints.back().y << ")" << endl;
                if( abs(intersectingPoints.back().x)+abs(intersectingPoints.back().y) != 0) //skip the  intersection at (0,0)
                {
                    //int previous_point_to_intersection_point_distance_1 = abs(intersectingPoints.back().x - previousPoint1.x) + abs(intersectingPoints.back().y - previousPoint1.y);
                    //int previous_point_to_intersection_point_distance_2 = abs(intersectingPoints.back().x - previousPoint2.x) + abs(intersectingPoints.back().y - previousPoint2.y);

                    int previous_point_to_intersection_point_distance_1 = sqrt( pow(intersectingPoints.back().x - previousPoint1.x,2) + pow(intersectingPoints.back().y - previousPoint1.y,2)   );
                    int previous_point_to_intersection_point_distance_2 = sqrt( pow(intersectingPoints.back().x - previousPoint2.x,2) + pow(intersectingPoints.back().y - previousPoint2.y,2)   );

                    int total_distance_1 = previous_point_to_intersection_point_distance_1 + previousPoint1.distance;
                    int total_distance_2 = previous_point_to_intersection_point_distance_2 + previousPoint2.distance;
                    cout << "Distance: " << total_distance_1 + total_distance_2 << endl;

                    if( (total_distance_1 + total_distance_2) < minDistance )
                        minDistance = total_distance_1 + total_distance_2;
                }
            }
            previousPoint2 = currentPoint2;
        }
        previousPoint1 = currentPoint1;
        previousPoint2 = {0,0,0}; // Have to reset this point to the beginning point again.
    }
    cout << "Min distance is: " << minDistance << endl;
    return 0;
}

int main()
{
    Part1();
    return 0;
}
