#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#define NUM_THREADS 10

/**	
 * Can use the following struct for
 * the nanosleep function.
 * the first value is sleep time in seconds
 * the second vaue is sleep time in nanoseconds.
 * 
 * struct timespec ts = {2, 0 };
 * 
 * you can call nano sleep as nanosleep(&ts, NULL);
*/

struct timespec ts = {2, 0};
void executeThread(void *threadId);
int gloablId = 0;

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER; // creating a mutex that is ready to be locked!

int main()
{

    pthread_t threads[NUM_THREADS];
    pthread_attr_t attr;
    int t;
    int threadExecute;
    void *status;

    /* Initializing and set thread attr*/
    pthread_attr_init(&attr);

    // creating the thread

    for (t = 0; t < NUM_THREADS; t++)
    {

        threadExecute = pthread_create(&threads[t], &attr, executeThread, (void *)t);
        if (threadExecute)
        {
            fprintf(stderr, "ERROR; return code from pthread_create() is %d\n", threadExecute);
            exit(-1);
        }
    }

    // now to wait for the thread to finalize

    for (t = 0; t < NUM_THREADS; t++)
    {
        threadExecute = pthread_join(threads[t], &status);

        if (threadExecute)
        {
            fprintf(stderr, "ERROR; return code from pthread_create() is %d\n", threadExecute);
            exit(-1);
        }

        fprintf(stderr, "Each thread completed with final status: %d\n", (int)gloablId);
    }

    pthread_mutex_destroy(&m);

    fprintf(stderr, "Final value of thread count is: %d\n", gloablId);

    // pthread_mutex_destroy(&m);
    // free(&m);

    printf("Exiting Thread...Completed\n");

    pthread_exit(NULL);
}

void executeThread(void *threadId)
{
    int value = 0;
    int tid;
    tid = (int)threadId;

    pthread_mutex_lock(&m);

    value = gloablId;
    fprintf(stderr, "Hello I'm thread #%d\n", tid);
    nanosleep(&ts, NULL);

    value += 10;

    fprintf(stderr, "Thread local variable: %d and now Adding 10 -> Thread #%d\n", tid, value);

    nanosleep(&ts, NULL);

    gloablId = value;

    pthread_mutex_unlock(&m); //end of Critical Section

    pthread_exit((void *)threadId);
}
