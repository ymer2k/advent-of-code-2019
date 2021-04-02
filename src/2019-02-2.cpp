#include <iostream>
#include <fstream> //used to read txt files.
#include <string>     /*  insert   */
#include <string.h>   /*  strlen   */
#include <vector>   /* vector */

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
        cout << str << endl;

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
            //cout << currentValue << endl;
            dataArray[i] = stoi(currentValue);
        }
        vector<int> v(begin(dataArray), end(dataArray)); //copy over content of dataArray to v.
        vector<int> vOrignal(begin(dataArray), end(dataArray));

        //loop through the possible combinations
        for(int nr1 = 0; nr1 <= 99; nr1++)
        {
            for(int nr2 = 0; nr2<=99; nr2++)
            {
                v=vOrignal; //reset the vector each loop;
                //apply new starting combination
                v[1]=nr1;
                v[2]=nr2;

                //Run the "program"
                int sum = 0;
                int product = 0;
                for(int k = 0; k < i; k += stepSize)
                {
                    if(v[k] == 99)
                    {
                        //finish
                        break;
                    }
                    else if(v[k] == 1)
                    {
                        sum = v[v[k+1]] + v[v[k+2]];
                        v[v[k+3]] = sum;
                    }
                    else if(v[k] == 2)
                    {
                        product = v[v[k+1]] * v[v[k+2]];
                        v[v[k+3]] = product;
                    }
                }
                //check if correct output
                if(v[0] == 19690720)
                {
                    for(int q=0; q<150; q++)
                    {
                        cout << v[q] << "," ;
                    }
                    cout << "\nnoun = " << nr1 << " verb = " << nr2 << endl;
                    cout << "\n" << "Answer: " << nr1*100+nr2 << endl;
                    return 0;
                }
            }
        }
    }
    return 0;
}

int main()
{
    repairComputer();
    return 0;
}
