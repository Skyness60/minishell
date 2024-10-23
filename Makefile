NAME = minishell
CC = cc -g3
CFLAGS = -Wall -Wextra -Werror
LINKLIBS = -lreadline -L./libft -lft
SRC = ./core/main.c ./init/init.c ./utils/free_fct.c ./utils/prompt.c ./utils/signals.c \
./parsing/parse_input.c ./exec/exec.c \
./utils/garbage_utils.c ./exec/exec_utils.c ./exec/ft_execvp.c ./builtins/builtins.c \
./builtins/cd.c ./builtins/echo.c ./builtins/env.c ./builtins/export.c ./builtins/pwd.c \
./builtins/unset.c ./utils/get_paths.c ./builtins/history.c ./split_if_quote/split_with_quote.c \
./split_if_quote/split_with_quote2.c ./split_if_quote/split_with_quote3.c ./parsing/syntax_errors.c \
./parsing/heredoc.c ./split_if_quote/split_with_quote4.c ./parsing/redirections.c \
./utils/struct_op.c ./utils/heredoc_utils.c ./parsing/get_cmd.c ./utils/check_infiles.c \
./parsing/get_args.c ./split_if_quote/split_pipe.c ./utils/redirect_utils.c ./builtins/export_utils.c \
./exec/waitfunction.c ./parsing/get_var.c ./parsing/get_var_utils.c ./builtins/export_utils2.c  \
./builtins/exit.c ./parsing/get_var_utils2.c 

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
