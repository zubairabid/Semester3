#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *referee(void*);
void *player(void*);

void referee_startGame(int);
void referee_enterCourt(int);
void referee_enterAcademy(int);
void referee_meetOrganizer(int);
void referee_adjustEquipment(int);

void player_warmUp(int);
void player_enterCourt(int);
void player_enterAcademy(int);
void player_meetOrganizer(int);

pthread_mutex_t organizer;
pthread_mutex_t pres;
pthread_mutex_t mutp[20000];
pthread_mutex_t mutr[10000];
pthread_cond_t condp[20000];
pthread_cond_t condr[10000];

pthread_t ref[10000];
pthread_t plr[20000];

int locked = 0;
int tempc = 2;

double timer = 0.0f;

int main() {

  // Initializing variables, not much to see here
  srand(time(0)); // Helper: setting a seed for rand
  int n, i, j, index, time_to_next = 0;
  int playercount, refcount, playat = 1, refat = 1;
  double playerprob, temp;
  pthread_mutex_init(&organizer, NULL);
  pthread_mutex_init(&pres, NULL);
  for(i = 0; i < 20000; i++) {
    if (i < 10000) {
      pthread_cond_init(&condr[i], NULL);
      pthread_mutex_init(&mutr[i], NULL);
    }
    pthread_cond_init(&condp[i], NULL);
    pthread_mutex_init(&mutp[i], NULL);
  }


  // Take input as n, for number of referees and half the number of players
  printf("Enter number n, given 3n people will come in total: \n");
  scanf("%d", &n);
  playercount = 2 * n;
  refcount = n;

  do {

    if (time_to_next <= 0) {
      time_to_next = 1 + (rand()/(double)RAND_MAX)*3;

      // Creating a new player
      // As per question requirements
      playerprob = ((double)playercount/(double)(playercount+refcount));
      temp = rand()/(double)RAND_MAX;
      if ( (playercount > 0) && ((refcount <= 0) || (temp <= playerprob)) ) {
        // New player is created
        index = 2*n - playercount + 1;
        pthread_create(&plr[index], NULL, player, (void *)index);
        playercount--;
      } else {
        if(refcount > 0) {
          // New referee is created
          index = n - refcount + 1;
          pthread_create(&plr[index], NULL, referee, (void *)index);
          refcount--;
        }
      }

    }


    sleep(1);


    // Alloting groups, if organizer is free and people available
    if (!locked) {
      if ( ((2*n-playercount)-playat+1) < 2 || ((n-refcount)-refat+1) < 1 ) {

        timer+=1;
        time_to_next--;
        if(playat >= 2*n || refat > n) {
          break;
        }

        continue;
      }
      pthread_mutex_lock(&organizer);
      locked = 1;

      pthread_cond_signal(&condp[playat]);
      pthread_cond_signal(&condp[playat+1]);
      // pthread_join(plr[playat], NULL);
      // pthread_join(plr[playat+1], NULL);
      pthread_cond_signal(&condr[refat]);
      // pthread_join(ref[refat], NULL);

      tempc = 2;
      playat += 2;
      refat++;
    }

    timer+=1;
    time_to_next--;
    // printf("%d\n", time_to_next);
  } while (1);
  // for(i = 1; i <= n; i++) {
  //   pthread_join(ref[i], NULL);
  // }
  return 0;
}

void *referee(void *args) {
  int index = (int) args;
  // Enter the academy
  referee_enterAcademy(index);

  // Try to meet organizer (mutex)(print)
  // Meet organizer (lock rest out)(print)
  pthread_mutex_lock(&organizer);
  locked = 1;
  referee_meetOrganizer(index);
  locked = 0;
  pthread_mutex_unlock(&organizer);

  pthread_mutex_lock(&mutr[index]);
  // Wait till signal for new match (wait)
  pthread_cond_wait(&condr[index], &mutr[index]);

  // Lock organizer
  //  Enter court (print)
  referee_enterCourt(index);

  //  Adjust equipment (wait) (print)
  referee_adjustEquipment(index);
  sleep(0.5);
  // timer += 0.5;

  while(tempc > 0);

  //  Start match (rint)
  referee_startGame(index);

  // Unlock organizer
  pthread_mutex_unlock(&organizer);
  locked = 0;
}

void *player(void *args) {
  int index = (int) args;
  // Enter the academy
  player_enterAcademy(index);

  // Try to meet organizer (mutex)(print)
  // Meet organizer (lock rest out)(print)
  pthread_mutex_lock(&organizer);
  locked = 1;
  player_meetOrganizer(index);
  locked = 0;
  pthread_mutex_unlock(&organizer);

  pthread_mutex_lock(&mutp[index]);
  // Wait till signal for new match (wait)
  pthread_cond_wait(&condp[index], &mutp[index]);

  // Lock organizer
  pthread_mutex_lock(&pres);
  //  Enter court (print)
  player_enterCourt(index);

  //  Warm up (wait) (print)
  player_warmUp(index);
  pthread_mutex_unlock(&pres);


  sleep(1);
  tempc--;
  // timer += 1;
  // Unlock organizer
}

// Define player actions

void player_meetOrganizer(int id) {
  printf("\x1B[37m%0.1f : Player %d met the organizer\n", timer, id);
}
void player_enterAcademy(int id) {
  printf("\x1B[37m%0.1f : Player %d entered the Academy\n", timer, id);
}
void player_enterCourt(int id) {
  printf("\x1B[33m%0.1f : Player %d entered the court\n", timer, id);
}
void player_warmUp(int id) {
  printf("\x1B[34m%0.1f : Player %d is warming up\n", timer, id);
}


// Define referee actions

void referee_meetOrganizer(int id) {
  printf("\x1B[37m%0.1f : Referee %d met the organizer\n", timer, id);
}
void referee_enterAcademy(int id) {
  printf("\x1B[37m%0.1f : Referee %d entered the Academy\n", timer, id);
}
void referee_enterCourt(int id) {
  printf("\x1B[33m%0.1f : Referee %d entered the court\n", timer, id);
}
void referee_adjustEquipment(int id) {
  printf("\x1B[34m%0.1f : Referee %d is adjusting equipment\n", timer, id);
}
void referee_startGame(int id) {
  printf("\x1B[32m%0.1f : Referee %d has started the game\n", timer, id);
}

// Organizer: mutex
