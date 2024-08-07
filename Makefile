NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
LINKLIBS = -lreadline
SRC = ./core/main.c ./init/init.c ./utils/free_fct.c ./signals.c
OBJ = $(SRC=.c:.o)

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) $(LINKLIBS) -c -o $@ $<

$(NAME) : $(OBJ)
	make -C ./libft
	cp -r ./libft/libft.a .
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf *.o
	rm -rf ./utils/*.o
	rm -rf ./init/*.o
	rm -rf ./signals/.o
	make clean -C ./libft

fclean:	clean
	rm -rf $(NAME)
	rm -rf libft.a
	make fclean -C ./libft

re: fclean all

.PHONY: re all clean fclean
