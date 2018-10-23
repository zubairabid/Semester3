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
  evm voting_at;
} voter;

typedef struct booth {
  voter voters[10000];
  evm evms[10000];
  pthread_mutex_t lock;
} booth;

typedef struct argument {
  int booth;
} ags;

void polling_ready_evm(booth, int);
void voter_wait_for_evm(booth);
void voter_in_slot(booth);

void *booth(void*);
void *vrobot(void*);
void *evmr(void*);

int number_voters[10000];
int number_evms[10000];

booth boothdetails[10000];

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

  return 0;
}

void *booth(void *args) {
  int i;
  int bno = args->booth;

  for (i = 0; i < number_voters; i++) {
    ags *argument = (ags*)malloc(sizeof(ags));
    argument->booth = bno;
    pthread_create(boothdetails[bno]->voters[i]->thread_id, NULL, vrobot, argument);
  }

  for (i = 0; i < number_evms; i++) {
    ags *argument = (ags*)malloc(sizeof(ags));
    argument->booth = bno;
    pthread_create(boothdetails[bno]->evms[i]->thread_id, NULL, evm, argument);
  }
}

void *vrobot(void *args) {
  int booth = args->booth;
  voter_wait_for_evm(boothdetails[booth]);


}

void *evmr(void *args) {
  int booth = args->booth;
  int slots;
  do {
    slots = 1 + (int)(rand()/(double)RAND_MAX)*9;
    polling_ready_evm(boothdetails[booth], slots);

  } while(true);
}

void voter_wait_for_evm(booth) {
  pthread_cond_wait(&evm_wait, &booth->lock);
}

void polling_ready_evm(booth, int) {
  pthread_cond_broadcast(&evm_wait);
}
