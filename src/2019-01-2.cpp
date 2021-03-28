#include <iostream>
#include <fstream> //used to read txt files.
#include <math.h>       /* floor */

using namespace std;

int sumFuelReq()
{
    ifstream inFile;
    inFile.open("C:\\Users\\Jonas\\Cprojects\\advent-of-code-2019\\data\\2019-01\\2019-01-1-data.txt");

    if (!inFile)
    {
        cerr << "Unable to open file datafile.txt";
        exit(1);   // call system to stop
    }

    char line[50];
    int sum=0;
    double reqFuel =0;
    while(inFile >> line)
    {

        cout << line << endl;
        int number = std::stoi(line);
        printf("number:%d\n",number);
        reqFuel = floor((number/3))-2;
        cout << reqFuel << endl;
        sum += reqFuel;
        while(reqFuel >= 0)
        {
            reqFuel = floor((reqFuel/3))-2;
            if(reqFuel > 0)
            {
                sum += reqFuel;
            }

        }
    }
    cout << "Total required fuel:" << sum << endl;
    return 0;
}



int main()
{
    sumFuelReq();
    return 0;
}
