#include "header.h"


void rewriteData(unsigned char oldData[], const unsigned char* newData, int start, int size) {

    for (int i = 0; i < size; i++) {
        oldData[i + start] = newData[i];
    }
}

void createBmp(char* opFileName) {

    // BITMAPFILEHEADER
    unsigned char fileHeader[] = {
        'B', 'M',               // [ BM ] Отметка формата BM
        0x00, 0x00, 0x00, 0x00, // *  0 * Размер файла (пока что 0)
        0x00, 0x00,             // [    ] Резерв1 (должен быть 0)
        0x00, 0x00,             // [    ] Резерв2 (должен быть 0)
        0x36, 0x00, 0x00, 0x00  // [ 54 ] Индекс первого пикселя (делаем через 3ю версию)
    };

    // Перезапись размера файла
    rewriteData(fileHeader, formatToByteArray(bmpTemplate.fileSize, 4), 2, 4);

    // BITMAPINFOHEADER
    unsigned char infoHeader[] = {
        0x28, 0x00, 0x00, 0x00, // [ 40 ] Размер info структуры (здесь 3-я версия)
        0x00, 0x00, 0x00, 0x00, // *  0 * Ширина изображения
        0x00, 0x00, 0x00, 0x00, // *  0 * Высота изображения
        0x01, 0x00,             // [  1 ] Количество слоёв? (всегда 1)
        0x18, 0x00,             // * 24 * Количество битов на пиксель (24 потому что 3 байта)
        0x00, 0x00, 0x00, 0x00, // [  0 ] Вид компрессии (у нас нет по этому 0)
        0x00, 0x00, 0x00, 0x00, // [  0 ] Размер пикселей в байтах (для компрессии)
        0x12, 0x0b, 0x00, 0x00, // [2834] Высота пиксель/метр (в aseprite`е так)
        0x12, 0x0b, 0x00, 0x00, // [2834] Ширина пиксель/метр (в aseprite`е так)
        0x00, 0x00, 0x00, 0x00, // *  0 * Размер таблицы цветов
        0x00, 0x00, 0x00, 0x00, // *  0 * Кол-во ячеек от начала таблицы до последней
    };

    // Перезапись ширины, высоты, и инфы про палитру
    rewriteData(infoHeader, formatToByteArray(bmpTemplate.width, 4), 4, 4);
    rewriteData(infoHeader, formatToByteArray(bmpTemplate.height, 4), 8, 4);
    rewriteData(infoHeader, formatToByteArray(bmpTemplate.bytesPerPixel * 8, 2), 14, 2);
    rewriteData(infoHeader, formatToByteArray(bmpTemplate.colorPaletteSize, 4), 32, 4);
    rewriteData(infoHeader, formatToByteArray(bmpTemplate.colorPaletteLength, 4), 36, 4);

    // BITMAPPIXELARRAY
    // bmpTemplate.pixelArray


    FILE* output = fopen(opFileName, "wb");
    if (output == NULL) {
        printf("ERROR: could not open output file\n");
        exit(0);
    }
    fwrite(fileHeader, sizeof(fileHeader), 1, output);
    fwrite(infoHeader, sizeof(infoHeader), 1, output);
    fwrite(bmpTemplate.pixelArray, sizeof(char) * bmpTemplate.pixelArrayLength, 1, output);
    fclose(output);
}
