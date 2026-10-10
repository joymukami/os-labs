#include <stdio.h>
#include <pthread.h>

int counter = 0;
pthread_mutex_t lock; // Step 6: Mutex for protection

// Thread function
void* worker(void* arg) {
    for (int i = 0; i < 10000; i++) {
        // Protect the shared counter
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_mutex_init(&lock, NULL);

    // Step 1: Create two threads
    pthread_create(&t1, NULL, worker, NULL);
    pthread_create(&t2, NULL, worker, NULL);

    // Step 3: Wait for both threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&lock);
    
    printf("Final Counter Value: %d (Expected: 20000)\n", counter);
    return 0;
}

