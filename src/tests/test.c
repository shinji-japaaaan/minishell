#include "../include/minishell.h"
#include "../include/parser.h"

int	main(void)
{
	t_linked_list	*head;
	int idx;

	idx = 1;
	//test 1
	char *str1 = "  		adj dasfj adk | dasj jdasg|dasf   	 	 	";
	printf("test%d: %s\n", idx++, str1);
	head = parser(str1);
	linked_list_print_with_token(head);

	//test 2
	char *str2 = "\"dsfljfd | dfa\"";
	printf("test%d: %s\n", idx++, str2);
	head = parser(str2);
	linked_list_print_with_token(head);

	char *str3 = "dsf \"abcd|\"adfadsf   ";
	printf("test%d: %s\n", idx++, str3);
	head = parser(str3);
	linked_list_print_with_token(head);

	char *str4 = "cat input.txt>output.txt";
	printf("test%d: %s\n", idx++, str4);
	head = parser(str4);
	linked_list_print_with_token(head);

	char *str5 = "cat input.txt>>output.txt";
	printf("test%d: %s\n", idx++, str5);
	head = parser(str5);
	linked_list_print_with_token(head);

	char *str6 = "input.txt < cat";
	printf("test%d: %s\n", idx++, str6);
	head = parser(str6);
	linked_list_print_with_token(head);

	char *str7 = "echo 'input.txt < cat   '   ";
	printf("test%d: %s\n", idx++, str7);
	head = parser(str7);
	linked_list_print_with_token(head);

	printf("\ntest for expansion\n");
	printf("===================================\n");

	char *str8 = "echo $USER \"$USER\" '$USER'";
	printf("test%d: %s\n", idx++, str8);
	head = parser(str8);
	linked_list_print_with_token(head);
}