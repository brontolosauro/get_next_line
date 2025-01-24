/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfani <rfani@student.42firenze.it>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:46:22 by rfani             #+#    #+#             */
/*   Updated: 2025/01/24 14:08:19 by rfani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;
//	size_t	dummy;
//	char	buff[1];

	fd = open("./test.txt", O_RDONLY);
	// dummy = read(fd, buff, 1);
	// printf("read() = %lu;\n", dummy);
	// printf("fd = %d;\n", fd);
	// printf("EOF int = %d;\n", (int)buff[0]);
	// printf("EOF str = %s;\n", buff);
	// if (EOF == buff[0])
	// 	printf("fine del file raggiunta\n");
	// if (!buff[0])
	// 	printf("stringa vuota\n");

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
