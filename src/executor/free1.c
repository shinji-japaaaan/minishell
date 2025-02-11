/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 21:22:29 by karai             #+#    #+#             */
/*   Updated: 2025/02/11 09:14:09 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free1dim(char **str)
{
	if (*str == NULL)
		return ;
	free(*str);
	*str = NULL;
}

void	free2dim(char ***str_array)
{
	size_t	i;

	if (*str_array == NULL)
		return ;
	i = 0;
	while ((*str_array)[i])
	{
		free((*str_array)[i]);
		i += 1;
	}
	free(*str_array);
	*str_array = NULL;
}

void	free_linked_list_only_node(t_linked_list **head_list)
{
	t_linked_list	*nxt_ptr;
	t_linked_list	*now_ptr;

	now_ptr = *head_list;
	while (now_ptr)
	{
		nxt_ptr = now_ptr->next;
		free(now_ptr);
		now_ptr = nxt_ptr;
	}
	*head_list = NULL;
}

void	free_linked_list_all(t_linked_list **head_list)
{
	t_linked_list	*nxt_ptr;
	t_linked_list	*now_ptr;

	now_ptr = *head_list;
	while (now_ptr)
	{
		nxt_ptr = now_ptr->next;
		free(now_ptr->content);
		free(now_ptr);
		now_ptr = nxt_ptr;
	}
	*head_list = NULL;
}
