#include <iostream>
using namespace std;
#include "astar.cpp"


int subSearch(Point &current)
{
    return search(current);
}

int main(int argc, char *argv[])
{

    M = initMatrix("./genMatrix.txt");

    clock_t clockCount = clock();

    if ( search( M[0][0] ) )
    {
        cout << "Found a path\n";
    } 
        else 
    {
        cout << "Did not found a path\n";
    }

    clockCount = clock() - clockCount;

    double timeSpent = clockCount / (double) CLOCKS_PER_SEC;

    //M.print();
    
    cout << "Time spent: " << timeSpent << endl;

    return 0;
}
