#include "shell.h"
#include "kernel.h"
#include "std_lib.h"

#define DEFAULT_USERNAME "user"
char current_color = 0x07; // default

static char username[64];
static char company_title[32] = "";

int x = 0;
int y = 0;
char res[32];

void shell() {
  char buf[128];
  char bufOriginal[128];
  char cmd[64];
  char arg[2][64];
  strcpy(username, DEFAULT_USERNAME);

  printString("Welcome to EorzeOS!\n");

  while (true) {
    printString(username);
    printString(company_title);
    printString("> ");

    readString(buf);
    strcpy(bufOriginal, buf);
    parseCommand(buf, cmd, arg);

    if (strcmp(cmd, "yogurt")) {
      int tick = getBiosTick();
      int idx;
      idx = mod(tick, 3) + 1;
        if (idx == 1) {
            printString("yo\n");
        } else if (idx == 2) {
            printString("ts unami gng </3\n");
        } else {
            printString("sygau\n");
        }
    } else if (strcmp(cmd, "yo")) {
      printString("gurt\n");
    } else if (strcmp(cmd, "gurt")) {
      printString("yo\n");
    } else if (strcmp(cmd, "user")) {
      if (arg[0][0] == '\0') {
        strcpy(username, DEFAULT_USERNAME);
        printString("Username changed to ");
        printString(username);
        printString("\n");
      } else {
        strcpy(username, arg[0]);
        printString("Username changed to ");
        printString(username);
        printString("\n");
      }
    } else if (strcmp(cmd, "grandcompany")) {
      if (strcmp(arg[0], "maelstrom")) {
        // Maelstrom: merah
        clearScreen(); // Clear screen
        strcpy(company_title, "@Storm");
        current_color = 0x04; // merah
      } else if (strcmp(arg[0], "twinadder")) {
        // Twin Adder: kuning
        clearScreen();
        strcpy(company_title, "@Serpent");
        current_color = 0x06;  // Kuning
      } else if (strcmp(arg[0], "immortalflames")) {
        // Immortal Flames: biru
        clearScreen();
        strcpy(company_title, "@Flame");
        current_color = 0x01;  // Biru
      } else {
        printString("Invalid Grand Company!\n");
      }
    } else if (strcmp(cmd, "clear")) {
      // Clear screen & reset warna + company
      clearScreen();
      current_color = 0x07; // Kembali ke putih abu-abu
      company_title[0] = '\0';

    } else if (strcmp(cmd, "add")) {
        if (arg[0][0] == '\0' || arg[1][0] == '\0') {
          printString("Usage: add <x> <y>\n");
        } else {
          atoi(arg[0], &x);
          atoi(arg[1], &y);
          itoa(x + y, res);
          printString(res);
          printString("\n");
        }
    } else if (strcmp(cmd, "sub")) {
        if (arg[0][0] == '\0' || arg[1][0] == '\0') {
        printString("Usage: sub <x> <y>\n");
      } else {
        atoi(arg[0], &x);
        atoi(arg[1], &y);
        itoa(x - y, res);
        printString(res);
        printString("\n");
      }
    } else if (strcmp(cmd, "mul")) {
      if (arg[0][0] == '\0' || arg[1][0] == '\0') {
        printString("Usage: mul <x> <y>\n");
      } else {
        atoi(arg[0], &x);
        atoi(arg[1], &y);
        itoa(x * y, res);
        printString(res);
        printString("\n");
      }
    } else if (strcmp(cmd, "div")) {
        if (arg[0][0] == '\0' || arg[1][0] == '\0') {
          printString("Usage: div <x> <y>\n");
        } else {
          atoi(arg[0], &x);
          atoi(arg[1], &y);
          if (y == 0) {
            printString("Error: Division by zero\n");
          } else {
            itoa(x / y, res);
            printString(res);
            printString("\n");
          }
        }
    } else if (cmd[0] == '\0') {
        continue; // Kosong, abaikan
    } else {
        // Command tidak dikenal → echo input asli
        printString(bufOriginal);
        printString("\n");
    }
  }
}

void parseCommand(char *buf, char *cmd, char arg[2][64]) {
  int i = 0, j = 0, k = 0;

  // Clear semua
  cmd[0] = '\0';
  arg[0][0] = '\0';
  arg[1][0] = '\0';

  // Ambil command
  while (buf[i] != ' ' && buf[i] != '\0') {
    cmd[i] = buf[i];
    i++;
  }
  cmd[i] = '\0';

  while (buf[i] == ' ') i++; // Skip spasi

  // Argumen pertama
  j = 0;
  while (buf[i] != ' ' && buf[i] != '\0') {
    arg[0][j++] = buf[i++];
  }
  arg[0][j] = '\0';

  while (buf[i] == ' ') i++; // Skip spasi

  // Argumen kedua
  k = 0;
  while (buf[i] != '\0') {
    arg[1][k++] = buf[i++];
  }
  arg[1][k] = '\0';
}
