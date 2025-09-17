#include <conio.h>
#include <stdio.h>
#include <dos.h>

void scroll(int direction, char l_row, char l_col, char r_row, char r_col, char attr)
{
    union REGS r;
    if (direction) {
        r.h.ah = 6;
        r.h.al = direction;
    } else {
        r.h.ah = 6;
        r.h.al = 0;
    }
    r.h.ch = l_row;
    r.h.cl = l_col;
    r.h.dh = r_row;
    r.h.dl = r_col;
    r.h.bh = attr;
    int86(0x10, &r, &r);
}

void displayColorCombinations(int x1, int y1, int x2, int y2, double T) {
    int row = 0;
    const char* colorNames[] = {
        "Black", "Blue", "Green", "Cyan", "Red", "Magenta", "Brown", "Light Gray",
        "Dark Gray", "Light Blue", "Light Green", "Light Cyan", "Light Red", "Light Magenta", "Yellow", "White"
    };
    const int colorCount = 16;
    int height = y2 - y1 + 1;
    window(x1, y1, x2, y2);
    for (int bg = 0; bg < colorCount; bg++) {
        for (int fg = 0; fg < colorCount; fg++) {
            textbackground(bg);
            textcolor(fg);
            if (row >= height) {
                scroll(0, y1, x1, y2, x2, bg);
                row = 0;
            }
            gotoxy(1, 1 + row);
            clreol();
            cprintf(" BС: %s, FС: %s", colorNames[bg], colorNames[fg]);
            row++;
            delay(T * 1000);
        }
    }
}

int main() {
    clrscr();
    displayColorCombinations(25, 5, 55, 15, 0.6);
    getch();
    return 0;
}