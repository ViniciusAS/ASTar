#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <cstdio>
#include <ctime>
using namespace std;
#include "matrix.h"
#include "utils.h"

Matrix M;


// search for neighbors that are'nt obstacles
vector<Point*> validNeighbors(Point &p){
    vector<Point*> ns;
    unsigned I = p.i;
    unsigned J = p.j;
    // filter for only valid matrix positions
    unsigned bI = ( I == 0         ) ? I : I-1;
    unsigned eI = ( I == M.lins-1  ) ? I : I+1;
    unsigned bJ = ( J == 0         ) ? J : J-1;
    unsigned eJ = ( J == M.cols-1  ) ? J : J+1;
    // all positions around and in it
    for (int i = bI; i <= eI; i++){
        for (int j = bJ; j <= eJ; j++){
            if ( ( i != I || j != J  )  // not the actual, just neighbors
                && M[i][j].type != 1    // not obstacles
            ) {
                ns.push_back( &M[i][j] );
            }
        }
    }
    return ns;
}

// calculate distance of several neighbors
void calculateNeighborsDistances(vector<Point*> &neighbors){
    for (Point *neighbor : neighbors){
        if (neighbor->distance == -1){
            neighbor->distance = twoPointsDistance(*neighbor, *(M.goal));
        }
    }
}


void finishSearch(Point &current, int res);


int subSearch(Point &current);

int diferentSearch(Point &current, vector<Point*> neighbors);

// THE search
int search(Point &current, bool callDiferentSearch)
{
    // if the distance is not calculated, calculate
    if (current.distance == -1){
        current.distance = twoPointsDistance(current, *(M.goal));
    }

    // if is the goal, stop
    if ( current.distance == 0 ){
        cout << "Distance 0: goal found" << endl;
        return 1;
    }

    // mark as used way
    current.label = "x";
    current.visit = 1;

    // search for neighbors
    vector<Point*> neighbors = validNeighbors( current );

    // if there's no more valid neighbors, stop
    if ( neighbors.size() == 0 ){
        cout << "Not enough neighbors\n";
        current.label = " ";
        return 0;
    }

    // order by distance
    calculateNeighborsDistances( neighbors );
    std::sort(neighbors.begin(), neighbors.end(), [](Point *a, Point *b) {
        return (  a->distance < b->distance  );
    });

    //M.print();
    //cout << "pressione qualquer tecla para continuar...";
    //getchar();

    // continue the recursive search
    if ( callDiferentSearch ){
        if (diferentSearch(current, neighbors)){
            finishSearch(current,1);
            return 1;
        }
    } else {
        for (Point *closerPoint : neighbors)
        {
            // if the closer point is a neighbor, stop
            if (closerPoint->visit == 1){
                break;
            }
            // if was not visited yet
            if (closerPoint->visit == -1){
                // if child find the way 
                if (subSearch( *closerPoint )){
                    finishSearch(current,1);
                    return 1;
                }
            }
        }
    }
    finishSearch(current,0);
    return 0;
}

void finishSearch(Point &current, int res){
    if ( res == 0 ) {
        // remove from used path, but still visited
        current.label = " ";
        current.visit = 2;
    }
}




