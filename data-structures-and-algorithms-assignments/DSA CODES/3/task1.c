#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
struct Tree_Node 
{
    char item;
    struct Tree_Node *left;
    struct Tree_Node *right;
}*root=NULL;
void tree_print_sorted(struct Tree_Node *root) 
{
    if (root!= NULL) 
    {  
    	tree_print_sorted( root->left ); 
        printf("%c ",root->item);  
        tree_print_sorted( root->right );
    }
} 
struct Tree_Node* tree_search(struct Tree_Node *root,char item) 
{
    struct Tree_Node *runner; 
    runner = root;
    while (1) 
    {
    	if (runner == NULL) 
    		return root;  
    	else if ((int)item==(int)(runner->item))
    	    return runner;
    	else if ((int)item<(int)(runner->item)) 
    	    runner = runner->left;
    	else 
    		runner = runner->right;
    }  
}
void tree_insert(struct Tree_Node **root, char data) 
{
	if (!*root) 
	{
	   printf("%c ",data);
       struct Tree_Node *newnode = malloc(sizeof(struct Tree_Node));
       newnode->item = data;
       newnode->left = NULL;
       newnode->right = NULL;
       *root = newnode;
    }
    else 
    {
       if ((int)((*root)->item)>(int)data)
          tree_insert(&(*root)->left,data);
       else 
          tree_insert(&(*root)->right,data);
    }
}
void tree_delete(struct Tree_Node* root) 
{
    if (root == NULL) return;
    tree_delete(root->left);
    tree_delete(root->right);
    printf("%c ", root->item);
    free(root);
}
int main()
{
	srand(time(NULL));
	char data1 = 'A' + (rand() % 26);
	char data2 = 'A' + (rand() % 26);
	root=NULL;
    printf("\nADDING:  ");
    tree_insert(&root,'F');tree_insert(&root,'L');tree_insert(&root,'O');tree_insert(&root,'C');
    tree_insert(&root,'C');tree_insert(&root,'I');tree_insert(&root,'N');tree_insert(&root,'A');
    tree_insert(&root,'U');tree_insert(&root,'C');tree_insert(&root,'I');tree_insert(&root,'N');
    tree_insert(&root,'I');tree_insert(&root,'H');tree_insert(&root,'I');tree_insert(&root,'L');
    tree_insert(&root,'I');tree_insert(&root,'P');tree_insert(&root,'I');tree_insert(&root,'L');
    tree_insert(&root,'I');tree_insert(&root,'F');tree_insert(&root,'I');tree_insert(&root,'C');
    tree_insert(&root,'A');tree_insert(&root,'T');tree_insert(&root,'I');tree_insert(&root,'O');
    tree_insert(&root,'N');
    printf("\nSORTED:  ");tree_print_sorted(root);printf("\n\n");
	if((int)data1==(int)(tree_search(root,data1)->item))
		printf("%c is FOUND\n",data1);
	else
 		printf("%c is NOT FOUND\n",data1);
    if((int)data2==(int)(tree_search(root,data2)->item))
		printf("%c is FOUND\n",data2);
	else
 		printf("%c is NOT FOUND\n",data2);
    printf("\nDELETED: ");tree_delete(root);printf("\n\n");
    return 0;
}