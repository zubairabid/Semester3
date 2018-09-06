#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

#define DELIM_TOKEN " \t\r\f\a\n"
#define BUF_DEFAULT 128

// The function splits the line into a bunch of arguments to use
char **parseline(char *line, int *argc) {

  // bsize Defines expected size of array. May need to be redefined as per
  // use case. count is used as a counter variable to assign values to array
  int bsize = BUF_DEFAULT, count = 0;

  char *token;
  char **tokens = (char**)malloc(bsize * sizeof(char*));

  // Splitting the string into arguments. The loop manages most of the work
  token = strtok(line, DELIM_TOKEN);
  do {

    // This would have done, but...
    tokens[count++] = token;

    // ... there's the possibility of overflow. So.
    if(count >= bsize) {
      bsize += BUF_DEFAULT;
      tokens = realloc(tokens, bsize * sizeof(char*));
    }

    // next token time
    token = strtok(NULL, DELIM_TOKEN);
  } while(token != NULL);

  *argc = count;
  return tokens;

}

char **splitlines(char *line, int *num) {
  int bsize = BUF_DEFAULT, count = 0;

  char *token;
  char **tokens = (char**)malloc(bsize * sizeof(char*));

  // Splitting the string into arguments. The loop manages most of the work
  token = strtok(line, ";");
  do {

    // This would have done, but...
    tokens[count++] = token;

    // ... there's the possibility of overflow. So.
    if(count >= bsize) {
      bsize += BUF_DEFAULT;
      tokens = realloc(tokens, bsize * sizeof(char*));
    }

    // next token time
    token = strtok(NULL, ";");
  } while(token != NULL);

  *num = count;
  return tokens;

}
