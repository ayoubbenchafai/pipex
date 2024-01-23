NAME= pipex
CC= cc
CFLAGS= -Wall -Wextra -Werror

SRC = final_herdoc.c functions_utils2.c functions_utils3.c ft_split.c \
		get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
    
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