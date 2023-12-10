#include "header.h"


bool** createModel() {

    bool** field = (bool**)calloc(bmpTemplate.width * bmpTemplate.height, sizeof(bool));
    for (int i = 0; i < bmpTemplate.height; i++) {
        field[i] = (bool*)calloc(bmpTemplate.width, sizeof(bool));
    }

    int pixelArrayLine = bmpTemplate.width * 3 + bmpTemplate.slashNLength;
    for (int i = 0; i < bmpTemplate.pixelArrayLength; i += 3) {
        if (i == bmpTemplate.width) { i += bmpTemplate.slashNLength; }
        field[i / pixelArrayLine][(i % (pixelArrayLine)) / 3] = (bmpTemplate.pixelArray[i] == 0x00);
    }

    return field; // LEAK!!
}


unsigned char* createPixelArray(bool** model) {

    unsigned char* pixelArray = (unsigned char*)calloc(bmpTemplate.pixelArrayLength, sizeof(char));

    int count = 0;
    for (int i = 0; i < bmpTemplate.height; i++) {
        for (int j = 0; j < bmpTemplate.width; j++) {
            for (int k = 0; k < 3; k++) {
                pixelArray[count++] = (model[i][j]) ? 0x00 : 0xff;
            }
        }
        for (int k = 0; k < bmpTemplate.slashNLength; k++) {
            pixelArray[count++] = 0x00;
        }
    }

    return pixelArray; // LEAK!!
}
