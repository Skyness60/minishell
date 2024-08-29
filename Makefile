NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
LINKLIBS = -lreadline -L./libft -lft
SRC = ./core/main.c ./init/init.c ./utils/free_fct.c ./utils/prompt.c ./utils/signals.c
OBJ = $(SRC:.c=.o)

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME) : $(OBJ)
	make -C ./libft
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LINKLIBS)

clean:
	rm -rf *.o
	rm -rf ./utils/*.o
	rm -rf ./init/*.o
	rm -rf ./core/*.o
	make clean -C ./libft

fclean:	clean
	rm -rf $(NAME)
	make fclean -C ./libft

re: fclean all

.PHONY: re all clean fclean
