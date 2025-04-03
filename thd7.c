#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>

#define NUM_THREADS 5

void *thread_function(void *arg);
int time_quantums[NUM_THREADS] = {10, 12, 2, 4, 8}; // Time quantum in milliseconds for each thread

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    
    int i, status;

    // Set the thread attributes for all threads
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    // Set the scheduling policy to Round Robin
    pthread_attr_setschedpolicy(&attr, SCHED_OTHER);

    // Create and run the threads
    for (i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
		printf("Thread %d needs %llu quantum\n", thread_ids[i], time_quantums[i]); fflush(stdout);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
        pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED)

        // Create the threads
        status = pthread_create(&threads[i], &attr, thread_function, &thread_ids[i]);

        if (status != 0) {
            printf("Error creating thread: %d\n", status);
        }
    }

    // Wait for all threads to finish
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_attr_destroy(&attr);

    return 0;
}

void *thread_function(void *arg) {
    int i;
	int thread_id = *(int *) arg;
    int quant=time_quantums[thread_id];
	
	for (i=0; i < quant; i++){
		printf("T%d  ", thread_id);fflush(stdout);
		sleep(1);
	}
    
    pthread_exit(NULL);
}
/*
In this code, we first define the number of threads to create (NUM_THREADS) and 
an array of time quantums for each thread (time_quantums). 

We then initialize a pthread_attr_t object and set the scheduling policy to Round Robin using the pthread_attr_setschedpolicy function.

Next, we create a loop to create each thread, where we set the thread attributes for each thread. 
We set the PTHREAD_EXPLICIT_SCHED attribute to indicate that the thread scheduling attributes are explicitly set, 
and the pthread_attr_setdetachstate function to indicate that the thread should be joinable.

We then set the time quantum for the thread using a struct sched_param object and the pthread_attr_setschedparam function. 
We set the sched_rr_quantum field of the sched_param object to the time quantum for the thread in nanoseconds, 
which is calculated by multiplying the time quantum in milliseconds by 1,000,000.

Finally, we create the thread using the pthread_create function and wait for all threads to finish using the pthread_join function.

The thread_function function simply prints a message indicating that the thread has started and finished, and then exits.
*/
