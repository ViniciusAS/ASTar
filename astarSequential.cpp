#include <iostream>
using namespace std;
#include "astar.cpp"

int diferentSearch(Point &current, vector<Point*> neighbors){}

int subSearch(Point &current)
{
     return search(current,false);
}

int main(int argc, char *argv[])
{

    M = initMatrix("./matrix.txt");

    clock_t clockCount = clock();

    if ( search( M[0][0], false ) )
    {
        cout << "Found a path\n";
    } 
        else 
    {
        cout << "Did not found a path\n";
    }

    clockCount = clock() - clockCount;

    double timeSpent = clockCount / (double) CLOCKS_PER_SEC;

    M.print();
    
    cout << "Time spent: " << timeSpent << endl;

    return 0;
}
