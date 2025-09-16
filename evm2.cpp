#include <conio.h>
#include <stdio.h>

struct textInfo {
    unsigned char winRight, winBottom;
    unsigned char attribute, normattr;
    unsigned char currMode;
    unsigned short screenHeight;
    unsigned short screenWidth;
    unsigned short curX, curY;
};

struct textInfo textInfo;

void window(int leftCol, int topRow, int rightCol, int bottomRow) {

    textInfo.winRight = rightCol;
    textInfo.winBottom = bottomRow;

    textInfo.screenWidth = getmaxx();
    textInfo.screenHeight = getmaxy();

    gotoxy(leftCol, topRow);
    textInfo.curX = leftCol;
    textInfo.curY = topRow;

    int width = rightCol - leftCol + 1;
    int height = bottomRow - topRow + 1;

    gotoxy(leftCol, topRow);
    printf("*");
    for (int i = 0; i < width - 2; i++) printf("-");
    printf("-");

    for (int i = topRow + 1; i < bottomRow; i++) {
        gotoxy(leftCol, i);
        printf("|");
        gotoxy(rightCol, i);
        printf("|");
    }

    gotoxy(leftCol, bottomRow);
    printf("-");
    for (int i = 0; i < width - 2; i++) printf("-");
    printf("-");

    gotoxy(leftCol + 1, topRow + 1);
    textInfo.curX = leftCol + 1;
    textInfo.curY = topRow + 1;
}

int main() {
    clrscr();

    window(25, 15, 55, 5);

    gotoxy(26, 7);
    printf("hello world");

    getch();
    return 0;
}