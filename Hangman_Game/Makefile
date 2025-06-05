NAME = Hangman_Game
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
OBJ = main.o utils.o

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
