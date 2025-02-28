/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfani <rfani@student.42firenze.it>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:22:12 by rfani             #+#    #+#             */
/*   Updated: 2025/02/28 12:08:11y rfani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

char	*get_next_line(int fd);
char	*gen_buff(int fd, int *buff_size);
char	*scan_buff(int fd, char **buffer, int *buff_index, int *buff_size);

char	*get_next_line(int fd)
{
	static char	*buffer;
	static int	buff_size;
	static int	buff_index;
	char		*line_str;

	if (buff_size <= 0 || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	line_str = NULL;
	if (buff_size == 0)
		buffer = gen_buff(fd, &buff_size);
	if (!buffer)
		return (NULL);
	if (buff_size > 0)
		line_str = scan_buff(fd, &buffer, &buff_index, &buff_size);
	return (line_str);
}

char	*gen_buff(int fd, int *buff_size)
{
	char	*buffer;
	int		read_size;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE));
	*buff_size = read(fd, buffer, buff_size);
	if (*buff_size == -1)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

char	*scan_buff(int fd, char **buffer, int *buff_index, int *buff_size)
{
	t_list	*line_lst;

	while (*buffer[*buff_index] != '\n' && *buff_index < *buff_size)
	{
		store_element(&line_lst, *buffer[*buff_index]);
		if (*buff_index == *buff_size - 1)
		{
			*buff_size = read(fd, *buffer, BUFFER_SIZE);
			*buff_index = 0;
		}
		if (*buff_size == 0)
			break ;
		if (*buff_size == -1)
			return (NULL);
		(*buff_index)++;
	}
}
