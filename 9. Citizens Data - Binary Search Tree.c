/* 
	NAMA : BENEDIKTUS HENGKI SETIAWAN
	NIM  : 2502025302
*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{
	long long int nik;
	char name[60];
	struct node *left, *right;
}*root = NULL;

struct node* MinValueNode(struct node* node){
    struct node* current = node;

    while(current->left != NULL)
    	current = current->left;
 
    return current;
}

struct node* add(struct node* r, long long int nik, char name[]){
	if(r == NULL){
        r = (struct node*)malloc(sizeof(struct node));
        r->nik = nik;
        strcpy(r->name, name);
		r->left = r->right = NULL;
		
		printf("---------- Data added successfully -----------\n");
	}
	else if(nik < r->nik){
		r->left = add(r->left, nik, name);
	}
	else if(nik > r->nik){
		r->right = add(r->right, nik, name);
	}
	else{
		printf("------------ Data already exists -------------\n");
	}
	
	return r;
}

struct node* deleteNode(struct node* r, long long int nik){
    if(r == NULL){
    	printf("-------------- There's No Data ---------------\n");
    	return r;
	}
	
	if(nik < r->nik){
		r->left = deleteNode(r->left, nik);	
	}
    else if(nik > r->nik){
    	r->right = deleteNode(r->right, nik);	
	}
    else{
    	if(r->left == NULL){
            struct node *temp = r->right;
            free(r);
			printf("--------- Data deleted successfully ----------\n");
            return temp;
        }
		else if(r->right == NULL){
        	struct node *temp = r->left;
            free(r);
            printf("--------- Data deleted successfully ----------\n");
            return temp;
        }
        struct node* temp = MinValueNode(r->right);
        r->nik = temp->nik;
        strcpy(r->name, temp->name);
        r->right = deleteNode(r->right, temp->nik);
    }
    
    return r;
}

struct node* update_node(struct node* r, long long int nik){
	if(r == NULL){
		printf("-------------- There's No Data ---------------\n");
        return r;
	}
	
	if(nik < r->nik){
		r->left = update_node(r->left, nik);	
	}
    else if(nik > r->nik){
    	r->right = update_node(r->right, nik);	
	}
    else{
    	printf("\nUpdate Menu :\n");
		printf("1. NIK\n");
		printf("2. Nama\n");
    	
    	int choice;
		printf("Input your choice [1-2] : ");
		scanf("%d", &choice);
		
		if(choice == 1){
			printf("Input the New NIK: ");
			scanf("%lld", &r->nik);
		    printf("--------- Data updated successfully ----------\n");
		}
		else if(choice == 2){
			printf("Input the New Full name: ");
			scanf(" %[^\n]", r->name);
		    printf("--------- Data updated successfully ----------\n");
		}
		else{
			printf("-------- Your choice is not available --------\n");		
		}
    }
    
    return r;
}

void Preorder(struct node* r){
	if(r != NULL){
		printf("| %-19lld | %-39s |\n", r->nik, r->name);
	    Preorder(r->left);
	    Preorder(r->right);
	}
}

void Inorder(struct node* r){
	if(r != NULL){
		int count = 1;
    	Inorder(r->left);
		printf("| %-19lld | %-39s |\n", r->nik, r->name);
        Inorder(r->right);
    }
}

void Postorder(struct node* r){
	if(r != NULL){
	    Postorder(r->left);
	    Postorder(r->right);
		printf("| %-19lld | %-39s |\n", r->nik, r->name);
	}
}

void displayMenu(){
	char menu[][15] = {"Pre-Order", "In-Order", "Post-Order", "Exit"};
	int choice, n=4;

	printf("================ Display BST =================\n");
	for (int i = 0; i < n; i++){
		if (i == n-1) printf("%d. %s\n", i+1, menu[i]);
		else printf("%d. Display %s\n", i+1, menu[i]);
	}
	printf("Input your choice : ");
	scanf("%d", &choice);

	if (root){

		printf("\n                      == Citizens data ==                      \n");
		printf("._____________________._________________________________________.\n");
		printf("|         NIK         |                  Name                   |\n");
		printf("'---------------------'-----------------------------------------'\n");

		switch (choice)
		{		
			case 1:
				Preorder(root);
				break;
			case 2:
				Inorder(root);
				break;
			case 3:
				Postorder(root);
				break;
			case 4:
				system("pause");
				exit(0);
			default:
				break;
		}
		
		printf("|_____________________|_________________________________________|\n\n");

	}else printf("-------------- There's No Data ---------------\n");			
}

int main(){
	long long int nik;
	char name[60], temp;
	
	printf("============ CItizens Data - BST =============\n");
	printf("==================== MENU ====================\n");
	printf("1. Add\n");
	printf("2. Update\n");
	printf("3. Delete\n");
	printf("4. Display\n");
	printf("5. Exit\n");
	
	int choice, count=1;
	printf("Input your choice [1-5] : ");
	scanf("%d", &choice);
	
	if (((choice == 2 || choice == 3 || choice == 4) && root) || (choice == 1 || choice == 5)){
		if ((choice == 2 || choice == 3) && root){
			printf("Do you want to see the data first [y/n]? ")	;
			scanf("\n%c", &temp);

			if (temp == 'y'){
				displayMenu();
			}
		}

		switch (choice)
		{
			case 1:
				printf("Input -1 if done\n");
				while (1)
				{
					printf("Data %d :\n", count);
					printf("  Input NIK: ");
					scanf("%lld", &nik);
					if (nik != -1){
						printf("  Input Full name: ");
						scanf(" %[^\n]", name);
						root = add(root, nik, name);
						count++;
					}else break;
				}
				
				break;
			case 2:
				printf("Input NIK to be updated: ");
				scanf("%lld", &nik);
				update_node(root, nik);
				break;
			case 3:
				printf("Input NIK to be deleted: ");
				scanf("%lld", &nik);
				root = deleteNode(root, nik);
				break;
			case 4:
				system("cls");
				displayMenu();
				break;
			case 5:
				exit(0);
				break;
			default:
				break;
		}
	}else if ((choice == 2 || choice == 3 || choice == 4) && !root){
		printf("---------- Please input data first -----------\n");
	}else {
		printf("-------- Your choice is not available --------\n");		
	}

	system("pause");
	system("cls");
	main();

	return 0;
}