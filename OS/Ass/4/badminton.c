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
pthread_cond_t condp[20000];
pthread_cond_t condr[10000];
int locked = 0;

int main() {

  // Initializing variables, not much to see here
  srand(time(0)); // Helper: setting a seed for rand
  int n, i, j, index;
  int playercount, refcount, playat = 1, refat = 1;
  double playerprob, temp;
  pthread_mutex_init(&organizer, NULL);
  for(i = 0; i < 20000; i++) {
    if (i < 10000) {
      pthread_cond_init(&condr[i], NULL);
    }
    pthread_cond_init(&condp[i], NULL);
  }


  // Take input as n, for number of referees and half the number of players
  printf("Enter number n, given 3n people will come in total: \n");
  scanf("%d", &n);
  playercount = 2 * n;
  refcount = n;


  pthread_t ref[n+1];
  pthread_t plr[2*n+1];


  do {

    // Creating a new player
    // As per question requirements
    playerprob = ((double)playercount/(double)(playercount+refcount));
    // printf("Creating new player: playerprob = %f\n", playerprob);
    temp = rand()/(double)RAND_MAX;
    // printf("Random number: %f\n", temp);
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
    sleep(1);

    printf("playercount = %d\tplayat = %d\nrefcount = %d\trefat = %d\n", playercount, playat, refcount, refat);

    // Alloting groups, if organizer is free and people available
    // pthread_create(&pint, NULL, allocator, NULL);
    if (!locked) {
      if ( ((2*n-playercount)-playat+1) < 2 || ((n-refcount)-refat+1) < 1 ) {
        // pthread_mutex_unlock(&organizer);
        // locked = 0;

        if(playat >= 2*n || refat > n) {
          break;
        }

        sleep(1);
        continue;
      }
      pthread_mutex_lock(&organizer);
      locked = 1;

      printf("Starting a game, organizer was unlocked\n");
      pthread_cond_signal(&condr[refat]);
      pthread_cond_signal(&condp[playat]);
      pthread_cond_signal(&condp[playat+1]);

      playat += 2;
      refat++;

    }
    else
      printf("organizer was locked, continuing\n");

  } while (1);

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

  // Wait till signal for new match (wait)
  pthread_cond_wait(&condr[index], &organizer);

  // Lock organizer
  //  Enter court (print)
  referee_enterCourt(index);

  //  Adjust equipment (wait) (print)
  referee_adjustEquipment(index);
  sleep(0.5);

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

  // Wait till signal for new match (wait)
  pthread_cond_wait(&condp[index], &organizer);

  // Lock organizer
  //  Enter court (print)
  player_enterCourt(index);

  //  Warm up (wait) (print)
  player_warmUp(index);
  sleep(1);
  // Unlock organizer
}



void *allocator(void *arg) {

}


// Define player actions

void player_meetOrganizer(int id) {
  printf("Player %d met the organizer\n", id);
}
void player_enterAcademy(int id) {
  printf("Player %d entered the Academy\n", id);
}
void player_enterCourt(int id) {
  printf("Player %d entered the court\n", id);
}
void player_warmUp(int id) {
  printf("Player %d is warming up\n", id);
}


// Define referee actions

void referee_meetOrganizer(int id) {
  printf("Referee %d met the organizer\n", id);
}
void referee_enterAcademy(int id) {
  printf("Referee %d entered the Academy\n", id);
}
void referee_enterCourt(int id) {
  printf("Referee %d entered the court\n", id);
}
void referee_adjustEquipment(int id) {
  printf("Referee %d is adjusting equipment\n", id);
}
void referee_startGame(int id) {
  printf("Referee %d has started the game\n", id);
}

// Organizer: mutex
