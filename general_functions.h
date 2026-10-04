#ifndef GENERAL_FUNCTIONS_H
#define GENERAL_FUNCTIONS_H

#include "variables.h"

// Global variable definitions
FILE *login = NULL;
char findBook = 0;
char password[10] = {0};
struct BOOK book;
char catagories[][15] = {"Computer", "Electronics", "Electrical", "Civil", "Mechnnical", "Architecture"};

void gotoxy(int x, int y)
{
    // ANSI Escape sequence for terminal cursor movement: 1-indexed row=y, col=x
    printf("\033[%d;%dH", y, x);
    fflush(stdout);
}

void returnfunc(void)
{
    printf(" \nPress ENTER to return to main menu");
    while (1) {
        int ch = getch();
        if (ch == 13 || ch == 10 || ch == '\n') {
            mainmenu();
            break;
        }
    }
}

void get_password(char* pass)
{
    int i = 0;
    while (1)
    {
        int ch = getch();
        if (ch == 13 || ch == 10 || ch == '\n') {
            printf("\n");
            break;
        }
        else if (ch == 8 || ch == 127) // Backspace (ASCII 8 or 127 on Linux)
        {
            if (i > 0) {
                printf("\b \b");
                fflush(stdout);
                i--;
            } else {
                printf("\a");
                fflush(stdout);
            }
        }
        else if (i < 9)
        {
            printf("*");
            fflush(stdout);
            pass[i] = (char)ch;
            i++;
        }
    }
    pass[i] = '\0';
}

void creditNclose(void) {
    clearScreen();
    gotoxy(16,3);
    printf("Programmer....");
    gotoxy(16,6);
    printf("Bibek Subedi");
    gotoxy(16,8);
    printf("E-mail:subedi_bibek@yahoo.co.in");
    gotoxy(16,10);
    printf("Department of Computer Enginnering");
    gotoxy(16,11);
    printf("Tribhuvan University, Nepal");
    gotoxy(10,17);
    printf("Exiting in 3 second...........>");
    fflush(stdout);
    Sleep(3000);
    exit(0);
}

int t(void) // for time
{
    time_t rawtime;
    time(&rawtime);
    printf("Date and time:%s\n", ctime(&rawtime));
    return 0;
}

void adminsignup(void) {
    char temp[10];
    login = fopen("password.dat", "wb");
    if (!login) {
        printf("Error opening password.dat for writing.\n");
        return;
    }
    gotoxy(10,10);
    printf("Enter password: ");
    get_password(password);
    gotoxy(10,11);
    printf("Re Enter Password: ");
    get_password(temp);
    while (strcmp(password, temp) != 0) {
        clearScreen();
        gotoxy(10,10);
        printf("Password did not matched! Enter again");
        gotoxy(10,11);
        printf("Enter password: ");
        get_password(password);
        gotoxy(10,12);
        printf("Re Enter Password: ");
        get_password(temp);
    }
    fwrite(&password, sizeof(password), 1, login);
    fclose(login);
}

void adminsignin(void) {
    char temp[10];
    login = fopen("password.dat", "rb");
    if (!login) {
        printf("Error opening password.dat.\n");
        return;
    }
    gotoxy(10,10);
    printf("Enter password: ");
    get_password(temp);
    while (fread(&password, sizeof(password), 1, login) == 1) {
        while (strcmp(temp, password) != 0) {
            clearScreen();
            gotoxy(10,10);
            printf("Password did not match! ");
            printf("Enter Again: ");
            get_password(temp);
        }
        gotoxy(10,11);
        printf("Password Match");
        break;
    }
    fclose(login);
    gotoxy(10,12);
    printf("Press any key...");
    fflush(stdout);
    getch();
}

void add_window(void) {
    gotoxy(20,5);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2SELECT CATEGOIES\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(20,7);
    printf("\xDB\xDB\xDB\xDB\xB2 1. Computer");
    gotoxy(20,9);
    printf("\xDB\xDB\xDB\xDB\xB2 2. Electronics");
    gotoxy(20,11);
    printf("\xDB\xDB\xDB\xDB\xB2 3. Electrical");
    gotoxy(20,13);
    printf("\xDB\xDB\xDB\xDB\xB2 4. Civil");
    gotoxy(20,15);
    printf("\xDB\xDB\xDB\xDB\xB2 5. Mechanical");
    gotoxy(20,17);
    printf("\xDB\xDB\xDB\xDB\xB2 6. Architecture");
    gotoxy(20,19);
    printf("\xDB\xDB\xDB\xDB\xB2 7. Back to main menu");
    gotoxy(20,21);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
}

int change_password(void) {
    clearScreen();
    FILE *fp;
    char old_pass[10], new_pass[10];
    gotoxy(10,10);
    printf("Enter Old password: ");
    get_password(old_pass);
    gotoxy(10,11);
    printf("Enter New password: ");
    get_password(new_pass);
    fp = fopen("password.dat", "rb+");
    if (!fp) {
        gotoxy(10,12);
        printf("Password file error!");
        return 0;
    }
    while (fread(&password, sizeof(password), 1, fp) == 1) {
        if (strcmp(old_pass, password) == 0) {
            strcpy(password, new_pass);
            fseek(fp, -(long)sizeof(password), SEEK_CUR);
            fwrite(&password, sizeof(password), 1, fp);
            fclose(fp);
            gotoxy(10,12);
            printf("Password sucessfully changed! ");
            return 1;
        } else {
            fclose(fp);
            gotoxy(10,12);
            printf("Password changing process failed!");
            return 0;
        }
    }
    fclose(fp);
    return 0;
}

#endif // GENERAL_FUNCTIONS_H
