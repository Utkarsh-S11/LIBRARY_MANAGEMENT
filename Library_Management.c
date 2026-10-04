#include "general_functions.h"
#include "core_functions.h"

int main(void) {
    login = fopen("password.dat", "rb");
    if (login == NULL) {
        gotoxy(10,9);
        printf("Database Do not exits. Be an adminstrator. Sign Up");
        adminsignup();
    } else {
        fclose(login);
        adminsignin();
    }
    mainmenu();
    return 0;
}

void mainmenu(void) {
    while (1) {
        clearScreen();
        gotoxy(20,3);
        printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MAIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
        gotoxy(20,5);
        printf("\xDB\xDB\xDB\xDB\xB2 1. Add Books   ");
        gotoxy(20,7);
        printf("\xDB\xDB\xDB\xDB\xB2 2. Delete Book");
        gotoxy(20,9);
        printf("\xDB\xDB\xDB\xDB\xB2 3. Search Book");
        gotoxy(20,11);
        printf("\xDB\xDB\xDB\xDB\xB2 4. View Book List");
        gotoxy(20,13);
        printf("\xDB\xDB\xDB\xDB\xB2 5. Edit Book Record ");
        gotoxy(20,15);
        printf("\xDB\xDB\xDB\xDB\xB2 6. Change Password");
        gotoxy(20,17);
        printf("\xDB\xDB\xDB\xDB\xB2 7. Close Application");
        gotoxy(20,19);
        printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
        gotoxy(20,21);
        printf("Enter your choice:");
        fflush(stdout);
        
        int ch = getch();
        switch (ch) {
            case '1':
                addbooks();
                break;
            case '2':
                deletebooks();
                break;
            case '3':
                searchbooks();
                break;
            case '4':
                viewbooks();
                break;
            case '5':
                editbooks();
                break;
            case '6':
                change_password();
                gotoxy(10,13);
                printf("press any key to continue....");
                fflush(stdout);
                getch();
                break;
            case '7':
                creditNclose();
                break;
            default:
                gotoxy(10,23);
                printf("\aWrong Entry!!Please re-entered correct option");
                fflush(stdout);
                getch();
        }
    }
}

void addbooks(void) {    // function that adds books
    clearScreen();
    FILE *fp;
    int choice;
    add_window();
    gotoxy(20,22);
    printf("Enter your choice:");
    fflush(stdout);
    if (scanf("%d", &choice) != 1) return;
    
    if (choice == 7)
        mainmenu();
        
    clearScreen();
    fp = fopen("Record.dat", "ab+");
    if (!fp) {
        printf("Error opening Record.dat\n");
        return;
    }
    
    if (getdata(choice) == 1) {
        set_category_by_index(&book, choice - 1);
        fseek(fp, 0, SEEK_END);
        fwrite(&book, sizeof(book), 1, fp);
        fclose(fp);
        gotoxy(21,14);
        printf("The record is sucessfully saved");
        gotoxy(21,15);
        printf("Save any more?(Y / N):");
        fflush(stdout);
        int ch = getch();
        if (ch == 'n' || ch == 'N')
            mainmenu();
        else {
            clearScreen();
            addbooks();
        }
    } else {
        fclose(fp);
    }
}

void deletebooks(void) {    // function that deletes items from file Record.dat
    FILE *ft, *fp;
    clearScreen();
    int d, findBook = 0;
    char another = 'y';
    
    while (another == 'y' || another == 'Y') {
        clearScreen();
        gotoxy(10,5);
        printf("Enter the Book ID to delete:");
        fflush(stdout);
        if (scanf("%d", &d) != 1) break;
        
        fp = fopen("Record.dat", "rb+");
        if (!fp) {
            gotoxy(10,7);
            printf("Record.dat not found.");
            getch();
            break;
        }
        
        findBook = 0;
        while (fread(&book, sizeof(book), 1, fp) == 1) {
            if (book.id == d) {
                gotoxy(10,7);
                printf("The book record is available");
                gotoxy(10,8);
                printf("Book name is %s", book.name);
                gotoxy(10,9);
                printf("Rack No. is %d", book.rackno);
                findBook = 1;
                gotoxy(10,10);
                printf("Do you want to delete it?(Y/N):");
                fflush(stdout);
                int ch = getch();
                if (ch == 'y' || ch == 'Y') {
                    ft = fopen("test.dat", "wb");
                    if (ft != NULL) {
                        rewind(fp);
                        while (fread(&book, sizeof(book), 1, fp) == 1) {
                            if (book.id != d) {
                                fwrite(&book, sizeof(book), 1, ft);
                            }
                        }
                        fclose(fp);
                        fclose(ft);
                        remove("Record.dat");
                        rename("test.dat", "Record.dat");
                        gotoxy(10,11);
                        printf("The record is sucessfully deleted");
                    }
                    break;
                }
            }
        }
        if (findBook == 0) {
            fclose(fp);
            gotoxy(10,10);
            printf("No record is found");
            getch();
        }
        gotoxy(10,12);
        printf("Delete another record?(Y/N)");
        fflush(stdout);
        flush_input();
        another = (char)getch();
    }
}

void searchbooks(void) {
    clearScreen();
    printf("*****************************Search Books*********************************");
    gotoxy(20,10);
    printf("\xDB\xDB\xDB\xB2 1. Search By ID");
    gotoxy(20,14);
    printf("\xDB\xDB\xDB\xB2 2. Search By Name");
    gotoxy(15,20);
    printf("Enter Your Choice:");
    fflush(stdout);
    
    int ch = getch();
    switch (ch) {
        case '1':
            searchByID();
            break;
        case '2':
            searchByName();
            break;
        default:
            getch();
            searchbooks();
    }
}

void viewbooks(void) {  // show the list of books in library
    int j;
    FILE *fp;
    clearScreen();
    gotoxy(1,1);
    printf("*********************************Book List*****************************");
    gotoxy(2,2);
    printf(" CATEGORY     ID    BOOK NAME     AUTHOR       QTY     PRICE     RackNo ");
    j = 4;
    fp = fopen("Record.dat", "rb");
    if (fp != NULL) {
        while (fread(&book, sizeof(book), 1, fp) == 1) {
            gotoxy(3,j);
            printf("%s", get_category_name(book.cat_ptr));
            gotoxy(16,j);
            printf("%d", book.id);
            gotoxy(22,j);
            printf("%s", book.name);
            gotoxy(36,j);
            printf("%s", book.Author);
            gotoxy(50,j);
            printf("%d", book.quantity);
            gotoxy(57,j);
            printf("%.2f", book.Price);
            gotoxy(69,j);
            printf("%d", book.rackno);
            printf("\n\n");
            j++;
        }
        fclose(fp);
    }
    gotoxy(35, 25);
    returnfunc();
}

void editbooks(void) {  // edit information about book
    clearScreen();
    FILE *fp;
    int c = 0, d;
    gotoxy(20,4);
    printf("****Edit Books Section****");
    char another = 'y';
    while (another == 'y' || another == 'Y') {
        clearScreen();
        gotoxy(15,6);
        printf("Enter Book Id to be edited:");
        fflush(stdout);
        if (scanf("%d", &d) != 1) break;
        
        fp = fopen("Record.dat", "rb+");
        if (!fp) {
            gotoxy(15,8);
            printf("Record.dat not found.");
            getch();
            break;
        }
        
        c = 0;
        while (fread(&book, sizeof(book), 1, fp) == 1) {
            if (book.id == d) {
                gotoxy(15,7);
                printf("The book is available");
                gotoxy(15,8);
                printf("The Book ID:%d", book.id);
                gotoxy(15,9);
                printf("Enter new name:"); fflush(stdout); scanf("%19s", book.name);
                gotoxy(15,10);
                printf("Enter new Author:"); fflush(stdout); scanf("%19s", book.Author);
                gotoxy(15,11);
                printf("Enter new quantity:"); fflush(stdout); scanf("%d", &book.quantity);
                gotoxy(15,12);
                printf("Enter new price:"); fflush(stdout); scanf("%f", &book.Price);
                gotoxy(15,13);
                printf("Enter new rackno:"); fflush(stdout); scanf("%d", &book.rackno);
                gotoxy(15,14);
                printf("The record is modified");
                
                fseek(fp, -(long)sizeof(book), SEEK_CUR);
                fwrite(&book, sizeof(book), 1, fp);
                fclose(fp);
                c = 1;
                break;
            }
        }
        if (c == 0) {
            fclose(fp);
            gotoxy(15,9);
            printf("No record found");
        }
        gotoxy(15,16);
        printf("Modify another Record?(Y/N)");
        fflush(stdout);
        flush_input();
        another = (char)getch();
    }
    returnfunc();
}
