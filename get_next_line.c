/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfani <rfani@student.42firenze.it>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:22:12 by rfani             #+#    #+#             */
/*   Updated: 2025/02/28 19:10:16 by rfani            ###   ########.fr       */
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
int		store_item(t_list **line_lst, char buff_item);
char	*lst_to_str(t_list **line_lst);

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
	int		storage_error;
	char	*line_str;

	line_lst = NULL;
	while (*buffer[*buff_index] != '\n')
	{
		storage_error = store_item(&line_lst, *buffer[*buff_index]);
		if (storage_error)
			return (NULL);
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
	line_str = lst_to_str(&line_lst);
	return (line_str);
}

int	store_item(t_list **line_lst, char buff_item)
{
	char	*item;
	t_list	*tail;

	item = (char *)malloc(sizeof(char));
	if (!item)
		return (1);
	if (!*line_lst)
	{
		*line_lst = ft_lstnew(item);
		if (!*line_lst)
			return (1);
	}
	else
	{
		tail = ft_lstnew(item);
		if (!tail)
			return (1);
		ft_lstadd_back(line_lst, tail);
		return (0);
	}
}

char	*lst_to_str(t_list **line_lst)
{
	char	*line_str;
	t_list	*temp;
	int		i;

	line_str = (char *)malloc(sizeof(char) * ft_lstsize(*line_lst));
	if (!line_str)
		return (NULL);
	i = 0;
	temp = *line_lst;
	while (temp)
	{
		line_str[i] = *((char *)temp->content);
		temp = temp->next;
		i++;
	}
	ft_lstclear(line_lst, free);
	return (line_str);
}
