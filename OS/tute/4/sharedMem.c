#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/ipc.h>
#define SHMSIZE 4

key_t key = IPC_PRIVATE; /* This is needed */

int main() {
	int *sharedArray;
	int shmid, i, j, k, status;

	/* Create a shared Memory segment of required size and get its id */
	shmid = shmget(key, sizeof(int) *SHMSIZE, IPC_CREAT| 0666);
	if(shmid == -1) {
		perror("Shmget failed");
		exit(1);
	}
	
	/* Attach the shared memory Segment to the given pointer */
	sharedArray = shmat(shmid, 0, 0);
	if(sharedArray == (void *)-1) {
		perror("Shmat failed");
		exit(1);
	}
	
	/* Modify the contents before fork */
	printf("Enter the contents of array:\n");
	for(i = 0; i < SHMSIZE; i++) {
		scanf("%d", &sharedArray[i]);
	}
	
	pid_t pid;

	if((pid = fork())<0) {
		perror("fork Failed");
		exit(1);
	}
	
	if(pid == 0) {
		/* Modify the contents after fork in child */
		printf("This is child.\n");
		for(j = 0; j < SHMSIZE; j += 2) {
			printf("Enter the new value for %d index: ", j+1);
			scanf("%d", &sharedArray[j]);
		}
		printf("Final Contents in child are:\n");
		for(i = 0; i < SHMSIZE; i++) {
			printf("%d ", sharedArray[i]);
		}
		printf("\n");

		/* Detach the shared memory */
		if(shmdt(sharedArray) == -1) {
		    perror("shmdt failed");
		}
	}
	
	else
	{
		waitpid(pid, &status, 0);
		/* Wait for the child to exit and see  the changed contents after fork */
		printf("Contents of array in parent finally:\n");
		for(i = 0; i < SHMSIZE; i++) {
			printf("%d ", sharedArray[i]);
		}
		printf("\n");
	}
	
	return 0;
}
