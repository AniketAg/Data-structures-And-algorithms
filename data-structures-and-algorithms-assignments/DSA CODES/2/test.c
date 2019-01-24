#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#define SIZE 256
float CAPACITY=99991;

struct people 
{
	char surname[20];
	char forename[20];
	char person_id[20];
	char deposition_id[20];
	struct people* next;

}	
*begin=NULL;

int next_field( FILE *f, char *buf, int max );
int hashcode(struct people* p);
int hashcodex(char s[]);
void fetch_name ( FILE *csv, struct people *p );
void print_name( struct people *p );
int search(char s[]);
void linkedlist(FILE *f);
void collision(FILE* f);

int main ( ) 
{
	FILE *f = fopen("ign.csv", "r");
	struct people p;
	if(!f) 
	{ 
		printf("unable to open\n"); 
		return 1; 
	}
	 // Creating the linked list and indexing it using linear probing on the basis of hash function
	char naam[20]; // Used to get name only.....misspelled on purpose
	while(!feof(f))
	{
		fetch_name(f,&p);
    	print_name(&p);
	
	}
	fclose(f);
	return 0;
}

int next_field( FILE *f, char *buf, int max ) 
{
	int i=0, end=0, quoted=0;
	for(;;) 
	{
		// fetch the next character from file		
		buf[i] = fgetc(f);
		// if we encounter quotes then flip our state and immediately fetch next char
		if(buf[i]=='"') { quoted=!quoted; buf[i] = fgetc(f); }
		// end of field on comma if we're not inside quotes
		if(buf[i]==',' && !quoted) { break; }
		// end record on newline or end of file
		if(feof(f) || buf[i]=='\n') { end=1; break; } 
		// truncate fields that would overflow the buffer
		if( i<max-1 ) { ++i; } 
	}
	buf[i] = 0; 
	return end; 
}

void fetch_name ( FILE *csv, struct people *p ) 
{
	char buf[SIZE];
	next_field( csv, p->person_id, SIZE );
	next_field( csv, p->deposition_id, SIZE );
	next_field( csv, p->surname, SIZE );
	next_field( csv, p->forename, SIZE );
}

void print_name( struct people *p ) 
{
	int abc=10;
	printf("%s\t\t%s\t%.15s\t\t%*.10s\t\t\n",p->person_id , p->deposition_id ,p->surname,abc, p->forename);
}

void linkedlist(FILE *f)
{
	while(!feof(f))
	{
		struct people *newdata,*curr;

  		newdata=(struct people *)malloc(37*sizeof(struct people));
  		fetch_name( f, newdata );
  		newdata->person_id;
  		newdata->next=NULL;

		if(begin==NULL)
  		{
 		 	begin=newdata;
  			curr=newdata;
  		}
  		else
  		{
  			curr->next=newdata;
  			curr=newdata;
  		}
 	}
}

