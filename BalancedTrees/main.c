#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*
 *Autores: Guilherme Sant
 *Data: 01/02/2024

 */

struct treeNode {
  int data;
  struct treeNode *leftPtr;
  struct treeNode *rightPtr;
};

typedef struct treeNode TreeNode;
typedef TreeNode *TreeNodePtr;

/*Prototype */
void insertNode(TreeNodePtr *treePtr, int value);
void listNode(TreeNodePtr treePtr);
void printTreeValue(int data, int tamSpace);
void showTree(TreeNodePtr treeNode, int tamSpace);
int levelTree(TreeNodePtr root);


//---  Main Function  ---//
int main(void) {
  int item;
  srand(time(NULL));

  TreeNodePtr rootPtr = NULL;

/*
  for (int i = 1; i <= 10; i++) {
    item = rand() % 100;
    insertNode(&rootPtr, item);

  }*/
  insertNode(&rootPtr, 24);
  insertNode(&rootPtr, 2);
  insertNode(&rootPtr, 30);
  insertNode(&rootPtr, 4);


  TreeNodePtr node = rootPtr;
  int level = levelTree(rootPtr);

  printf("\nNivel: %d\n", level);
  showTree(rootPtr, 0);

  printf("\nOrdem de inserção!\n");
  listNode(rootPtr);
  printf(" End\n");
}
//--- End Main  ---//



// Show a binary tree on the screen in a hierarchical manner //
void showTree(TreeNodePtr treeNode, int tamSpace) { 
	
/*
// The "tamSpace" variable controls the amount of space 
(and indentation) each node should have relative to the tree level
*/

if (treeNode == NULL) {
    printTreeValue('*', tamSpace);
    return;
}
showTree(treeNode->rightPtr, tamSpace+1);
printTreeValue(treeNode->data, tamSpace);
showTree(treeNode->leftPtr, tamSpace+1);
}

//This function prints the value of a node on the screen, with a specific indentation determined by the tamSpace variable.
void printTreeValue(int data, int tamSpace) {
  int i;
  for (i = 0; i < tamSpace; i++){
    printf("   ");
  }
  printf("%d\n", data);
}

// End Functions Screen //


void insertNode(TreeNodePtr *treePtr, int value) {
    if (*treePtr == NULL) {
        *treePtr = malloc(sizeof(TreeNode));
        (*treePtr)->data = value;
        (*treePtr)->leftPtr = NULL;
        (*treePtr)->rightPtr = NULL;
    } else {
        if (value < (*treePtr)->data) {
            insertNode(&((*treePtr)->leftPtr), value);
        } else if (value > (*treePtr)->data) {
            insertNode(&((*treePtr)->rightPtr), value);
        }
    }
}

void listNode(TreeNodePtr treePtr) {
  if(treePtr != NULL){
    printf("%d ->", treePtr->data);
    listNode(treePtr->leftPtr);
    listNode(treePtr->rightPtr);
  }
}



int levelTree(TreeNodePtr root) {
  if(root == NULL){
  	return -1;
  } else {
  	int treeLeft = levelTree(root->leftPtr);
  	int treeRight = levelTree(root->rightPtr);

  	if(treeLeft > treeRight){
  		return treeLeft + 1;
  	} else {
  		return treeRight + 1;
  	}
  }
}

