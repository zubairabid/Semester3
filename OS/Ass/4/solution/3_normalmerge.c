#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>

/*USAGE:
	For use with int in C
	The functions must be initilaised before main(). The rest may come after.
	Sorts by ascending order.
	Call m_sort(array_name, start_index_of_array, end_index_of_array)
	Declare the array globally.
*/

void m_sort(int*, int, int);
void merge(int*, int, int);

void print(int* array, int size);
// Main
int main() {

  // Initializing shared memory array, following tute and manpages
  int sharedArray[100007];

  // Standard OJ sequence of inputs
  int n, i;

  scanf("%d", &n);
  for (i = 0; i < n; i++) {
    scanf("%d", &sharedArray[i]);
  }

  // print(sharedArray, n);
  // exit(0);
  // selectionsort(sharedArray, 0, n-1);
  m_sort(sharedArray, 0, n-1);
  print(sharedArray, n);
}

/*
	Called first for merge purposes
	Recursively breaks the array into smaller arrays and passes them for merging
*/
void m_sort(int* a, int l, int r) {
    if(l==r)
        return;
    m_sort(a, l, ((l+r)/2));

    m_sort(a, (((l+r)/2)+1), r);
    merge(a, l, r);
    return;
}

/*
	Called by function m_sort
	Merges the smaller arrays by comparing against each element in succession
*/
void merge(int* a, int l, int r) {
    int m = (l+r)/2 + 1;
    int start = 0;
    int b[r-l+1];
	int i, j;

    int cl = l, cr = r, cm = m;
    while(start <= r-l) {
        if(((a[cl] <= a[cm])||(cm>r)) && (cl<m)) {
            b[start++] = a[cl++];       }
        else {
            b[start++] = a[cm++];
        }
    }
    for(i = l, j = 0; i <= r; i++, j++) {
        a[i] = b[j];
    }
    return;
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
