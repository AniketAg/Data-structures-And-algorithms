#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
int s=0,comp=0;
void swapping(int* a, int* b);
void selectionSort(int a[], int n);
char check(int arr[], int n);
void printArray(int a[], int n);
void randomize ( int a[], int n );
int main()
{
    clock_t begin = clock();
    
    int n=10000;srand(time(NULL));
    int a1[n]; for(int i = 1; i<=n; i++) a1[i] = i;randomize(a1,n);
    int a2[n]; for(int i = 1; i<=n; i++) a2[i] = rand() % 10 + 1;
    int a3[n]; for(int i = 1; i<=n; i++) a3[i] = i;
    int a4[n]; for(int i = 1; i<=n; i++) a4[i] = n-i;
    int a5[n]; for(int i = 1; i<=n; i++) a5[i] = 3;
    char y;
    printf("\n\nRunning profile tests with %d elements\n\n",n);
    s=0;comp=0;selectionSort(a1,n);y=check(a1,n);//printArray(a1,n);
    printf("\nTEST   : Unique random values  \nSORTED : %c\nSWAPS  : %d\nCOMPS  : %d\n",y,s,comp);
    s=0;comp=0;selectionSort(a2,n);y=check(a2,n);
    printf("\nTEST   : Random values         \nSORTED : %c\nSWAPS  : %d\nCOMPS  : %d\n",y,s,comp);
    s=0;comp=0;selectionSort(a3,n);y=check(a3,n);
    printf("\nTEST   : Ascending sorted list \nSORTED : %c\nSWAPS  : %d\nCOMPS  : %d\n",y,s,comp);
    s=0;comp=0;selectionSort(a4,n);y=check(a4,n);
    printf("\nTEST   : Descending sorted list\nSORTED : %c\nSWAPS  : %d\nCOMPS  : %d\n",y,s,comp);
    s=0;comp=0;selectionSort(a5,n);y=check(a5,n);
    printf("\nTEST   : Uniform list          \nSORTED : %c\nSWAPS  : %d\nCOMPS  : %d\n",y,s,comp);  
	
	clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nTIME SPENT:%f",time_spent);
    
    return 0;
}
int compare(int a, int b)
{
	comp++;
    if(a<b)	return 1;
    else return 0;
}
void swapping(int* a, int* b)
{
    if(*a!=*b)
    {
        int t = *a;
        *a = *b;
        *b = t;
        s++;
    }
}
void selectionSort(int a[], int n)
{
    int i, j, min;
    for(i = 1; i < n+1; i++)
    {
        min = i;
        for(j = i+1; j < n+1; j++)
        	if(compare(a[j],a[min])) 
        		min = j;
       	swapping(&a[min],&a[i]);
    }
}
void printArray(int a[], int n)
{
    for(int i=1; i <=n; i++)
        printf("%d",a[i]);
}
void randomize ( int a[], int n )
{
    srand(time(NULL) );
    for (int i = n-1; i > 0; i--)
    {
        int j=rand()%(i+1);
        swapping(&a[i], &a[j]);
    }
}
char check(int arr[], int n)
{
    if (n == 1 || n == 0)
        return 'Y';
    if (arr[n] < arr[n-1])
        return 'N';
    return check(arr, n-1);
}
/*
Running profile tests with 100000 elements


TEST   : Unique random values
SORTED : Y
SWAPS  : 99989
COMPS  : 704982704

TEST   : Random values
SORTED : Y
SWAPS  : 89916
COMPS  : 704982704

TEST   : Ascending sorted list
SORTED : Y
SWAPS  : 0
COMPS  : 704982704

TEST   : Descending sorted list
SORTED : Y
SWAPS  : 50000
COMPS  : 704982704

TEST   : Uniform list
SORTED : Y
SWAPS  : 0
COMPS  : 704982704

TIME SPENT:111.740000
*/