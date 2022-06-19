/* 
	NAMA : BENEDIKTUS HENGKI SETIAWAN
	NIM  : 2502025302
*/

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

int is_empty(){
    if (tail == 0){
        return 1;
    }else {
        return 0;
    }
}

struct flight* search_flight(char* temp){
    struct flight* ptr = flights; 

    while (strcmp(ptr -> flight_id, temp) != 0 && ptr -> next != flights){
        ptr = ptr -> next;
    }

    if (strcmp(ptr -> flight_id, temp) == 0) return ptr;

    return NULL;
}

void create_dll(){
    char temp[51];
    struct flight *ptr;

    if (!flights){
        while (1)
        {
            printf("\nEnter -1 to end\n");
            printf("Enter airline name [max. 50 chars]: ");
            scanf("\n%[^\n]s", &temp);

            if (strcmp(temp, "-1") != 0){
                // allocate memory for new node
                struct flight *newNode = (struct flight*) malloc(sizeof(struct flight));

                strcpy(newNode -> airline_name, temp);
                printf("Enter flight id [max. 10 chars]: ");
                scanf("\n%[^\n]s", &newNode -> flight_id);
                
                tail++;

                if (!flights) {
                    newNode -> next = newNode;
                    newNode -> prev = newNode;
                    flights = newNode;
                    head++;
                }
                else {
                    
                    newNode->prev = flights->prev;
                    newNode->next = flights;
                    flights->prev->next = newNode;
                    flights->prev = newNode;            
                }
            }else {
                break;
            }
        }
    }         
}

void display(){ 
    if (!is_empty()){
        printf("\n                        == Flights Data ==                         \n");
        printf(".____________.____________________________________________________.\n");
        printf("|   Flight   |                     Airline Name                   |\n");
        printf("'------------'----------------------------------------------------'\n");

        struct flight *ptr = flights;
        
        if (head == tail){
            printf("| %-10s | %-50s | --> head & tail\n", ptr -> flight_id, ptr -> airline_name);
        }else {
            for (int i = 0; i < tail; i++){
                if (i == head-1) printf("| %-10s | %-50s | --> head\n", ptr -> flight_id, ptr -> airline_name);
                else if (i == tail-1) printf("| %-10s | %-50s | --> tail\n", ptr -> flight_id, ptr -> airline_name);
                else printf("| %-10s | %-50s |\n", ptr -> flight_id, ptr -> airline_name);
                ptr = ptr -> next;
            }
        }

        printf("|____________|____________________________________________________|\n\n");
    }else {
        printf("-- Circular double linked list is empty --\n");
    }
}

void pop_head(){
    if (!is_empty()){
        struct flight* ptr = flights;
        char temp[50];
        strcpy(temp, ptr -> airline_name);
        
        flights -> prev -> next = ptr -> next;
        flights = ptr -> next;
        flights -> prev = ptr -> prev;

        if (tail == 1) {
            head--;
        }
        tail--;

        free(ptr);
        printf("-- %s deleted from data --\n", temp);

    }else printf("-- Circular Double linked list is empty! --\n");
}

void pop_tail(){
    if (!is_empty()){
        struct flight* ptr = flights->prev;
        
        flights->prev = ptr->prev;
        ptr->prev->next = flights;

        if (tail == 1) {
            head--;
        }
        tail--;

        printf("-- %s deleted from data --\n", ptr -> airline_name);
        free(ptr);
    }else printf("-- Circular Double linked list is empty! --\n");
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
            ptr -> prev -> next = ptr -> next;
            ptr -> next -> prev = ptr -> prev;

            if (ptr == flights) flights = temp;

            printf("-- %s deleted from data --\n", ptr -> airline_name);
            free(ptr);

            
            tail--;

        }else printf("-- %s unfounded --\n", search);        
    }else printf("-- Circular Double linked list is empty! --\n");
}

void pop_after_node(){
    if (tail < 2) printf("-- At least have 2 data to use this menu --\n");
    else if (!is_empty()){
        char choice;
        char search[20];
        struct flight* temp = NULL;
        struct flight* ptr = NULL;

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
            ptr -> prev -> next = ptr -> next;
            ptr -> next -> prev = ptr -> prev;

            if (ptr == flights) flights = temp;

            printf("-- %s deleted from data --\n", ptr -> airline_name);
            free(ptr);

            tail--;

        }else printf("-- %s unfounded --\n", search);        
    }else printf("-- Circular Double linked list is empty! --\n");
}

void push_head(){
    struct flight *newNode = (struct flight*) malloc(sizeof(struct flight));

    printf("Enter airline name [max. 50 chars]: ");
    scanf("\n%[^\n]s", &newNode -> airline_name);
    printf("Enter flight id [max. 10 chars]: ");
    scanf("\n%[^\n]s", &newNode -> flight_id);
    
    newNode->next = flights;
    newNode->prev = flights->prev;
    flights = newNode;    

    tail++;

}

void push_tail(){
    struct flight *newNode = (struct flight*) malloc(sizeof(struct flight));

    printf("Enter airline name [max. 50 chars]: ");
    scanf("\n%[^\n]s", &newNode -> airline_name);
    printf("Enter flight id [max. 10 chars]: ");
    scanf("\n%[^\n]s", &newNode -> flight_id);

    newNode -> next = flights;
    newNode -> prev = flights -> prev;
    flights -> prev -> next = newNode;
    flights -> prev = newNode;

    tail++;

}

void push_before_node(){
    if (is_empty()) printf("-- At least have 1 data to use this menu --\n");
    else {
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

        printf("Search flight id : ");
        scanf("\n%[^\n]s", &search);

        ptr = search_flight(search);

        if (ptr){
            struct flight* newNode = (struct flight*) malloc(sizeof(struct flight));
            
            printf("New node : \n");
            printf("  Enter airline name [max. 50 chars]: ");
            scanf("\n%[^\n]s", &newNode -> airline_name);
            printf("  Enter flight id [max. 10 chars]: ");
            scanf("\n%[^\n]s", &newNode -> flight_id);
            
            newNode -> next = ptr;
            newNode -> prev = ptr -> prev;
            ptr -> prev -> next = newNode;
            ptr -> prev = newNode;
            tail++;

        }else  printf("-- %s unfounded --\n", search);
    }
}

void push_after_node(){
    if (is_empty()) printf("-- At least have 1 data to use this menu --\n");
    else {
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

        printf("Search flight id : ");
        scanf("\n%[^\n]s", &search);

        ptr = search_flight(search);

        if (ptr){
            struct flight* newNode = (struct flight*) malloc(sizeof(struct flight));
            
            printf("New node : \n");
            printf("  Enter airline name [max. 50 chars]: ");
            scanf("\n%[^\n]s", &newNode -> airline_name);
            printf("  Enter flight id [max. 10 chars]: ");
            scanf("\n%[^\n]s", &newNode -> flight_id);
            
            newNode -> prev = ptr;
            newNode -> next = ptr -> next;
            ptr -> next -> prev = newNode;
            ptr -> next = newNode;
            
            tail++;

        }else  printf("-- %s unfounded --\n", search);
    }
}

int main(){
    printf("========================= FLIGHTS DATA =========================\n");
    printf("============== Create circular double linked list ==============\n");
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
        printf("10. is data empty?\n");
        printf("0. Exit\n");
        printf("Enter your choice [0-10]: ");
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