#include "header.h"

int countNeighbors(bool** field, unsigned x, unsigned y) {

    int sum = 0;

    if (x > 0) {
        if (field[y][x - 1]) sum++;
        if (y > 0 && field[y - 1][x - 1]) sum++;
        if (y < bmpTemplate.height - 1 && field[y + 1][x - 1]) sum++;
    }
    if (x < bmpTemplate.width - 1) {
        if (field[y][x + 1]) sum++;
        if (y > 0 && field[y - 1][x + 1]) sum++;
        if (y < bmpTemplate.height - 1 && field[y + 1][x + 1]) sum++;
    }
    if (y > 0 && field[y - 1][x]) sum++;
    if (y < bmpTemplate.height - 1 && field[y + 1][x]) sum++;

    return sum;
}

void gameOfLife(bool** field) {

    int* neighborsArray = (int*)calloc(bmpTemplate.width * bmpTemplate.height, sizeof(int*));

    int count = 0;
    for (int i = 0; i < bmpTemplate.height; i++) {
        for (int j = 0; j < bmpTemplate.width; j++) {
            neighborsArray[count++] = countNeighbors(field, j, i);
        }
    }

    for (int i = 0; i < bmpTemplate.height; i++) {
        for (int j = 0; j < bmpTemplate.width; j++) {
            if (field[i][j]) {
                field[i][j] = (neighborsArray[i * bmpTemplate.width + j] == 2 || neighborsArray[i * bmpTemplate.width + j] == 3) ? true : false;
            }
            else {
                field[i][j] = (neighborsArray[i * bmpTemplate.width + j] == 3) ? true : false;
            }
        }
    }
}
