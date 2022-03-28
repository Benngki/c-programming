#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

struct student_array{
    char name[51];
    long long int nim;
    char class[5];
} *students_arr = NULL;

struct student_linked_list{
    char name[51];
    long long int nim;
    char class[5];
    struct student_linked_list* next;
} *students_ll = NULL;   

int top = 0;
int capacity;
int mode;

int is_empty(){
    if (top == 0){
        return 1;
    }else {
        return 0;
    }
}

int is_full(){
    if (top == capacity){
        return 1;
    }else {
        return 0;
    }
}

void create_stack(){
    char temp[51];
    printf("Enter size of stack : ");
    scanf("%d", &capacity);

    if (mode == 1){
        if (!students_arr){
            students_arr = (struct student_array*) malloc(capacity*sizeof(struct student_array));
            
            do {
                printf("\nEnter -1 to end\n");
                printf("Enter student name [max. 50 chars]: ");
                scanf("\n%[^\n]s", &temp);

                if (strcmp(temp, "-1") == 0){
                    break;
                }
                
                strcpy(students_arr[top].name, temp);

                printf("Enter student nim [10 chars]: ");
                scanf("%lld", &students_arr[top].nim);
                printf("Enter student class [4 chars]: ");
                scanf("\n%[^\n]s", &students_arr[top].class);

                top++;
            } while (1);       
        }
    }else {
        if (!students_ll){            
            students_ll = (struct student_linked_list*) malloc(capacity*sizeof(struct student_linked_list));

            printf("\nEnter -1 to end\n");
            printf("Enter student name [max. 50 chars]: ");
            scanf("\n%[^\n]s", &temp);
            if (strcmp(temp, "-1") != 0){
                strcpy(students_ll -> name, temp);
                printf("Enter student nim [10 chars]: ");
                scanf("%lld", &students_ll -> nim);
                printf("Enter student class [4 chars]: ");
                scanf("\n%[^\n]s", &students_ll -> class);
                students_ll -> next = NULL;
                top++;
                
                do {
                    struct student_linked_list *new_node = (struct student_linked_list*) malloc(sizeof(struct student_linked_list));                                        

                    printf("\nEnter -1 to end\n");
                    printf("Enter student name [max. 50 chars]: ");
                    scanf("\n%[^\n]s", &temp);

                    if (strcmp(temp, "-1") == 0){
                        break;
                    }

                    strcpy(new_node -> name, temp);
                    printf("Enter student nim [10 chars]: ");
                    scanf("%lld", &new_node -> nim);
                    printf("Enter student class [4 chars]: ");
                    scanf("\n%[^\n]s", &new_node -> class);
                    
                    new_node -> next = students_ll;
                    students_ll = new_node;
                    top++;
                } while (1);       
            }
        }
    }
}

void display(){
    if (top != 0){
        printf("\n                             === Student List ===                              \n");
        printf(".____________________________________________________.____________._______.\n");
        printf("|                        Name                        |    NIM     | Class |\n");
        printf("'----------------------------------------------------'------------'-------'\n");

        if (mode == 1){
            for (int i = top-1; i >= 0; i--){
                if (i == top-1){
                    printf("| %-50s | %-10lld | %4s  | --> top\n", students_arr[i].name, students_arr[i].nim, students_arr[i].class);
                }else {
                    printf("| %-50s | %-10lld | %4s  |\n", students_arr[i].name, students_arr[i].nim, students_arr[i].class);                
                }
            }
        }else {
            struct student_linked_list *ptr = students_ll;
            int i = 1;

            while (ptr != NULL){
                if (i == 1){
                    printf("| %-50s | %-10lld | %4s  | --> top\n", ptr -> name, ptr -> nim, ptr -> class);
                }else {
                    printf("| %-50s | %-10lld | %4s  |\n", ptr -> name, ptr -> nim, ptr -> class);                
                }
                i++;
                ptr = ptr -> next;
            }
        }

        printf("|____________________________________________________|____________|_______|\n\n");
    }else {
        printf("-- the list is empty --\n");
    }
}

void push(){
    if (!is_full()) {
        char again;
        if (mode == 1){
            do {
                printf("\nEnter student name [max. 50 chars]: ");
                scanf("\n%[^\n]s", &students_arr[top].name);
                printf("Enter student nim [10 chars]: ");
                scanf("%lld", &students_arr[top].nim);
                printf("Enter student class [4 chars]: ");
                scanf("\n%[^\n]s", &students_arr[top].class);

                top++;

                printf("Push again [y/n]? ");
                scanf("\n%c", &again);
            } while (again == 'y' && !is_full());
            if (is_full() && again == 'y') printf("-- Stack is full --\n");
        }else if (mode == 2){
            do {
                struct student_linked_list* new_node = (struct student_linked_list*) malloc(sizeof(struct student_linked_list));
                printf("\nEnter student name [max. 50 chars]: ");
                scanf("\n%[^\n]s", &new_node -> name);
                printf("Enter student nim [10 chars]: ");
                scanf("%lld", &new_node -> nim);
                printf("Enter student class [4 chars]: ");
                scanf("\n%[^\n]s", &new_node -> class);

                new_node -> next = students_ll;
                students_ll = new_node;

                top++;

                printf("Push again [y/n]? ");
                scanf("\n%c", &again);
            } while (again == 'y' && !is_full());
            if (is_full()) printf("-- Stack is full --\n");
        }
    }
    else {
        printf("-- Stack is full --\n");
    }
}

void pop(){
    if (!is_empty()){
        if (mode == 1){
            char temp[51];
            strcpy(temp, students_arr[top-1].name);

            strcpy(students_arr[top-1].name, "");
            students_arr[top-1].nim = (int) NULL;
            strcpy(students_arr[top-1].class, "");

            printf("-- %s popped from stack --\n", temp);
        }else {
            struct student_linked_list* ptr = students_ll;

            students_ll = ptr -> next;

            printf("-- %s popped from stack --\n", ptr -> name);

            free(ptr);
        }
        top--;
    }else {
        printf("-- the list is empty --\n");
    }
}

void peek(){
    if (!is_empty()){
        if (mode == 1) printf("The top element is : %s\n", students_arr[top-1].name);
        else printf("The top element is : %s\n", students_ll -> name);
    }else printf("-- the list is empty --\n");        
}

void menu(){
    int choice;

    while (1){
        printf("============== Menu ==============\n");
        printf("1. Display the student table\n");
        printf("2. Push a student\n");
        printf("3. Pop a student\n");
        printf("4. Peek the student\n");
        printf("5. is stack full?\n");
        printf("6. is stack empty?\n");
        printf("0. Exit\n");
        printf("Enter your choice [0-6]: ");
        scanf("%d", &choice);

        switch (choice){
            case 1:
                display();
                break;
            case 2:
                push();
                break;
            case 3:
                pop();
                break;            
            case 4:
                peek();
                break;            
            case 5:
                if (is_full()) printf("Yes\n");
                else printf("No\n");
                break;
            case 6:
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
        printf("============== Create stack ==============\n");
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

    create_stack(mode);
    system("pause");
    system("cls");

    menu();

    return 0;
}