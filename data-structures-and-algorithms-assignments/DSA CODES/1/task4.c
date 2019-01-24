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
	int hash_value;
	char age[20];
	char persontype[20];
	char gender[20];
	char nationality[20];
	char religion[20];
	char occupation[20];
    struct people* next;
}
	*Begin=NULL;

int next_field( FILE *f, char *buf, int max );
int hashcodex(char s[]);
int hashcode(struct people* p);
void reverse(struct people** head_ref);
void fetch_name ( FILE *csv, struct people *p );
void print_name( struct people *p );
int search(char s[]);
void linkedlist(FILE *f);
void collision(FILE* f);

int main ( ) 
{
	FILE *f = fopen("people.csv", "r");
	struct people p;
	if(!f) 
	{ 
		printf("unable to open\n"); 
		return 1; 
	}
	linkedlist(f);  // Creating the linked list and indexing it using linear probing on the basis of hash function
	collision(f);   // Calculating the no. of terms and collision and the load factor
	reverse(&Begin);// Reversing the linked list
	char naam[20];  // Used to get name only.....misspelled on purpose
	while(strcmp(naam,"quit")!=0)
	{
		printf("\nEnter term to get frequency or type quit to escape:\n>>> ");
		gets(naam);
		int a=search(naam);
    	if (strcmp(naam,"quit")==0)
    		continue;
    	if (a>0)
			printf(" ");//	printf("%s %d",naam,a);
		else
	   		printf("%s not in table",naam);
	
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
	next_field( csv, p->age, SIZE );
	next_field( csv, p->persontype, SIZE );
	next_field( csv, p->gender, SIZE );
	next_field( csv, p->nationality, SIZE );
	next_field( csv, p->religion, SIZE );
	next_field( csv, p->occupation, SIZE );
	p->hash_value = hashcode(p);
}

void print_name( struct people *p ) 
{
	int abc=10;
	printf("%s\t\t%s\t%.15s\t\t%*.10s\t\t%*.10s\t\t%*s\n",p->person_id , p->deposition_id ,p->surname,abc, p->forename,abc, p->age,abc, p->persontype);
}

int search(char s[])
{
	 
	int a=0;
    struct people* curr = Begin;  // Initialize curr
    while (curr != NULL)
    {	
        if (strcmp(curr->surname,s)==0)
        {
        	a++;
        	if(a==1)
        	{
  	        	printf("Person_ID\tDeposition_ID\tSurname\t\t  Forename\t\t\tAge\t\tPerson Type\n");
  	        	print_name(curr);

        	}
        	if(a>1)
        		print_name(curr);

        }
          	curr = curr->next;
    }
    return a;
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

void reverse(struct people** head)
{
    struct people* prev   = NULL;
    struct people* curr = *head;
    struct people* next;
    while (curr != NULL)
    {
        next = curr->next;  
        curr->next = prev;   
        prev = curr;
        curr = next;
    }
    *head = prev;
}

long hashcode1(char s[])
{
	long seed = 33; 
	long hash = 5831;
	for(int i = 0; i < SIZE; i++)
    	hash = (hash * seed) + s[i];
  return (hash % 99991);
}

long hashcode2(char s[])
{
	long seed = 33; 
	long hash = 5831;
	for(int i = 0; i < SIZE; i++)
    	hash = (hash * seed) + s[i];
  return (99991-(hash % 99991));
}

int hashcodex(char s[])
{
  return (hashcode1(s)-hashcode2(s));
}

int hashcode(struct people* p)
{
  char* s=p->surname;	
  return (hashcode1(s)-hashcode2(s));
}

void collision(FILE* f)
{
	int count = 0;
	int collisions = 0;
	char *x;
    int array[99991];
    struct people* curr = Begin;
    while(curr!=NULL)
  	{
  		x=curr->surname;count++;
    	curr=curr->next;
    	array[count] = hashcodex(x);
    	for(int i = 0; i<count; i++)
    	{
        	if(array[i]==array[count])
        	{
            	collisions++;// Once we've found one collision, we don't want to count all of them.
            	break;
       		}
    	}    
    } 
 	printf("Num Terms  :%d\nCollisions :%d\nLoad Factor:%.3f\n",count-2,collisions,floorf(((count-2)/CAPACITY)*1000)/1000);
}