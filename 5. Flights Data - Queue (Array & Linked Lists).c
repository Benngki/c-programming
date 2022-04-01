#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

struct flight_array{
    char airline_name[51];
    char flight_id[11];
} *flights_arr = NULL;

struct flight_linked_list{
    char airline_name[51];
    char flight_id[11];
    struct flight_linked_list* next;
} *flights_ll = NULL;   

int head = 0;
int tail = 0;
int capacity;
int mode;

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

void create_queue(){
    char temp[51];
    printf("Enter size of queue : ");
    scanf("%d", &capacity);

    if (mode == 1){
        if (!flights_arr){
            flights_arr = (struct flight_array*) malloc(capacity*sizeof(struct flight_array));
            
            do {
                printf("\nEnter -1 to end\n");
                printf("Enter airline name [max. 50 chars]: ");
                scanf("\n%[^\n]s", &temp);

                if (strcmp(temp, "-1") == 0){
                    break;
                }
                
                strcpy(flights_arr[tail].airline_name, temp);

                printf("Enter flight id [max. 10 chars]: ");
                scanf("\n%[^\n]s", &flights_arr[tail].flight_id);
                
                if (head == 0) head++;
                tail++;
            } while (1 && !is_full());       
        }
    }else {
        if (!flights_ll){            
            flights_ll = (struct flight_linked_list*) malloc(capacity*sizeof(struct flight_linked_list));
            struct flight_linked_list* ptr = flights_ll;

            printf("\nEnter -1 to end\n");
            printf("Enter airline name [max. 50 chars]: ");
            scanf("\n%[^\n]s", &temp);
            if (strcmp(temp, "-1") != 0){
                strcpy(flights_ll -> airline_name, temp);
                printf("Enter flight id [max. 10 chars]: ");
                scanf("\n%[^\n]s", &flights_ll -> flight_id);
                flights_ll -> next = NULL;
                head++;
                tail++;
                
                do {
                    struct flight_linked_list* new_node = (struct flight_linked_list*) malloc(sizeof(struct flight_linked_list));                                        

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
                    new_node -> next = NULL;
                    ptr = new_node;
                    tail++;
                } while (1 && !is_full());
            }
        }
    }
    if (is_full()) printf("-- Queue is full --\n");
}

void display(){ 
    if (!is_empty()){
        printf("\n                        == Flights Data ==                         \n\n");
        printf(".____________.____________________________________________________.\n");
        printf("|   Flight   |                     Airline Name                   |\n");
        printf("'------------'----------------------------------------------------'\n");

        if (mode == 1){
            for (int i = head-1; i < tail; i++){
                if (i == head-1) printf("| %-10s | %-50s | --> head\n", flights_arr[i].flight_id, flights_arr[i].airline_name);
                else if (i == tail-1) printf("| %-10s | %-50s | --> tail\n", flights_arr[i].flight_id, flights_arr[i].airline_name);
                else printf("| %-10s | %-50s |\n", flights_arr[i].flight_id, flights_arr[i].airline_name);
            }
        }else {
            struct flight_linked_list *ptr = flights_ll;
            int i = 0;

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
        printf("-- Queue is empty --\n");
    }
}

void enqueue(){
    if (!is_full()){
        char again;
        if (mode == 1){
            do {
                printf("\nEnter airline name [max. 50 chars]: ");
                scanf("\n%[^\n]s", &flights_arr[tail].airline_name);
                printf("Enter filght id [max. 10 chars]: ");
                scanf("\n%[^\n]s", &flights_arr[tail].flight_id);

                tail++;

                printf("Enqueue again [y/n]? ");
                scanf("\n%c", &again);
            } while (again == 'y' && !is_full());
        }else {
            if (is_empty()){
                printf("Enter airline name [max. 50 chars]: ");
                scanf("\n%[^\n]s", &flights_ll -> airline_name);
                printf("Enter flight id [max. 10 chars]: ");
                scanf("\n%[^\n]s", &flights_ll -> flight_id);
                flights_ll -> next = NULL;

                head++;
                tail++;

                printf("Enqueue again [y/n]? ");
                scanf("\n%c", &again);
            }

            if (again == 'y' || !is_empty()) {
                struct flight_linked_list* ptr = flights_ll;

                while (ptr -> next != NULL){
                    ptr = ptr -> next;
                }

                do {
                    struct flight_linked_list* new_node = (struct flight_linked_list*) malloc(sizeof(struct flight_linked_list));
                    
                    printf("Enter airline name [max. 50 chars]: ");
                    scanf("\n%[^\n]s", &new_node -> airline_name);
                    printf("Enter flight id [max. 10 chars]: ");
                    scanf("\n%[^\n]s", &new_node -> flight_id);
                    
                    new_node -> next = NULL;
                    ptr -> next = new_node;
                    ptr = new_node;
                    tail++;

                    printf("Enqueue again [y/n]? ");
                    scanf("\n%c", &again);
                } while (again == 'y' && !is_full());
            }
        }

        if (is_full() && again == 'y') printf("-- Queue is full --\n");
    }else printf("-- Queue is full -- \n");

}

void dequeue(){
    if (!is_empty()){
        if (mode == 1){
            char temp[51];
            strcpy(temp, flights_arr[head-1].airline_name);

            for (int i = 0; i < tail-1; i++){
                strcpy(flights_arr[i].airline_name, flights_arr[i+1].airline_name);
                strcpy(flights_arr[i].flight_id, flights_arr[i+1].flight_id);
            }

            printf("-- %s dequeue from queue --\n", temp);
        }else {
            struct flight_linked_list* ptr = flights_ll;

            printf("-- %s dequeue from queue --\n", ptr -> airline_name);

            if (tail > 1) {
                flights_ll = ptr -> next;
                free(ptr);
            }else ptr = NULL;
        }
        
        if (tail > 1) tail--;
        else {
            head--;
            tail--;
        }
    }else {
        printf("-- Queue is empty --\n");
    }
}

void menu(){
    int choice;

    while (1){
        printf("============== Menu ==============\n");
        printf("1. Display the flight data\n");
        printf("2. Enqueue a flight data\n");
        printf("3. Dequeue a flight data\n");
        printf("4. is queue full?\n");
        printf("5. is queue empty?\n");
        printf("0. Exit\n");
        printf("Enter your choice [0-5]: ");
        scanf("%d", &choice);

        switch (choice){
            case 1:
                display();
                break;
            case 2:
                enqueue();
                break;
            case 3:
                dequeue();
                break;            
            case 4:
                if (is_full()) printf("Yes\n");
                else printf("No\n");
                break;            
            case 5:
                if (is_empty()) printf("Yes\n");
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
}

int main(){
    do {
        printf("============== Create queue ==============\n");
        printf("Using :\n");
        printf("1. Array\n");
        printf("2. Linked Lists\n");
        printf("Enter your choice : ");
        scanf("%d", &mode);

        if (mode > 2 || mode < 1){
            printf("-- The input doesn't exist! --\n");
            system("pause");
            system("cls");
        }
        else break;
    }while (1);

    create_queue(mode);
    system("pause");
    system("cls");

    menu();

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
 */