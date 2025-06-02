#include "shell.h"
#include "kernel.h"

// Warna default: Light Grey on Black
int cursorOffset = 0; // posisi offset global (di video memory)

#define VIDEO_MEMORY 0xB800
#define MAX_COL 80
#define MAX_ROW 25

int main() {
  clearScreen();
  shell();
}
// void setCursor(int offset) {
//     int pos = offset / 2;
//     int row = pos / MAX_COL;
//     int col = pos - (pos / MAX_COL) * MAX_COL;
//     interrupt(0x10, 0x0200, 0, (row << 8) | col, 0);
// }

// void printChar(char c) {
//     if (c == '\n') {
//         cursorOffset = ((cursorOffset / 160) + 1) * 160;
//     } else if (c == '\r') {
//         cursorOffset = (cursorOffset / 160) * 160; // kembali ke awal baris
//     } else {
//         putInMemory(VIDEO_MEMORY, cursorOffset, c);
//         putInMemory(VIDEO_MEMORY, cursorOffset + 1, current_color);
//         cursorOffset += 2;
//     }
//     setCursor(cursorOffset);
// }

// void printString(char *str) {
//     int i = 0;
//     while (str[i] != '\0') {
//         printChar(str[i]);
//         i++;
//     }
// }

void printString(char *str)
{
  //TODO: Implementasi fungsi untuk mencetak string
  int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '\n') {
            // newline: pindah baris
            interrupt(0x10, 0x0E0A, 0, 0, 0); // '\n'
            interrupt(0x10, 0x0E0D, 0, 0, 0); // '\r'
        } else {
            interrupt(0x10, 0x0E00 + str[i], 0, 0, 0);
            // interrupt(0x10, 0x0900 + str[i], 0x0001, current_color, 0);
        }
        i++;
    }
}

void readString(char *buf)
{
  int i = 0;
    char c;

    while (1) {
        c = interrupt(0x16, 0, 0, 0, 0); // baca keyboard

        if (c == 0x0D) { // ENTER
            buf[i] = '\0';
            printString("\n");
            break;
        } else if (c == 0x08) { // BACKSPACE
            if (i > 0) {
                i--;
                printString("\b \b");
            }
        } else {
            buf[i++] = c;
            interrupt(0x10, 0x0E00 + c, 0, 0, 0); // tampilkan char
        }
    }
}

void clearScreen()
{
  //TODO: Implementasi fungsi untuk membersihkan layar
  int i;
  for (i = 0; i < 25 * 80; i++) {
    putInMemory(0xB800, i * 2, ' ');
    putInMemory(0xB800, i * 2 + 1, 0x07);
  }
  interrupt(0x10, 0x0200, 0, 0, 0);
}
