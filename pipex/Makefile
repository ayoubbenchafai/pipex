NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = mandatory/main.c mandatory/ft_split.c mandatory/gnl_utils.c mandatory/functions_utils1.c \
	mandatory/functions_utils2.c

SRC_BONUS = bonus/main_bonus.c bonus/functions_utils1_bonus.c bonus/functions_utils2_bonus.c \
	bonus/ft_split_bonus.c bonus/get_next_line_bonus.c \
	bonus/gnl_utils_bonus.c bonus/ft_herdoc_bonus.c

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

bonus: $(OBJ_BONUS)
	$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(NAME)

mandatory/%.o: mandatory/%.c pipex.h
	$(CC) $(CFLAGS) -c $< -o $@

bonus/%.o: bonus/%.c pipex_bonus.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all