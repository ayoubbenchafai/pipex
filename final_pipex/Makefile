NAME= pipex
CC= cc
CFLAGS= -Wall -Wextra -Werror


SRC = functions_utils.c final.c
	
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	
%.o: %.c pipex.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) 
 
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all 