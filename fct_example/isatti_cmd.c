#include <unistd.h>
#include <stdio.h>

int	main()
{
	int	fd = 0;
	if (isatty(fd))
		printf("Le file est lie au terminal.\n");
	else
		printf("Le file n'est pas lie au terminal.\n");
	return (0);
}
