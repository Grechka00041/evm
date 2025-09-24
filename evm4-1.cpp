#include "dos.h"
#include "conio.h"
#include "stdio.h"

int code();

void my_clrscr() {
    union REGS regs;
    regs.h.ah = 0x06;
    regs.h.al = 0;
    regs.h.bh = 7;
    regs.h.ch = 0;
    regs.h.cl = 0;
    regs.h.dh = 24;
    regs.h.dl = 79;
    int86(0x10, &regs, &regs);
}
void my_gotoxy(int x, int y) {
    union REGS regs;
    regs.h.ah = 0x02;
    regs.h.dl = x;
    regs.h.dh = y;
    regs.h.bh = 0;
    int86(0x10, &regs, &regs);
}

void my_putch(char c) {
    union REGS regs;
    regs.h.ah = 0x09;
    regs.h.al = c;
    regs.h.bl = 0x20;
    regs.h.bh = 0;
    regs.x.cx = 1;
    int86(0x10, &regs, &regs);
}
int main() {
    int x = 1, y = 1, ch = 0;
    my_clrscr();
    textbackground(GREEN);
    int x1 = 25, y1 = 5, x2 = 55, y2 = 15;
    window(25, 5, 55, 15);

    do {
        clrscr();
        my_gotoxy(x + x1 - 2, y + y1 - 2);
        my_putch('*');
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