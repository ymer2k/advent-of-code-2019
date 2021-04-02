#include <iostream>
#include <fstream> //used to read txt files.
#include <math.h>       /* floor */
#include <string>     /*  insert   */
#include <string.h>   /*  strlen   */




using namespace std;

int repairComputer()
{
    ifstream inFile;
    inFile.open("C:\\Users\\Jonas\\Cprojects\\advent-of-code-2019\\data\\2019-02\\2019-02-1-data.txt");

    if (!inFile)
    {
        cerr << "Unable to open file datafile.txt";
        exit(1);   // call system to stop
    }


    int stepSize = 4;
    int dataArray[150] = {0};
    int i; //represents the ith element if it was an int array


    char line[150];
    while(inFile >> line)
    {
        string str = line;
        cout << str << endl;

        //replace position 1 with the value 12 and replace position 2 with the value 2. Keep in mind the commas
        str.replace(2,1,"12");
        str.replace(5,1,"2");
        //cout << str << endl;

        //Did this to make it easier to extract the first and final value of the string
        str.insert(0,",");
        str.append(",");
        //cout << str << endl;

        //transform the char array into an int array to make it easier to manipulate.
        size_t start1, start2 = 0;
        size_t length = str.length();
        for(i=0; start2<length-1; i++)
        {
            start1 = str.find(",",start2);
            start2 = str.find(",",start1+1);

            string currentValue = string(&str[start1+1], &str[start2]);
            cout << currentValue << endl;
            dataArray[i] = stoi(currentValue);
        }

        int sum = 0;
        int product = 0;
        for(int k = 0; k < i; k += stepSize)
        {
            if(dataArray[k] == 99)
            {
                //finish
                break;
            }
            else if(dataArray[k] == 1)
            {
                sum = dataArray[dataArray[k+1]] + dataArray[dataArray[k+2]];
                dataArray[dataArray[k+3]] = sum;
            }
            else if(dataArray[k] == 2)
            {
                product = dataArray[dataArray[k+1]] * dataArray[dataArray[k+2]];
                dataArray[dataArray[k+3]] = product;
            }
        }

    }

    //print int array
    for(int p=0; p < i ; p++)
    {
        cout << dataArray[p] << ",";
    }
    cout << "\n" << "Answer: " << dataArray[0] << endl;
    return 0;
}



int main()
{
    repairComputer();
    return 0;
}
