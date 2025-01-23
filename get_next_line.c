/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfani <rfani@student.42firenze.it>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:22:12 by rfani             #+#    #+#             */
/*   Updated: 2025/01/23 13:40:58 by rfani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

char			*get_next_line(int fd);
static t_list	*fetch_stream(int fd);
static t_list	*increase_buffer(t_list *current_buffer, int *i);
static char		*gen_line(t_list *head_buffer);

char	*get_next_line(int fd)
{
	t_list			*buffer_list;
	char			*line;

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer_list = fetch_stream(fd);
	if (!buffer_list)
		return (NULL);
	line = gen_line(buffer_list);
	if (!line || !line[0])
		return (NULL);
	return (line);
}

static t_list	*fetch_stream(int fd)
{
	int		i;
	char	*buffer;
	t_list	*head_buffer;
	t_list	*current_buffer;

	i = 0;
	buffer = (char *)ft_calloc(BUFFER_SIZE, sizeof(char));
	head_buffer = ft_lstnew(buffer);
	current_buffer = head_buffer;
	while (read(fd, current_buffer->content + i * sizeof(char), 1) >= 0)
	{
		if (((char *)current_buffer->content)[i] == '\n' || \
			((char *)current_buffer->content)[i] == '\0')
			break ;
		else if (i == BUFFER_SIZE - 1)
			current_buffer = increase_buffer(current_buffer, &i);
		else
			i++;
	}
	return (head_buffer);
}

static t_list	*increase_buffer(t_list *current_buffer, int *i)
{
	t_list	*new_buffer_list;
	char	*new_buffer;

	new_buffer = (char *)ft_calloc(BUFFER_SIZE, sizeof(char));
	new_buffer_list = ft_lstnew(new_buffer);
	current_buffer->next = new_buffer_list;
	*i = 0;
	return (new_buffer_list);
}

static char	*gen_line(t_list *head_buffer)
{
	t_list	*temp;
	char	*line;
	int		buffer_list_size;
	int		j;

	buffer_list_size = ft_lstsize(head_buffer);
	line = (char *)ft_malloc(buffer_list_size * BUFFER_SIZE, sizeof(char));
	j = 0;
	while (j < buffer_list_size)
	{
		temp = head_buffer;
		ft_memcpy(&line[j * BUFFER_SIZE], temp->content, BUFFER_SIZE);
		head_buffer = temp->next;
		ft_lstdelone(temp, free);
		j++;
	}
	return (line);
}
