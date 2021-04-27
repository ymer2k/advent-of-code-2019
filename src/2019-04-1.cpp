#include <iostream>
#include <fstream> //used to read txt files.

#include <string>     /*  insert   */
//#include <string.h>   /*  strlen   */
#include <vector>   /* vector */
//#include <cstdlib> /* abs()  */
//#include <math.h>       /* sqrt */

using namespace std;

int Part1()
{
    ifstream inFile;
    inFile.open("C:\\Users\\jonas\\Cprojects\\advent-of-code-2019\\data\\2019-04\\2019-04-1-data.txt");

    if (!inFile)
    {
        cerr << "Unable to open file datafile.txt";
        exit(1);   // call system to stop
    }

    string line;
    getline(inFile, line);
    cout << line << endl;

    //seperate the min max ranges.
    std::size_t pos;
    pos = line.find("-");
    string min = line.substr(0,pos);
    string max = line.substr(pos+1,string::npos);
    cout << "Min: " << min << "Max: " << max << endl;

    cout << min[0] << " " << min[1] << endl;

    vector<string> OkPasswords;
    //loop through all possible numbers.
    for(int i=stoi(min); i <= stoi(max); i++)
    {
        string current = to_string(i);
        //string next = to_string(i+1);
        int test1=1;
        int test2=0;
        // loop through all numbers
        for(int k=0; k < (min.length()-1); k++ )
        {

            //check if next number is larger or same
            if( current[k] <= current[k+1] )
            {
                test1=1;
            }
            else
            {
                test1=0;
                break;
            }

            //check if at least two neighbour numbers are same
            if( current[k] == current[k+1] )
                test2=1;
        }
        //if passed both tests add to OkPasswords.
        if(test1 && test2)
            OkPasswords.push_back(current);
    }
    cout << "Nr of OK passwords: " << OkPasswords.size() << endl;
    return 0;
}

int main()
{
    Part1();
    return 0;
}
