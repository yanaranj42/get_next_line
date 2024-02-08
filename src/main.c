#include <stdio.h>
#include "get_next_line.h"
int main()
{
	int		fd;
	char	*line;

	fd = open("get_next_line.c", O_RDONLY | O_CREAT);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s",line);
		ft_free(&line, NULL);
	}
	close (fd);
	return (0);
}
