/*
 int arr[] = {5, 4, 7, 2, 11};
    int n = sizeof(arr)/sizeof(arr[0]);
 	treeSort(arr, n);
	root = NULL;    // Start with empty tree.
    build_tree();   // Insert words from data into tree.  Also modifies
                //   the data by replacing each \n with a 0.
 
    cout << "Sorted Array : ";
    for (int i=0; i<n; i++)
       cout << arr[i] << " ";
 
void preorderPrint(struct Tree_node *root ) {
           // Print all the items in the tree to which root points.
           // The item in the root is printed first, followed by the
           // items in the left subtree and then the items in the
           // right subtree.
        if ( root != NULL ) {  // (Otherwise, there's nothing to print.)
           printf("%s ",root->item);      // Print the root item.
           preorderPrint( root->left );    // Print items in left subtree.
           preorderPrint( root->right );   // Print items in right subtree.
        }
     }


// A utility function to create a new BST Node
struct Node *newNode(int item)
{
    struct Node *temp = new Node;
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}
void storeSorted(Node *root, int arr[], int &i)
{
    if (root != NULL)
    {
        storeSorted(root->left, arr, i);
        arr[i++] = root->key;
        storeSorted(root->right, arr, i);
    }
}
void treeSort(int arr[], int n)
{
    struct Node *root = NULL;
    root = insert(root, arr[0]);
    for (int i=1; i<n; i++)
        insert(root, arr[i]);
    int i = 0;
    storeSorted(root, arr, i);
}
 
// Driver Program to test above functions


       // end preorderPrint()
     void postorderPrint( Tree_node *root ) {
           // Print all the items in the tree to which root points.
           // The items in the left subtree are printed first, followed 
           // by the items in the right subtree and then the item in the
           // root node.
        if ( root != NULL ) {  // (Otherwise, there's nothing to print.)
           postorderPrint( root->left );    // Print items in left subtree.
           postorderPrint( root->right );   // Print items in right subtree.
           printf("%p ",root->item);       // Print the root item.
        }
     } // end postorderPrint()

void read_data() {
   FILE *f = fopen("unsorted_words.dat", "r"); // open file for reading.
   if (!f) {
       printf("Can't open file unsorted_words.dat for reading.\n");
       exit(1);  
   }
   fseek(f,0,SEEK_END);  // move file pointer to end of file.
   data_size = ftell(f); // get current file pointer value; this will
                         //    be the number of bytes in the file.
   rewind(f);  // move the file pointer back to start of file.
   data = malloc(data_size);  // allocate memory to hold entire file contents
   size_t bytesread = fread( data, 1, data_size, f);
   if (bytesread != data_size) {
       printf("Couldn't read data from file unsorted_words.dat.\n");
       exit(1);  
   }
   // printf("Read %d bytes from file unsorted_words.dat.\n", data_size);
}

/*-------------------- Binary Sort Tree implementation -----------------*/

/* Insert a string into a binary sort tree.  The second parameter
 * should be the address of the variable that holds a pointer to the
 * root of the tree.
 
void tree_insert( char *str, struct Tree_node **tree) {
   if ( ! *tree ) {
       struct Tree_node *newnode = malloc(sizeof(struct Tree_node));
       newnode->item = str;
       newnode->left = NULL;
       newnode->right = NULL;
       *tree = newnode;
   }
   else {
       int cmp = strcmp( str, (*tree)->item );
       if (cmp < 0)
          tree_insert( str, &(*tree)->left );
       else if (cmp > 0)
          tree_insert( str, &(*tree)->right );
   }
}

*/