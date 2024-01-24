NAME= pipex
CC= cc
CFLAGS= -Wall -Wextra -Werror

SRC_BONUS = main_bonus.c functions_utils1_bonus.c functions_utils2_bonus.c ft_split_bonus.c \
	get_next_line_bonus.c gnl_utils_bonus.c ft_herdoc_bonus.c \
    
OBJ = $(SRC_BONUS:.c=.o)	

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(SRC_BONUS) -o $(NAME)
	
%.o: %.c pipex.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) 
 
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all 