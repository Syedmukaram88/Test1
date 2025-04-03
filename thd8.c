#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>

#define NUM_THREADS 5

void *tf1(void *arg);
void *tf2(void *arg);
void *tf3(void *arg);
void *tf4(void *arg);
void *tf5(void *arg);

int arr_times[NUM_THREADS];
int burst_times[NUM_THREADS]; 

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
        thread_ids[i] = i+1;
		
		printf("Enter the arrival time and burst time of Thread T%d: ", i+1);
		scanf("%d %d", &arr_times[i], &burst_times[i]);
	}
	
	for (j = 0; j < arr_times[0]; j++)
        sleep(1);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
        pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
        status = pthread_create(&threads[0], &attr, tf1, &thread_ids[0]);

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

void *tf1(void *arg) {
    int i;
	int thread_id = *(int *) arg;
    int quant=burst_times[thread_id];
	printf("/nCreated thread <%d> with arrival %d and burst %d",thread_id, arr_times[thread_id] ,burst_times[thread_id]);
	/*for (i=0; i < quant; i++){
		printf("T%d  ", thread_id);fflush(stdout);
		sleep(1);
	}*/
    
    pthread_exit(NULL);
}
