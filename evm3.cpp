#include <graphics.h>
#include <math.h>
#include <stdio.h>
#include <conio.h>

#define PI 3.14159265359

double function(double x) {
    return pow(cos(x/2), 2) + sqrt(x);
}

int worldToScreenX(double x, double startX, double endX, int screenWidth) {
    return (int)((x - startX) * (screenWidth - 100) / (endX - startX)) + 50;
}

int worldToScreenY(double y, double minY, double maxY, int screenHeight) {
    return (int)((maxY - y) * (screenHeight - 100) / (maxY - minY)) + 50;
}

void findMaxValue(double startX, double endX, double *maxX, double *maxY) {
    double x, y;
    int points = 10000;
    *maxY = -1000000;
    for (int i = 0; i <= points; i++) {
        x = startX + (endX - startX) * i / points;
        y = function(x);
        if (y > *maxY) {
            *maxY = y;
            *maxX = x;
        }
    }
}

int main() {

    int gd = DETECT, gm;
    double startX = 3 * PI / 2;
    double endX = 18 * PI;
    double x, y;
    double minY, maxY;
    double maxX, maxYCoord;
    int points = 1000;
    int i;
    initgraph(&gd, &gm, "");
    minY = 1000000;
    maxY = -1000000;

    for (i = 0; i <= points; i++) {
        x = startX + (endX - startX) * i / points;
        y = function(x);
        if (y < minY) minY = y;
        if (y > maxY) maxY = y;
    }

    double yRange = maxY - minY;
    minY -= yRange * 0.1;
    maxY += yRange * 0.1;

    findMaxValue(startX, endX, &maxX, &maxYCoord);

    int originY = getmaxy() - 60;
    line(50, originY, getmaxx() - 50, originY);

    int originX = 50;
    line(originX, 50, originX, getmaxy() - 60);

    setcolor(WHITE);

    settextjustify(CENTER_TEXT, TOP_TEXT);
    int xAxisY = getmaxy() - 60;
    for (i = 0; i <= 18; i+=2) {
        double xValue = i * PI;
        if (xValue >= startX && xValue <= endX) {
            int screenX = worldToScreenX(xValue, startX, endX, getmaxx());
            line(screenX, xAxisY - 5, screenX, xAxisY + 5);
            char label[20];
            sprintf(label, "%dpi", i);
            outtextxy(screenX, xAxisY + 10, label);
        }
    }


    settextjustify(RIGHT_TEXT, CENTER_TEXT);
    int yAxisX = 50;
    for (i = 0; i <= 5; i++) {
        double yTick = minY + (maxY - minY) * i / 5;
        int screenY = worldToScreenY(yTick, minY, maxY, getmaxy());
        if (screenY > 50 && screenY < getmaxy() - 50) {
            line(yAxisX - 5, screenY, yAxisX + 5, screenY);
            char label[20];
            int intValue = (int)(yTick + 0.5);
            sprintf(label, "%d", intValue);
            outtextxy(yAxisX - 10, screenY, label);
        }
    }

    setcolor(WHITE);
    settextjustify(CENTER_TEXT, TOP_TEXT);
    outtextxy(getmaxx() - 70, originY - 20, "X");
    settextjustify(LEFT_TEXT, CENTER_TEXT);
    outtextxy(originX + 10, 60, "Y");

    setcolor(YELLOW);
    settextjustify(CENTER_TEXT, TOP_TEXT);
    outtextxy(getmaxx()/2, 20, "y = cos^2(x/2) + x^0.5");


    setcolor(RED);
    moveto(worldToScreenX(startX, startX, endX, getmaxx()),
           worldToScreenY(function(startX), minY, maxY, getmaxy()));

    for (i = 1; i <= points; i++) {
        x = startX + (endX - startX) * i / points;
        y = function(x);

        int screenX = worldToScreenX(x, startX, endX, getmaxx());
        int screenY = worldToScreenY(y, minY, maxY, getmaxy());

        lineto(screenX, screenY);
    }

    setcolor(GREEN);
    int maxScreenX = worldToScreenX(maxX, startX, endX, getmaxx());
    int maxScreenY = worldToScreenY(maxYCoord, minY, maxY, getmaxy());
    circle(maxScreenX, maxScreenY, 5);
    floodfill(maxScreenX, maxScreenY, GREEN);

    getch();
    cleardevice();
    setcolor(WHITE);
    rectangle(100, 100, 540, 250);

    settextjustify(CENTER_TEXT, CENTER_TEXT);
    setcolor(YELLOW);
    outtextxy(320, 130, "MAX VALUE");

    setcolor(WHITE);
    char maxWindowInfo[200];
    sprintf(maxWindowInfo, "Max value of a function y = cos^2(x/2) + x^0.5");
    outtextxy(320, 160, maxWindowInfo);

    char maxCoords[100];
    sprintf(maxCoords, "X = %.6f", maxX);
    outtextxy(320, 190, maxCoords);
    char maxValue[100];
    sprintf(maxValue, "Y = %.6f", maxYCoord);
    outtextxy(320, 220, maxValue);

    setcolor(LIGHTBLUE);
    outtextxy(320, 270, "Press any key to exit...");
    getch();
    closegraph();

    return 0;
}