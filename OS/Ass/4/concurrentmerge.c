#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>

#define SHMSIZE 10000

void c_m_sort(int* array, int l, int r);
void merge(int* array, int l, int r, int length);
void selectionsort(int* array, int l, int r);

void print(int* array, int size);


// Main
int main() {

  // Initializing shared memory array, following tute and manpages
  int* sharedArray;
  key_t key = IPC_PRIVATE;
  int shmid, temp;

  shmid = shmget(key, sizeof(int) * SHMSIZE, IPC_CREAT | 0666);
  if (shmid == -1) {
    // error
    perror("shmid failed");
    exit(1);
  }
  sharedArray = shmat(shmid, 0, 0);
  if (sharedArray == (void *)-1) {
    // error
    perror("shmat failed");
    exit(1);
  }


  // Standard OJ sequence of inputs
  int n, i;

  scanf("%d", &n);
  for (i = 0; i < n; i++) {
    scanf("%d", &sharedArray[i]);
  }

  print(sharedArray, n);
  // exit(0);
  // selectionsort(sharedArray, 0, n-1);
  c_m_sort(sharedArray, 0, n-1);
  print(sharedArray, n);


  // Cleaning up shared memory
  temp = shmdt(sharedArray);
  if (temp == -1) {
    perror("shmdt error");
    exit(1);
  }

  temp = shmctl(shmid, IPC_RMID, NULL);
  if (temp == -1) {
    perror("shmctl error");
    exit(1);
  }

}

/*
 * Function to call for the merge sort to begin.
 * Splits the array into parts, creates processes for each,
 *  and calls the selectionsort/merge routines as needed.
 * Parameters:
 * array: pointer to the first element of the array. Just
 *  pass the array itself
 * l: leftmost index of range (inclusive)
 * r: rightmost index of range (inclusive)
 */
void c_m_sort(int* array, int l, int r) {
  // Since both bounds are inclusive, length is the
  // difference + 1
  int length = r - l + 1;

  if (length <= 5) {
    // selectionsort for such cases
    selectionsort(array, l, r);
    return;
  }
  // Forking out the branches
  pid_t pid_l, pid_r;
  pid_l = fork();
  if (pid_l < 0) {
    // Error
    perror("error with fork on right child process");
    exit(1);
  }
  else if (pid_l == 0) {
    // Do a merge on the left half of the array
    c_m_sort(array, l, l + length/2 - 1);
    exit(0);
  }
  else {
    // Create another child process for the right half
    pid_r = fork();
    if (pid_r < 0) {
      // Error
      perror("error with fork on right child process");
      exit(1);
    }
    else if (pid_r == 0) {
      // Merge on the right half of the array
      c_m_sort(array, l + length/2, r);
      exit(0);
    }
  }
  int temp;

  waitpid(pid_l, &temp, 0);
  waitpid(pid_r, &temp, 0);

  merge(array, l, r, length);
}

void merge(int* array, int l, int r, int length) {
  // mid: point where second array starts
  int mid = l + length/2;
  int copy[length];
  int start = 0, cl = l, cr = r, cm = mid;
  int i, j;

  while (start < length) {
    if ( ((array[cl] <= array[cm])||(cm > r)) && (cl < mid)) {
      copy[start++] = array[cl++];
    }
    else {
      copy[start++] = array[cm++];
    }
  }

  for (i = l, j = 0; i <= r; i++, j++) {
    array[i] = copy[j];
  }
  return;
}

/*
 * Performs a selectionsort from array[l] to array[r], both inclusive
 * Standard selection sort algorithm implementat
 * Parameters:
 * array: Pointer to the first element of the array. Just
 *  pass the array itself
 * l: leftmost index of range (inclusive)
 * r: rightmost index of range (inclusive)
 */
void selectionsort(int* array, int l, int r) {
  int i, j, temp, min, minpos;
  for (i = l; i < r; i++) {
    // Assign current val as minimum value so far
    min = array[i];
    minpos = i;
    // Get the minimum value in array segment left
    for(int j = i+1; j <= r; j++) {
      if (array[j] < min) {
        min = array[j];
        minpos = j;
      }
    }
    // Swap values
    temp = array[i];
    array[i] = array[minpos];
    array[minpos] = temp;
  }
}

/* Utility function, prints array list till index size-1
 * Parameters:
 * list: pointer to the first element of the array. Just
 *  pass the array itself
 * size: size of the array (number of elements)
 */
void print(int* list, int size) {
  int i = 0;
  for (i = 0; i < size; i++) {
    printf("%d\t", list[i]);
  }
  printf("\n");
}
