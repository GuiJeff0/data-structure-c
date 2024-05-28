#include <stdlib.h>
#include <stdio.h>

struct listNode{
    int data;
    struct listNode *nextPtr;
    struct listNode *previousPtr;
};

typedef struct listNode ListNode;
typedef ListNode *ListNodePtr;

void instructions(void);
void insertEnqueue(ListNodePtr *headPtr, ListNodePtr *tailPtr, int info);
void deleteEnqueue(ListNodePtr *heaPtr, ListNodePtr *tailPtr);
void printList(ListNodePtr currentPtr);
void pushStack(ListNodePtr *topPtr, int info);
void popStack(ListNodePtr *topPtr);
void printStack(ListNodePtr currentPtr);
void freeQueue(ListNodePtr *headPtr);
void freeStack(ListNodePtr *topPtr);
void insertList(ListNodePtr *headPtr, ListNodePtr *backPtr, int info, int key);
void deleteList(ListNodePtr *headPtr, ListNodePtr *backPtr, int key);


int main(){
    ListNodePtr head = NULL;
    ListNodePtr tail = NULL;
    ListNodePtr top = NULL;
    ListNodePtr listHead = NULL;
    ListNodePtr listBack = NULL;
    int choose;
    int exit = 0;
    do{
        printf("Digite 1 para inserir em fila\n");
        printf("Digite 2 para inserir em pilha\n");
        printf("Digite 3 para aleatorio\n");
        printf("Digite 4 para sair do programa\n");
        scanf("%d", &choose);

        switch (choose)
        {
        case 1:
            
            int maneiraFila;
            int valorFila;
            int endFila = 0;
            while(endFila != 1){
                instructions();
                scanf("%d", &maneiraFila);
                if(maneiraFila == 1){
                    printf("Digite o valor: ");
                    scanf("%d", &valorFila);
                    insertEnqueue(&head, &tail, valorFila);
                    printList(head);
                } else if(maneiraFila == 2){
                    deleteEnqueue(&head, &tail);
                    printList(head);
                } else if(maneiraFila == 3){
                    endFila = 1;
                } else {
                    printf("Escolha invalida!\n");
                }
            }
            break;
        case 2:
            int maneiraPilha;
            int valorPilha;
            int endPilha = 0;
            while (endPilha != 1)
            {
                instructions();
                scanf("%d", &maneiraPilha);
                if(maneiraPilha == 1){
                    printf("Digite o valor: ");
                    scanf("%d", &valorPilha);
                    pushStack(&top, valorPilha);
                    printStack(top);

                }else if(maneiraPilha == 2){
                    popStack(&top);
                    printStack(top);
                }else if(maneiraPilha == 3){
                    endPilha = 1;
                }else{
                    printf("Escolha Invalida!\n");
                }
            }
            break;
        case 3:
            int maneiraLista;
            int valorLista;
            int chaveLista;
            int endLista = 0;
            while (endLista != 1)
            {   
                
                instructions();
                scanf("%d", &maneiraLista);
                if(maneiraLista == 1){
                    printList(listHead);
                    printf("Digite uma chave: ");
                    scanf("%d", &chaveLista);
                    printf("Digite um valor: ");
                    scanf("%d", &valorLista);
                    insertList(&listHead, &listBack, valorLista, chaveLista);
                    printList(listHead);
                } else if(maneiraLista == 2){
                    printList(listHead);
                    printf("Digite uma chave a ser deletada: ");
                    scanf("%d", &chaveLista);
                    deleteList(&listHead, &listBack, chaveLista);
                    printList(listHead);
                } else if(maneiraLista == 3){
                    endLista = 1;
                } else {
                    printf("Escolha Invalida!\n");
                }
                
            }
            
         break;
        
        default:
            printf("Deletando...\n");
            freeQueue(&head);
            freeStack(&top);
            freeQueue(&listHead);
            exit=1;
            break;
        }


    }while(exit == 0);
    
    


    return 0;
}
void instructions(void){
    printf("1 -- Inserir\n");
    printf("2 -- Deletar\n");
    printf("3 -- Sair\n");
}

void insertEnqueue(ListNodePtr *headPtr, ListNodePtr *tailPtr, int info){
    ListNodePtr newPtr;
    newPtr = malloc(sizeof(ListNode));

    if(newPtr != NULL){
        newPtr->data = info;
        newPtr->nextPtr = NULL;
        newPtr->previousPtr = NULL;

        if(*headPtr == NULL && *tailPtr == NULL){
            *headPtr = newPtr;
            *tailPtr = newPtr;
        } else {
            newPtr->previousPtr = *tailPtr;
            (*tailPtr)->nextPtr = newPtr;
            *tailPtr = newPtr;
        }

    } else {
        printf("memory allocation failure\n");
        return;
    }
}

void printList(ListNodePtr currentPtr){
    if(currentPtr == NULL){
        printf("Empty list\n");
    } else {
        while(currentPtr != NULL){
            printf("%d --> ", currentPtr->data);
            currentPtr = currentPtr->nextPtr;
        }
        printf("NULL\n\n");
    }

}

void deleteEnqueue(ListNodePtr *headPtr, ListNodePtr *tailPtr){

    if(*headPtr == NULL){
        printf("Queue is empty\n");
        return;
    }

    ListNodePtr tempPtr = *headPtr;

    if ((*headPtr)->nextPtr != NULL) {
        
        (*headPtr)->nextPtr->previousPtr = NULL;
    } else {
        *tailPtr = NULL;
    }

    *headPtr = (*headPtr)->nextPtr;

    if (*headPtr != NULL) {
        (*headPtr)->previousPtr = NULL;
    }

    free(tempPtr);
}

void pushStack(ListNodePtr *topPtr, int info){
    ListNodePtr newPtr;
    newPtr = malloc(sizeof(ListNode));

    if(newPtr != NULL){
        newPtr->data = info;
        if(*topPtr == NULL){
            newPtr->nextPtr = NULL;
            newPtr->previousPtr = NULL;
            *topPtr = newPtr;
        }else{
            (*topPtr)->nextPtr = newPtr;
            newPtr->previousPtr = *topPtr;
            *topPtr = newPtr;
        }
    }else {
        printf("memory allocation failure\n");
        return;
    }
}

void popStack(ListNodePtr *topPtr){
    if(*topPtr == NULL){
        printf("Stack is empty\n");
        return;
    }

    ListNodePtr tempPtr = *topPtr;
    *topPtr = (*topPtr)->previousPtr;
    if(*topPtr != NULL){
        (*topPtr)->nextPtr = NULL;
    }

    free(tempPtr);

    
}

void printStack(ListNodePtr currentPtr){
    while(currentPtr != NULL){
        printf("%d --> ", currentPtr->data);
        currentPtr = currentPtr->previousPtr;
    }
    printf("NULL\n\n");
}

void freeQueue(ListNodePtr *headPtr){
    ListNodePtr currentPtr = *headPtr;
    ListNodePtr tempPtr;

    while(currentPtr != NULL){
        tempPtr = currentPtr;
        currentPtr = currentPtr->nextPtr;
        free(tempPtr);
    }   

    *headPtr = NULL;
}

void freeStack(ListNodePtr *topPtr){
    ListNodePtr currentPtr = *topPtr;
    ListNodePtr tempPtr;

    while(currentPtr != NULL){
        tempPtr = currentPtr;
        currentPtr =  currentPtr->previousPtr;
        free(tempPtr);
    }

    *topPtr = NULL;
}

void insertList(ListNodePtr *headPtr, ListNodePtr *backPtr, int info, int key){
    ListNodePtr newPtr;
    ListNodePtr currentPtr;
    newPtr = malloc(sizeof(ListNode));
     
     if(newPtr != NULL){
        newPtr->data = info;
        newPtr->nextPtr = NULL;
        newPtr->previousPtr = NULL;

        if(*headPtr == NULL && *backPtr == NULL){
            *headPtr = newPtr;
            *backPtr = newPtr;
        } else {
            currentPtr = *headPtr;
            while(currentPtr != NULL && currentPtr->data != key){
                currentPtr = currentPtr->nextPtr;
            }

            if(currentPtr != NULL){
                newPtr->nextPtr = currentPtr->nextPtr;
                if(currentPtr->nextPtr != NULL){
                    currentPtr->nextPtr->previousPtr = newPtr;
                }
                newPtr->previousPtr = currentPtr;
                currentPtr->nextPtr = newPtr;

                if(newPtr->nextPtr == NULL){
                    *backPtr = newPtr;
                }
            } else {
                printf("The key was not found\n");
            }
        }
     } else {
        printf("memory allocation failure\n");
        return;
     }

}

void deleteList(ListNodePtr *headPtr, ListNodePtr *backPtr, int key){
    ListNodePtr currentPtr, tempPtr;

    if(*headPtr == NULL){
        printf("Empty List\n");
        return;
    }

    currentPtr = *headPtr;

    while(currentPtr != NULL && currentPtr->data != key){
        currentPtr = currentPtr->nextPtr;
    }

    if(currentPtr != NULL){
        tempPtr = currentPtr;

        if(currentPtr->previousPtr == NULL){
            *headPtr = currentPtr->nextPtr;
            if(*headPtr != NULL){
                (*headPtr)->previousPtr = NULL;
            }
        } else {
            currentPtr->previousPtr->nextPtr = currentPtr->nextPtr;
            if(currentPtr->nextPtr != NULL){
                currentPtr->nextPtr->previousPtr = currentPtr->previousPtr;
            } else {
                *backPtr = currentPtr->previousPtr;
            }
        }

        free(tempPtr);
    } else {
        printf("The key was not found\n");
    }
}