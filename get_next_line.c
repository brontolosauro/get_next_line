/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfani <rfani@student.42firenze.it>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:22:12 by rfani             #+#    #+#             */
/*   Updated: 2025/02/24 18:01:49 by rfani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

char	*get_next_line(int fd);

char	*get_next_line(int fd)
{
	static char	*buffer;
	static int	buffer_size;
	static int	buffer_index;
	t_list		*line_list;

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	line_list = NULL;
	if (buffer_size == 0)
		buffer = gen_buffer(fd, &buffer_size);
	if (!buffer)
		return (NULL);
	while (buffer_size > 0)
	{
		while (buffer_index < buffer_size && buffer[buffer_index] != '\n')
			buffer_index++;
		if (buffer[buffer_index] == '\n')
		{
			store_buffer(&line_list, buffer, &buffer_index, &buffer_size);
			break ;
		}
		store_buffer(&line_list, buffer, &buffer_index, &buffer_size);
	}
	return (list_to_str(&line_list));
}
