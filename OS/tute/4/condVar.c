#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

void *func(void *);

pthread_mutex_t mutex;
pthread_cond_t cond;
int var;

int main() {

    pthread_t tid;

    var = 0;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_create(&tid, NULL, func, NULL);

    sleep(1);

    pthread_mutex_lock(&mutex);
    printf("MAIN acquired lock\n");

    // Wait for user input
    getchar();
    // Change var
    var = 1;

    // Wake up the waiting thread
    printf("MAIN signaled\n");
    pthread_cond_signal(&cond);

    sleep(5);

    printf("MAIN released lock\n");
    pthread_mutex_unlock(&mutex);

    // Wait for thread to finish
    pthread_join(tid, NULL);

    return 0;
}

void *func(void *arg) {
    pthread_mutex_lock(&mutex);
    printf("THREAD acquires lock\n");

    if(var == 0) {
    	printf("THREAD waits for signal\n");
    	// Give up lock and wait for signal
    	pthread_cond_wait(&cond, &mutex);
    	printf("THREAD got signal\n");
    }
    printf("THREAD func here\n");

    printf("THREAD released lock\n");
    pthread_mutex_unlock(&mutex);
}
