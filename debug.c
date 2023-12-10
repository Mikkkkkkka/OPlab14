#include "header.h"


// ВАЖНО: в BITMAPPIXELARRAY пиксели расположены по рядам слева направо, СНИЗУ вверх

void consoleLogUCa(unsigned char* byteArray, int size, int lineLength) {

    int lines = 0;
    for (int i = 0; i < size; i++) {
        if (byteArray[i] < 0x10) { printf("0"); }
        printf("%x ", byteArray[i]);
        if (++lines == lineLength) {
            lines = 0;
            printf("\n");
        }
    }
    printf("\n\n");
}


void consoleLogBa(bool** boolArray, int x, int y) {

    int lines = 0;
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            printf("%d ", (boolArray[i][j]) ? 1 : 0);
            if (++lines == y) {
                lines = 0;
                printf("\n");
            }
        }
    }
    printf("\n\n");
}


void consoleLogIa(int* intArray, int size, int lineLength) {

    int count = 0, line = 0;
    for (int i = 0; i < size; i++) {
        printf("%d ", intArray[count++]);
        if (++line == lineLength) {
            line = 0;
            printf("\n");
        }
    }
    printf("\n\n");
}
