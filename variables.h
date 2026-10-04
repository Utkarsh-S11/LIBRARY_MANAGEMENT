#ifndef VARIABLES_H
#define VARIABLES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <stddef.h>

#ifdef _WIN32
  #include <conio.h>
  #include <windows.h>
  static inline void custom_sleep(unsigned int milliseconds) {
      Sleep(milliseconds);
  }
  static inline void clearScreen(void) {
      system("cls");
  }
  static inline void flush_input(void) {
      fflush(stdin);
  }
#else
  #include <unistd.h>
  #include <termios.h>
  #include <ctype.h>
  static inline int getch(void) {
      struct termios oldattr, newattr;
      int ch;
      if (tcgetattr(STDIN_FILENO, &oldattr) != 0) {
          return getchar();
      }
      newattr = oldattr;
      newattr.c_lflag &= ~(ICANON | ECHO);
      tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
      ch = getchar();
      tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
      return ch;
  }
  static inline void custom_sleep(unsigned int milliseconds) {
      usleep(milliseconds * 1000);
  }
  static inline void clearScreen(void) {
      printf("\033[2J\033[H");
      fflush(stdout);
  }
  static inline void flush_input(void) {
      tcflush(STDIN_FILENO, TCIFLUSH);
  }
#endif

#define Sleep(ms) custom_sleep(ms)

extern FILE *login;
extern char findBook;
extern char password[10];

// Explicit 60-byte binary packing for cross-platform struct BOOK compatibility
#pragma pack(push, 1)
struct BOOK
{
    int32_t id;         // 4 bytes (offset 0)
    char name[20];      // 20 bytes (offset 4)
    char Author[20];    // 20 bytes (offset 24)
    int32_t quantity;   // 4 bytes (offset 44)
    float Price;        // 4 bytes (offset 48)
    int32_t rackno;     // 4 bytes (offset 52)
    uint32_t cat_ptr;   // 4 bytes (offset 56) -> Total: 60 bytes
};
#pragma pack(pop)

extern struct BOOK book;

// Global categories defined in original application
extern char catagories[][15];
extern const uint32_t VMA_CATEGORY_POINTERS[6];

// Helper functions for Category pointer resolution
static inline const char* get_category_name(uint32_t cat_ptr) {
    static const uint32_t ptrs[6] = {
        0x00404000, // Computer
        0x0040400F, // Electronics
        0x0040401E, // Electrical
        0x0040402D, // Civil
        0x0040403C, // Mechnnical
        0x0040404B  // Architecture
    };
    static const char *names[6] = {
        "Computer", "Electronics", "Electrical", "Civil", "Mechnnical", "Architecture"
    };

    for (int i = 0; i < 6; i++) {
        if (cat_ptr == ptrs[i]) {
            return names[i];
        }
    }
    if (cat_ptr >= 0x00404000 && cat_ptr <= 0x00404050) {
        int idx = (cat_ptr - 0x00404000) / 15;
        if (idx >= 0 && idx < 6) return names[idx];
    }
    return names[0];
}

static inline void set_category_by_index(struct BOOK *b, int index) {
    static const uint32_t ptrs[6] = {
        0x00404000, 0x0040400F, 0x0040401E, 0x0040402D, 0x0040403C, 0x0040404B
    };
    if (index >= 0 && index < 6) {
        b->cat_ptr = ptrs[index];
    } else {
        b->cat_ptr = ptrs[0];
    }
}

// Function prototypes
void returnfunc(void);
void mainmenu(void);
void addbooks(void);
void deletebooks(void);
void editbooks(void);
void searchbooks(void);
void issuebooks(void);
void viewbooks(void);
void closeapplication(void);
int  getdata(int);
int  checkid(int);
void Password(void);
void get_password(char *);
void issuerecord(void);
void creditNclose(void);
void adminsignup(void);
void adminsignin(void);
void add_window(void);
int  change_password(void);

#endif // VARIABLES_H
