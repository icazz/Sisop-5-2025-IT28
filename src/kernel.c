#include "shell.h"
#include "kernel.h"

int main() {
  clearScreen();
  shell();
}

void printString(char *str)
{
  //TODO: Implementasi fungsi untuk mencetak string
  int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '\n') {
            // newline: pindah baris
            interrupt(0x10, 0x0E0D, 0x0000, 0x0001, 0); // '\r'
            interrupt(0x10, 0x0E0A, 0x0000, 0x0001, 0); // '\n'
        } else {
            interrupt(0x10, 0x0900 + str[i], current_color, 0x0001, 0);
            interrupt(0x10, 0x0E00 + str[i], 0x0000, 0x0001, 0);
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
                // Gerak mundur kursor 1 kolom
                interrupt(0x10, 0x0E08, 0, 0, 0); // tampilkan backspace
                interrupt(0x10, 0x0E20, current_color, 0, 0); // tampilkan spasi di posisi sekarang
                interrupt(0x10, 0x0E08, 0, 0, 0); // kembali lagi 1 posisi
            }
        } else {
            buf[i++] = c;
            interrupt(0x10, 0x0900 + c, current_color, 0x0001, 0); // tampilkan char
            interrupt(0x10, 0x0E00 + c, 0, 0, 0);
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
