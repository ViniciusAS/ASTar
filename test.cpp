#include <iostream>
#include <pthread.h>
using namespace std;


void inc(int &x){
    for (int i = 0; i < 10; i++){
        cout << x << " ";
        x++;
    }
}

void *incT(void *x_ptr){
    inc(*(int*) x_ptr);
    return NULL;
}

int main(int argc, char *argv[]) {
	pthread_t thread_A;
    
    int x = 0;
    
    if ( pthread_create(&thread_A, NULL, incT, &x) ){
        cout << "Thread 'A' NOT created" << endl;
    }
    inc(x);

	if(pthread_join(thread_A, NULL)) {

	    cout << "Thread dead\n" << endl;
	    return 2;
	}

    cout << endl << x << endl;
    return 0;

}
