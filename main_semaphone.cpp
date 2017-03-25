#include <iostream>
#include <thread>
#include <ctime>
#include "int_semaphore.h"

#define SEMNUMBER 1
#define NUMTHREAD 50
#define SLEEPTIMEMAX 4000
#define SLEEPTIMEMIN 200

using namespace std;

void *PrintHello(void *threadid);

int main(){
	init(SEMNUMBER);
	pthread_t threads[NUMTHREAD];
	int rc;
	srand(time(NULL));
	for (int i = 0; i < NUMTHREAD; ++i) {
		 rc = pthread_create(&threads[i], NULL, PrintHello, (void *)i);
		 if (rc){
			cout << "Error:unable to create thread: " << rc << endl;
		 }
		 else{
			cout << "Created thread: " << i << endl;
		 }
	}
	pthread_exit(NULL);
}


void *PrintHello(void *threadid)
{
	long tid;
	tid = (long)threadid;
	
	
	while(true){
		
		int rand_time = rand()%(SLEEPTIMEMAX-SLEEPTIMEMIN + 1) + SLEEPTIMEMIN;
		P();
		cout << "Critical section ID: " << tid <<" for "<<rand_time<<" ms"<< endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(rand_time));
		V();
		
	}
	pthread_exit(NULL);
}