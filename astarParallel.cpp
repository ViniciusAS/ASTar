#include <iostream>
#include <queue>
#include <pthread.h>
using namespace std;
#include "astar.cpp"

#define nThreads 3

pthread_t threads[nThreads];

bool pathFound = false;

struct searchWaiting{

    Point *p;
    int ret = -1;
    pthread_mutex_t lock;

    searchWaiting(Point *p){
        this->p = p;
    }

    void wait(){
        pthread_mutex_lock(&lock);
        pthread_mutex_lock(&lock);
    }
};

queue<searchWaiting> searchs;
pthread_mutex_t searchsMutex;

//void * searchAdapt(void *current){
//    return (void*) new int(search( *(Point*) current ));
//}

void *solve(void *none){
    while (!pathFound){
        pthread_mutex_lock(&searchsMutex);
        if ( searchs.size() > 0 ){
            searchWaiting s = searchs.front();
            searchs.pop();
            pthread_mutex_unlock(&searchsMutex);

            s.ret = search(*(s.p));
            pthread_mutex_unlock(&(s.lock));
        } else 
            pthread_mutex_unlock(&searchsMutex);
    }
    return NULL;
}

void startThreads(){
    int started = nThreads;
    for (int i = 0; i < nThreads; i++){
        if ( pthread_create(&threads[i], NULL, solve, NULL) ){
            cout << "Error on thread "<< i <<" create\n";
            started--;
        }
    }
    cout << started << " Threads started" << endl;
}

void joinThreads(){
    for (int i = 0; i < nThreads; i++){
        if (pthread_join(threads[i], NULL) ){
            cout << "Thread "<< i <<" dead\n";
        }
    }
}

// use of multithreading for time improvement
int parallelSearch(Point &closerPoint){
    searchWaiting s( &closerPoint );
    searchs.push(s);
    s.wait();
    return s.ret;
}



int subSearch(Point &current)
{
    if ( parallelSearch(current) ){
        pathFound = true;
        return true;
    }
    return false;
}

int main(int argc, char *argv[])
{

    M = initMatrix("./genMatrix.txt");

    clock_t clockCount = clock();
    
    startThreads();

    if ( search( M[0][0] ) )
    {
        cout << "Found a path\n";
    } 
        else 
    {
        cout << "Did not found a path\n";
    }

    joinThreads();

    clockCount = clock() - clockCount;

    double timeSpent = clockCount / (double) CLOCKS_PER_SEC;

    //M.print();
    
    cout << "Time spent: " << timeSpent << endl;


    return 0;
}

