#include <iostream>
#include <fstream> //used to read txt files.

//#include <string>     /*  insert   */
//#include <string.h>   /*  strlen   */
//#include <vector>   /* vector */
//#include <cstdlib> /* abs()  */
//#include <math.h>       /* sqrt */



using namespace std;


int Part1()
{
    ifstream inFile;
    inFile.open("C:\\Users\\Jonas\\Cprojects\\advent-of-code-2019\\data\\2019-04\\2019-04-1-data.txt");

    if (!inFile)
    {
        cerr << "Unable to open file datafile.txt";
        exit(1);   // call system to stop
    }


}

int main()
{
    Part1();
    return 0;
}
