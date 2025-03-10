/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfani <rfani@student.42firenze.it>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:22:12 by rfani             #+#    #+#             */
/*   Updated: 2025/03/10 15:20:14 by rfani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 32
#endif
// needed for main()
// #include <stdio.h>
// #include <stdlib.h>
// #include <fcntl.h>

char	*get_next_line(int fd);
int		scan_buff(t_list **line_lst, char *buffer, int *buff_index,
			ssize_t buff_size);
void	store_item(t_list **line_lst, char buff_item);
char	*lst_to_str(t_list **line_lst, char *buffer);

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("./test.txt", O_RDONLY);
// 	printf("fd: %d\n", fd);
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		printf("%s", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	free(line);
// 	close(fd);
// 	return (0);
// }

char	*get_next_line(int fd)
{
	static char		*buffer;
	static ssize_t	buff_size;
	static int		buff_index;
	t_list			*line_lst;

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (!buffer)
	{
		buffer = (char *)ft_calloc(BUFFER_SIZE, sizeof(char));
		if (!buffer)
			return (NULL);
		buff_size = read(fd, buffer, BUFFER_SIZE);
	}
	line_lst = NULL;
	while (scan_buff(&line_lst, buffer, &buff_index, buff_size))
	{
		buff_size = read(fd, buffer, BUFFER_SIZE);
		if (BUFFER_SIZE == 1 && buff_size == 0)
			break ;
	}
	return (lst_to_str(&line_lst, buffer));
}

int	scan_buff(
	t_list **line_lst, char *buffer, int *buff_index, ssize_t buff_size)
{
	if (buff_size == 0)
		return (0);
	if (buff_size < 0)
		return (ft_lstclear(line_lst, free), 0);
	while (*buff_index < buff_size)
	{
		store_item(line_lst, buffer[*buff_index]);
		if (buffer[*buff_index] == '\n')
		{
			(*buff_index)++;
			return (0);
		}
		(*buff_index)++;
	}
	if (buff_size - BUFFER_SIZE == 0)
	{
		*buff_index = 0;
		return (1);
	}
	return (0);
}

void	store_item(t_list **line_lst, char buff_item)
{
	char	*item;
	t_list	*tail;

	item = (char *)ft_calloc(1 + 1, sizeof(char));
	*item = buff_item;
	tail = ft_lstnew(item);
	ft_lstadd_back(line_lst, tail);
}

char	*lst_to_str(t_list **line_lst, char *buffer)
{
	char	*line_str;
	t_list	*temp;
	int		i;
	int		lst_size;

	if (!*line_lst)
		return (free(buffer), NULL);
	lst_size = ft_lstsize(*line_lst);
	line_str = (char *)ft_calloc((ssize_t)lst_size + 1, sizeof(char));
	if (!line_str)
		return (free(buffer), NULL);
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
