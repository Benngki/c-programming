#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

struct flight{
    struct flight* prev;
    char airline_name[51];
    char flight_id[11];
    struct flight* next;
} *flights = NULL;   

int head = 0;
int tail = 0;
int capacity;

int is_empty(){
    if (tail == 0){
        return 1;
    }else {
        return 0;
    }
}

int is_full(){
    if (tail == capacity){
        return 1;
    }else {
        return 0;
    }
}

struct flight* search_flight(char* temp){
    struct flight* ptr = flights; 

    while (strcmp(ptr -> flight_id, temp) != 0 && ptr -> next != NULL){
        ptr = ptr -> next;
    }

    if (strcmp(ptr -> flight_id, temp) == 0) return ptr;

    return NULL;
}

void create_dll(){
    char temp[51];
    printf("Enter size of double linked list : ");
    scanf("%d", &capacity);
    
    if (!flights){
        flights = (struct flight*) malloc(capacity*sizeof(struct flight));
        struct flight* ptr = flights;

        printf("\nEnter -1 to end\n");
        printf("Enter airline name [max. 50 chars]: ");
        scanf("\n%[^\n]s", &temp);
        if (strcmp(temp, "-1") != 0){
            strcpy(flights -> airline_name, temp);
            printf("Enter flight id [max. 10 chars]: ");
            scanf("\n%[^\n]s", &flights -> flight_id);
            flights -> next = NULL;
            flights -> prev = NULL;
            head++;
            tail++;
            
            do {
                struct flight* new_node = (struct flight*) malloc(sizeof(struct flight));                                        

                printf("\nEnter -1 to end\n");
                printf("Enter airline name [max. 50 chars]: ");
                scanf("\n%[^\n]s", &temp);

                if (strcmp(temp, "-1") == 0){
                    break;
                }

                strcpy(new_node -> airline_name, temp);
                printf("Enter flight id [max. 10 chars]: ");
                scanf("\n%[^\n]s", &new_node -> flight_id);
                
                ptr -> next = new_node;
                new_node -> prev = ptr;
                new_node -> next = NULL;
                ptr = new_node;
                tail++;
            } while (1 && !is_full());
        }
    }
    if (is_full()) printf("-- Double linked list is full --\n");
}

void display(){ 
    if (!is_empty()){
        printf("\n                        == Flights Data ==                         \n");
        printf(".____________.____________________________________________________.\n");
        printf("|   Flight   |                     Airline Name                   |\n");
        printf("'------------'----------------------------------------------------'\n");

        struct flight *ptr = flights;
        int i = 0;

        if (head == tail){
            printf("| %-10s | %-50s | --> head & tail\n", ptr -> flight_id, ptr -> airline_name);
        }else {
            while (ptr != NULL || i == tail-1){
                if (i == head-1) printf("| %-10s | %-50s | --> head\n", ptr -> flight_id, ptr -> airline_name);
                else if (i == tail-1) printf("| %-10s | %-50s | --> tail\n", ptr -> flight_id, ptr -> airline_name);
                else printf("| %-10s | %-50s |\n", ptr -> flight_id, ptr -> airline_name);
                i++;
                ptr = ptr -> next;
            }
        }

        printf("|____________|____________________________________________________|\n\n");
    }else {
        printf("-- Double linked list is empty --\n");
    }
}

void pop_head(){
    if (!is_empty()){
        struct flight* ptr = flights;
        
        printf("-- %s deleted from data --\n", ptr -> airline_name);

        if (tail > 1) {
            flights = ptr -> next;
            flights -> prev = NULL;
            ptr -> next = NULL;
            free(ptr);
        }else {
            ptr = NULL;
            head--;
        }
        tail--;
    }else printf("-- Double linked list is empty! --\n");
}

void pop_tail(){
    if (!is_empty()){
        struct flight* ptr = flights;
        struct flight* preptr = flights;

        while (ptr -> next != NULL) {
            preptr = ptr;
            ptr = ptr -> next;
        }
        
        printf("-- %s deleted from data --\n", ptr -> airline_name);

        if (tail > 1) {
            preptr -> next = NULL;
            free(ptr);
        }else {
            ptr = NULL;
            head--;
        }
        tail--;
    }else printf("-- Double linked list is empty! --\n");
}

void pop_before_node(){
    if (tail < 2) printf("-- At least have 2 data to use this menu --\n");
    else if (!is_empty()){
        char choice;

        // ask to user to see the data first
        printf("Do you want to see the data first [y/n]? ");
        scanf("\n%c", &choice);
        if (choice == 'y'){
            display();
        }

        char search[20];
        struct flight* temp = NULL;
        struct flight* ptr = NULL;
        struct flight* preptr = NULL;

        printf("Search flight id : ");
        scanf("\n%[^\n]s", &search);

        temp = search_flight(search);
        
        if (temp){
            ptr = temp -> prev;

            if (ptr != NULL){
                printf("-- %s deleted from data --\n", ptr -> airline_name);

                if (ptr -> prev != NULL){
                    preptr = ptr -> prev;
                    preptr -> next = temp;
                    temp -> prev = preptr;
                }else {
                    ptr -> next -> prev = NULL;
                    flights = ptr -> next;
                }

                free(ptr);
                tail--;
            }else printf("-- Data is out of range --\n ");

        }else printf("-- %s unfounded --\n", search);        
    }else printf("-- Double linked list is empty! --\n");
}

void pop_after_node(){
    if (tail < 2) printf("-- At least have 2 data to use this menu --\n");
    else if (!is_empty()){
        char choice;
        char search[20];
        struct flight* temp = NULL;
        struct flight* ptr = NULL;
        struct flight* preptr = NULL;

        // ask to user to see the data first
        printf("Do you want to see the data first [y/n]? ");
        scanf("\n%c", &choice);
        if (choice == 'y'){
            display();
        }

        printf("Search flight id : ");
        scanf("\n%[^\n]s", &search);

        temp = search_flight(search);
        
        if (temp){
            ptr = temp -> next;

            if (ptr != NULL){
                printf("-- %s deleted from data --\n", ptr -> airline_name);

                if (ptr -> next != NULL){
                    preptr = temp;
                    preptr -> next = ptr -> next;
                    ptr -> next -> prev = preptr;
                }else {
                    preptr -> next = NULL;
                }

                free(ptr);
                tail--;
            }else printf("-- Data is out of range --\n ");

        }else printf("-- %s unfounded --\n", search);        
    }else printf("-- Double linked list is empty! --\n");
}

void push_head(){
    char again;

    if (is_empty()){
        printf("Enter airline name [max. 50 chars]: ");
        scanf("\n%[^\n]s", &flights -> airline_name);
        printf("Enter flight id [max. 10 chars]: ");
        scanf("\n%[^\n]s", &flights -> flight_id);
        flights -> next = NULL;
        flights -> prev = NULL;

        head++;
        tail++;

        printf("Insert again [y/n]? ");
        scanf("\n%c", &again);

        if (again == 'y') push_head();
    }else if (!is_full()){
        struct flight* ptr = flights;        

        do {
            struct flight* new_node = (struct flight*) malloc(sizeof(struct flight));
            
            printf("Enter airline name [max. 50 chars]: ");
            scanf("\n%[^\n]s", &new_node -> airline_name);
            printf("Enter flight id [max. 10 chars]: ");
            scanf("\n%[^\n]s", &new_node -> flight_id);
            
            new_node -> next = ptr;
            new_node -> prev = NULL;
            ptr -> prev = new_node;
            flights = new_node;
            ptr = flights;
            tail++;

            printf("Insert again [y/n]? ");
            scanf("\n%c", &again);
        } while (again == 'y' && !is_full());
        
        if (again == 'y' && is_full()) printf("-- Double linked list is full! --\n");
    }else printf("-- Double linked list is full! --\n");
}

void push_tail(){
    char again;

    if (is_empty()){
        printf("Enter airline name [max. 50 chars]: ");
        scanf("\n%[^\n]s", &flights -> airline_name);
        printf("Enter flight id [max. 10 chars]: ");
        scanf("\n%[^\n]s", &flights -> flight_id);
        flights -> next = NULL;
        flights -> prev = NULL;

        head++;
        tail++;

        printf("Insert again [y/n]? ");
        scanf("\n%c", &again);

        if (again == 'y') push_tail();
    }else if (!is_full()){
        struct flight* ptr = flights;

        while (ptr -> next != NULL){
            ptr = ptr -> next;
        }

        do {
            struct flight* new_node = (struct flight*) malloc(sizeof(struct flight));
            
            printf("Enter airline name [max. 50 chars]: ");
            scanf("\n%[^\n]s", &new_node -> airline_name);
            printf("Enter flight id [max. 10 chars]: ");
            scanf("\n%[^\n]s", &new_node -> flight_id);
            
            new_node -> next = NULL;
            new_node -> prev = ptr;
            ptr -> next = new_node;
            ptr = new_node;
            tail++;

            printf("Insert again [y/n]? ");
            scanf("\n%c", &again);
        } while (again == 'y' && !is_full());
        
        if (again == 'y' && is_full()) printf("-- Double linked list is full! --\n");
    }else printf("-- Double linked list is full! --\n");
}

void push_before_node(){
    if (is_empty()) printf("-- At least have 1 data to use this menu --\n");
    else if (!is_full()){
        char choice;
        char search[20];
        char again;
        struct flight* ptr = NULL;

        // ask to user to see the data first
        printf("Do you want to see the data first [y/n]? ");
        scanf("\n%c", &choice);
        if (choice == 'y'){
            display();
        }

        do {
            printf("Search flight id : ");
            scanf("\n%[^\n]s", &search);

            ptr = search_flight(search);

            if (ptr){
                struct flight* new_node = (struct flight*) malloc(sizeof(struct flight));
                
                printf("New node : \n");
                printf("  Enter airline name [max. 50 chars]: ");
                scanf("\n%[^\n]s", &new_node -> airline_name);
                printf("  Enter flight id [max. 10 chars]: ");
                scanf("\n%[^\n]s", &new_node -> flight_id);
                
                new_node -> next = ptr;
                new_node -> prev = ptr -> prev;
                ptr -> prev = new_node;
                new_node -> prev -> next = new_node;
                tail++;

                printf("Insert again [y/n]? ");
                scanf("\n%c", &again);
            }else  printf("-- %s unfounded --\n", search);
        } while (again == 'y' && !is_full());

        if (again == 'y' && is_full()) printf("-- Double linked list is full! --\n");
    }else printf("-- Double linked list is full! --\n");
}

void push_after_node(){
    if (is_empty()) printf("-- At least have 1 data to use this menu --\n");
    else if (!is_full()){
        char choice;
        char search[20];
        char again;
        struct flight* ptr = NULL;

        // ask to user to see the data first
        printf("Do you want to see the data first [y/n]? ");
        scanf("\n%c", &choice);
        if (choice == 'y'){
            display();
        }

        do {
            printf("Search flight id : ");
            scanf("\n%[^\n]s", &search);

            ptr = search_flight(search);

            if (ptr){
                struct flight* new_node = (struct flight*) malloc(sizeof(struct flight));
                
                printf("New node : \n");
                printf("  Enter airline name [max. 50 chars]: ");
                scanf("\n%[^\n]s", &new_node -> airline_name);
                printf("  Enter flight id [max. 10 chars]: ");
                scanf("\n%[^\n]s", &new_node -> flight_id);
                
                new_node -> prev = ptr;
                new_node -> next = ptr -> next;
                new_node -> next -> prev = new_node;
                ptr -> next = new_node;
                
                tail++;

                printf("Insert again [y/n]? ");
                scanf("\n%c", &again);
            }else  printf("-- %s unfounded --\n", search);
        } while (again == 'y' && !is_full());

        if (again == 'y' && is_full()) printf("-- Double linked list is full! --\n");
    }else printf("-- Double linked list is full! --\n");
}

int main(){
    printf("============== Create double linked list ==============\n");
    create_dll();
    system("pause");
    system("cls");

    int choice;

    while (1){
        printf("============== Menu ==============\n");
        printf("1. Display a table of nodes\n");
        printf("2. Add the node at the beginning\n");
        printf("3. Add the node at the end\n");
        printf("4. Add before a node\n");
        printf("5. Add after a node\n");
        printf("6. Delete the first node\n");
        printf("7. Delete the last node\n");
        printf("8. Delete before a node\n");
        printf("9. Delete after a node\n");
        printf("10. Is data full?\n");
        printf("11. is data empty?\n");
        printf("0. Exit\n");
        printf("Enter your choice [0-11]: ");
        scanf("%d", &choice);

        switch (choice){
            case 1:
                display();
                break;
            case 2:
                push_head();
                break;
            case 3:
                push_tail();
                break;            
            case 4:
                push_before_node();
                break;            
            case 5:
                push_after_node();
                break;
            case 6:
                pop_head();
                break;
            case 7:
                pop_tail();
                break;
            case 8:
                pop_before_node();
                break;
            case 9:
                pop_after_node();
                break;
            case 10:
                if (is_full() == 1) printf("Yes\n");
                else printf("No\n");
                break;
            case 11:
                if (is_empty() == 1) printf("Yes\n");
                else printf("No\n");
                break;
            case 0:
                exit(0);
                break;
            default:
                printf("-- The input doesn't exist --\n");
                break;
        }
        system("pause");
        system("cls");
    }

    return 0;
}

/* 
Garuda
GA-101
Citilink
CT-001
Lion Air
LA-21
Sriwijaya Air
SJ-102
Batik Air
BT-018
Batavia Air
BA-116
 */