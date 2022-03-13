#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    long long int nim;
    char name[18], email[23];
    struct student* next;
};

struct student* display(struct student* start){
    struct student* ptr = start;
    int index = 1;
    
    printf("\n                       === Student List ===                       \n");
    printf("._____.____________________.____________.________________________.\n");
    printf("| No. |        Nama        |    NIM     |         Email          |\n");
    printf("'-----'--------------------'------------'------------------------'\n");
    while(ptr != NULL){
        printf("| %2d. | %-18s | %-10lld | %-22s |\n", index, ptr -> name, ptr -> nim, ptr -> email);
        ptr = ptr -> next;
        index++;
    }
    printf("|_____|____________________|____________|________________________|\n\n");

    return start;
}

struct student* pop_head(struct student* start){
    if (start != NULL){
        struct student* ptr = start;
        start = start -> next;
        free(ptr);
    }
    return start;
}

struct student* pop_tail(struct student* start){
    if (start != NULL){
        struct student* ptr = start;
        struct student* preptr = start;
        
        while(ptr -> next != NULL){
            preptr = ptr;
            ptr = ptr -> next;
        }

        preptr -> next = NULL;
        free(ptr);
    }
    return start;
}

struct student* pop_before_node(struct student* start, int node_value){
    if (start != NULL){
        struct student* ptr = start;
        struct student* preptr = start;
        
        while(ptr -> next -> nim != node_value){
            preptr = ptr;
            ptr = ptr -> next;
        }

        preptr -> next = ptr -> next;
        free(ptr);
    }
    return start;
}

struct student* pop_after_node(struct student* start, int node_value){
    if (start != NULL){
        struct student* ptr = start;
        struct student* preptr = start;
        
        while(preptr -> nim != node_value){
            preptr = ptr;
            ptr = ptr -> next;
        }

        preptr -> next = ptr -> next;
        free(ptr);
    }
    return start;
}

struct student* push_head(struct student* start, char* name, long long int nim, char* email){
    if (start != NULL){
        struct student* ptr = start;
        struct student* new_node = NULL;
        
        new_node = (struct student*) malloc(sizeof(struct student));
        start = new_node;
        strcpy(new_node -> name, name);
        new_node -> nim = nim;
        strcpy(new_node -> email, email);
        new_node -> next = ptr;
        
    }

    return start;
}

struct student* push_tail(struct student* start, char* name, int nim, char* email){
    if (start != NULL){
        struct student* ptr = start;
        struct student* new_node = NULL;

        new_node = (struct student*) malloc(sizeof(struct student));
        strcpy(new_node -> name, name);
        new_node -> nim = nim;
        strcpy(new_node -> email, email);
        new_node -> next = NULL;

        while (ptr -> next != NULL){
            ptr = ptr -> next;
        }
        ptr -> next = new_node;
    }
    return start;
}

struct student* push_after_node(struct student* start, int node_value, char* name, int nim, char* email){
    if (start != NULL){
        struct student* ptr = start;
        struct student* new_node = NULL;

        new_node = (struct student*) malloc(sizeof(struct student));
        strcpy(new_node -> name, name);
        new_node -> nim = nim;
        strcpy(new_node -> email, email);

        while (ptr -> nim != node_value){
            ptr = ptr -> next;
        }

        new_node -> next = ptr -> next;
        ptr -> next = new_node;       
    }

    return start;
}

struct student* push_before_node(struct student* start, int node_value, char* name, int nim, char* email){
    if (start != NULL){
        struct student* ptr = start;
        struct student* preptr = start;
        struct student* new_node = NULL;

        new_node = (struct student*) malloc(sizeof(struct student));
        strcpy(new_node -> name, name);
        new_node -> nim = nim;
        strcpy(new_node -> email, email);

        while (ptr -> nim != node_value){
            preptr = ptr;
            ptr = ptr -> next;
        }
        
        new_node -> next = ptr;
        preptr -> next = new_node;
    }

    return start;
}

int search_nim(struct student* start, long long int nim){
    struct student* ptr = start; 

    while (ptr -> next != NULL){
        if (ptr -> nim == nim){
            return 1;
        }
        ptr = ptr -> next;
    }

    return 0;
}

int main(){

    struct student* head = NULL;
    struct student* second = NULL;
    struct student* third = NULL;

    head = (struct student*) malloc(sizeof(struct student));
    second = (struct student*) malloc(sizeof(struct student));
    third = (struct student*) malloc(sizeof(struct student));

    strcpy(head -> name, "Benediktus");
    head -> nim = 2502021234;
    strcpy(head -> email, "benediktus@binus.ac.id");
    head -> next = second;

    strcpy(second -> name, "Hengki");
    second -> nim = 2502021235;
    strcpy(second -> email, "hengki@binus.ac.id");
    second -> next = third;

    strcpy(third -> name, "Setiawan");
    third -> nim = 2502021236;
    strcpy(third -> email, "setiawan@binus.ac.id");
    third -> next = NULL;

    do{

        int choice;
        long long int nim, nodeVal;
        char name[18], email[23];
        printf("============== Menu ==============\n");
        printf("1. Add a node at the beginning\n");
        printf("2. Add a node at the end\n");
        printf("3. Add before a node\n");
        printf("4. Add after a node\n");
        printf("5. Delete the first node\n");
        printf("6. Delete the last node\n");
        printf("7. Delete before a node\n");
        printf("8. Delete after a node\n");
        printf("9. Display a table of nodes\n");
        printf("0. Exit\n");
        printf("Enter your choice [0-9] : ");
        scanf("%d", &choice);

        switch (choice){
            case 1:
                printf("Enter name : ");    
                scanf("\n%[^\n]s", &name);
                printf("Enter nim [10 digits] : ");
                scanf("%lld", &nim);
                printf("Enter email [max. 22 char] : ");
                scanf("\n%[^\n]s", &email);

                head = push_head(head, name, nim, email);
                system("pause");
                break;

            case 2:
                printf("Enter name : ");    
                scanf("\n%[^\n]", &name);
                printf("Enter nim [10 digits] : ");
                scanf("%lld", &nim);
                printf("Enter email [max. 22 char] : ");
                scanf("\n%[^\n]", &email);
                    
                head = push_tail(head, name, nim, email);
                system("pause");
                break;

            case 3:
                printf("Search student nim : ");  
                scanf("%lld", &nodeVal);    
                if (!search_nim(head, nodeVal)){
                    printf("-- NIM not found --\n");
                }
                else {
                    printf("\nNew student:\n");
                    printf("Enter name : ");    
                    scanf("\n%[^\n]", &name);
                    printf("Enter nim [10 digits] : ");
                    scanf("%lld", &nim);
                    printf("Enter email [max. 22 char] : ");
                    scanf("\n%[^\n]", &email);                    
                    head = push_before_node(head, nodeVal, name, nim, email);
                }

                system("pause");
                break;

            case 4:
                printf("Search student nim : ");  
                scanf("%lld", &nodeVal);    
                if (!search_nim(head, nodeVal)){
                    printf("-- NIM not found --\n");
                }
                else {
                    printf("\nNew student:\n");
                    printf("Enter name : ");    
                    scanf("\n%[^\n]", &name);
                    printf("Enter nim [10 digits] : ");
                    scanf("%lld", &nim);
                    printf("Enter email [max. 22 char] : ");
                    scanf("\n%[^\n]", &email);                    
                    head = push_after_node(head, nodeVal, name, nim, email);
                }

                system("pause");
                break;

            case 5:
                head = pop_head(head);
                system("pause");
                break;

            case 6:
                head = pop_tail(head);
                system("pause");
                break;

            case 7:
                printf("Search student nim : ");      
                scanf("%lld", &nodeVal);
                if (!search_nim(head, nodeVal)){
                    printf("-- NIM not found --\n");
                }
                else {
                    
                }
                head = pop_before_node(head, nodeVal);
                system("pause");
                break;

            case 8:
                printf("Search student nim : ");      
                scanf("%lld", &nodeVal);
                if (!search_nim(head, nodeVal)){
                    printf("-- NIM not found --\n");
                }
                else {
                    
                }
                head = pop_after_node(head, nodeVal);
                system("pause");
                break;

            case 9:
                head = display(head);
                system("pause");
                break;

            case 0:
                exit(0);
                break;

            default:
                break;
        }
        system("cls");

    }while (1);

    return 0;
}
