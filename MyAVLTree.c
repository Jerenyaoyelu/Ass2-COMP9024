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

// increase height
void increaseH(AVLTreeNode *N){
	AVLTreeNode *current;
	current = N;
	while(current->parent!=NULL){
		current->height++;
		current = current->parent;
	}
}

//rotation
AVLTree *rotation(AVLTree *unbalancedT, AVLTreeNode *insertedN){
	AVLTree *balancedT;
	if(unbalancedT->size <= 1){
		return unbalancedT;
	}else{
		// find x,y,z
		AVLTreeNode *x=NULL, *y=NULL, *z = NULL;
		AVLTreeNode *a, *b, *c;
		AVLTreeNode *current = insertedN;
		while(1){
			if(isBalance(current->parent)){
				current = current->parent;
			}else{
				break;
			}
		}
		z = current;
		if(z->left->height >= z->right->height){
			y = z->left;
		}else{
			y = z->right;
		}
		if(y->left->height >= y->right->height){
			x = y->left;
		}else{
			x = y->right;
		}
		// assign a,b,c
		if(comparasion(x,y->key,y->value)>=0){
			c = x;
			a = y;
			if(comparasion(y,z->key,z->value)>=0){
				a = z;
				b = y;
			}else{
				if(comparasion(x,z->key,z->value)>=0){
					b = z;
				}else{
					b = x;
					c = z;
				}
			}
		}else{
			a = x;
			c = y;
			if(comparasion(y,z->key,z->value)>=0){
				if(comparasion(x,z->key,z->value)>=0){
					a = z;
					b = x;
				}else{
					b = z;
				}
			}else{
				b = y;
				c = z;
			}
		}
		//restructring the tree
		b->parent = z->parent;
		if(b->left != NULL){
			a->right = b->left;
		}
		b->left = a;
		if(b->right != NULL){
			c->left = b->right;
		}
		b->right = c;
		//assign the balanced tree
		balancedT = unbalancedT;
		return balancedT;
	}
}

// return NULL when it is an empty tree, otherwise, return the node being about to be the parent of the new node.
AVLTreeNode *BS(AVLTreeNode *Root, int k, int v)
{
  // put your code here
	AVLTreeNode *position;
	if(Root == NULL){
		// The tree is empty, so return the T itself.
		return NULL;
	}else if(comparasion(Root,k,v)>=0){
		// return a node when it is not empty.
		if (Root->left == NULL){
			position = Root;
		}
		position = BS(Root->left, k,v);
	}else{
		if (Root->right == NULL){
			position = Root;
		}
		position = BS(Root->right, k,v);
	}
	return position;
}

// put the time complexity analysis for InsertNode() here    
int InsertNode(AVLTree *T, int k, int v)
{
	//have to apply rotation after each insertion.
	//put your code here

	//serach for the inserting position
	AVLTreeNode *node;
	AVLTreeNode *newNode;
	AVLTree *balancedTree;
	newNode->key = k;
	newNode->value = v;
	node = BS(T,k,v);
	// insert new node
	if (node == NULL){
		T->root = newNode;
	}else{
		if(comparasion(node,k,v)>=0){
			node->left = newNode;
		}else{
			node->right = newNode;
		}
		newNode->parent = node;
		// increase all the parent's height by 1 after inserting a node
		increaseH(node);
	}
	// increase the size of the tree
	T->size++;
	// do rotation
	balancedTree = rotation(T,newNode);
	return balancedTree;
}

// put your time complexity for DeleteNode() here
int DeleteNode(AVLTree *T, int k, int v)
{
 // put your code here
}

// Compare two nodes
// returns 1 when the about-to-insert node is smaller; 
// returns 0 when they are equal; returns -1 when he about-to-insert node is bigger.
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

// count the size from the current node
// int size(AVLTreeNode *node){
// 	if(node == NULL){
// 		return 0;
// 	}else{
// 		return (size(node->left)+size(node->right)+1);
// 	}
// }

// put your time complexity analysis for Search() here
// This function is just for search the specific node
AVLTreeNode *Search(AVLTree *T, int k, int v)
{
	AVLTreeNode *Target;
  // put your code here
	if(T->root == NULL){
		// The tree is empty, so return NULL.
		return NULL;
	}else{
		// return a node if it finds the item, otherwise, return NULL.
		AVLTree *subtree;
		if(comparasion(T->root,k,v) == 0){
			return T->root;
		}else if(comparasion(T->root,k,v) > 0){
			if(T->root->left != NULL){
				// make the left part as a subtree for recursion
				// attention: the size of this subtree will always be 0, because we did not calculate it due to its uselessness here.
				subtree->root = T->root->left;
				Target = Search(subtree, k,v);
			}
		}else{
			if(T->root->right != NULL){
				// make the right part as a subtree for recursion
				subtree->root = T->root->right;
				Target = Search(subtree, k,v);
			}
		}
	}
	return Target;
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
