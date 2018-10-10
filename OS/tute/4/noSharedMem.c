#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#define SIZE 4
int a[SIZE],i,j,status;

int main() {

	printf("Enter the values of Elements\n");
	for(i = 0; i < SIZE; i++) {
		scanf("%d",&a[i]);
	}

	pid_t pid;

	pid = fork();
	
	if(pid < 0) {
		perror("Fork Failed");
		exit(1);
	}

	if(pid == 0) {
		printf("This is child.\n");
		
		for(i = 0; i < SIZE; i += 2) {
			printf("Enter the new value for %d index: ", i+1);
			scanf("%d",&a[i]);
		}
		
		printf("Final Contents in child are\n");
		for(i = 0; i < SIZE; i++) {
			printf("%d ",a[i]);
		}
		printf("\n");
	}
	
	else
	{
		waitpid(pid, &status, 0);
		printf("This is Parent. Contents are\n");
		
		for(i = 0; i < SIZE; i++) {
			printf("%d ", a[i]);
		}
		printf("\n");
	}
	
	return 0;
}
