#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
using namespace std;

//#define LINS 40
//#define COLS  60

#define LINS 8000
#define COLS 8000

int main(int argc, char *argv[])
{
    srand(time(NULL));
    ofstream mfile;
    mfile.open ("genMatrix.txt");
    int iGoal = rand() % LINS;
    int jGoal = rand() % COLS;
    for (int i = 0; i < LINS; i++){
        for (int j = 0; j < COLS; j++){
            if ( i == iGoal && j == jGoal )
                mfile << "2";
            else
                mfile << ( rand()%5 == 0 ?  "1" : "0" );
            if ( j != COLS-1 ){
                mfile << " ";
            }
        }
        if ( i != LINS-1 ){
            mfile << "\n";
        }
    }
    mfile.close();
    return 0;
}
