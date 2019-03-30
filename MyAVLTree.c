#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include<stdbool.h>

// all the basic data structures and functions are included in this template
// you can add your own auxiliary functions as you like 

// data type for avl tree nodes
typedef struct AVLTreeNode {
	int key; //key of this item
	int  value;  //value (int) of this item 
	int height; //height of the subtree rooted at this node
	struct AVLTreeNode *parent; //pointer to parent
	struct AVLTreeNode *left; //pointer to left child
	struct AVLTreeNode *right; //pointer to right child
} AVLTreeNode;

//data type for AVL trees
typedef struct AVLTree{
	int  size;      // count of items in avl tree
	AVLTreeNode *root; // root
} AVLTree;

// create a new AVLTreeNode
AVLTreeNode *newAVLTreeNode(int k, int v )
{
	AVLTreeNode *new;
	new = malloc(sizeof(AVLTreeNode));
	assert(new != NULL);
	new->key = k;
	new->value = v;
	new->height = 0; // height of this new node is set to 0
	new->left = NULL; // this node has no child
	new->right = NULL;
	new->parent = NULL; // no parent
	return new;
}

// create a new empty avl tree
AVLTree *newAVLTree()
{
	AVLTree *T;
	T = malloc(sizeof (AVLTree));
	assert (T != NULL);
	T->size = 0;
	T->root = NULL;
	return T;
}

// get the key and value from a pointer,returns two integers using splitting string based on specific delimiters
int getKV(char *pointer){
	int values[2];
	// set up the delimiter to split the string
	char deli2[] ='(,)';
	char *p = strtok(&pointer,deli2);
	while(p!=NULL){
		//assign two intgers to the int array
		values[0] = atoi(&p);
		p++;
		if (p == NULL){
			printf("Errors in input!");
			exit(0);
		}else{
			values[1] = atoi(&p);
		}
		p = strtok(NULL,deli2);
	}
	int *pint = values;
	return pint;
}

// put your time complexity analysis of CreateAVLTree() here
AVLTree *CreateAVLTree(const char *filename)
{
 // create an empty tree
 AVLTree *tree;
 char data_string[255];
 if(strncmp(filename,"stdin",5)==0){
	 // set up the delimiter to split the input string line by line
	 char delimiter[] =" ";
	 while (1){
		 // assgin the input string to the data_string line by line
		  gets(data_string);
			// if it is a empty line, then the input is done, ending up reading from the standard input
			if(strlen(data_string)==0){
				break;
			}
			//take each item from the line one by one and insert them into the tree.
			char *ptr = strtok(data_string,delimiter);
			while (ptr!=NULL){
				//get the key and value from the tuple
				int *pts = getKV(ptr);
				int key, value;
				//assign key and value
				key = &pts;
				pts++;
				value = &pts;
				//insert the new item
				InsertNode(tree,key,value);
				//split the string from the next token's starting position it remembers
				ptr = strok(NULL,delimiter);
			}
	 }
 }else{
		FILE *fp;
		fp = fopen(filename,"r");
		if (fp == NULL){
			printf("Error occurs when opening file!");
			return NULL;
		}
		//iteratively read tuples until the end of the file
		while(1){
			//reads string and stops when encounter white-space or new line
			fscanf(fp,"%s",data_string);
			//end of the file
			if(feof(fp)){
				break;
			}
			char *ptr = data_string;
			//get the key and value from the tuple
			int *pts = getKV(ptr);
			int key, value;
			//assign key and value
			key = &pts;
			pts++;
			value = &pts;
			//insert the new item
			InsertNode(tree,key,value);
		}
	 }
}

// put your time complexity analysis for CloneAVLTree() here
AVLTree *CloneAVLTree(AVLTree *T)
{
 // put your code here
  
}
 
// put your time complexity for ALVTreesUNion() here
AVLTree *AVLTreesUnion(AVLTree *T1, AVLTree *T2)
{
	//put your code here
}
 
// put your time complexity for ALVTreesIntersection() here
AVLTree *AVLTreesIntersection(AVLTree *T1, AVLTree *T2)
{
	 //put your code here
}

// check if the node is in balance
bool isBalance(AVLTreeNode *newNode){
	if((newNode->height - newNode->left->height) > 2 || (newNode->height - newNode->right->height) > 2){
		return false;
	}else{
		return true;
	}
}

// put the time complexity analysis for InsertNode() here    
int InsertNode(AVLTree *T, int k, int v)
{
	//have to apply rotation after each insertion.
	//put your code here

}

// put your time complexity for DeleteNode() here
int DeleteNode(AVLTree *T, int k, int v)
{
 // put your code here
}

// Compare two nodes
int comparasion(AVLTreeNode *node,int k, int v){
	if (node->key > k){
		return 1;
	}else if(node->key == k){
		if(node->value > v){
			return 1;
		}else if(node->value == v){
			return 0;
		}else{
			return -1;
		}
	}else{
		return -1;
	}
}

// put your time complexity analysis for Search() here
AVLTreeNode *Search(AVLTree *T, int k, int v)
{
  // put your code here
	if(T->size == 0){
		// The tree is empty, so return the T itself.
		return T;
	}else{
		AVLTreeNode *current;
		
	}
}

// put your time complexity analysis for freeAVLTree() here
void FreeAVLTree(AVLTree *T)
{
// put your code here	
}

// put your time complexity analysis for PrintAVLTree() here
void PrintAVLTree(AVLTree *T)
{
 // put your code here
}

int main() //sample main for testing 
{ int i,j;
 AVLTree *tree1, *tree2, *tree3, *tree4, *tree5, *tree6, *tree7, *tree8;
 AVLTreeNode *node1;
 
 tree1=CreateAVLTree("stdin");
 PrintAVLTree(tree1);
 FreeAVLTree(tree1);
 //you need to create the text file file1.txt
 // to store a set of items without duplicate items
 tree2=CreateAVLTree("file1.txt"); 
 PrintAVLTree(tree2);
 tree3=CloneAVLTree(tree2);
 PrintAVLTree(tree3);
 FreeAVLTree(tree2);
 FreeAVLTree(tree3);
 //Create tree4 
 tree4=newAVLTree();
 j=InsertNode(tree4, 10, 10);
 for (i=0; i<15; i++)
  {
   j=InsertNode(tree4, i, i);
   if (j==0) printf("(%d, %d) already exists\n", i, i);
  }
  PrintAVLTree(tree4);
  node1 = Search(tree4,20,20);
  if (node1!=NULL)
    printf("key= %d value= %d\n",node1->key,node1->value);
  else 
    printf("Key 20 does not exist\n");
  
  for (i=17; i>0; i--)
  {
    j=DeleteNode(tree4, i, i);
	if (j==0) 
	  printf("Key %d does not exist\n",i);  
    PrintAVLTree(tree4);
  }
 FreeAVLTree(tree4);
 //Create tree5
 tree5=newAVLTree();
 j=InsertNode(tree5, 6, 25);
 j=InsertNode(tree5, 6, 10);
 j=InsertNode(tree5, 6, 12);
 j=InsertNode(tree5, 6, 20);
 j=InsertNode(tree5, 9, 25);
 j=InsertNode(tree5, 10, 25);
 PrintAVLTree(tree5);
 //Create tree6
 tree6=newAVLTree();
 j=InsertNode(tree6, 6, 25);
 j=InsertNode(tree6, 5, 10);
 j=InsertNode(tree6, 6, 12);
 j=InsertNode(tree6, 6, 20);
 j=InsertNode(tree6, 8, 35);
 j=InsertNode(tree6, 10, 25);
 PrintAVLTree(tree6);
 tree7=AVLTreesIntersection(tree5, tree6);
 tree8=AVLTreesUnion(tree5,tree6);
 PrintAVLTree(tree7);
 PrintAVLTree(tree8);
 return 0; 
}
