#include "header.h"

// Глобальные структуры
ConsoleParameters parameters;
BmpTemplate bmpTemplate;

int main(int argc, char* argv[]) {

    // Проверяем количество аргументов
    if (argc < 3) {
        printf("Error: program requires at least two parameters");
        exit(0);
    }

    // Присваиваем аргументы по молчанию
    parameters.input = argv[1];
    parameters.output = argv[2];
    parameters.max_iter = -1;
    parameters.dump_freq = 1;

    // Проверяем существует ли заданный директорий
    char dirname[0x100];
    snprintf(dirname, sizeof(dirname), "%s", parameters.output);
    DIR* dir = opendir(dirname);
    if ((errno == ENOENT) && (mkdir(dirname) == -1)) {
        closedir(dir);
        printf("ERROR: output directory path is invalid\n");
        exit(0);
    }
    closedir(dir);

    // Принимаем параметры --max_iter и --dump_freq
    for (int i = 3; i < argc; i++) {
        if (strcmp(argv[i], "--max_iter") == 0) {
            if ((i + 1 >= argc) || (argv[i + 1][0] == '-')) {
                printf("Error --max_iter parameter takes 1 argument");
                exit(0);
            }
            parameters.max_iter = atoi(argv[i + 1]);
        }
        if (strcmp(argv[i], "--dump_freq") == 0) {
            if ((i + 1 >= argc) || (argv[i + 1][0] == '-')) {
                printf("Error --dump_freq parameter takes 1 argument");
                exit(0);
            }
            parameters.dump_freq = atoi(argv[i + 1]);
        }
    }

    //  Открываем исходный файл
    char fileNameBuffer[0x100];
    snprintf(fileNameBuffer, sizeof(fileNameBuffer), "%s", parameters.input);
    FILE* inp = fopen(fileNameBuffer, "r");
    if (inp == NULL) {
        printf("Error: --input not found");
        exit(0);
    }

    // Читаем исходный файл
    unsigned long long bufferSize = 100000;
    unsigned char fileData[bufferSize];
    fread(&fileData, sizeof(char), bufferSize, inp);

    // Параметры глобальной vmpTemplate
    bmpTemplate.fileSize = byteSectionValue(fileData, 2, 4);
    bmpTemplate.pixelArrayBegin = byteSectionValue(fileData, 10, 4);
    bmpTemplate.width = byteSectionValue(fileData, 18, 4);
    bmpTemplate.height = byteSectionValue(fileData, 22, 4);
    bmpTemplate.colorPaletteSize = byteSectionValue(fileData, 46, 4);
    bmpTemplate.colorPaletteLength = byteSectionValue(fileData, 50, 4);
    bmpTemplate.pixelArrayLength = calculatePixelArrayLength(bmpTemplate.width, bmpTemplate.height);
    bmpTemplate.slashNLength = slashNLength(bmpTemplate.width);
    bmpTemplate.pixelArray = dataSlice(fileData, bmpTemplate.pixelArrayBegin, bmpTemplate.pixelArrayLength);


    // Создаём
    bool** stepState = createModel();
    // consoleLogBa(stepState, bmpTemplate.width, bmpTemplate.height);

    char outputFileBuffer[0x100];
    unsigned stepNum = 0;
    while (true) {

        if (stepNum++ == parameters.max_iter) break;

        snprintf(outputFileBuffer, sizeof(outputFileBuffer), "%s\\Step%d.bmp", parameters.output, stepNum);
        printf("%s\n", outputFileBuffer);

        gameOfLife(stepState);
        //        consoleLogBa(stepState, bmpTemplate.width, bmpTemplate.height);

        bmpTemplate.pixelArray = createPixelArray(stepState);
        //        consoleLogUCa(bmpTemplate.pixelArray, bmpTemplate.pixelArrayLength, 3*bmpTemplate.width+bmpTemplate.slashNLength);

        createBmp(outputFileBuffer);
        time_t time2Wait = time(NULL) + parameters.dump_freq;
        while (time(NULL) < time2Wait);
    }

    fclose(inp);

    return 0;
}

// g++ -o app *.c *.h

// .\app.exe .inputfiles\collision.bmp out --max_iter 50 --dump_freq 1
