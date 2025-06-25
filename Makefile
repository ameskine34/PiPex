NAME = pipex
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC =  function1.c function.c pipex.c

CC = cc
CFLAGS = -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(LIBFT):
	@cd libft && make

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o pipex

clean:
	rm -rf $(OBJ)
	@cd $(LIBFT_DIR) && make clean

fclean: clean
	rm -rf $(NAME)
	@cd $(LIBFT_DIR) && make fclean

re: fclean all

.phony: all clean fclean re
