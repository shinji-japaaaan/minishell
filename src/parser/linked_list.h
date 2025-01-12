/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 09:21:34 by karai             #+#    #+#             */
/*   Updated: 2025/01/12 16:42:49 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKED_LIST_H
# define LINKED_LIST_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_linked_list
{
	char					*content; //moziretu
	int						type; // pipe or string or redirect or someting
	struct s_linked_list	*next; // next pointer
}							t_linked_list;

t_linked_list				*linked_list_init(t_linked_list *new_node);
void						linked_list_append(t_linked_list *list_head,
								char *str);
void						linked_list_print(t_linked_list *list_head);

#endif
