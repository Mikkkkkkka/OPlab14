#include "header.h"


int byteSectionValue(const unsigned char* fileData, int start, int size) {

    int value = 0;
    for (int i = 0; i < size; i++) {
        value += fileData[i + start] * pow(16, 2 * i);
    }
    return value;
}


int slashNLength(int width) {
    return width % 4;
}


int calculatePixelArrayLength(int width, int height) {
    return height * (width * 3 + slashNLength(width));
}


unsigned char* dataSlice(const unsigned char* fileData, int start, int size) {

    unsigned char* slicedData = (unsigned char*)calloc(size, sizeof(char));
    if (slicedData == NULL) {
        printf("\nMemory was not allocated!");
        exit(1);
    }

    for (int i = 0; i < size; i++) {
        slicedData[i] = fileData[i + start];
    }
    return slicedData; // LEAK!!
}


unsigned char* formatToByteArray(int value, int size) {

    unsigned char* bytes = (unsigned char*)calloc(size, sizeof(char));
    for (int i = 0; i < size; i++) {
        bytes[i] = (value > 0) ? value % 256 : 0x00;
        value /= 256;
    }

    return bytes; // LEAK!!
}
