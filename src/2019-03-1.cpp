#include <iostream>
#include <fstream> //used to read txt files.
#include <string>     /*  insert   */
#include <string.h>   /*  strlen   */
#include <vector>   /* vector */



using namespace std;




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
    return input;
}

std::vector<int> getCoordinates(vector<string> input)
{ /* Returns coordinates for each step */
    int x_pos = 0;
    int y_pos = 0;
    std::vector<int> coordinates;
    for (string element : input)
    {
        if(element.compare(0,1,"R") == 0)
            x_pos += stoi(element.substr(1,string::npos));
        if(element.compare(0,1,"D") == 0)
            y_pos -= stoi(element.substr(1,string::npos));
        if(element.compare(0,1,"L") == 0)
            x_pos -= stoi(element.substr(1,string::npos));
        if(element.compare(0,1,"U") == 0)
            y_pos += stoi(element.substr(1,string::npos));

        //Update coordinates for this step.
        coordinates.push_back(x_pos);
        coordinates.push_back(y_pos);
    }
    return coordinates;
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
    vector<int> coords1;
    vector<int> coords2;
    int counter = 0; //used to save the second lines coordinates
    vector<string> input;
    while(!inFile.eof())
    {
        string line;
        getline(inFile, line); //put a line of inFile into line.
        input = splitString(line,",");

        int x_pos=0;
        int y_pos=0;
        for (string element : input)
        {
            if(element.compare(0,1,"R") == 0)
                x_pos += stoi(element.substr(1,string::npos));
            if(element.compare(0,1,"D") == 0)
                y_pos -= stoi(element.substr(1,string::npos));
            if(element.compare(0,1,"L") == 0)
                x_pos -= stoi(element.substr(1,string::npos));
            if(element.compare(0,1,"U") == 0)
                y_pos += stoi(element.substr(1,string::npos));
        }
        //To save the two different coordinates.
        if(counter ==0)
           {
            coords1 = getCoordinates(input);
           }else
           {
                coords2 = getCoordinates(input);
           }
        counter++;
    }
    //Next step is to See if each line between two point intersect with a line between two points of the other wire.
    //Use the algorithm. for each pair of coordinates of each wire, test if they intersect. Loop through all lines for both wires. (should be 300*300 tests.)

    return 0;
}

int main()
{
    Part1();
    return 0;
}
