#include <conio.h>
#include <dos.h>

void scrollDown(char l_row, char l_col, char r_row, char r_col, char attr)
{
    union REGS r;
    r.h.ah = 0x07;
    r.h.al = 1;
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
    for (int bg = 0; bg < colorCount/2; bg++) {
        for (int fg = 0; fg < colorCount; fg++) {
            textbackground(bg);
            textcolor(fg);
            if (row > height) {
                scrollDown(y1-1, x1-1, y2-1, x2-1, bg);
                row--;
            }
            gotoxy(1, (row % height) + 1);
            clreol();
            cprintf("BC: %s, FC: %s", colorNames[bg], colorNames[fg]);
            row++;
            delay(T * 1000);

        }
    }
}

int main() {
    clrscr();
    displayColorCombinations(25, 5, 55, 15, 0.6);
    gotoxy(1, 1);
    cprintf("Program finished. Press any key to exit...");
    getch();
    clrscr();
    return 0;
}