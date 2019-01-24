#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 100

struct ign 
{
	char title[SIZE];
	char platform[SIZE];
	int score;
	int year;
	struct ign* next;
}
*Begin=NULL;// Basically the head of the  element

int next_field(FILE *f, char *buf, int max );
void fetch_title (FILE *csv, struct ign *p );
void linkedlist(FILE *f);
void print( struct ign *p );
void printy( struct ign *p ,int yr);

void insertion(struct ign** sorted, struct ign* cur)
{
    struct ign* newcur;
    if (*sorted == NULL || (*sorted)->score <= cur->score)
    {
        cur->next = *sorted;
        *sorted = cur;
    }
    else// Locate the node before the point of insertion
    {
        newcur = *sorted;
        while (newcur->next!=NULL && newcur->score >= cur->score)
            newcur = newcur->next;
        cur->next = newcur->next;
        newcur->next = cur;
    }
}
void sort(struct ign **head)
{
    struct ign *sorted = NULL;
    struct ign *cur = *head;
    while (cur != NULL)
    {
        struct ign *Next = cur->next;        // Store next for next iteration
        insertion(&sorted, cur);        // insert cur in sorted linked list
        cur = Next;        // Update cur
    }
    *head = sorted;    // Update head to point to sorted linked list
}
int main () 
{
	FILE *f = fopen("ign.csv", "r");
	if(!f) 
	{ 
		printf("unable to open\n"); 
		return 1; 
	}	
	linkedlist(f);
	sort(&Begin);
	printf("\nTOP TEN VALUES OF LAST 20 YEARS\n");
	print(Begin);

	printf("\n\n");//printm(Begin);
	int year=1996;
	while(year<2017)
	{
		printf("\nTOP FIVE VALUES OF THE YEAR %d\n",year);
		printy(Begin,year++);
		printf("\n\n");
	}
	fclose(f);
	free(Begin);
	return 0;
}
int next_field( FILE *f, char *buf, int max ) //Reffered from solutions of Assignment 0
{
	int i=0, end=0, quoted=0;
	for(;;) {
		buf[i] = fgetc(f);
		if(buf[i]=='"') { quoted=!quoted; buf[i] = fgetc(f); }
		if(buf[i]==',' &&  !quoted) { break; }
		if(feof(f) || buf[i]=='\n') { end=1; break; } 
		if( i<max-1 ) { ++i; } 
	}
	buf[i] = 0; 
	return end;
}
void fetch_title ( FILE *csv, struct ign *p )//Reffered from solutions of Assignment 0
{
	char buf[SIZE];
	next_field( csv, p->title, SIZE );
	next_field( csv, p->platform, SIZE );
	next_field( csv, buf, SIZE );
	p->score=atoi(buf);
	next_field( csv, buf, SIZE );
	p->year=atoi(buf);
}
void linkedlist(FILE *f)
{
	while(!feof(f))
 	{
  		struct ign *newdata,*curr;
	   	newdata=(struct ign *)malloc(sizeof(struct ign));
  		fetch_title( f, newdata );
  		newdata->score;
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
void print( struct ign *p ) 
{
	int i=0;
	while(i<10)
	{			
		p=p->next;
		printf("\n%d||%s||%s||%d||%d\n",++i,p->title,p->platform,p->score,p->year);
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	}
}
void printy( struct ign *p ,int yr) 
{
	int j=0;
	while(p!=NULL && j<5)
	if(p->year==yr)
	{	
		printf("\n%s||%s||%d||%d\n",p->title,p->platform,p->score,p->year);//printf("%s\n",p->title);//
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
		p=p->next;j++;
	}
	else p=p->next;
}
/*
void printm( struct ign *p ) 
{
	int i=0;
	char word[10000][SIZE];
	while(i<8)
	{			
		//printf("e\n");
		strcpy(word[i],p->title);
		int j=0;
		while(j<=i)
		{
			int c=0;//printf("f\n");
			if (strcmp(word[j++],p->title)==0 && c<1)
			{
				printf("\n%d\t%.50s\t\t%*s\t\t%*d\t%*d\n",++i,p->title,15,p->platform,2,p->score,4,p->year);//printf("%s\n",p->title);//
				p=p->next;c++;
			}
			else p=p->next;
		}
	}
}
*/