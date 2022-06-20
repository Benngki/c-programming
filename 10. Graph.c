/* 
	NAMA : BENEDIKTUS HENGKI SETIAWAN
	NIM  : 2502025302
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define true 1
#define false 0

int n;
void adjacency_matrix(int *G){

    char temp[20];

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            printf("%d ", *(G + i*n + j));
        }
        printf("\n");
    }
};

void adjacency_list(int *G){
    int tempG[n];

    // cek apakah tiap node saling terhubung
    for (int i = 0; i < n; i++){
        tempG[i] = 0;
        for (int j = 0; j < n; j++){
            if (*(G + n*i + j) == 1) {
                tempG[i] = 1;
                break;
            }
        }
    }

    for (int i = 0; i < n; i++){
        if (tempG[i] == 1){
            printf("%d", i+1);
            for (int j = 0; j < n; j++){
                // printf("%d%s", i+1, ?" -> ":"");
                // if (*(G + n*i + j) == 1) printf("%d ", j+1);
                if (*(G + n*i + j) == 1) printf("%s%d", (j != 0 || j != n-1)?" -> ":"", j+1);
            }
        }
        printf("\n");
    }
};

void degree_of_all_vertices(int *G){
    int deg[n];
    for (int i = 0; i < n; i++){
        deg[i] = 0;
        for (int j = 0; j < n; j++){
            if (*(G + n*i + j) == 1) deg[i]++;
        }
        printf("%d = %d\n", i+1, deg[i]);
    }
};

int* create_graph(){
    
    int temp[2];
    char help;

    printf("Input the sum of nodes : ");
    scanf("%d", &n);
    
    int *G = (int*) malloc(n*n*sizeof(int));

    printf("Input the edge :\n");
    
    printf("View help [y/n]?");
    scanf("\n%c", &help);
    if (help == 'y') {
        printf("Example : 1 3\n");
        printf("  That means there is a edge between node 1 to node 3 \n");
    }

    // mengosongkan matrix
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            *(G + i*n + j) = 0;
        }
    }

    printf("Input -1 if you done\n");

    while (1)
    {
        scanf("%d", &temp[0]);

        if (temp[0] == -1) break;
        else{
            scanf("%d", &temp[1]);
            
            if (temp[0] != temp[1]) *(G + (temp[0]-1)*n + (temp[1]-1)) = 1;
            // G[temp[0]-1][temp[1]-1] = 1;
        }                
    }

    return G;
}

void header(){
    printf("=================== GRAPH ====================\n");
}

int main(){
    int *G, choice, temp;
    
    header();
    G = create_graph();

    while (true){
        
        system("pause");
        system("cls");

        header();
        printf("1. Show adjacency Matrix\n");
        printf("2. Show adjacency List\n");
        printf("3. Show degree of all vertices\n");
        printf("4. Exit\n");
        printf("Input your choice : ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                adjacency_matrix(G);
                break;        
            case 2:
                adjacency_list(G);
                break;        
            case 3:
                degree_of_all_vertices(G);
                break;
            case 4:
                exit(0);
                break;
            default:
                break;
        }
    }


    return 0;
}
