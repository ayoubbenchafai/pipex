NAME_M = pipex
NAME_B = pipex_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = mandatory/pipex.c mandatory/ft_split.c mandatory/gnl_utils.c mandatory/functions_utils1.c \
	mandatory/functions_utils2.c

SRC_BONUS = bonus/pipex_bonus.c bonus/functions_utils1_bonus.c bonus/functions_utils2_bonus.c \
	bonus/ft_split_bonus.c bonus/get_next_line_bonus.c \
	bonus/gnl_utils_bonus.c bonus/ft_herdoc_bonus.c

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

all: $(NAME_M)

$(NAME_M): $(OBJ) mandatory/pipex.h
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME_M)

bonus: $(OBJ_BONUS) bonus/pipex_bonus.h
	$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(NAME_B)

clean:
	rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	rm -f $(NAME_M) $(NAME_B)

re: fclean all

.PHONY: clean fclean re all