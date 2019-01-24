#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<assert.h>
#define SIZE 20
float CAPACITY=99991;

struct Names 
{
	char name[SIZE];
	int hash_value;
	struct Names* next;
}
*Begin=NULL;// Basically the head of the  element

int next_field(FILE *f, char *buf, int max );
int hash(struct Names* p);
int hashing(char * s);
void fetch_name (FILE *csv, struct Names *p );
int search(char s[]);
void linkedlist(FILE *f);
void collision(FILE* f);

int main () 
{
	FILE *f = fopen("names.csv", "r");
	struct Names p;
	if(!f) 
	{ 
		printf("unable to open\n"); 
		return 1; 
	}
	linkedlist(f); // Creating the linked list and indexing it using linear probing on the basis of hash function
	collision(f);  // Calculating the no. of terms and collision and the load factor
	char naam[20]; // Used to get name only.....misspelled on purpose
	while(strcmp(naam,"quit")!=0)
	{
		printf("\nEnter term to get frequency or type quit to escape:\n>>> ");
		gets(naam);
		int a = search(naam);
   	    if (strcmp(naam,"quit")==0)
      		continue;
		    if (a>0)
		    	printf("%s %d",naam,a);
		    else
	        printf("%s not in table",naam);
	}
	fclose(f);
	return 0;
}

int next_field( FILE *f, char *buf, int max ) //Reffered from solutions of Assignment 0
{
	int i=0, end=0, quoted=0;
	for(;;) 
	{
		buf[i] = fgetc(f);
		if(feof(f) || buf[i]=='\n') { end=1; break; } 
		if( i<max-1 ) { ++i; } 
	}
	buf[i] = 0; 
	return end; 
}

int hash(struct Names* p)// As given in the assignment 1 slightly modified according to my requirement
{
	char *s = p->name;
	int hash = 0;
  	while(*s)
  	{
		  hash = hash + *s;
		  s++;
	  }
	return hash;
}

int hashing(char * s)// As given in the assignment 1 
{
	int hash = 0;
	while(*s)
	{
		hash = hash + *s;
		s++;
	}
	return hash;
}

void fetch_name ( FILE *csv, struct Names *p )//Reffered from solutions of Assignment 0
{
	char buf[SIZE];
	next_field( csv, p->name, SIZE );  // name and type are just strings so read
	p->hash_value = hash(p);
}

int search(char s[])
{
	int i=0;
    struct Names* curr = Begin;  // Initialize curr
    while (curr != NULL)
    {
      if (curr->hash_value==hashing(s))
      i++;
      curr = curr->next;
    }
    return i;
}

void linkedlist(FILE *f)
{
	while(!feof(f))
 	{
  		struct Names *newdata,*curr;

	   	newdata=(struct Names *)malloc(sizeof(struct Names));
  		fetch_name( f, newdata );
  		newdata->hash_value;
  		newdata->next=NULL;
		  if(Begin==NULL)
  	    {
  			Begin=newdata;
  			curr=newdata;
  		}
  		else
  		{
  			curr->next=newdata;
   			curr=newdata;
  		}
 	}
}

void collision(FILE* f)
{
	int count = 0;
   	int collisions = 0;
  	char *x;
  	int array[30000];
  	struct Names* curr = Begin;
  	while(curr!=NULL)
  	{
  		x=curr->name;count++;
   		curr=curr->next;
    	array[count] = hashing(x);
    	for(int i = 0; i<count; i++)
    	{
        	if(array[i]==array[count])
        	{
            	collisions++;// Once we've found one collision, we don't want to count all of them.
            	break;
        	}
    	}	    
  	} 
	printf("Num Terms  :%d\nCollisions :%d\nLoad Factor:%.3f\n",count,collisions,floorf((count/CAPACITY) * 1000) / 1000);
}