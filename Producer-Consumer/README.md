# csc415-p5 

![AppVeyor](https://img.shields.io/appveyor/ci/gruntjs/grunt.svg)

## Part 1 - Threadracer

A extended version of the produce race condition. 
This assignment we add synchronization to eliminate of possible race conditions to produce
the correct number of threads.


Compile Instructions:
```
make threadracer
```
Run Instructions:
```
./threadracer
```

```c
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
```

## Problems I faced (Part 1)
Accumulating a global variable count of 10, instead of 100.
Problem was solved by setting my value to my globalId.

## Part 2 - Producer and Consumer

Implemented Producers and Consumer threads with a bounded buffer queue of N elements

Compile Instructions:
```
make pandc
```
Run Instructions:
```
./pandc
```

## Consumer Function

```c
void *consumer(void *param)
{
    consumers *consumer = (consumers *)param;
    int capacity = consumer->consumerFillCount;
    int cmsID = consumer->consumerId;

    int count = 0;

    while (count++ < capacity) // P * X / C
    {
        sleep(consumer->totalConsumerTime);
        sem_wait(&full);
        pthread_mutex_lock(&m);

        // set the cBufferIndex = dequeue();

        // prints item and consume
        printf("\n%d is consumed by thread-> %d", buffer[cBufferIndex], cmsID + 1); // consumption

        consumerArray[consumerCounter] = buffer[cBufferIndex];
        consumerCounter++;

        // iterate through the consumer buffer until reached N size buffers

        if (cBufferIndex == (bufferAmt - 1))
        {
            cBufferIndex = 0; // reset to 0
        }
        else
        {
            cBufferIndex++;
        }

        // sleep(consumer->totalConsumerTime);

        pthread_mutex_unlock(&m);
        sem_post(&empty);
    }

    pthread_exit(0);
}
```

## Producer Function

```c
void *producer(void *param)
{
    producers *producer = (producers *)param;
    int capacity = producer->producerFillCount;
    int prodId = producer->producerId;

    int count = 0;

    while (count++ < capacity) // X
    {
        // sleep(producer->totalProducerTime);
        sem_wait(&empty);
        pthread_mutex_lock(&m);

        printf("\n%d was produced by thread-> %d", count_items, prodId + 1);

        //enqueue item in buffer
        // buffer[pBufferIndex] = count_items;
        producerArray[producerCounter] = count_items;

        //enqueue item in buffer
        buffer[pBufferIndex] = count_items;
        // count++;
        count_items++;
        producerCounter++;
        buffer_capacity++;

        // iterate through the proudcer buffer until reached N size buffers
        if (pBufferIndex == (bufferAmt - 1))
        {
            pBufferIndex = 0; // reset
        }
        else
        {
            pBufferIndex++;
        }

        sleep(producer->totalProducerTime);

        pthread_mutex_unlock(&m);
        sem_post(&full);
    }

    pthread_exit(0);
}
```

## Problems I faced (Part 2)
I had issues printing out the proper values of my consumer and producer array. 
At times I got a bunch of zeros then values towards the end of each index.
Luckily this issue was later resolved. 

### What I learned from this assignment
How to make use of adding sycrhonization with the use of p_threads and semaphores. 
System programming is far more difficult to grasp in c than I thought. 
The use of semaphores states are changed atomically, which just isn't a simple variable, it's a larger construct. 


## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
