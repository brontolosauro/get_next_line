/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfani <rfani@student.42firenze.it>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:22:12 by rfani             #+#    #+#             */
/*   Updated: 2025/03/03 03:58:09 by rfani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif
// needed for main()
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

char	*get_next_line(int fd);
int		scan_buff(
			t_list **line_lst,
			char *buffer, int *buff_index, ssize_t buff_size);
void	store_item(t_list **line_lst, char buff_item);
char	*lst_to_str(t_list **line_lst, char *buffer, ssize_t buff_size);

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("./test.txt", O_RDONLY);
	printf("fd: %d\n", fd);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (0);
}

char	*get_next_line(int fd)
{
	static char		*buffer;
	static ssize_t	buff_size;
	static int		buff_index;
	t_list			*line_lst;
	int				eof;

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	line_lst = NULL;
	eof = 0;
	if (buff_size == 0)
	{
		buffer = calloc(BUFFER_SIZE, sizeof(char));
		buff_size = read(fd, buffer, BUFFER_SIZE);
	}
	while (scan_buff(&line_lst, buffer, &buff_index, buff_size) && !eof)
	{
		buff_size = read(fd, buffer, BUFFER_SIZE);
		buff_index = 0;
		if (buff_size < BUFFER_SIZE)
			eof = 1;
	}
	return (lst_to_str(&line_lst, buffer, buff_size));
}

int	scan_buff(
	t_list **line_lst, char *buffer, int *buff_index, ssize_t buff_size)
{
	while (*buff_index < buff_size)
	{
		store_item(line_lst, buffer[*buff_index]);
		if (buffer[*buff_index] == '\n')
		{
			if (*buff_index == buff_size - 1)
				return (0);
			(*buff_index)++;
			return (0);
		}
		(*buff_index)++;
	}
	if ((buff_size < BUFFER_SIZE) && buff_index == buff_size - 1)
		continue_scan = 0;
	else
		continue_scan = 1;
	return (1);
}

void	store_item(t_list **line_lst, char buff_item)
{
	char	*item;
	t_list	*tail;

	item = (char *)calloc(1, sizeof(char));
	*item = buff_item;
	tail = ft_lstnew(item);
	ft_lstadd_back(line_lst, tail);
}

char	*lst_to_str(t_list **line_lst, char *buffer, ssize_t buff_size)
{
	char	*line_str;
	t_list	*temp;
	int		i;
	int		lst_size;

	lst_size = ft_lstsize(*line_lst);
	line_str = (char *)calloc((ssize_t)lst_size, sizeof(char));
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
	if (buff_size <= 0)
		free(buffer);
	return (line_str);
}
