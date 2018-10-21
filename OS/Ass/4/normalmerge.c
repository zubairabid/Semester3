#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>

/*USAGE: 
	For use with long long int in C
	The functions must be initilaised before main(). The rest may come after. 
	Sorts by ascending order. 
	Call m_sort(array_name, start_index_of_array, end_index_of_array)
	Declare the array globally.
*/

void m_sort(long long int*,long long int, long long int);
void merge(long long int*, long long int, long long int);

/*
	Called first for merge purposes
	Recursively breaks the array into smaller arrays and passes them for merging
*/
void m_sort(long long int* a, long long int l, long long int r) {
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
void merge(long long int* a, long long int l, long long int r) {
    long long int m = (l+r)/2 + 1;
    long long int start = 0;
    long long int b[r-l+1];
	long long int i, j;
	
    long long int cl = l, cr = r, cm = m;
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

