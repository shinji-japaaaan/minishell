/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 20:18:22 by karai             #+#    #+#             */
/*   Updated: 2025/02/11 16:07:34 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_TokenType	get_token_type(char *str)
{
	if (ft_strcmp(str, "|") == 0)
		return (TYPE_PIPE);
	if (ft_strcmp(str, "<") == 0)
		return (TYPE_REDIRECT_IN);
	if (ft_strcmp(str, ">") == 0)
		return (TYPE_REDIRECT_OUT);
	if (ft_strcmp(str, "<<") == 0)
		return (TYPE_HEREDOC);
	if (ft_strcmp(str, ">>") == 0)
		return (TYPE_REDIRECT_APPEND);
	return (TYPE_COMMAND);
}

void	assign_token_types(t_linked_list *list_head)
{
	t_linked_list	*ptr_temp;

	ptr_temp = list_head->next;
	while (ptr_temp)
	{
		ptr_temp->token_type = get_token_type(ptr_temp->content);
		ptr_temp = ptr_temp->next;
	}
}

int	is_delimeter(char *str)
{
	if (str[0] == '\0')
		return (0);
	if (str[0] == '>' && str[1] == '>')
		return (2);
	if (str[0] == '<' && str[1] == '<')
		return (2);
	if (*str == '|' || *str == '<' || *str == '>')
		return (1);
	return (0);
}

size_t	get_token_length(char *input)
{
	bool	inside_single_quote;
	bool	inside_double_quote;
	size_t	len;

	inside_single_quote = false;
	inside_double_quote = false;
	len = 0;
	if (is_delimeter(input) != 0)
		return (is_delimeter(input));
	while (input[len])
	{
		if (input[len] == '\'')
			inside_single_quote = !inside_single_quote;
		if (input[len] == '\"')
			inside_double_quote = !inside_double_quote;
		if (inside_double_quote == false && inside_single_quote == false)
		{
			if (is_delimeter(&(input[len])) != 0)
				return (len);
			if (is_blank(input[len]))
				return (len);
		}
		len += 1;
	}
	return (len);
}

t_linked_list	*tokenize_input(t_linked_list *head, char *input)
{
	size_t	len;
	char	*str_temp;

	while (*input != '\0')
	{
		while (*input != '\0' && is_blank(*input))
			input += 1;
		if (*input == '\0')
			break ;
		len = get_token_length(input);
		str_temp = strdup_len(input, len);
		if (str_temp == NULL)
			return (free_linked_list_all(&head), NULL);
		if (linked_list_append(head, str_temp) == NULL)
			return (NULL);
		input += len;
	}
	return (head);
}
