#include <fstream>
#include <math.h>
#include <vector>
#include <sstream>
using namespace std;


vector<string> strSplit(string str, char del){
    stringstream ss(str);
    vector<string> elems;
    string item;
    while ( std::getline( ss, item, del ) ) {
        elems.push_back(item);
    }
    return elems;
}

double twoPointsDistance(Point a, Point b){
    return sqrt(
        pow( 
            (double) b.j
                      -
            (double) a.j
        , 2 )
        + pow(
            (double) b.i
                      -
            (double) a.i
        , 2 )
    );
}

Point * searchGoal(Matrix M){
    for (unsigned i = 0; i < M.lins; i++){
        for (unsigned j = 0; j < M.cols; j++){
            if ( M[i][j].type == 2 ){
                return &(M[i][j]);
            }
        }
    }
    return NULL;
}

Matrix initMatrix(string filename){
    Matrix M;
    // read and create lines
    vector<string> lines;
    ifstream file( filename );
    if ( file.is_open() ){
        string line;
        while ( getline( file, line ) ){
            lines.push_back(line);
        }
    }
    file.close();
    M.matrix = new Point*[ lines.size() ];
    M.lins = lines.size();
    // proccess each line
    for (int i = 0; i < M.lins; i++){
        vector<string> cols = strSplit( lines[i], ' ' );
        M.matrix[i] = new Point[cols.size()];
        M.cols = cols.size();
        for (int j = 0; j < M.cols; j++){
            M.matrix[i][j] = Point( stoi(cols[j]), i, j );
        }
    }
    M.goal = searchGoal(M);
    return M;
}



