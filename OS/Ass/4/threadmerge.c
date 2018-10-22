#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>

typedef struct tstruct {
  int *array;
  int left;
  int right;
} construct;

void *t_m_sort(void*);
void merge(int* array, int l, int r, int length);
void selectionsort(int* array, int l, int r);

void print(int* array, int size);


// Main
int main() {

  // Initializing shared memory array, following tute and manpages
  int* array;

  // Standard OJ sequence of inputs
  int n, i;

  scanf("%d", &n);
  array = (int*)malloc(sizeof(int) * n);

  for (i = 0; i < n; i++) {
    scanf("%d", &array[i]);
  }

  construct *args;
  args->array = array;
  args->left = 0;
  args->right = n-1;

  t_m_sort((void*)args);
  print(array, n);

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
void *t_m_sort(void *args) {

  construct *vars = (construct*)args;
  int *array = vars->array;
  int l = vars->left;
  int r = vars->right;

  // Since both bounds are inclusive, length is the
  // difference + 1
  int length = r - l + 1;

  if (length <= 5) {
    // selectionsort for such cases
    selectionsort(array, l, r);
    return;
  }

  construct *left, *right;

  left->array = array;
  left->left = l;
  left->right = left + length/2 -1;

  right->array = array;
  right->left = l + length/2;
  right->right = r;

  pthread_t thleft, thright;

  pthread_create(&thleft, NULL, t_m_sort, (void*)left);
  pthread_create(&thright, NULL, t_m_sort, (void*)right);

  pthread_join(thleft, NULL);
  pthread_join(thright, NULL);

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
