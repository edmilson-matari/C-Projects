NAME = Hangman_Game
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
OBJ = main.o utils.o

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(Obj)

clean:
	rm -f main.o utils.o

fclean: clean
	rm -f $(NAME)

re: fclean all
