#include <stdio.h>
#include <stdlib.h>

/*
Data: 22/02/2024

*/

// Estrutura para representar um nó da árvore AVL
struct treeNode {
    int data;
    struct treeNode *leftPtr;
    struct treeNode *rightPtr;
    short altura;
};

typedef struct treeNode TreeNode;
typedef TreeNode *TreeNodePtr;

// Protótipos das funções
void insertNode(TreeNodePtr *treePtr, int value);
TreeNodePtr deleteNode(TreeNodePtr root, int key);
TreeNodePtr minValueNode(TreeNodePtr node);
void preOrder(TreeNodePtr treePtr);
void inOrder(TreeNodePtr treePtr);
void postOrder(TreeNodePtr treePtr);
int max(int a, int b);
int height(TreeNodePtr treePtr);
int balanceFactor(TreeNodePtr treePtr);
void rightRotate(TreeNodePtr *treePtr);
void leftRotate(TreeNodePtr *treePtr);
void balance(TreeNodePtr *treePtr);
void printTreeValue(int data, int tamSpace);
void showTree(TreeNodePtr treeNode, int tamSpace);
void deleteTree(TreeNodePtr treeNode);


// Função principal
int main() {
    TreeNodePtr rootPtr = NULL; // Inicialmente, a árvore está vazia
    int escolha;
    int end = 1;
    int value;
    
    do {
        printf("\n---------- M E N U ----------\n");
        printf("\n1 - Inserir\n");
        printf("2 - Deletar\n");
        printf("3 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1: 
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &value);
                insertNode(&rootPtr, value);
                showTree(rootPtr,0);
                printf("\nÁrvore em ordem (inOrder): ");
                inOrder(rootPtr);
                printf("\nÁrvore em pós-ordem (postOrder): ");
                postOrder(rootPtr);
                printf("\nÁrvore em pré-ordem (preOrder): ");
                preOrder(rootPtr);
                break;
            case 2:
                printf("Arvore antes da exlusão\n");
                showTree(rootPtr,0);
                printf("\nDigite o valor a ser excluído: ");
                scanf("%d", &value);
                rootPtr = deleteNode(rootPtr, value);
                showTree(rootPtr,0);
                printf("\nÁrvore em ordem (inOrder): ");
                inOrder(rootPtr);
                printf("\nÁrvore em pós-ordem (postOrder): ");
                postOrder(rootPtr);
                printf("\nÁrvore em pré-ordem (preOrder): ");
                preOrder(rootPtr);
                break;
            case 3: 
                printf("Saindo...\n");
                deleteTree(rootPtr);
                end = 0; // Sair do loop
                break;
            default:
                printf("\nEscolha inválida!\n");
                break;
        }
        
    } while (end != 0);

    return 0;
}

// Função para inserir um novo nó na árvore AVL
void insertNode(TreeNodePtr *treePtr, int value) {
    if (*treePtr == NULL) {
        *treePtr = (TreeNodePtr)malloc(sizeof(TreeNode));
        if (*treePtr == NULL) {
            printf("Erro ao alocar memória para o novo nó.\n");
            exit(1);
        }
        (*treePtr)->data = value;
        (*treePtr)->leftPtr = NULL;
        (*treePtr)->rightPtr = NULL;
        (*treePtr)->altura = 1;
    } else {
        if (value < (*treePtr)->data) {
            insertNode(&((*treePtr)->leftPtr), value);
        } else if (value > (*treePtr)->data) {
            insertNode(&((*treePtr)->rightPtr), value);
        }

        (*treePtr)->altura = 1 + max(height((*treePtr)->leftPtr), height((*treePtr)->rightPtr));

        balance(treePtr);
    }
}

// Função para percorrer a árvore em pré-ordem (raiz, esquerda, direita)
void preOrder(TreeNodePtr treePtr) {
    if (treePtr != NULL) {
        printf("%d ", treePtr->data);
        preOrder(treePtr->leftPtr);
        preOrder(treePtr->rightPtr);
    }
}

// Função para percorrer a árvore em ordem (esquerda, raiz, direita)
void inOrder(TreeNodePtr treePtr) {
    if (treePtr != NULL) {
        inOrder(treePtr->leftPtr);
        printf("%d ", treePtr->data);
        inOrder(treePtr->rightPtr);
    }
}

// Função para percorrer a árvore em pós-ordem (esquerda, direita, raiz)
void postOrder(TreeNodePtr treePtr) {
    if (treePtr != NULL) {
        postOrder(treePtr->leftPtr);
        postOrder(treePtr->rightPtr);
        printf("%d ", treePtr->data);
    }
}

// Função para calcular o máximo de dois números
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Função para obter a altura de um nó
int height(TreeNodePtr treePtr) {
    return (treePtr == NULL) ? 0 : treePtr->altura;
}

// Função para calcular o fator de balanceamento de um nó
int balanceFactor(TreeNodePtr treePtr) {
    if (treePtr == NULL) {
        return 0;
    }
    return height(treePtr->leftPtr) - height(treePtr->rightPtr);
}

// Função para realizar a rotação para a direita
void rightRotate(TreeNodePtr *treePtr) {
    TreeNodePtr leftChild = (*treePtr)->leftPtr;
    (*treePtr)->leftPtr = leftChild->rightPtr;
    leftChild->rightPtr = *treePtr;
    (*treePtr)->altura = 1 + max(height((*treePtr)->leftPtr), height((*treePtr)->rightPtr));
    leftChild->altura = 1 + max(height(leftChild->leftPtr), height(leftChild->rightPtr));
    *treePtr = leftChild;
}

// Função para realizar a rotação para a esquerda
void leftRotate(TreeNodePtr *treePtr) {
    TreeNodePtr rightChild = (*treePtr)->rightPtr;
    (*treePtr)->rightPtr = rightChild->leftPtr;
    rightChild->leftPtr = *treePtr;
    (*treePtr)->altura = 1 + max(height((*treePtr)->leftPtr), height((*treePtr)->rightPtr));
    rightChild->altura = 1 + max(height(rightChild->leftPtr), height(rightChild->rightPtr));
    *treePtr = rightChild;
}

// Função para balancear a árvore
void balance(TreeNodePtr *treePtr) {
    int bf = balanceFactor(*treePtr);

    if (bf > 1) {
        if (balanceFactor((*treePtr)->leftPtr) >= 0) {
            rightRotate(treePtr);
        } else {
            leftRotate(&((*treePtr)->leftPtr));
            rightRotate(treePtr);
        }
    } else if (bf < -1) {
        if (balanceFactor((*treePtr)->rightPtr) <= 0) {
            leftRotate(treePtr);
        } else {
            rightRotate(&((*treePtr)->rightPtr));
            leftRotate(treePtr);
        }
    }
}

// Função auxiliar para encontrar o nó com o menor valor na árvore
TreeNodePtr minValueNode(TreeNodePtr node) {
    TreeNodePtr current = node;
    while (current && current->leftPtr != NULL)
        current = current->leftPtr;
    return current;
}

// Função para excluir um nó da árvore AVL
TreeNodePtr deleteNode(TreeNodePtr root, int key) {
    if (root == NULL) return root;

    if (key < root->data)
        root->leftPtr = deleteNode(root->leftPtr, key);
    else if (key > root->data)
        root->rightPtr = deleteNode(root->rightPtr, key);
    else {
        if ((root->leftPtr == NULL) || (root->rightPtr == NULL)) {
            TreeNodePtr temp = root->leftPtr ? root->leftPtr : root->rightPtr;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;
            free(temp);
        } else {
            TreeNodePtr temp = minValueNode(root->rightPtr);
            root->data = temp->data;
            root->rightPtr = deleteNode(root->rightPtr, temp->data);
        }
    }

    if (root == NULL) return root;

    root->altura = 1 + max(height(root->leftPtr), height(root->rightPtr));

    int bf = balanceFactor(root);

    if (bf > 1 && balanceFactor(root->leftPtr) >= 0)
        rightRotate(&root);
    if (bf > 1 && balanceFactor(root->leftPtr) < 0) {
        leftRotate(&(root->leftPtr));
        rightRotate(&root);
    }
    if (bf < -1 && balanceFactor(root->rightPtr) <= 0)
        leftRotate(&root);
    if (bf < -1 && balanceFactor(root->rightPtr) > 0) {
        rightRotate(&(root->rightPtr));
        leftRotate(&root);
    }

    return root;
}

// Função para imprimir o valor de um nó na tela
void printTreeValue(int data, int tamSpace) {
    int i;
    for (i = 0; i < tamSpace; i++) {
        printf("       ");
    }
    printf("%d\n", data);
}

// Função para mostrar a árvore na tela de forma hierárquica
void showTree(TreeNodePtr treeNode, int tamSpace) {
    if (treeNode == NULL) {
        printTreeValue('*', tamSpace);
        return;
    }
    showTree(treeNode->rightPtr, tamSpace + 1);
    printTreeValue(treeNode->data, tamSpace);
    showTree(treeNode->leftPtr, tamSpace + 1);
}

// Função para liberar toda a memória alocada para os nós da árvore
void deleteTree(TreeNodePtr treeNode) {
    if (treeNode == NULL) {
        return;
    }
    deleteTree(treeNode->leftPtr);
    deleteTree(treeNode->rightPtr);
    free(treeNode);
}
