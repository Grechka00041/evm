#include <dos.h>
#include <conio.h>
#include <stdio.h>

int code() {
    union REGS r;
    r.h.ah = 0x07;
    int86(0x21, &r, &r);
    return r.h.al;
}

int pressed() {
    union REGS r;
    r.h.ah = 0x0B;
    int86(0x21, &r, &r);
    return r.h.al;
}

void init() {
    union REGS r;
    r.x.ax = 0;
    int86(0x33, &r, &r);
}

void unlock() {
    union REGS r;
    r.x.ax = 1;
    int86(0x33, &r, &r);
}

void lock() {
    union REGS r;
    r.x.ax = 2;
    int86(0x33, &r, &r);
}

int main() {

    int ch = 0;

    init();
    unlock();
    clrscr();

    do {
        if (pressed()) {
            ch = code();
            switch (ch) {
                case 77:
                    lock();
                    puts("Mouse is locked.");
                    break;
                case 75:
                    unlock();
                    puts("Mouse is unlocked.");
                    break;
            }
        }
        delay(50);
    } while (ch != 27);

    return 0;
}