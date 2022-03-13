#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct airfreshener {
    char code[6];
    char name[50];
    int available;
    int price;
} data_airfreshener[7] = {"AR004", "Classic Rose", 20, 28000,
                        "AR005", "Fresh Lemon", 40, 30000,
                        "AR007", "Wild Lavender", 25, 30000,
                        "AR011", "Elegant Vanilla", 20, 32000,
                        "AR016", "Freesia & Jasmine", 18, 33000,
                        "AR019", "Exotic Flower", 21, 34000,
                        "AR022", "Ocean Scape", 30, 35000};

void buat_harga(char* temp, int num){
    char strNum[30];
    sprintf(strNum, "%d", num);
    int len = strlen(strNum);
    if (len > 3){
        int tempNum = len;
        while (tempNum-3 > 0){
            tempNum-=3;
        }
        sprintf(temp, "Rp. ");
        int i=4, k=0, comma=tempNum+4;
        do{
            if (i == comma){
                temp[i] = '.';
                comma+=4;
            }
            else{
                temp[i] = strNum[k];
                k++;
            }
            i++;
            if (k == len-1) temp[i+1] = '\000';
        }while (k < len);
        strcat(temp, ",-");
    }
    else sprintf(temp, "Rp. %d,-", num);
}

void buat_judul(char *judul, char token, int len){
    int lenA, lenZ;
    len = len - strlen(judul);
    if (len%2 == 0){
        lenA = lenZ = len/2;
    }
    else {
        lenA = len/2;
        lenZ = len/2+1;
    }

    for (int j = 0; j < lenA; j++)
    {
        printf("%c", token);
    }
    printf("%s", judul);
    for (int k = 0; k < lenZ; k++)
    {
        printf("%c", token);
    }
}

void sell(){
    char code[6];
    int q, indexItem=-1;
    // code
    printf("Input air freshener code [5 chars]: ");
    scanf("%s", code);
    // checking the input code
    for (int i = 0; i < 7; i++){
        if (strcmp(code, data_airfreshener[i].code) != 0 && i == 6){
            printf("--- The air freshener code doesn’t exist ---\n");
        }
        else if (strcmp(code, data_airfreshener[i].code) == 0){
            indexItem = i;
            break;
        }
    }
    
    if (indexItem>=0){
        // quantity
        printf("Input the quantity [0..%d] : ", data_airfreshener[indexItem].available);
        scanf("%d", &q);
        // checking quantity
        if (q > data_airfreshener[indexItem].available || q < 0){
            printf("--- The quantity of air freshener is not enough ---\n");
        }
        // if quantity available
        else {
            char temp[50];
            // show total
            buat_harga(temp, data_airfreshener[indexItem].price * q);
            printf("\nTotal price is : Rp %d,- x %d = %s\n\n--- Thank You ---\n", data_airfreshener[indexItem].price, q, temp);
            // update quantity
            data_airfreshener[indexItem].available -= q;
        }
    }
    system("pause");
}

void add_stock(){
    char code[6];
    int q, indexItem=-1;
    // code
    printf("Input air freshener code [5 chars]: ");
    scanf("%s", code);
    // checking the input code
    for (int i = 0; i < 7; i++){
        if (strcmp(code, data_airfreshener[i].code) != 0 && i == 6){
            printf("--- The air freshener code doesn’t exist ---\n");
        }
        else if (strcmp(code, data_airfreshener[i].code) == 0){
            indexItem = i;
            break;
        }
    }    
    if (indexItem>=0){
        // quantity
        printf("Input the quantity [1..100] : ");
        scanf("%d", &q);
        // checking quantity
        if (q > 100 || q < 1){
            printf("--- The input is wrong ---\n");
        }
        // if quantity correct
        else {
            // show message success
            printf("\n--- Adding Stock Success ---\n");
            // update quantity
            data_airfreshener[indexItem].available += q;
        }
    }
    system("pause");
}

int main(){
    char temp[50], temp2[50];
    do {
        buat_judul("JOJO AIR FRESHENER CASHIER", ' ', 62);
        printf("\n");
        buat_judul("==========================", ' ', 62);
        printf("\n\n");
        printf("| %s | %s | %s | %s |    %s   |\n", "No", "Code ", "Air Freshener Name", "Available", " Price ");
        printf("--------------------------------------------------------------\n");
        for (int i = 0; i < 7; i++){
            // no
            itoa(i+1, temp2, 10);
            strcpy(temp, "0");
            strcat(temp, temp2);
            printf("|");
            buat_judul(temp, ' ', 4);
            // code
            printf("|");
            buat_judul(data_airfreshener[i].code, ' ', 7);
            // name
            printf("|");
            buat_judul(data_airfreshener[i].name, ' ', 20);
            // available
            itoa(data_airfreshener[i].available, temp, 10);
            printf("|");
            buat_judul(temp, ' ', 11);
            // price
            printf("|");
            buat_harga(temp, data_airfreshener[i].price);
            buat_judul(temp, ' ', 14);
            printf("|\n");
        }
        printf("--------------------------------------------------------------\n");

        // menu
        int ch;
        printf("\nMenu :\n");
        printf("1. Sell\n");
        printf("2. Add Stock\n");
        printf("3. Exit\n");
        printf("Input choice : ");
        scanf("%d", &ch);
        switch (ch){
        case 1:
            sell();
            break;    
        case 2:
            add_stock();
            break;    
        case 3:
            exit(0);
            break;    
        default:
            printf("The choice doesn't exist!\n");
            break;
        }
        system("cls");
    }while(1);

    return 0;
}
