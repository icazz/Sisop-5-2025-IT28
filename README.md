# Sisop-5-2025-IT28

## Kelompok

| Nama                          | NRP        |
| ----------------------------- | ---------- |
| Yuan Banny Albyan             | 5027241027 | (just give very little advice and make the readme)
| Ica Zika Hamizah              | 5027241058 | (98% author of this repo)
| Nafis Faqih Allmuzaky Maolidi | 5027241095 |

## Daftar Isi

- [Kelompok](#kelompok)
- [Daftar Isi](#daftar-isi)
- [Soal](#soal)
- [Petunjuk Soal](#petunjuk-soal)
  - [Source](#source)
  - [Headers](#headers)
  - [Makefile](#makefile)
  - [Video Demonstrasi](#video-demonstrasi)
- [Laporan](#laporan)

## Soal

Pada suatu hari, anda merasa sangat lelah dari segala macam praktikum yang sudah ada, sehingga anda berencana untuk tidur yang nyenyak di sebuah jam 3:34AM yang cerah. Tetapi, anda terbangun di dalam dunia berbeda yang bernama "Eorzea". Ada sesuatu yang mengganggu pikiran anda sehingga anda diharuskan membuat sebuah operating system bernama "EorzeOS" untuk mendampingi diri anda dalam dunia ini.

1. Sebagai seorang main character dari dunia ini, ternyata anda memiliki kekuatan yang bernama "The Echo", kekuatan ini memungkinkan anda untuk berbicara pada Operating System ini (mungkin sebenarnya bukan ini kekuatannya, tetapi ini cukup kuat juga), dengan tujuan agar semua hal yang anda katakan, bila bukan merupakan sebuah command yang valid, akan mengulang hal yang anda katakan.

   Ilustrasi:

   ```
   user> Hello!
   Hello!
   user> I have the Echo
   I have the Echo
   ```

2. gurt: yo

   Ilustrasi:

   ```
   user> yo
   gurt
   user> gurt
   yo
   ```

3. Seorang main character memerlukan sebuah nama yang semua orang bisa ingat dengan baik. Buatlah sebuah command yang memungkinkan pengguna untuk mengubah nama user pada shell yang digunakan:

   - `user <username>` = mengubah username menjadi `<username>`
   - `user` = mengubah username menjadi default `user`

   Ilustrasi:

   ```
   user> user Tia
   Username changed to Tia
   Tia> user
   Username changed to user
   user>
   ```

4. Tiga negara besar dari Eorzean Alliance butuh bantuan anda untuk ikut serta dalam "Grand Company" mereka sehingga anda bisa mengubah warna terminal ajaib anda sesuai warna utama dari company mereka:

   - `grandcompany maelstrom` = clear terminal, ubah semua teks berikutnya jadi merah
   - `grandcompany twinadder` = clear terminal, ubah semua teks berikutnya jadi kuning
   - `grandcompany immortalflames` = clear terminal, ubah semua teks berikutnya jadi biru
   - `grandcompany <selain atau kosong>` = tunjukkan error message
   - `clear` = clear terminal, ubah semua teks berikutnya kembali jadi awal (para Grand Company sedih kamu netral)

   Selain mengubah seluruh warna terminal, nama anda di dalam terminal akan diberikan tambahan nama judul Grand Company:

   - Maelstrom = `user@Storm`
   - Twin Adder = `user@Serpent`
   - Immortal Flames = `user@Flame`
   - `clear` = menghapus nama grand company

   Ilustrasi:

   ```
   gurt> grandcompany maelstrom
   -- terminal clear menjadi warna merah --
   gurt@Storm> clear
   -- terminal clear menjadi warna putih --
   ```

5. Sebagai pahlawan terkenal di antara ketiga negara besar Eorzean Alliance, salah satu supplier senjata terbesar di seluruh Eorzea bernama "Rowena's House of Splendors" tiba-tiba memerlukan bantuan anda untuk membuat sebuah sistem kalkulator sederhana melalui command karena pemimpin mereka tertidur setelah mengurus semua orang di dalam Eorzea:

   - `add <x> <y>` = x + y
   - `sub <x> <y>` = x - y
   - `mul <x> <y>` = x \* y
   - `div <x> <y>` = x / y

   Ilustrasi:

   ```
   user> add 4 2
   6
   user> sub 4 2
   2
   user> mul 3 -2
   -6
   user> div -6 -2
   3
   ```

6. me: yogurt

   gurt:

   - `yo`
   - `ts unami gng </3`
   - `sygau`

   pilih secara _random_

   Ilustrasi:

   ```
   user> yogurt
   gurt> yo
   user> yogurt
   gurt> ts unami gng </3
   user> yogurt
   gurt> sygau
   ```

7. Perusahaan mesin "Garlond Ironworks" tiba-tiba lelah mengurus permintaan senjata perang untuk orang ke-148649813234 yang berusaha menghadapi final boss yang sama, sehingga mereka perlu bantuan kamu untuk melengkapi `Makefile` yang diberikan dengan command-command yang sesuai untuk compile seluruh operating system ini.

## Petunjuk Soal

### Source

- [kernel.asm](src/kernel.asm)
  - `_putInMemory`: penjelasan terdapat dalam modul
  - `_interrupt`: fungsi untuk interrupt
    - `number`: interrupt vector number
    - `AX`,`BX`,`CX`,`DX`: register untuk diisi
    - `AX` merupakan kombinasi dari `AH` dan `AL`, pola ini juga berlaku untuk `BX`,`CX`, dan `DX`
    - Untuk menggabungkan jenis register `H` dan `L` menjadi `X` bisa menggunakan salah satu metode berikut:
      ```c
      AX = AH << 8 | AL    // first method
      AX = AH * 256 + AL   // second method
      ```
  - `getBiosTick`: fungsi untuk mendapatkan tick dari BIOS
- [kernel.c](src/kernel.c)
  - Diisi penerapan fungsi `printString`, `readString`, dan `clearScreen` dengan bantuan `kernel.asm`
    - untuk `printString`: Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 10h` dengan parameter `AH = 0x0E` untuk _teletype output_. Karakter yang ditampilkan dapat dimasukkan pada register `AL`. Fungsi ini akan menampilkan string karakter ASCII (_null-terminated_) ke layar.
    - untuk `readString`: Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 16h` dengan parameter `AH = 0x00` untuk _keyboard input_. Fungsi ini akan membaca karakter ASCII (_non-control_) yang dimasukkan oleh pengguna dan menyimpannya pada buffer hingga menekan tombol `Enter`. Handle tombol `Backspace` dibebaskan kepada praktikan.
    - untuk `clearScreen`: Ukuran layar adalah `80x25` karakter. Setelah layar dibersihkan, kursor akan kembali ke posisi awal yaitu `(0, 0)` dan buffer video untuk warna karakter diubah ke warna putih. Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 10h` atau menggunakan fungsi `putInMemory` untuk mengisi memori video.
- [shell.c](src/shell.c)
  - Diisi penerapan shell yang menggunakan fungsi kernel untuk parsing keseluruhan command yang diinput

### Headers

- [std_type.h](include/std_type.h)
  - `byte`: unsigned char data type, untuk angka 0-255 (`0x00`-`0xFF`)
  - `bool`: untuk boolean (true/false), karena boolean tidak built-in
- [std_lib.h](include/std_lib.h)
  - `div`: division
  - `mod`: modulo
  - Pembagian dan modulo tidak ada dalam assembly, sehingga harus dilengkapi dengan operator yang tersedia (`+`,`-`,`*`,`<<`,`>>`)
  - `strcmp`: membandingkan dua string
  - `strcpy`: copy string
  - `clear`: fill memory dengan `0`
  - `atoi`: alphanumeric to integer (string menjadi angka)
  - `itoa`: integer to alphanumeric (angka menjadi string)
- [kernel.h](include/kernel.h)
  - Deklarasi header untuk fungsi-fungsi dalam `kernel.c`
- [shell.h](include/shell.h)
  - Deklarasi header untuk fungsi-fungsi dalam `shell.c`

### Makefile

- [makefile](./makefile)
  - `prepare` : membuat disk image baru `floppy.img` pada direktori `bin/` dengan ukuran 1.44 MB.
  - `bootloader` : mengkompilasi `bootloader.asm` menjadi `bootloader.bin` pada direktori `bin/`.
  - `stdlib` : mengkompilasi `std_lib.c` menjadi `std_lib.o` pada direktori `bin/`.
  - `shell`: mengkompilasi `shell.c` menjadi `shell.o` pada direktori `bin/`.
  - `kernel` : mengkompilasi `kernel.c` menjadi `kernel.o` pada direktori `bin/` dan mengkompilasi `kernel.asm` menjadi `kernel_asm.o` pada direktori `bin/`.
  - `link` : menggabungkan `bootloader.bin`, `kernel.o`, `kernel_asm.o`, dan `std_lib.o` menjadi `floppy.img`.
  - `build` : menjalankan perintah `prepare`, `bootloader`, `stdlib`, `kernel`, dan `link`.

## Video Demonstrasi

[Akses Video dalam Assets](./assets/demo_IT28.mp4)

## Laporan

Pada suatu hari, anda merasa sangat lelah dari segala macam praktikum yang sudah ada, sehingga anda berencana untuk tidur yang nyenyak di sebuah jam 3:34AM yang cerah. Tetapi, anda terbangun di dalam dunia berbeda yang bernama "Eorzea". Ada sesuatu yang mengganggu pikiran anda sehingga anda diharuskan membuat sebuah operating system bernama "EorzeOS" untuk mendampingi diri anda dalam dunia ini.

Sebelum masuk ke soal utama, di sini ada beberapa fungsi yang didefinisikan di header file,
di kernel.h:

```c
extern void putInMemory(int segment, int address, char character);
extern int interrupt(int number, int AX, int BX, int CX, int DX);
unsigned int getBiosTick();
extern char current_color;

void printString(char* str); //untuk print ke layar terminal boch
void readString(char* buf); //untuk menerima input dari terminal boch
void clearScreen(void); //untuk menghapus semua tampilan di layar (agar rapih)
```

di shell.h

```c
extern char current_color;

void shell(void); //menjadi jembatan agar bisa diakses di kernel.c
void parseCommand(char *buf, char *cmd, char arg[2][64]);
```

di std_lib.h

```c
int div(int a, int b);
int mod(int a, int b);

bool strcmp(char *str1, char *str2);
void strcpy(char *dst, char *src);
void clear(byte *buf, unsigned int size);

void atoi(char *str, int *num);
void itoa(int num, char *str);
untuk define function yang diperlukan (karna tidak bisa include library serupa (jadi didefine sendiri))
```

di std_type.h

```c
typedef unsigned char byte;

typedef char bool;
#define true 1
#define false 0
mirip dengan std_lib.h (hanya untuk fungsi utilitas)
```

1. Sebagai seorang main character dari dunia ini, ternyata anda memiliki kekuatan yang bernama "The Echo", kekuatan ini memungkinkan anda untuk berbicara pada Operating System ini (mungkin sebenarnya bukan ini kekuatannya, tetapi ini cukup kuat juga), dengan tujuan agar semua hal yang anda katakan, bila bukan merupakan sebuah command yang valid, akan mengulang hal yang anda katakan.

   Ilustrasi:

   ```
   user> Hello!
   Hello!
   user> I have the Echo
   I have the Echo
   ```

   Pada soal ini kami menggunakan fungsi dari readString yang membaca string dari input, kemudian diprint menggunakan printString, sehingga setiap karakter yang dimasukkan ke terminal akan dikeluarkan lagi

```c
readString(buf);
    strcpy(bufOriginal, buf);
    parseCommand(buf, cmd, arg);
.
.
} else {
        // Command tidak dikenal → echo input asli
        printString(bufOriginal);
        printString("\n");
    }
```

2. gurt: yo

   Ilustrasi:

   ```
   user> yo
   gurt
   user> gurt
   yo
   ```

   konsepnya sama seperti echo, hanya saja ada sedikit speciality, dimana, ketika input 'yo' maka mengeluarkan 'gurt'
   menggunakan function yang didefine di std_lib (strcmp(), mod())

   ```c
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
   ```

3. Seorang main character memerlukan sebuah nama yang semua orang bisa ingat dengan baik. Buatlah sebuah command yang memungkinkan pengguna untuk mengubah nama user pada shell yang digunakan:

   - `user <username>` = mengubah username menjadi `<username>`
   - `user` = mengubah username menjadi default `user`

   Ilustrasi:

   ```
   user> user Tia
   Username changed to Tia
   Tia> user
   Username changed to user
   user>
   ```

   awalnya saat terminal dilaunch, maka user defaultnya adalah 'user' dan ketika readstring menerima input yang ada 'user' di dalamnya makan akan melakukan beberapa perubahan (det username nya 'user' ketika hanya ditemukan 'user' pada readstring, set username nya string input, ketika setelah input 'user' ada string lainnya)

   ```c
    else if (strcmp(cmd, "user")) {
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
    }
   ```

4. Tiga negara besar dari Eorzean Alliance butuh bantuan anda untuk ikut serta dalam "Grand Company" mereka sehingga anda bisa mengubah warna terminal ajaib anda sesuai warna utama dari company mereka:

   - `grandcompany maelstrom` = clear terminal, ubah semua teks berikutnya jadi merah
   - `grandcompany twinadder` = clear terminal, ubah semua teks berikutnya jadi kuning
   - `grandcompany immortalflames` = clear terminal, ubah semua teks berikutnya jadi biru
   - `grandcompany <selain atau kosong>` = tunjukkan error message
   - `clear` = clear terminal, ubah semua teks berikutnya kembali jadi awal (para Grand Company sedih kamu netral)

   Selain mengubah seluruh warna terminal, nama anda di dalam terminal akan diberikan tambahan nama judul Grand Company:

   - Maelstrom = `user@Storm`
   - Twin Adder = `user@Serpent`
   - Immortal Flames = `user@Flame`
   - `clear` = menghapus nama grand company

   Ilustrasi:

   ```
   gurt> grandcompany maelstrom
   -- terminal clear menjadi warna merah --
   gurt@Storm> clear
   -- terminal clear menjadi warna putih --
   ```

   di sini, konsep 'mengubah username nya mirip dengan sebelumya, hanya saja ada tambahan default color nya menyesuaikan grandcompany apa
   ketika terminal menerima input yang ada 'grandcompany' maka akan clearscreen(), lalu menambahkan komponen nama dan warna tergantung dari grandcompany apa,berkaitan dengan perubahan variabel global untuk perubahan nama, dan penambahan @[string] nya dengan strcpy()
   dan di sini hanya

   ```c
   } else if (strcmp(cmd, "grandcompany")) {
      if (strcmp(arg[0], "maelstrom")) {
        // Maelstrom: merah
        clearScreen(); // Clear screen
        strcpy(company_title, "@Storm");
        current_color = merah; // merah
      } else if (strcmp(arg[0], "twinadder")) {
        // Twin Adder: kuning
        clearScreen();
        strcpy(company_title, "@Serpent");
        current_color = kuning;  // Kuning
      } else if (strcmp(arg[0], "immortalflames")) {
        // Immortal Flames: biru
        clearScreen();
        strcpy(company_title, "@Flame");
        current_color = biru;  // Biru
      } else {
        printString("Invalid Grand Company!\n");
      }
    }
   ```

5. Sebagai pahlawan terkenal di antara ketiga negara besar Eorzean Alliance, salah satu supplier senjata terbesar di seluruh Eorzea bernama "Rowena's House of Splendors" tiba-tiba memerlukan bantuan anda untuk membuat sebuah sistem kalkulator sederhana melalui command karena pemimpin mereka tertidur setelah mengurus semua orang di dalam Eorzea:

   - `add <x> <y>` = x + y
   - `sub <x> <y>` = x - y
   - `mul <x> <y>` = x \* y
   - `div <x> <y>` = x / y

   Ilustrasi:

   ```
   user> add 4 2
   6
   user> sub 4 2
   2
   user> mul 3 -2
   -6
   user> div -6 -2
   3
   ```

   untuk bagian ini hanya melakukan readstring, dibandingkan menggunakan strcmp, atoi untuk memparsing input setelahnya kedalam sebuah variabel, melakukan operasi dengan itoa, dan mengeluarkannya sebagai res, lalu diprint

   ```c
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
    }
   ```

6. me: yogurt

gurt:

- `yo`
- `ts unami gng </3`
- `sygau`

pilih secara _random_

Ilustrasi:

```
user> yogurt
gurt> yo
user> yogurt
gurt> ts unami gng </3
user> yogurt
gurt> sygau
```

di soal ini untuk fungsi random, kami menggunakan getBiosTick(fungsi waktu) dan di modulo agar hasilnya konstan (range nya)

```c
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
```

11. Perusahaan mesin "Garlond Ironworks" tiba-tiba lelah mengurus permintaan senjata perang untuk orang ke-148649813234 yang berusaha menghadapi final boss yang sama, sehingga mereka perlu bantuan kamu untuk melengkapi `Makefile` yang diberikan dengan command-command yang sesuai untuk compile seluruh operating system ini.
    makefile dibuat dengan komponen:
    - prepare (ngeset image)
    - bootloader (run bootloader dan add bootloader ke img)
    - stdlib: ngerun stdlib
    - shell: ngerun shell
    - kernel: ngerun kernel asm dan kernel.c
    - link: ld86 -o bin/kernel.bin -d bin/kernel.o bin/kernel-asm.o bin/shell.o bin/std_lib.o (untuk menggabungkan file file hasil bcc dan nasm (berupa .biin atau .o agar menjadi 1 executable)
    - build: untuk ngerun sekaligus semuanya
    - clean: untuk membersihkan workspace (just some utilities)
    - run: untuk menjalankan build dan bochsrc agar sekali command saja
