NAME= pipex
CC= cc
CFLAGS= -Wall -Wextra -Werror

SRC = main.c ft_split.c gnl_utils.c functions_utils1.c functions_utils2.c 
OBJ = $(SRC:.c=.o)	

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	
%.o: %.c pipex.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) 
 
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all 