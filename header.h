#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <malloc.h>
#include <string.h>
#include <dir.h>
#include <time.h>

// Глобальные структуры
typedef struct {
    char* input;
    char* output;
    int max_iter;
    int dump_freq;
} ConsoleParameters;
extern ConsoleParameters parameters;

typedef struct {
    int fileSize;
    int pixelArrayBegin;
    int width;
    int height;
    unsigned char* pixelArray;
    int pixelArrayLength;
    int slashNLength;
    int colorPaletteSize;
    int colorPaletteLength;
} BmpTemplate;
extern BmpTemplate bmpTemplate;

// Декларации функций и файлы в которых они определены
// "bmpTemplateFuncs.c" (Функции взаимодействующие с глобальной bmpTemplate)
int byteSectionValue(const unsigned char* fileData, int start, int size);
unsigned char* dataSlice(const unsigned char* fileData, int start, int size);
int slashNLength(int width);
int calculatePixelArrayLength(int width, int height);
unsigned char* formatToByteArray(int value, int size);

// "boolFuncs.c" (Создание модели, преобразование модели в формат BITMAPPIXELARRAY)
bool** createModel();
unsigned char* createPixelArray(bool** model);

// "gameOfLife.c" (Логика игры Жизнь)
// int countNeighbors(bool** field, unsigned x, unsigned y)
void gameOfLife(bool** field);

// "createBmp.c" (Создание нового bmp файла)
// void rewriteData(unsigned char oldData[], const unsigned char* newData, int start, int size);
void createBmp(char* opFileName);


// "debug.c" (Функции для отладки)
void consoleLogBa(bool** boolArray, int x, int y);
void consoleLogUCa(unsigned char* byteArray, int size, int lineLength);
void consoleLogIa(int* intArray, int size, int lineLength);


#endif // HEADER_H
