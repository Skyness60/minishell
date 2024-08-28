#include <stdio.h>

int main(int argc, char **argv, char **env)
{
	int i;

	i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
}
