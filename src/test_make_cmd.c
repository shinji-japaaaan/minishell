/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_make_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 22:47:27 by karai             #+#    #+#             */
/*   Updated: 2025/01/18 09:07:22 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/linked_list.h"
#include "../../include/parser.h"

void	print_redirect(t_redirect *head)
{
	t_redirect	*ptr_temp;

	ptr_temp = head->next;
	while (ptr_temp)
	{
		printf("%s\n", ptr_temp->filename);
		ptr_temp = ptr_temp->next;
	}
}

void	print_cmd(t_cmd_invoke *head)
{
	t_cmd_invoke	*ptr_temp;
	size_t			i;

	i = 0;
	ptr_temp = head->next;
	while (ptr_temp)
	{
		i = 0;
		printf("cmd\n");
		while (ptr_temp->cmd_list[i])
		{
			printf("%s\n", ptr_temp->cmd_list[i]);
			i += 1;
		}
		printf("redirect_in\n");
		print_redirect(ptr_temp->redirect_in_head);
		printf("redirect_out\n");
		print_redirect(ptr_temp->redirect_out_head);
		// printf("%p\n", ptr_temp);
		ptr_temp = ptr_temp->next;
	}
}

int	main(void)
{
	t_cmd_invoke	*head;
	int				idx;

	idx = 1;
	//test 1
	char *str1 = "  		adj dasfj adk | dasj jdasg|dasf   	 	 	";
	printf("test%d: %s\n", idx++, str1);
	head = parser(str1);
	print_cmd(head);

	//test 2
	char *str2 = "\"dsfljfd | dfa\"";
	printf("test%d: %s\n", idx++, str2);
	head = parser(str2);
	print_cmd(head);

	char *str3 = "dsf \"abcd|\"adfadsf   ";
	printf("test%d: %s\n", idx++, str3);
	head = parser(str3);
	print_cmd(head);

	char *str4 = "cat input.txt>output.txt";
	printf("test%d: %s\n", idx++, str4);
	head = parser(str4);
	print_cmd(head);

	char *str5 = "cat input.txt>>output.txt";
	printf("test%d: %s\n", idx++, str5);
	head = parser(str5);
	print_cmd(head);

	char *str6 = "input.txt < cat";
	printf("test%d: %s\n", idx++, str6);
	head = parser(str6);
	print_cmd(head);

	char *str7 = "echo 'input.txt < cat   '   ";
	printf("test%d: %s\n", idx++, str7);
	head = parser(str7);
	print_cmd(head);

	printf("\ntest for expansion\n");
	printf("===================================\n");

	char *str8 = "echo $USER \"$USER\" '$USER'";
	printf("test%d: %s\n", idx++, str8);
	head = parser(str8);
	print_cmd(head);

	char *str9 = "cat -e | < in1 <in2 >>out1 cat <in3 -e >out2 >out3";
	printf("test%d: %s\n", idx++, str9);
	head = parser(str9);
	print_cmd(head);
}
