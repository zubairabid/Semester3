#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct evm {
  pthread_t thread_id;

} evm;

typedef struct voter {
  pthread_t thread_id;
  int voted;
  evm *voting_at;
} voter;

typedef struct booth {
  pthread_t thread_id;
  voter *voters[10000];
  evm *evms[10000];
  pthread_mutex_t lock;
} booth;

typedef struct argument {
  int booth;
} ags;

void polling_ready_evm(booth, int);
void voter_wait_for_evm(booth);
void voter_in_slot(booth);

void *boothr(void*);
void *vrobot(void*);
void *evmr(void*);

int number_voters[10000];
int number_evms[10000];

booth *boothdetails[10000];

int main() {

  int i;
  int number_booths;
  srand(time(0));

  printf("Enter number of booths\n");
  scanf("%d", &number_booths);

  for (i = 0; i < number_booths; i++) {
    scanf("%d", &number_voters[i]);
    scanf("%d", &number_evms[i]);
  }

  // Call each booth
  for (i = 0; i < number_booths; i++) {
    ags *argument = (ags*)malloc(sizeof(ags));
    argument->booth = i;
    pthread_create(boothdetails[i]->thread_id, NULL, boothr, (void*)argument);
  }

  return 0;
}

void *boothr(void *args) {
  int i;
  int bno = (ags*)args->booth;

  for (i = 0; i < number_voters; i++) {
    ags *argument = (ags*)malloc(sizeof(ags));
    argument->booth = bno;
    pthread_create(boothdetails[bno]->voters[i]->thread_id, NULL, vrobot, (void*)argument);
  }

  for (i = 0; i < number_evms; i++) {
    ags *argument = (ags*)malloc(sizeof(ags));
    argument->booth = bno;
    pthread_create(boothdetails[bno]->evms[i]->thread_id, NULL, evmr, (void*)argument);
  }
}

void *vrobot(void *args) {
  int booth = (ags*)args->booth;
  voter_wait_for_evm(boothdetails[booth]);


}

void *evmr(void *args) {
  int booth = (ags*)args->booth;
  int slots;
  do {
    slots = 1 + (int)(rand()/(double)RAND_MAX)*9;
    polling_ready_evm(boothdetails[booth], slots);

  } while(true);
}

void voter_wait_for_evm(booth bth) {
  pthread_cond_wait(&evm_wait, &bth->lock);
}

void polling_ready_evm(booth bth, int count) {
  pthread_cond_broadcast(&evm_wait);
  // printf("EVM %d at booth %d is ready with %d slots\n", );
  printf("EVM ready\n");
}
