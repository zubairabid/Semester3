#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

#include "ls.h"


int shls(char **argv, int argc) {
  struct dirent **namelist;
  struct stat fdetails;
  int n, i, j, lflag = 0, aflag = 0;

  char *dir = (char*)malloc(PATH_MAX*sizeof(char)), *filename, *filepath, *perm, *times = (char*)malloc(20*sizeof(char)), *userp = (char*)malloc(256*sizeof(char)), *grpp = (char*)malloc(256*sizeof(char));
  perm = (char*)malloc(10*sizeof(char));

  // get options
  for(i = 1; i < argc; i++) {
    // printf("Looking for options\n");
    if(argv[i][0] == '-') {
      // printf("Found - flag\n");
      // printf("%lu\n", strlen(argv[i]));
      for(j = 1; j < strlen(argv[i]); j++) {
        if(argv[i][j] == 'l') {
          lflag = 1;
        }
        if(argv[i][j] == 'a') {
          aflag = 1;
        }
      }
    }
  }

  // printf("lflag = %d\n", lflag);
  // printf("aflag = %d\n", aflag);

  // get directory to print
  for(i = 1; i < argc; i++) {
    if(argv[i][0] == '-')
      continue;
    dir = argv[i];
  }
  if (argc == 1 || argv[argc-1][0] == '-')
    dir = ".";


  // Gets a list of all files in the namelist as a dirent struct
  n = scandir(dir, &namelist, NULL, alphasort);



  if (n < 0) {
    perror("Could not list files in directory");
    // Error
  }
  else {
    // Printing the details
    for (i = 0; i < n; i++) {

      filename = namelist[i]->d_name;

      filepath = (char*)malloc((strlen(dir) + strlen(filename) + 2)*sizeof(char));
      strcpy(filepath, dir);
      strcat(filepath, "/");
      strcat(filepath, filename);

      // Get file data
      lstat(filepath, &fdetails);

      // Setting up permissions printing et al
      strcpy(perm, "----------");
      if(S_ISDIR(fdetails.st_mode))
        perm[0] = 'd';
      if(S_ISLNK(fdetails.st_mode))
        perm[0] = 'l';
      if(fdetails.st_mode & S_IRUSR)
        perm[1] = 'r';
      if(fdetails.st_mode & S_IWUSR)
        perm[2] = 'w';
      if(fdetails.st_mode & S_IXUSR)
        perm[3] = 'x';
      if(fdetails.st_mode & S_IRGRP)
        perm[4] = 'r';
      if(fdetails.st_mode & S_IWGRP)
        perm[5] = 'w';
      if(fdetails.st_mode & S_IXGRP)
        perm[6] = 'x';
      if(fdetails.st_mode & S_IROTH)
        perm[7] = 'r';
      if(fdetails.st_mode & S_IWOTH)
        perm[8] = 'w';
      if(fdetails.st_mode & S_IXOTH)
        perm[9] = 'x';


      // dealing with the cases
      if(aflag == 0) {
        if(filename[0] == '.') {
          continue;
        }
      }

      if(lflag == 1) {
        // printf("\n", );
        strftime(times, 20, "%d-%m-%y", localtime(&(fdetails.st_ctime)));

        if(fdetails.st_uid == 1000) {
          userp = getenv("USER");
        }
        if(fdetails.st_gid == 1000) {
          grpp = getenv("USER");
        }
        if(fdetails.st_uid == 0) {
          userp = "root";
        }
        if(fdetails.st_gid == 0) {
          grpp = "root";
        }


        printf("%s\t%s\t%s\t%ld\t%s\t%s\n", perm, userp, grpp, fdetails.st_size, times, namelist[i]->d_name);
      }
      else {
        printf("%s\n", filename);
      }



      free(namelist[i]);
      free(filepath);
    }
    free(namelist);
  }

  return 1;
}
