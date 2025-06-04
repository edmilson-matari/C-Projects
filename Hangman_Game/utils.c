#include "functions.h"

int rand_num(int interval) {
	srand(time(NULL));

	return (rand() % interval);
}

void load_words(Dictionary** words, char* file) {
	int words_num;
	int i;
	FILE* fp;
	char line[100];

	words_num = 0;
	i = 0;
	fp = fopen(file, "r");
	if (!fp) {
	printf("faile opening file\n");
		return ;
	}
	while (fgets(line, sizeof(line), fp) != NULL) {
		words_num++;
	}
	*words = (Dictionary*)malloc(sizeof(Dictionary) * words_num);
	if (!(*words)) {
		printf("Error allocating memory\n");
		return ;
	}
	rewind(fp);
	while (fgets(line, sizeof(line), fp) != NULL) {
		if (sscanf(line, "%d %[^,]s", &(*words)[i].num, (*words)[i].word) == 2) {
			i++;
		} else {
			printf("Skipping bad line format\n");
		}
	}
	fclose(fp);
}	

void display_word(char* hidden_word, char* given_word) {
	int size;
	
	size = strlen(given_word);
	printf("===============\n");
	printf("  Hangman Game\n");
	printf("===============\n\n  ");
	for (int i = 0; i < size; i++) {
		printf("%c ", hidden_word[i]);
	}
	printf("\n\n");
}

void fill_word(char* given_word, char* hidden_word) {
	int size;
	
	size = strlen(given_word);
	for (int i = 0; i < size; i++) {
		hidden_word[i] = '_';
	}
	hidden_word[size] = '\0';
}

void set_letter(int index, char* given_word, char* hidden_word) {
	hidden_word[index] = given_word[index];
	given_word[index] = ' ';
}

int find_letter(char* given_word, char given_letter) {
	int size;
	
	size = strlen(given_word);
	for (int i = 0; i < size; i++) {
		if (given_word[i] == given_letter) {
			return i;
		}
	}
	return -1;
}
