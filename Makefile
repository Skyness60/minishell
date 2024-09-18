NAME = minishell
CC = cc -g3
CFLAGS = -Wall -Wextra -Werror
LINKLIBS = -lreadline -L./libft -lft
SRC = ./core/main.c ./init/init.c ./utils/free_fct.c ./utils/prompt.c ./utils/signals.c \
./parsing/parse_input.c ./utils/split_if_quotes.c ./exec/exec.c ./exec/exec_pipe.c \
./utils/garbage_utils.c ./exec/exec_utils.c ./exec/ft_execvp.c ./builtins/builtins.c \
./builtins/cd.c ./builtins/echo.c ./builtins/env.c ./builtins/export.c ./builtins/pwd.c \
./builtins/unset.c ./utils/get_paths.c ./builtins/history.c

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
