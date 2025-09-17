#include <conio.h>
#include <stdio.h>
#include <dos.h>

struct textInfo {
    unsigned char winRight, winBottom;
    unsigned char attribute, normattr;
    unsigned char currMode;
    unsigned short screenHeight;
    unsigned short screenWidth;
    unsigned short curX, curY;
};

struct textInfo textInfo;

void displayColorCombinations(int x1, int y1, int x2, int y2, double T) {
    int row = 0;
    const char* colorNames[] = {
        "Black", "Blue", "Green", "Cyan", "Red", "Magenta", "Brown", "Light Gray",
        "Dark Gray", "Light Blue", "Light Green", "Light Cyan", "Light Red", "Light Magenta", "Yellow", "White"
    };

    const int colorCount = 16;

    int width = x2 - x1 + 1;
    int height = y2 - y1 + 1;

    window(x1, y1, x2, y2);

    for (int bg = 0; bg < colorCount; bg++) {
        for (int fg = 0; fg < colorCount; fg++) {

            textbackground(bg);
            textcolor(fg);


                    gotoxy(x1, y1 + row);
                    clreol();

                    cprintf(" BG: %s, FG: %s", colorNames[bg], colorNames[fg]);



            row = row++ % (height-1);
            delay(T * 1000);
        }
    }
}

void window(int leftCol, int topRow, int rightCol, int bottomRow) {
    int i;
    textInfo.winRight = rightCol;
    textInfo.winBottom = bottomRow;

    textInfo.screenWidth = 80;
    textInfo.screenHeight = 25;

    gotoxy(leftCol, topRow);
    textInfo.curX = leftCol;
    textInfo.curY = topRow;

    int width = rightCol - leftCol + 1;
    int height = bottomRow - topRow + 1;

    gotoxy(leftCol, topRow);
    printf("*");

    for (i = 0; i < width - 2; i++) printf("-");
    printf("-");

    for (i = topRow + 1; i < bottomRow; i++) {
        gotoxy(leftCol, i);
        printf("|");
        gotoxy(rightCol, i);
        printf("|");
    }

    gotoxy(leftCol, bottomRow);
    printf("-");
    for (i = 0; i < width - 2; i++) printf("-");
    printf("-");

    gotoxy(leftCol + 1, topRow + 1);
    textInfo.curX = leftCol + 1;
    textInfo.curY = topRow + 1;
}

int main() {
    clrscr();

    displayColorCombinations(25, 5, 55, 15, 0.6);

    getch();
    return 0;
}