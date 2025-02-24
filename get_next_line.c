/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfani <rfani@student.42firenze.it>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:22:12 by rfani             #+#    #+#             */
/*   Updated: 2025/02/17 20:00:17 by rfani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

char		*get_next_line(int fd);
static int	check_buffer(char *buffer, int *buffer_index, ssize_t buffer_len);

char	*get_next_line(int fd)
{
	static char			*buffer;
	static int			buffer_index;
	static ssize_t		buffer_len;
	int					new_line_index;
	char				*line;

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (!buffer)
	{
		buffer = (char *)malloc(BUFFER_SIZE);
		if (!buffer)
			return (NULL);
		buffer_len = read(fd, buffer, BUFFER_SIZE);
	}
	if (buffer_len <= 0)
		return (NULL);
	new_line_index = check_buffer(buffer, buffer_index, buffer_len);
	if (new_line_index == -1)
		increase_buffer(buffer, buffer_index, buffer_len);
	return (line);
}

static int check_buffer(char *buffer, int *buffer_index, ssize_t buffer_len)
{
	int		i;

	i = 0;
	while (*buffer_index < buffer_len || buffer[*buffer_index] != '\n')
	{
		(*buffer_index)++;
		i++;
	}
	if (buffer[*buffer_index] == '\n')
	{
		(*buffer_index)++;
		return (i);
	}
	else if (buffer_len < BUFFER_SIZE)
	{
		buffer[*buffer_index] = '\n';
		(*buffer_index)++;
		return (i);
	}
	else
	{
		add_to_line(line, temp, i);
		buffer_len = read(fd, buffer, BUFFER_SIZE);
		*buffer_index = 0;
		check_buffer(buffer, buffer_index, buffer_len);
	
	else
	{
		add_to_line(line, temp, i);
		buffer_len = read(fd, buffer, BUFFER_SIZE);
		*buffer_index = 0;
		check_buffer(buffer, buffer_index, buffer_len);
	}
	{
		add_to_line(line, temp, i);
		buffer_len = read(fd, buffer, BUFFER_SIZE);
		*buffer_index = 0;
		check_buffer(buffer, buffer_index, buffer_len);
	}
}
{
	int		i;

	i = 0;
	while (*buffer_index < *read_ret || (*buffer)[*buffer_index] != '\n')
	{
		(*buffer_index)++;
		i++;
	}
	if ((*buffer)[*buffer_index] == '\n')
	{
		(*buffer_index)++;
		return (i);
	}
	else
	{
		add_to_line(line, temp, i);
		*read_ret = read(fd, *buffer, BUFFER_SIZE);
		*buffer_index = 0;
		check_buffer(buffer, buffer_index, line, read_ret);
	}
}
