// main - Created on Wed Apr  2 13:03:05 WAT 2025
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

typedef struct {
	int num;
	char word[50];
} Dictionary;

int rand_num(int interval) {
	srand(time(NULL));

	return (rand() % interval);
}

void load_words(Dictionary** words, char* file) {
	int words_num = 0;
	int i = 0;
	FILE* fp = fopen(file, "r");
	if (!fp) {
	printf("faile opening file\n");
		return;
	}

	char line[100];
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
			printf("Skipping bad line\n");
		}
	}
	fclose(fp);
}	


void display_word(char* hidden_word, char* given_word) {
	printf("===============\n");
	printf("  Hangman Game\n");
	printf("===============\n\n  ");
	for (int i = 0; i < strlen(given_word); i++) {
		printf("%c ", hidden_word[i]);
	}
	printf("\n\n");
}

void fill_word(char* given_word, char* hidden_word) {
	for (int i = 0; i < strlen(given_word); i++) {
		hidden_word[i] = '_';
	}
	hidden_word[strlen(given_word)] = '\0';
}

void set_letter(int index, char* given_word, char* hidden_word) {
	hidden_word[index] = given_word[index];
	given_word[index] = ' ';
}

int find_letter(char* given_word, char given_letter) {
	for (int i = 0; i < strlen(given_word); i++) {
		if (given_word[i] == given_letter) {
			return i;
		}
	}
	return -1;
}

int game_state(char* hidden_word) {
	for (int i = 0; i < strlen(hidden_word); i++) {
		if (hidden_word[i] == '_') {
			return 1;
		}
	}
	return 0;
}

int isvalid(char c) {
	if (c >= '1' && c <= '9') {
		return 1;
	}
	return 0;
}

int main(void) {
	//code here
	char word_copy[50];
	int index;
	int life = 6;
	char letter;
	char file[50] = "words.txt";
	Dictionary* dictionary;
	load_words(&dictionary, file);
	char word[50] = "";
	printf("%s\n", dictionary[rand_num(4)].word);
	strcpy(word, dictionary[rand_num(4)].word);
	fill_word(word, word_copy);
	while (1) {
		display_word(word_copy, word);
		printf("Insert your guess letter: ");
		scanf(" %c", &letter);
		while (isvalid(letter)) {
				printf("Insert a valid guess: ");
				scanf(" %c", &letter);
		}
		index = find_letter(word, toupper(letter));
		if (index >= 0) {
			set_letter(index, word, word_copy);
		} else {
			life--;
			printf("\nWrong Answer\nYou have %d lifes left\n", life);
		}
		if (life == 0) {
			printf("Game Over");
			break ;
		}
		if (!game_state(word_copy)) {
			display_word(word_copy, word);
			printf("Game Won\n");			
			break ;
		}
	}
	free(dictionary);
	return 0;
}
