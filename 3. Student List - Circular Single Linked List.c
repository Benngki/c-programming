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
    
    if (start != NULL){
        printf("\n                       === Student List ===                       \n");
        printf("._____.____________________.____________.________________________.\n");
        printf("| No. |        name        |    NIM     |         Email          |\n");
        printf("'-----'--------------------'------------'------------------------'\n");
        do {
            printf("| %2d. | %-18s | %-10lld | %-22s |\n", index, ptr -> name, ptr -> nim, ptr -> email);
            ptr = ptr -> next;
            index++;
        } while(ptr != start);
        printf("|_____|____________________|____________|________________________|\n\n");
    }
    else {
        printf("-- The list is empty --\n");
    }

    return start;
}

struct student* pop_head(struct student* start){
    if (start != NULL){
        struct student* ptr = start;

        while (ptr -> next != start){
            ptr = ptr -> next;
        }
        
        ptr -> next = start -> next;
        
        free(start);
        start = ptr -> next;
    }
    else{
        printf("-- The list is empty --\n");
    }
    
    return start;
}

struct student* pop_tail(struct student* start){
    if (start != NULL){
        struct student* ptr = start;
        struct student* preptr = start;
        
        while(ptr -> next != start){
            preptr = ptr;
            ptr = ptr -> next;
        }

        preptr -> next = start;
        free(ptr);
    }
    
    else{
        printf("-- The list is empty --\n");
    }
    return start;
}

struct student* pop_before_node(struct student* start, long long int node_value){
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
    else{
        printf("-- The list is empty --\n");
    }
    return start;
}

struct student* pop_after_node(struct student* start, long long int node_value){
    if (start != NULL){
        struct student* ptr = start;
        struct student* preptr = start;
        
        while(preptr -> nim != node_value){
            preptr = ptr;
            ptr = ptr -> next;
        }

        preptr -> next = ptr -> next;
        free(ptr);
    }else{
        printf("-- The list is empty --\n");
    }

    return start;
}

struct student* push_head(struct student* start, char* name, long long int nim, char* email){
    if (start != NULL){
        struct student* ptr = start;
        struct student* new_node = NULL;
        
        new_node = (struct student*) malloc(sizeof(struct student));
        
        strcpy(new_node -> name, name);
        new_node -> nim = nim;
        strcpy(new_node -> email, email);
        
        ptr = start;
        while (ptr -> next != start){
            ptr = ptr -> next;
        }

        new_node -> next = start;
        ptr -> next = new_node;
        start = new_node;
        
    }

    return start;
}

struct student* push_tail(struct student* start, char* name, long long int nim, char* email){
    if (start != NULL){
        struct student* ptr = start;
        struct student* new_node = NULL;

        new_node = (struct student*) malloc(sizeof(struct student));
        strcpy(new_node -> name, name);
        new_node -> nim = nim;
        strcpy(new_node -> email, email);

        while (ptr -> next != start){
            ptr = ptr -> next;
        }

        ptr -> next = new_node;
        new_node -> next = start;

    }
    return start;
}

struct student* push_after_node(struct student* start, long long int node_value, char* name, long long int nim, char* email){
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

struct student* push_before_node(struct student* start, long long int node_value, char* name, long long int nim, char* email){
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

    while (ptr -> nim != nim){
        if (ptr -> next == NULL){
            return 0;
        }
        ptr = ptr -> next;
    }

    return 1;
}

struct student* create_cll(struct student* start){
    struct student* ptr = NULL;
    long long int nim, nodeVal;
    char name[18], email[23];

    if (start == NULL){
        printf("Enter -1 to end\n");
        printf("Enter name : ");    
        scanf("\n%[^\n]s", &name);

        while (strcmp(name, "-1") != 0){    
            struct student* new_node = NULL;    
            new_node = (struct student*) malloc(sizeof(struct student));

            printf("Enter nim [10 digits] : ");
            scanf("%lld", &nim);
            printf("Enter email [max. 22 char] : ");
            scanf("\n%[^\n]s", &email);

            strcpy(new_node -> name, name);
            new_node -> nim = nim;
            strcpy(new_node -> email, email);

            if (start == NULL){
                new_node -> next = new_node;
                start = new_node;
            }
            else{
                ptr = start;
                
                while (ptr -> next != start){
                    ptr = ptr -> next;
                }

                ptr -> next = new_node;
                new_node -> next = start;
                
            }

            printf("\nEnter -1 to end\n");
            printf("Enter name : ");    
            scanf("\n%[^\n]s", &name);
            
        }
    }else{
        printf("The list already created!\n");
    }

    return start;

}

int main(){

    struct student* head;

    head = (struct student*) malloc(sizeof(struct student));
    head = NULL;

    do{

        int choice;
        long long int nim, nodeVal;
        char name[18], email[23];
        printf("============== Menu ==============\n");
        printf("1. Create Circular Linked List\n");
        printf("2. Display a table of nodes\n");
        printf("3. Add a node at the beginning\n");
        printf("4. Add a node at the end\n");
        printf("5. Add before a node\n");
        printf("6. Add after a node\n");
        printf("7. Delete the first node\n");
        printf("8. Delete the last node\n");
        printf("9. Delete before a node\n");
        printf("10. Delete after a node\n");
        printf("0. Exit\n");
        printf("Enter your choice [0-10] : ");
        scanf("%d", &choice);

        switch (choice){
            case 1:
                head = create_cll(head);
                system("pause");
                break;

            case 2:
                head = display(head);
                system("pause");
                break;

            case 3:
                printf("Enter name : ");    
                scanf("\n%[^\n]s", &name);
                printf("Enter nim [10 digits] : ");
                scanf("%lld", &nim);
                printf("Enter email [max. 22 char] : ");
                scanf("\n%[^\n]s", &email);

                head = push_head(head, name, nim, email);
                system("pause");
                break;

            case 4:
                printf("Enter name : ");    
                scanf("\n%[^\n]", &name);
                printf("Enter nim [10 digits] : ");
                scanf("%lld", &nim);
                printf("Enter email [max. 22 char] : ");
                scanf("\n%[^\n]", &email);
                    
                head = push_tail(head, name, nim, email);
                system("pause");
                break;                

            case 5:
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

            case 6:
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

            case 7:
                head = pop_head(head);
                system("pause");
                break;

            case 8:
                head = pop_tail(head);
                system("pause");
                break;

            case 9:
                printf("Search student nim : ");      
                scanf("%lld", &nodeVal);
                if (!search_nim(head, nodeVal)){
                    printf("-- NIM not found --\n");
                }
                else {
                    head = pop_before_node(head, nodeVal);                    
                }
                system("pause");
                break;

            case 10:
                printf("Search student nim : ");      
                scanf("%lld", &nodeVal);
                if (!search_nim(head, nodeVal)){
                    printf("-- NIM not found --\n");
                }
                else {
                    head = pop_after_node(head, nodeVal);                    
                }
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