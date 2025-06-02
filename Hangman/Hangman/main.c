// main - Created on Wed Apr  2 13:03:05 WAT 2025
#include "functions.h"

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
