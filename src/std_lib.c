#include "std_lib.h"

// NOTE: HARUS BISA ANGKA NEGATIF
int div(int a, int b) {
    int q;
    int neg;
    
    q = 0;
    neg = 0;

    if (b == 0) return 0;

    if (a < 0) {
        a = -a;
        neg = 1;
    }

    if (b < 0) {
        b = -b;
        neg = 1 - neg;
    }

    while (a >= b) {
        a -= b;
        q++;
    }

    if (neg)
        q = -q;

    return q;
}

int mod(int a, int b) {
    int neg;
    int r;

    if (b == 0) return 0; // Hindari pembagian dengan 0

    neg = 0;
    if (a < 0) {
        a = -a;
        neg = 1;
    }

    if (b < 0) {
        b = -b;
    }

    while (a >= b) {
        a -= b;
    }

    r = a;
    if (neg) {
        r = -r;
        // Pastikan hasil tetap positif
        if (r < 0) r += b;
    }

    return r;
}

bool strcmp(char *str1, char *str2) {
    while (*str1 && *str2) {
        if (*str1 != *str2) return false;
        str1++;
        str2++;
    }
    return (*str1 == '\0' && *str2 == '\0');
}

void strcpy(char *dst, char *src) {
    while (*src) {
        *dst++ = *src++;
    }
    *dst = '\0';
}

// clear buffer dengan nilai 0
void clear(byte *buf, unsigned int size) {
  unsigned int i;
    for (i = 0; i < size; i++) {
        buf[i] = 0;
    }
}

// TODO: Implementasi konversi string ke integer
// NOTE: HARUS BISA ANGKA NEGATIF
void atoi(char *str, int *num)
{
    int sign = 1;
    int result = 0;
    int i = 0;

    // Tangani tanda negatif
    if (str[0] == '-') {
        sign = -1;
        i = 1;
    }

    // Proses tiap karakter angka
    for (; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9') break; // berhenti jika bukan angka
        result = result * 10 + (str[i] - '0');
    }

    *num = result * sign;
}

// TODO: Implementasi konversi integer ke string
// NOTE: HARUS BISA ANGKA NEGATIF
void itoa(int num, char *str) {
    char buf[12];
    int i;
    int neg;
    int j;

    i = 0;
    neg = 0;

    if (num < 0) {
        neg = 1;
        num = -num;
    }

    do {
        buf[i] = mod(num, 10) + '0';
        i++;
        num = div(num, 10);
    } while (num > 0);

    if (neg) {
        buf[i] = '-';
        i++;
    }

    j = 0;
    while (i > 0) {
        i--;
        str[j] = buf[i];
        j++;
    }

    str[j] = '\0';
}
