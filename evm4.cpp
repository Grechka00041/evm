#include "dos.h"
#include "conio.h"
#include "stdio.h"

int code();

int main() {
    int x = 1, y = 1, ch = 0;
    clrscr();
    textbackground(GREEN);
    window(25, 5, 55, 15);

    do {
        clrscr();
        gotoxy(x, y);
        putch('*');
        ch = code();

        switch (ch) {
            case 72:
                if ((y - 1) >= 1) {
                    y -= 1;
                }
                break;
            case 80:
                if ((y) <= (15 - 5)) {
                    y += 1;
                }
                break;
            case 75:
                if ((x - 1) >= 1) {
                    x -= 1;
                }
                break;
            case 77:
                if ((x + 1) <= (55 - 25)) {
                    x += 1;
                }
                break;
        }
    } while (ch != 27);

    return 0;
}

int code() {
    union REGS r;
    r.h.ah = 0x7;
    int86(0x21, &r, &r);
    return r.h.al;
}