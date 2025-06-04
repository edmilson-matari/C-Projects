#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

typedef struct {
	int num;
	char word[50];
} Dictionary;

int rand_num(int);

void load_words(Dictionary**, char*);

void display_word(char*, char*);

void fill_word(char*, char*);

void set_letter(int, char*, char*);

int find_letter(char*, char);

int game_state(char*);

int isvalid(char c);

#endif
