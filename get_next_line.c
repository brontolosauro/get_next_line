/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfani <rfani@student.42firenze.it>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:22:12 by rfani             #+#    #+#             */
/*   Updated: 2025/01/20 00:48:06 by rfani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif

char		*get_next_line(int fd);
static char	*gen_line(t_list *head_buffer_list, void *current_buffer, int i);
static void	clean_buffer(void *current_buffer, int i);
static void	increase_buffer(t_list *current_buffer_list, int *i);

char	*get_next_line(int fd)
{
	int	i;
	t_list			*head_buffer_list;
	t_list			*current_buffer_list;
	char			*line;
	char			*buffer;

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	i = 0;
	buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));
	head_buffer_list = ft_lstnew(buffer);
	current_buffer_list = head_buffer_list;
	line = NULL;
	while (read(fd, current_buffer_list->content + i * sizeof(char), 1) > 0)
	{
		if (((char *)current_buffer_list->content)[i] == '\n' || \
			((char *)current_buffer_list->content)[i] == '\0')
		{
			line = gen_line(head_buffer_list, current_buffer_list->content, i);
			break;
		}
		if (i == BUFFER_SIZE - 1)
			increase_buffer(current_buffer_list, &i);
		else
			i++;
	}
	return (line);
}

static char	*gen_line(t_list *head_buffer_list, void *current_buffer, int i)
{
	t_list	*temp;
	char	*line;
	int		buffer_list_size;
	int		j;

	buffer_list_size = ft_lstsize(head_buffer_list);
	clean_buffer(current_buffer, i);
	line = (char *)malloc((buffer_list_size * BUFFER_SIZE) * sizeof(char));
	j = 0;
	while (j < buffer_list_size)
	{
		temp = head_buffer_list;
		ft_memcpy(&line[j * BUFFER_SIZE], temp->content, BUFFER_SIZE);
		head_buffer_list = temp->next;
		ft_lstdelone(temp, free);
		j++;
	}
	return (line);
}

static void	clean_buffer(void *current_buffer, int i)
{
	while (i < BUFFER_SIZE)
	{
		((char *)current_buffer)[i] = '\0';
		i++;
	}
}

static void	increase_buffer(t_list *current_buffer_list, int *i)
{
	t_list	*new_buffer_list;
	char	*new_buffer;

	new_buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));
	new_buffer_list = ft_lstnew(new_buffer);
	current_buffer_list->next = new_buffer_list;
	current_buffer_list = new_buffer_list;
	*i = 0;
}
