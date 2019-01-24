#include "bstdb.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int n=109000;
int a1[109000],m=-1,i=0,inserts=0;
double searches,cmp;
struct Bstnode
{
	int doc_id;
	char *name;
	int word_count;
	int height;
    struct Bstnode *left;
	struct Bstnode *right;
}*root=NULL;

void randomize ( int a[], int n )
{
    srand(time(NULL));
    for (int i = n-1; i > 0; i--)
    {
        int j = rand() % (i+1);
        if(a[i]!=a[j])
    	{
    	 	 int t = a[i];
     		 a[i] = a[j];
    		 a[j] = t;
    	}
    }
}
int max(int a, int b)
{
  return (a >= b)? a: b;
}
int height(struct Bstnode *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}    
struct Bstnode *rightRotate(struct Bstnode *y)
{
    struct Bstnode *x = y->left;
    struct Bstnode *T2 = x->right;
 
    x->right = y;
    y->left = T2;
 
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
 
    return x;
}
struct Bstnode *leftRotate(struct Bstnode *x)
{
    struct Bstnode *y = x->right;
    struct Bstnode *T2 = y->left;
 
    y->left = x;
    x->right = T2;
 
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
 
    return y;
}
int getBalance(struct Bstnode *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
struct Bstnode* insert(struct Bstnode* node, char* name, int doc_id, int word_count)
{
    if (node == NULL)
    {
        struct Bstnode *temp =  (struct Bstnode *)malloc(sizeof(struct Bstnode));
        temp->doc_id = doc_id;
        temp->name = name;
        temp->word_count = word_count;
        temp->height = 1;
        temp->left = temp->right = NULL;inserts++;
        return temp;
    }
 
    else
    {
        if (doc_id < node->doc_id)
            node->left  = insert(node->left, name,doc_id,word_count);
        else if(doc_id > node->doc_id)
            node->right = insert(node->right, name,doc_id,word_count); 
        else  return node; 
    }
    
    node->height = 1 + max(height(node->left),height(node->right)); 
    int balance = getBalance(node);
 
    // Left Left Case
    if (balance > 1 && doc_id < node->left->doc_id)
        return rightRotate(node);
 
    // Right Right Case
    if (balance < -1 && doc_id > node->right->doc_id)
        return leftRotate(node);
 
    // Left Right Case
    if (balance > 1 && doc_id > node->left->doc_id)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
 
    // Right Left Case
    if (balance < -1 && doc_id < node->right->doc_id)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}
void inorder(struct Bstnode *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d %s %d %d\n", root->word_count,root->name,root->doc_id,++i);
        inorder(root->right);
    }
}
void tree_delete(struct Bstnode* root) 
{
    if (root == NULL) return;
    tree_delete(root->left);
    tree_delete(root->right);
    free(root);
}
int checkBST(struct Bstnode *root,struct Bstnode *l,struct Bstnode *r)
{
    if (root == NULL)
        return 0;
    if (l != NULL && root->doc_id < l->doc_id)
        return -1;
    if (r != NULL && root->doc_id > r->doc_id)
        return -1;
    return checkBST(root->left, l, root) && checkBST(root->right, root, r);
}
int Balanced(struct Bstnode *root)
{
   int lh,rh;
   if(root == NULL)
    return 1; 
 
   lh = height(root->left);
   rh = height(root->right);
 
   if( abs(lh-rh) <= 1 &&  Balanced(root->left) &&  Balanced(root->right))
	   return 1;

   return 0;
}
int countnodes (struct Bstnode* root)
{
    if (root == NULL)
     return 0;
    return countnodes (root->left) + countnodes (root->right) + 1;
}

int bstdb_init ( void ) 
{
	for(int i = 0; i<n; i++) a1[i] = i;
	randomize(a1,n);
	return 1;
}
int bstdb_add ( char *name, int word_count )
{
  	root=insert(root,name,a1[++m],word_count);
   	return a1[m];
}
int bstdb_get_word_count ( int doc_id )
{
	struct Bstnode *runner; 
    runner = root;
    while (1) 
    {
        cmp++;
    	if (runner == NULL) 
    		{cmp++;return -1;}  
    	else if (doc_id==runner->doc_id)
    	    {searches++;cmp++;return runner->word_count;}
    	else if (doc_id<runner->doc_id) 
    	    {runner = runner->left;}
    	else 
    		runner = runner->right;
    }
}
char* bstdb_get_name ( int doc_id ) 
{
	struct Bstnode *runner; 
    runner = root;
    while (1) 
    {
        cmp++;
    	if (runner == NULL) 
    		{cmp++;return NULL;}  
    	else if (doc_id==runner->doc_id)
    	    {searches++;cmp++;return runner->name;}
    	else if (doc_id<runner->doc_id) 
    	    {runner = runner->left;}
    	else 
    		runner = runner->right;
    }
}
void bstdb_stat ( void ) {
//	inorder(root);
	printf("\nSTAT:-\n~~~~~~~~~~~~~\n");

	printf("\nAvg comparisons per search  ->%f",(cmp/searches));
	printf("\nList size matches expected? ->");
	if(inserts==countnodes(root)) printf("Y\n");
	else printf("N\n");

	printf("\nCheck if it is a BST or not:-\n");
	if(checkBST(root,NULL,NULL)==0) printf("It is a Bst.\nAnd all the values are unique.\n");
	else printf("It is not a Bst\n");

	printf("\nHeight of the tree: %d\n",height(root));

    printf("\nPrinting the no. of nodes: %d\n",countnodes(root));

	printf("\nCheck if BST is a balanced or not:-\n");
	if(Balanced(root)) printf("It is balanced\n");
	else printf("It is not a balanced\n");

	printf("\n\n");
}
void bstdb_quit ( void )
{
	tree_delete(root);
}