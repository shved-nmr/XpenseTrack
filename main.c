#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_DESC_SZ 80
#define ACT_MAX_SZ 4

struct time{
    int day;
    int month;
    int year;
};
struct user_data{
    int trans_type;
    char trans_description[MAX_DESC_SZ];
    float money_amount;
    struct time trans_time;
};


void print_data();
void record_data();
void clean_records();


int main() {

    int choice;

    while (1) {


        printf("=============== Financial Record Database ================\n\n");

        printf("1. Add New Record\n\n");
        printf("2. Display Your Financial Report\n\n");
        printf("3. Erase All Records\n\n");
        printf("0. Exit\n\n");

        printf("~~~~~~~~~~~~~~~~~~~~~~ XpenseTrack ~~~~~~~~~~~~~~~~~~~~~~\n\n");

        printf("\nPlease, enter your action:");
        scanf("%d", &choice);


                switch (choice) {
                    case 1:
                        record_data();
                        break;

                    case 2:
                        print_data();
                        break;

                    case 3:
                        clean_records();
                        break;
                    case 0:
                        exit(0);
                }
    }
        return 0;

}

    void print_data() {

        FILE *infile;
        struct user_data d;
        float income = 0;
        float expense = 0, total = 0;


        infile = fopen("c:\\Users\\erkki\\Documents\\XpenseTrack\\data.dat", "rb");

        if (infile == NULL) {
            printf("File could not be opened, exiting program. \n");
        } else {
            while (1) {
                fread(&d, sizeof(d), 1, infile);
                if (feof(infile)) {
                    break;
                }

                if (d.trans_type == 1) {
                    printf("Type:        income\n"
                           "Description: %-80s\n"
                           "Amount:      %.2f\n"
                           "Date:        %d.%d.%d\n",
                             d.trans_description, d.money_amount, d.trans_time.day, d.trans_time.month, d.trans_time.year);
                    income = income + d.money_amount;
                    printf("---------------------------------------------\n");
                } else if (d.trans_type == 0){
                    printf("Type:        expense\n"
                           "Description: %-80s\n"
                           "Amount:      %.2f\n"
                           "Date:        %d.%d.%d\n",
                            d.trans_description, d.money_amount, d.trans_time.day, d.trans_time.month, d.trans_time.year);
                    expense = expense + d.money_amount;
                    printf("---------------------------------------------\n");
                }


                total = income - expense;

            }
            printf("Your total income is:    %10.2f\n", income);
            printf("Your total expense is:   %10.2f\n", expense);
            printf("Your current balance is: %10.2f\n", total);
            printf("---------------------------------------------\n");
        }
        fclose(infile);
    }

    void record_data() {
        FILE *outfile;
        char trans_type[10];
        struct user_data d1;

        outfile = fopen("c:\\Users\\erkki\\Documents\\XpenseTrack\\data.dat", "ab");
        if (outfile == NULL) {
            printf("Error!\n");

        }

        for (;;) {
            printf("\nPlease, enter the transaction type,\n[Income/Expense]: \n");
            scanf("%s", trans_type);

            if (strncmp(trans_type, "Expense", 4) == 0 || strncmp(trans_type, "expense", 4) == 0 ||
                strncmp(trans_type, "EXPENSE", 4) == 0
                || strncmp(trans_type, "e", 4) == 0 || strncmp(trans_type, "E", 4) == 0) {
                d1.trans_type = 0;
                break;
            } else if (strncmp(trans_type, "Income", 4) == 0 || strncmp(trans_type, "income", 4) == 0 ||
                       strncmp(trans_type, "INCOME", 4) == 0
                       || strncmp(trans_type, "i", 4) == 0 || strncmp(trans_type, "I", 4) == 0) {
                d1.trans_type = 1;
                break;
            } else {
                printf("The input is invalid!\n");
            }
        }

        fseek(stdin, 0, SEEK_END);

        printf("\nPlease, enter the transaction description (max. 80 characters):\n");
        fgets(d1.trans_description, MAX_DESC_SZ, stdin);

        if (d1.trans_type == 0) {
            printf("\nPlease, enter the amount of money spent: \n");
        } else {
            printf("\nPlease, enter the amount of money received: \n");
        }
        scanf("%f", &d1.money_amount);


        for (;;) {
            printf("\nPlease, enter the transaction date (DD.MM.YY): \n");
            scanf("%d.%d.%d", &d1.trans_time.day, &d1.trans_time.month, &d1.trans_time.year);

            if (d1.trans_time.day <= 31 && d1.trans_time.month <= 12) {
                break;
            } else {
                printf("The input is invalid. Please, re-enter the date.\n");
            }
        }

        fwrite(&d1, sizeof(d1), 1, outfile);
        fclose(outfile);
    }

    void clean_records() {
        FILE *outfile;
        char action[ACT_MAX_SZ];

        printf("Are you sure you want to delete all data?\n"
               "The action is irreversible![Y/N]\n");
        scanf("%s", action);

        if (strncmp(action, "Y", 1) == 0 || strncmp(action, "y", 1) == 0 ||
            strncmp(action, "Yes", 3) == 0
            || strncmp(action, "YES", 3) == 0 || strncmp(action, "yes", 3) == 0) {
            outfile = fopen("c:\\Users\\erkki\\Documents\\XpenseTrack\\data.dat", "wb");
            if (outfile == NULL) {
                printf("Error!\n");
            } else{
                printf("Your data has been erased!\n");
            }
            fclose(outfile);
        }else{
            printf("The data has not been erased!\n");
        }

    }




/*Appropriate credits are given to:
 * https://vinodthebest.wordpress.com/2012/11/15/how-to-store-structures-data-in-c/ (Mr. Vinod Pillai);
 * (stackoverflow.com) anonymous users;
 * https://alvinalexander.com/programming/printf-format-cheat-sheet (Alvin Alexander);
 * Keijo Länsikunnas' lectures
 * */