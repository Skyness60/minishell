NAME = minishell
CC = cc -g3
CFLAGS = -Wall -Wextra -Werror
LINKLIBS = -lreadline -L./libft -lft
SRC = ./core/main.c ./init/init.c ./utils/free_fct.c ./utils/prompt.c ./utils/signals.c ./utils/get_paths.c \
./parsing/parse_utils.c ./parsing/parse.c ./utils/split_if_quotes.c ./exec/exec.c ./exec/exec_pipe.c ./exec/parse_input.c \
/utils/garbage_utils.c

OBJECTS = $(SRC:.c=.o)
#################################################################################

RED = '\033[0;31m'
GREEN = '\033[0;32m'
YELLOW = '\033[0;33m'
BLUE = '\033[0;34m'
PURPLE = '\033[0;35m'
CYAN = '\033[0;36m'
MAGENTA = '\033[0;35m'
NC = '\033[0m'

#################################################################################


OBJ = $(SRC:.c=.o)

all : $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo $(GREEN)✅ $< compiled! $(NC)

$(NAME) : $(OBJ)
	@make -C ./libft --no-print-directory
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LINKLIBS)
	@echo $(BLUE)✅ $@ built! $(NC)

clean:
	@rm -f $(OBJECTS)
	@echo $(YELLOW)🗑️ $(OBJECTS) deleted! $(NC)

fclean:	clean
	@rm -rf $(NAME)
	@make fclean -C ./libft --no-print-directory
	@echo $(RED)🗑️ $(NAME) and $(BONUS) deleted! $(NC)

re: fclean all

.PHONY: re all clean fclean
