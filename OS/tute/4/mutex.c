#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

void *func(void *);

pthread_mutex_t mutex;

int main() {
    pthread_t tid;
    
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_lock(&mutex);

    pthread_create(&tid, NULL, func, NULL);

    // Wait for user input
    getchar();
    
    pthread_mutex_unlock(&mutex);

    // Wait for thread to finish
    pthread_join(tid, NULL);
        
    return 0;
}

void *func(void *arg) {
    pthread_mutex_lock(&mutex);

    printf("func called\n");
    
    pthread_mutex_unlock(&mutex);
}
