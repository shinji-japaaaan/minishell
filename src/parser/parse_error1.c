/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 13:05:40 by karai             #+#    #+#             */
/*   Updated: 2025/02/09 14:03:41 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	parse_error_quote(char *input)
{
	bool	inside_single_quote;
	bool	inside_double_quote;

	inside_single_quote = false;
	inside_double_quote = false;
	while (*input)
	{
		if (inside_double_quote && *input == '\"')
			inside_double_quote = false;
		else if (inside_single_quote && *input == '\'')
			inside_single_quote = false;
		else if (!inside_double_quote && !inside_single_quote)
		{
			if (*input == '\"')
				inside_double_quote = true;
			if (*input == '\'')
				inside_single_quote = true;
		}
		input += 1;
	}
	if (inside_double_quote || inside_single_quote)
		return (true);
	else
		return (false);
}

bool	parse_error_last_token(t_linked_list *head)
{
	t_linked_list	*temp_ptr;
	t_TokenType		token_type;

	temp_ptr = head->next;
	while (temp_ptr)
	{
		if (temp_ptr->next == NULL)
		{
			token_type = temp_ptr->token_type;
			if (token_type == TYPE_PIPE || token_type == TYPE_REDIRECT_IN
				|| token_type == TYPE_REDIRECT_OUT
				|| token_type == TYPE_REDIRECT_APPEND)
			{
				return (true);
			}
			else
			{
				return (false);
			}
		}
		temp_ptr = temp_ptr->next;
	}
	return (false);
}

bool	parse_error_consec_red(t_linked_list *head)
{
	t_linked_list	*temp_ptr;
	t_TokenType		token_type;
	int				state;

	temp_ptr = head->next;
	state = 0;
	while (temp_ptr)
	{
		token_type = temp_ptr->token_type;
		if (token_type == TYPE_REDIRECT_IN || token_type == TYPE_REDIRECT_OUT
			|| token_type == TYPE_REDIRECT_APPEND)
		{
			if (state == 1)
				return (true);
			else
				state = 1;
		}
		else
			state = 0;
		temp_ptr = temp_ptr->next;
	}
	return (false);
}

bool	parse_error_consecutive_pipe(t_linked_list *head)
{
	t_linked_list	*temp_ptr;
	t_TokenType		token_type;
	int				state;

	temp_ptr = head->next;
	state = 0;
	while (temp_ptr)
	{
		token_type = temp_ptr->token_type;
		if (token_type == TYPE_PIPE)
		{
			if (state == 1)
				return (true);
			else
				state = 1;
		}
		else
			state = 0;
		temp_ptr = temp_ptr->next;
	}
	return (false);
}

// int	main(void)
// {
// 	int				val;
// 	t_linked_list	*head;
// 	char			*str_temp;
// 	size_t			len;
// 	char			*input;

// 	input = "dafsijhio | | ss ";
// 	val = parse_error_quote(input);
// 	printf("quote %d\n", val);
// 	if (val)
// 		return (1);
// 	val = parse_error_unexpected_str(input);
// 	printf("unexpected str %d\n", val);
// 	if (val)
// 		return (1);
// 	head = linked_list_init(head);
// 	while (*input != '\0')
// 	{
// 		while (*input != '\0' && is_blank(*input))
// 			input += 1;
// 		if (*input == '\0')
// 			break ;
// 		len = split_len(input);
// 		str_temp = strdup_len(input, len);
// 		linked_list_append(head, str_temp);
// 		input += len;
// 	}
// 	linked_list_tokenize(head);
// 	val = parse_error_last_token(head);
// 	printf("last token %d\n", val);
// 	if (val)
// 		return (1);
// 	val = parse_error_consecutive_redirect(head);
// 	printf("redirect %d\n", val);
// 	if (val)
// 		return (1);
// 	val = parse_error_consecutive_pipe(head);
// 	printf("pipe %d\n", val);
// 	if (val)
// 		return (1);
// }
