#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int splitInput(char *input, char **command) {
	char word[29];
	int symbolCount = 0, wordCount = 0;
	for (int i = 0; i < 29; i++) {
		if (input[i] != ' ' && input[i] != '\n' && input[i] != 0)
			word[symbolCount++] = input[i];
		else {
			word[symbolCount++] = 0;
			command[wordCount] = (char *)malloc(sizeof(char) * symbolCount);
			strcat(command[wordCount++], word);
			symbolCount = 0;
			
			if (input[i] == '\n') break;
		}
	}
	return wordCount;
}

int executeCommand(char *input, char **command) {
	int result;
	if ((result = splitInput(input, command)) < 0) {
		return result;
	}
	printf("%s %s\n", command[0], command[1]);
	return 0;
}

int main() {
	int x, y, result;

	// Mamy dwa obszary w pamięci.
	char *input = (char *)malloc(sizeof(char) * 29);
	char **command = malloc(sizeof(char *) * 14);
	input[29] = 0;

	// Myślę, że nie masz pytań.
	printf("Halo! Witamy w grze \"Życie\"!\n\nNajpierw, napisz liczbę kratków dla x i y (że są ograniczone typem int):\n\n> ");
	scanf("%d%d", &x, &y);
	
	// Blok generowania pola.
	int board[y][x]; // Dla rządów mamy y, dla kolumn -- x.

	printf("Następne, napisz numer kratki, w której chcesz utworzyć życie! Albo możesz popatrzeć na wszystkie komandy.\n\n");
	while (1) {
		printf("> ");
		scanf(" "); // fgets czyta pierwszy znak jako "\n" i powtarza ">"
		fgets(input, 28, stdin);
		result = executeCommand(input, command);
	}
	return 0;
}
