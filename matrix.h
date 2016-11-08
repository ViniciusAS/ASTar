#include <string>
using namespace std;

/*
 *   Point types:
 *      0: nothing
 *      1: obstacle
 *      2: goal
*/

struct Point {
    int type;
    unsigned i, j;

    double distance = -1;

    int visit = -1;
    string label = " ";

    Point(){}

    Point(int type, int i, int j){
        this->type = type;
        this->i    = i;
        this->j    = j;
        switch (type) {
            case 1: 
                label = "-";
                break;
            case 2: 
                label = "G";
                break;
        }
    }


    Point operator[](int index)
    {
       return *( this + index );
    }
};

struct Matrix{

    Point **matrix;
    unsigned lins, cols;

    Point *goal;

    void print(){
        cout << "Matrix: \n";
        for (int i = 0; i < lins; i++) {
            for (int j = 0; j < cols; j++) {
                cout << matrix[i][j].label << " ";
            }
            cout << endl;
        }
        cout << endl;
    }


    Point * operator[](int index)
    {
       return *( this->matrix + index );
    }
};







