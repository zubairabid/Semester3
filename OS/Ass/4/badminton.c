#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int main() {

  int n, i, j;
  int playercount, refcount;

  scanf("%d", &n);
  playercount = 2 * n;
  refcount = n;

  return 0;
}

// New person:
// Try to meet organizer (mutex)(print)
// Meet organizer (lock rest out)(print)
// Wait till signal for new match (wait)
// Lock organizer
// Referee:
//  Enter court (print)
//  Adjust equipment (wait) (print)
//  Start match (print)
// Player:
//  Enter court (print)
//  Warm up (wait) (print)
// Unlock organizer

// Organizer: mutex
