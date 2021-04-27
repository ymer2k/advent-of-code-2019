#include <iostream>
#include <fstream> //used to read txt files.

#include <string>     /*  insert   */
//#include <string.h>   /*  strlen   */
#include <vector>   /* vector */
//#include <cstdlib> /* abs()  */
//#include <math.h>       /* sqrt */

using namespace std;

int Part2()
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

    std::size_t pos;
    pos = line.find("-");
    string min = line.substr(0,pos);
    string max = line.substr(pos+1,string::npos);
    cout << "Min: " << min << "Max: " << max << endl;

    cout << min[0] << " " << min[1] << endl;

    vector<string> OkPasswords;
    vector<int> test2Vec;
    //loop through all possible numbers.
    for(int i=stoi(min); i <= stoi(max); i++)
    {
        string current = to_string(i);
        int test1=1;
        int test2Counter =0;
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

            if( current[k] == current[k+1])
            {
                test2Counter++; // count how many times we find the same number. If at least one number is a pair (2 of the same number) it is OK!
            }
            else
            {
                test2Vec.push_back(test2Counter);
                test2Counter=0;
            }
        }

        test2Vec.push_back(test2Counter); //add the test2Counter when we reach the end of the password.
        //if passed both tests add to OkPasswords.
        for(int element : test2Vec)
        {
            if( test1 == 1 && element == 1 )
            {
                OkPasswords.push_back(current);
                break; //at this point since test1 == 1 and we have at least one pair and two adjacent matching digits are not part of a larger group of matching digits
                //We know that the password is OK and we can break and continue with the next password. (otherwise we will count the same password several times. Eg 112233
            }
        }

        //reset tests
        test1 = 1;
        test2Vec.clear();
    }
    cout << "Nr of OK passwords: " << OkPasswords.size() << endl;

    return 0;
}

int main()
{
    Part2();
    return 0;
}
