#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"

int parseInt(char *number) {
	int result = 0;
	int digit = 1;
	for (int i = strlen(number) - 1; i > -1; i--) {
		switch (number[i]) {
			case '0':
				result += 0 * digit;
				break;
			case '1':
				result += 1 * digit;
				break;
			case '2':
				result += 2 * digit;
				break;
			case '3':
				result += 3 * digit;
				break;
			case '4':
				result += 4 * digit;
				break;
			case '5':
				result += 5 * digit;
				break;
			case '6':
				result += 6 * digit;
				break;
			case '7':
				result += 7 * digit;
				break;
			case '8':
				result += 8 * digit;
				break;
			case '9':
				result += 9 * digit;
				break;
			default:
				return -1;
		}
		digit *= 10;
	}
	return result;
}

int split(char *input, char splitSymbol, char **result) {

    char *symbol = (char *)malloc(sizeof(char) * 1);
    struct list *currentWord = createList();
    struct list *words = createList();
    if (currentWord == NULL || words == NULL) {
        fprintf(stderr, "An error occured while creating a list\n");
        return -1;
    }

    for (int i = 0; i < strlen(input); i++) {
        *symbol = input[i];
        if (*symbol != splitSymbol) {
            addElement(symbol, currentWord);
        } else {
            free(symbol);
            symbol = (char *)malloc(sizeof(char) * 1);
            *symbol = 0;
            addElement(symbol, currentWord);
            addElement(compileLine(currentWord), words);
            removeList(currentWord);
            currentWord = createList();
        }
        symbol = (char *)malloc(sizeof(char) * 1);
    }

    addElement(compileLine(currentWord), words);
    removeList(currentWord);
    int length = getListLength(words);

    char **temp = ltos(words);
    for (int i = 0; i < length; i++) {
        result[i] = temp[i];
    }

    return length;
}

int *readConfig(char *fileName) {
    FILE *configFile = fopen(fileName, "r");
    if (configFile == NULL) {
        fprintf(stderr, "Could not opasdfen config file\n");
        return NULL;
    }

    int height = -1, width = -1, x = -1, y = -1;

    struct list *lines = readLines(configFile);
    int length = getListLength(lines);
    char **strLines = ltos(lines);

    for (int i = 0; i < length; i++) {
        char **words = (char **)malloc(sizeof(char *) * length);
        int lineLength = split(strLines[i], ' ', words);

        if (lineLength < 3) {
            fprintf(stderr, "Not enough elements in a line\n");
            return NULL;
        }
        if (!strcmp(words[0], "height")) {
            height = parseInt(words[2]);
        } else if (!strcmp(words[0], "width")) {
            width = parseInt(words[2]);
        } else if (!strcmp(words[0], "x")) {
            x = parseInt(words[2]);
        } else if (!strcmp(words[0], "y")) {
            y = parseInt(words[2]);
        }
    }
    if (x < 1 || y < 1 || width < 1 || height < 1) {
        fprintf(stderr, "Not enough variables in a config file\n");
        return NULL;
    }
    int *result = (int *)malloc(sizeof(int) * 4);
    result[0] = height;
    result[1] = width;
    result[2] = x;
    result[3] = y;

    fclose(configFile);
    return result;
}

int main() {
    int *result = readConfig("/home/sandwitch/Documents/gameoflife/data/config.conf");
    printf("%d %d %d %d\n", result[0], result[1], result[2], result[3]);
    return 0;
}