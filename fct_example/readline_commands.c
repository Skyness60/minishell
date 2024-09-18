#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>

#define HISTORY_FILE ".my_history"

int main()
{
	char *prompt;

	read_history(HISTORY_FILE);
	
	while (1)
	{
		prompt = readline("Entrez du texte :");
		if (strcmp(prompt, "exit") == 0)
		{
			free(prompt);
			break ;
		}
		add_history(prompt);
		if (strcmp(prompt, "clear") == 0)
			rl_clear_history();
		else if (strcmp(prompt, "newline"))
			rl_on_new_line();
		else if (strncmp(prompt, "replace", 8))
		{
			rl_replace_line(prompt + 8, 0);
			rl_redisplay();
		}
		else
			printf("Commande rentree : %s\n", prompt);
		free(prompt);
	}
	write_history(HISTORY_FILE);
}
