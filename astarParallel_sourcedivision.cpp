#include <iostream>
#include <queue>
#include <pthread.h>
using namespace std;
#include "astar.cpp"



void * parallelSearch(void *ptr){
    return (void*) new int(subSearch( *(Point*) ptr ));
}

int joinThread(pthread_t &t){
    void *num;
    pthread_join(t,&num);
    return *(int*) num;
}

int diferentSearch(Point &current, vector<Point*> neighbors){
    pthread_t *threads = new pthread_t[neighbors.size()];
    int thread = 0;
    for (Point *closerPoint : neighbors){
        // if the closer point is a neighbor, stop
        if (closerPoint->visit == 1){
            return 0;
        }
        // if was not visited yet
        if (closerPoint->visit == -1){
            // if child find the way 
            pthread_create(&(threads[thread]),NULL,parallelSearch,closerPoint);
            thread++;/*
            if (subSearch( *closerPoint )){
                finishSearch(current,1);
                return 1;
            }*/
        }
    }
    for (int i = 0; i < neighbors.size(); i++){
        if (joinThread(threads[i])){
            return 1;
        }
    }
    return 0;
}

int subSearch(Point &current)
{
     return search(current,false);
/*
    if ( parallelSearch(current) ){
        pathFound = true;
        return 1;
    }
    return 0;
*/
}

int main(int argc, char *argv[])
{

    M = initMatrix("./genMatrix.txt");

    clock_t clockCount = clock();
    
    //startThreads();

    if ( search( M[0][0], true ) )
    {
        cout << "Found a path\n";
    } 
        else 
    {
        cout << "Did not found a path\n";
    }

    //joinThreads();

    clockCount = clock() - clockCount;

    double timeSpent = clockCount / (double) CLOCKS_PER_SEC;

    //M.print();
    
    cout << "Time spent: " << timeSpent << endl;


    return 0;
}

