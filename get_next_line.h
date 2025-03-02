/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfani <rfani@student.42firenze.it>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 10:55:14 by rfani             #+#    #+#             */
/*   Updated: 2025/03/02 21:58:16 by rfani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;
char	*get_next_line(int fd);
int		ft_lstsize(t_list *lst);
void	*ft_calloc(size_t nmemb, size_t size);
t_list	*ft_lstnew(void *content);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstadd_back(t_list **lst, t_list *new);

#endif