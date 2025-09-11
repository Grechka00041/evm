#include <cmath>
#include <cstdint>
#include <iostream>
#include "windows.h"

using namespace std;

union db{
    uint64_t bits;
    double numberDouble;
};

template <typename T>
T checkedInput(T const floor = numeric_limits<T>::min(), T const ceiling = numeric_limits<T>::max()) {
    T num;
    cin >> num;
    while (cin.fail() || cin.peek() != '\n' || num > ceiling || num < floor) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Введите корректное значение: ";
        cin >> num;
    }
    return num;
}

void binaryDouble(db& numberDouble) {
    const int size = sizeof(uint64_t) * 8;
    uint64_t mask = static_cast<uint64_t>(1) << (size - 1);
    cout << "Ваше число в памяти компьютера выглядит так: ";
    for (int i = 0; i <= size; ++i) {
        putchar(numberDouble.bits & mask ? '1' : '0');
        mask >>= 1;
        if (i == 0 || i == 11) {
            putchar(' ');
        }
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
        if ((i + 1) % 8 == 0) {
            putchar(' ');
        }
    }
    cout << endl;
}

void changeBitsUnsignedInt(unsigned int num, int numOfBitsForChange, int firstBit) {
    int value;
    for (int i = 0; i < numOfBitsForChange; i++) {
        int bitPosition = firstBit + i;
        cout << "Введите значение бита(0 или 1)";
        cin >> value;
        while (value !=0 && value != 1) {
            cout << "Введите корректное значение: ";
            cin >> value;
        }
        if (value == 1) {
            num |= 1 << (bitPosition);
        }
        else{
            num &= ~(1 << (bitPosition));
        }
    }
    binaryUnsignedInt(num);
}


void changeBitsDouble(db& numberDouble, int numOfBitsForChange, int firstBit) {
    uint64_t mask;
    int value;
    for (int i = 0; i < numOfBitsForChange; i++) {
        int bitPosition = firstBit + i;
        mask = static_cast<uint64_t>(1) << bitPosition;
        cout << "Введите значение бита(0 или 1)";
        cin >> value;
        while (value !=0 && value != 1) {
            cout << "Введите корректное значение: ";
            cin >> value;
        }
        if (value == 1) {
            numberDouble.bits |= mask;
        } else {
            numberDouble.bits &= ~mask;
        }

    }
    binaryDouble(numberDouble);

}

int main() {

    SetConsoleOutputCP(CP_UTF8);

    db numD;
    unsigned int numUI;
    int numOfBitsForChange, firstBit, value;

    cout << "Введите число типа double:";
    numD.numberDouble = checkedInput<double>();
    binaryDouble(numD);

    cout << "Введите число типа unsigned int:";
    numUI = checkedInput<unsigned int>();
    binaryUnsignedInt(numUI);

    cout << "Изменение unsigned int\n";
    cout << "Введите номер младшего бита для изменения: ";
    firstBit = checkedInput<int>();
    while ((firstBit >= sizeof(unsigned int)*8) || (firstBit < 0)) {
        cout << "Введите корректное значение: ";
        cin >> firstBit;
    }

    cout << "Введите кол-во битов для изменения: ";
    numOfBitsForChange = checkedInput<int>();
    while (numOfBitsForChange > sizeof(unsigned int)*8) {
        cout << "Введите корректное значение: ";
        cin >> numOfBitsForChange;
    }
    changeBitsUnsignedInt(numUI, numOfBitsForChange, firstBit);

    cout << "Изменение double\n";
    cout << "Введите номер младшего бита для изменения: ";
    firstBit = checkedInput<int>();
    while ((firstBit >= sizeof(double)*8) || (firstBit < 0)) {
        cout << "Введите корректное значение: ";
        cin >> firstBit;
    }

    cout << "Введите кол-во битов для изменения: ";
    numOfBitsForChange = checkedInput<int>();
    while (numOfBitsForChange > sizeof(double)*8) {
        cout << "Введите корректное значение: ";
        cin >> numOfBitsForChange;
    }
    changeBitsDouble(numD, numOfBitsForChange, firstBit-1);
    return 0;
}