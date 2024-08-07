#include <unistd.h>
#include <stdio.h>

int	main()
{
	int	fd = 1;

	printf("path : %s\nn terminal : %d\n", ttyname(fd), ttyslot());
}
