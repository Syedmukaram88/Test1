#include <pthread.h>

int pthread_create( pthread_t* thread,
                    const pthread_attr_t* attr,
                    void* (*start_routine)(void* ),
                    void* arg );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RETURN VALUE
If successful, the pthread_create() function returns zero. Otherwise, an error number is returned to indicate the error.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ERRORS
The pthread_create() function will fail if:
[EAGAIN]
The system lacked the necessary resources to create another thread, or the system-imposed limit on the total number of threads in a process PTHREAD_THREADS_MAX would be exceeded.
[EINVAL]
The value specified by attr is invalid.
[EPERM]
The caller does not have appropriate permission to set the required scheduling parameters or scheduling policy.
The pthread_create() function will not return an error code of [EINTR].
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
attr


void pthread_exit(void *retval);

Parameters: This method accepts a mandatory parameter retval which is the pointer to an integer that stores the return status of the thread terminated. The scope of this variable must be global so that any thread waiting to join this thread may read the return status.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int pthread_join(pthread_t th, 
                 void **thread_return);
				 
Parameter: This method accepts following parameters:

th: thread id of the thread for which the current thread waits.
thread_return: pointer to the location where the exit status of the thread mentioned in th is stored.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
thread_self: used to get the thread id of the current thread.
Syntax:

pthread_t pthread_self(void);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
pthread_equal: compares whether two threads are the same or not. If the two threads are equal, the function returns a non-zero value otherwise zero.
Syntax:

int pthread_equal(pthread_t t1, 
                  pthread_t t2);
Parameters: This method accepts following parameters:

t1: the thread id of the first thread
t2: the thread id of the second thread
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
