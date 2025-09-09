#include <cmath>
#include <iostream>
#include "windows.h"

using namespace std;

union db{
    unsigned int Double[2];
    double numberDouble;
};

void binaryDouble(union db numberDouble) {

    unsigned int mask = 1 << 31;
    int size = sizeof(double) * 8;
    cout << "Ваше число в памяти компьютера выглядит так: ";
    for (int i = 0; i <= size; ++i) {
        putchar(numberDouble.Double[1] & mask ? '1' : '0');
        mask >>= 1;
        if (i == 0 || i == 11) {
            putchar(' ');
        }
    }
    mask = 1 << 31;
    for (int i = 0; i <= size; ++i) {
        putchar(numberDouble.Double[0] & mask ? '1' : '0');
        mask >>= 1;
    }
    cout << endl;
}

void binaryUnsignedInt(unsigned int num) {

    int size = sizeof(unsigned int) * 8;
    unsigned int mask = 1 << (size - 1);
    cout << "Ваше число в памяти компьютера выглядит так: ";
    for (int i = 0; i < size; i++) {
        putchar(num & mask ? '1' : '0');
        mask >>= 1;
        if (i % 8 == 0 || i == 31) {
            putchar(' ');
        }
    }
    cout << endl;
}

void changeBitsUnsignedInt(unsigned int num, int numOfBitsForChange, int firstBit) {
    int value;
    for (int i = 1; i <= numOfBitsForChange; i++) {
        cout << "Введите значение бита(0 или 1)";
        cin >> value;
        while (value !=0 && value != 1) {
            cout << "Введите корректное значение: ";
            cin >> value;
        }
        if (value == 1) {
            num = num << (firstBit + i);
        }
        if (value == 0) {
            num = num >> (firstBit + i);
        }
    }
    binaryUnsignedInt(num);
}

void changeBitsDouble(union db numberDouble, int numOfBitsForChange, int firstBit) {
    int value;
    for (int i = 1; i <= numOfBitsForChange; i++) {
        cout << "Введите значение бита(0 или 1)";
        cin >> value;
        while (value !=0 && value != 1) {
            cout << "Введите корректное значение: ";
            cin >> value;
        }
        if (value == 1) {
                numberDouble.Double[1] = numberDouble.Double[1] << (firstBit + i);
        }
        if (value == 0) {
                numberDouble.Double[1] = numberDouble.Double[1] >> (firstBit + i);
        }

        binaryDouble(numberDouble);
    }


}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    db numD;
    unsigned int numUI;
    int numOfBitsForChange, firstBit, value;

    cout << "Введите число типа double:";
    cin >> numD.numberDouble;
    binaryDouble(numD);

    cout << "Введите число типа unsigned int:";
    cin >> numUI;
    binaryUnsignedInt(numUI);

    cout << "Изменение unsigned int\n";
    cout << "Введите номер младшего бита для изменения: ";
    cin >> firstBit;
    while (firstBit > sizeof(unsigned int)*8 & firstBit < 0) {
        cout << "Введите корректное значение: ";
        cin >> firstBit;
    }

    cout << "Введите кол-во битов для изменения: ";
    cin >> numOfBitsForChange;
    while (numOfBitsForChange > sizeof(unsigned int)*8) {
        cout << "Введите корректное значение: ";
        cin >> numOfBitsForChange;
    }
    changeBitsUnsignedInt(numUI, numOfBitsForChange, firstBit);

    cout << "Изменение double\n";
    cout << "Введите номер младшего бита для изменения: ";
    cin >> firstBit;
    cin >> firstBit;
    while (firstBit > sizeof(unsigned int)*8 & firstBit < 0) {
        cout << "Введите корректное значение: ";
        cin >> firstBit;
    }

    cout << "Введите кол-во битов для изменения: ";
    cin >> numOfBitsForChange;
    while (numOfBitsForChange > sizeof(unsigned int)*8) {
        cout << "Введите корректное значение: ";
        cin >> numOfBitsForChange;
    }
    changeBitsDouble(numD, numOfBitsForChange, firstBit);

    return 0;
}