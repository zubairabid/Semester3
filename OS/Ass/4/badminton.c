#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *referee(void*);
void *player(void*);

pthread_mutex_t organizer;
pthread_cond_t cond;

int main() {

  // Initializing variables, not much to see here
  srand(time(0)); // Helper: setting a seed for rand
  int n, i, j, index;
  int playercount, refcount;
  double playerprob;
  pthread_mutex_init(&organizer, NULL);
  pthread_cond_init(&cond, NULL);


  // Take input as n, for number of referees and half the number of players
  scanf("%d", &n);
  playercount = 2 * n;
  refcount = n;


  pthread_t ref[n+1];
  pthread_t plr[2*n+1];


  do {

    // Creating a new player
    // As per question requirements
    playerprob = ((double)playercount/(playercount+refcount));
    if ( (playercount != 0) && ((refcount == 0) || (rand() <= playerprob)) ) {
      // New player is created
      index = 2*n - playercount + 1;
      pthread_create(&plr[index], NULL, player, (void *)index);
      playercount--;
    } else {
      // New referee is created
      pthread_create(&plr[n-refcount+1], NULL, referee, NULL);
      refcount--;
    }

    // Alloting groups, if organizer is free and people available



  } while (true);

  return 0;
}

void *referee(void *args) {
  int index = (int) args;
  // Enter the academy
  referee_enterAcademy(index);
  // Try to meet organizer (mutex)(print)
  // Meet organizer (lock rest out)(print)
  // Wait till signal for new match (wait)
  // Lock organizer
  //  Enter court (print)
  referee_enterCourt(index);
  //  Adjust equipment (wait) (print)
  //  Start match (rint)
  // Unlock organizer
}

void *player(void *args) {
  int index = (int) args;
  // Enter the academy
  // Try to meet organizer (mutex)(print)
  // Meet organizer (lock rest out)(print)
  // Wait till signal for new match (wait)
  // Lock organizer
  //  Enter court (print)
  //  Warm up (wait) (print)
  // Unlock organizer
}


// Define player actions

void player_meetOrganizer(int id) {
  print("Player %d met the organizer", id);
}
void player_enterAcademy(int id) {
  print("Player %d entered the Academy", id);
}
void player_enterCourt(int id) {
  print("Player %d entered the court", id);
}
void player_warmUp(int id) {
  print("Player %d is warming up", id);
}


// Define referee actions

void referee_meetOrganizer(int id) {
  print("Referee %d met the organizer", id);
}
void referee_enterAcademy(int id) {
  print("Referee %d entered the Academy", id);
}
void referee_enterCourt(int id) {
  print("Referee %d entered the court", id);
}
void referee_adjustEquipment(int id) {
  print("Referee %d is adjusting equipment", id);
}
void referee_startGame(int id) {
  print("Referee %d has started the game", id);
}

// Organizer: mutex
