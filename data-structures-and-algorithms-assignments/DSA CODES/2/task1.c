#include <stdio.h>
#include<stdlib.h> 
#include <time.h>
int s=0,comp=0;
void quickSort(int *a, int low, int high);
void printArray(int a[], int n);
int Partition(int arr[],int i, int j, int pivot);
void randomize ( int a[], int n );
char check(int arr[], int n);
int main()
{
    clock_t begin = clock();char y;
    int n=10000;srand(time(NULL));
    int a1[n]; for (int i = 0; i<n; i++) a1[i] = i;randomize(a1,n);
    int a2[n]; for (int i = 0; i<n; i++) a2[i] = rand() % 100 + 1;
    int a3[n]; for (int i = 0; i<n; i++) a3[i] = i+1;
    int a4[n]; for (int i = 0; i<n; i++) a4[i] = n-i;
    int a5[n]; for (int i = 0; i<n; i++) a5[i] = 3;
    printf("\n\nRunning profile tests with %d elements\n\n",n);
    s=0;comp=0;
    quickSort(a1,0,n-1);y=check(a1,n);
    printf("\nTEST   : Unique random values  \nSORTED : %c\nSWAPS  : %d\nCOMPS  : %d\n",y,s,comp);
    s=0;comp=0;
    quickSort(a2,0,n-1);y=check(a2,n);
    printf("\nTEST   : Random values         \nSORTED : %c\nSWAPS  : %d\nCOMPS  : %d\n",y,s,comp);
    s=0;comp=0;
    quickSort(a3,0,n-1);y=check(a3,n);
    printf("\nTEST   : Ascending sorted list \nSORTED : %c\nSWAPS  : %d\nCOMPS  : %d\n",y,s,comp);
    s=0;comp=0;
    quickSort(a4,0,n-1);y=check(a4,n);
    printf("\nTEST   : Descending sorted list\nSORTED : %c\nSWAPS  : %d\nCOMPS  : %d\n",y,s,comp);
    s=0;comp=0;
    quickSort(a5,0,n-1);y=check(a5,n);
    printf("\nTEST   : Uniform list          \nSORTED : %c\nSWAPS  : %d\nCOMPS  : %d\n",y,s,comp);    
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nTIME SPENT:%f",time_spent);
    return 0;
}
int compare(int a, int b)
{
    comp++;
    if(a<=b) return 1;
    else return 0;
}
int compare1(int a, int b)
{
    comp++;
    if(a<b) return 1;
    else return 0;
}
int compare2(int a, int b)
{
    comp++;
    if(a>b) return 1;
    else return 0;
}
void swaping(int* a, int* b)
{
    if(*a!=*b)
    {
     int t = *a;
     *a = *b;
     *b = t;
     s++;
    }
}
int Partition(int arr[],int i, int j, int pivot)
{
    while(compare(i,j))
    {
        while(compare1(arr[i],pivot)) i++;
        while(compare2(arr[j],pivot)) j--;
        if(compare(i,j))
        {
            if(arr[i]!=arr[j]) swaping(&arr[i],&arr[j]) ;
            i++;
            j--;
        }
    }
    return i;
}
void quickSort(int arr[], int low, int high)
{
    if (low<high)
    {
        int median= arr[(low + high)/2];
        int index= Partition(arr, low, high, median);
        if(index>low)  quickSort(arr, low, index-1);
        if(index<high) quickSort(arr,index, high);
    }
}
void printArray(int a[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf(" %d",a[i]);
}
void randomize ( int a[], int n )
{
    srand(time(NULL));
    for (int i = n-1; i > 0; i--)
    {
        int j = rand() % (i+1);
        swaping(&a[i], &a[j]);
    }
}
char check(int arr[], int n)
{
    if (n == 1 || n == 0)  return 'Y';
    if (arr[n-1]<arr[n-2]) return 'N';
    return check(arr, n-1);
}
/*
Running profile tests with 100000 elements


TEST   : Unique random values
SORTED : Y
SWAPS  : 871135
COMPS  : 19963133

TEST   : Random values
SORTED : Y
SWAPS  : 359939
COMPS  : 50837511

TEST   : Ascending sorted list
SORTED : Y
SWAPS  : 0
COMPS  : 70497041

TEST   : Descending sorted list
SORTED : Y
SWAPS  : 50000
COMPS  : 90082705

TEST   : Uniform list
SORTED : Y
SWAPS  : 0
COMPS  : 50311046

TIME SPENT:0.932000
*/