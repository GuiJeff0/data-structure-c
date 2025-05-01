#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/*
POST /students: cadastra um estudante com nome e nota (0 a 10)
GET /students: retorna uma lista com os estudantes cadastrados (exibindo id, nome e nota)
GET /students/:id: retorna os dados de um estudante específico pelo id (id, nome, nota)

##Requisitos:

*O armazenamento pode ser feito em memória (array, lista) ou em banco de dados, 
conforme a preferência do candidato

*Deve validar se a nota está entre 0 e 10

*Deve funcionar com pelo menos 3 registros diferentes

*Para toda rota GET, adicionar um campo que retorna a primeira letra do nome que não se repete. Se todas as letras se repetirem, retornar '_'.
Exemplo: Se houver um estudante chamado "Gabriel", a letra não repetida do nome é 'g'. 
Se houver um estudante chamado "Anna", todas as letras se repetem, então o valor retornado deve ser '_'.****

*/

#define HASH_TABLE_SIZE 100

typedef struct Student {
    int id;
    char name[60];
    float grade;
} Student;

typedef struct Node {
    Student student;
    struct Node* next;
} Node;

Node* listHashTable[HASH_TABLE_SIZE];
int next_id = 1;


int hash(int id) {
    return id % HASH_TABLE_SIZE;
}


char findUniqueLetter(const char* name) {
    int count[256] = {0};
    for (int i = 0; name[i]; i++) {
        char c = tolower(name[i]);
        if (c != ' ')
            count[(unsigned char)c]++;
    }
    for (int i = 0; name[i]; i++) {
        char c = tolower(name[i]);
        if (c != ' ' && count[(unsigned char)c] == 1)
            return c;
    }
    return '_';
}



void insertStudent(char* name, float grade) {
    if (grade < 0 || grade > 10) {
        printf("Estudante nao cadastrado\nNota deve estar entre 0 e 10.\n");
        return;
    }

    Student s;
    s.id = next_id++;
    strcpy(s.name, name);
    s.grade = grade;

    int index = hash(s.id);
    Node* new_node = malloc(sizeof(Node));
    new_node->student = s;
    new_node->next = listHashTable[index];
    listHashTable[index] = new_node;
}


void allStudents() {
    printf("Lista de estudantes:\n");
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        Node* current = listHashTable[i];
        while (current) {
            Student s = current->student;
            char unique = findUniqueLetter(s.name);
            printf("{\n");
            printf("\"id\": \"%d\",\n", s.id);
            printf("\"nome\": \"%s\",\n", s.name);
            printf("\"nota\": \"%.2f\",\n", s.grade);
            printf("\"letra_unica\": \"%c\"\n", unique);
            printf("},\n");
            current = current->next;
        }
    }
}


void getStudent(int id) {
    int index = hash(id);
    Node* current = listHashTable[index];
    while (current) {
        if (current->student.id == id) {
            Student s = current->student;
            char unique = findUniqueLetter(s.name);
            printf("{\n");
            printf("\"id\": \"%d\",\n", s.id);
            printf("\"nome\": \"%s\",\n", s.name);
            printf("\"nota\": \"%.2f\",\n", s.grade);
            printf("\"letra_unica\": \"%c\"\n", unique);
            printf("},\n");
            return;
        }
        current = current->next;
    }
    printf("Estudante com id %d nao encontrado.\n", id);
}

void menu() {
    int choice;
    char input[10];

    while (1) {
        printf("\nEscolha uma opcao:\n");
        printf("1 - Cadastrar estudante (POST /students)\n");
        printf("2 - Listar estudantes (GET /students)\n");
        printf("3 - Buscar estudante por ID (GET /students/{id})\n");
        printf("0 - Sair\n");

        fgets(input, sizeof(input), stdin);
        if (sscanf(input, "%d", &choice) != 1) {
            printf("Entrada invalida. Digite um numero.\n");
            continue;
        }

        if (choice == 0) break;

        if (choice == 1) {
            char name[100];
            float grade;
            printf("Nome: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = 0;

            printf("Nota: ");
            fgets(input, sizeof(input), stdin);
            if (sscanf(input, "%f", &grade) != 1) {
                printf("Nota invalida.\n");
                continue;
            }

            insertStudent(name, grade);
        } else if (choice == 2) {
            allStudents();
        } else if (choice == 3) {
            int id;
            printf("ID: ");
            fgets(input, sizeof(input), stdin);
            if (sscanf(input, "%d", &id) != 1) {
                printf("ID invalido.\n");
                continue;
            }
            getStudent(id);
        } else {
            printf("Erro: Opcao invalida\n");
        }
    }
}


int main() {
    menu();
    return 0;
}

