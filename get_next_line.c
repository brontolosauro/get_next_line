/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfani <rfani@student.42firenze.it>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:22:12 by rfani             #+#    #+#             */
/*   Updated: 2025/03/01 19:52:08 by rfani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

char	*get_next_line(int fd);
char	*gen_buff(int fd, ssize_t *buff_size);
char	*scan_buff(int fd, char **buffer, int *buff_index, ssize_t *buff_size);
int		store_item(t_list **line_lst, char buff_item);
char	*lst_to_str(t_list **line_lst, char *buffer, ssize_t buff_size);

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("./test.txt", O_RDONLY);
	printf("fd: %d\n", fd);

	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	close(fd);
	return (0);
}

char	*get_next_line(int fd)
{
	static char		*buffer;
	static ssize_t	buff_size;
	static int		buff_index;
	char			*line_str;

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	line_str = NULL;
	if (buff_size == 0)
		buffer = gen_buff(fd, &buff_size);
	if (!buffer)
		return (NULL);
	if (buff_size > 0)
		line_str = scan_buff(fd, &buffer, &buff_index, &buff_size);
	else
		free(buffer);
	return (line_str);
}

char	*gen_buff(int fd, ssize_t *buff_size)
{
	char		*buffer;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE));
	*buff_size = read(fd, buffer, BUFFER_SIZE);
	if (*buff_size == -1)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

char	*scan_buff(int fd, char **buffer, int *buff_index, ssize_t *buff_size)
{
	t_list	*line_lst;
	int		storage_error;

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
		{
			return (NULL);
			free(*buffer);
		}
		(*buff_index)++;
	}
	return (lst_to_str(&line_lst, *buffer, *buff_size));
}

int	store_item(t_list **line_lst, char buff_item)
{
	char	*item;
	t_list	*tail;
	int		err_code;

	item = (char *)malloc(sizeof(char));
	if (!item)
		return (1);
	*item = buff_item;
	tail = ft_lstnew(item);
	ft_lstadd_back(line_lst, tail);
	if (!tail)
		err_code = 1;
	else
		err_code = 0;
	return (err_code);
}

char	*lst_to_str(t_list **line_lst, char *buffer, ssize_t buff_size)
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
	if (buff_size == 0)
		free(buffer);
	return (line_str);
}
