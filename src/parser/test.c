/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 12:35:19 by karai             #+#    #+#             */
/*   Updated: 2025/01/13 10:59:32 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"
#include "parser.h"

int	main(void)
{
	t_linked_list	*head;
	int idx;

	idx = 1;
	//test 1
	char *str1 = "  		adj dasfj adk | dasj jdasg|dasf   	 	 	";
	printf("test%d: %s\n", idx++, str1);
	head = parser(str1);
	linked_list_print(head);

	//test 2
	char *str2 = "\"dsfljfd | dfa\"";
	printf("test%d: %s\n", idx++, str2);
	head = parser(str2);
	linked_list_print(head);

	char *str3 = "dsf \"abcd|\"adfadsf   ";
	printf("test%d: %s\n", idx++, str3);
	head = parser(str3);
	linked_list_print(head);

	char *str4 = "cat input.txt>output.txt";
	printf("test%d: %s\n", idx++, str4);
	head = parser(str4);
	linked_list_print(head);

	char *str5 = "cat input.txt>>output.txt";
	printf("test%d: %s\n", idx++, str5);
	head = parser(str5);
	linked_list_print(head);

	char *str6 = "input.txt < cat";
	printf("test%d: %s\n", idx++, str6);
	head = parser(str6);
	linked_list_print(head);

	char *str7 = "echo 'input.txt < cat   '   ";
	printf("test%d: %s\n", idx++, str7);
	head = parser(str7);
	linked_list_print(head);

	printf("\ntest for expansion\n");
	printf("===================================\n");

	char *str8 = "echo $USER \"$USER\" '$USER'";
	printf("test%d: %s\n", idx++, str8);
	head = parser(str8);
	linked_list_print(head);
	// head = linked_list_init(head);
	// linked_list_append(head, "aaaa");
	// linked_list_append(head, "bbbb");
	// linked_list_append(head, "cccc");
	// linked_list_print(head);
}
