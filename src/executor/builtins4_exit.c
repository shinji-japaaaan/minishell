#include "../../include/minishell.h"

void	free_in_exitcmd(t_cmd_invoke *parsed_list, char ***env,
		t_History *history, bool is_parent)
{
	free_all(&parsed_list);
	free_env(*env);
	if (history->history_path && is_parent)
		save_history_to_file(history->history_path, history);
	free_history(history);
}

void	exit_parent(t_cmd_invoke *parsed_list, int *last_status, char ***env,
		t_History *history)
{
	if (ft_strcmp(parsed_list->next->cmd_list[0], "exit") == 0)
	{
		if (parsed_list->next->cmd_list[1] && parsed_list->next->cmd_list[2])
		{
			put_str(STDERR_FILENO, "exit: too many arguments\n");
			*last_status = 1;
		}
		else if (parsed_list->next->cmd_list[1])
		{
			if (!is_numeric(parsed_list->next->cmd_list[1])
				|| !is_within_long(parsed_list->next->cmd_list[1]))
			{
				put_str(STDERR_FILENO, "exit: ");
				put_str(STDERR_FILENO, parsed_list->next->cmd_list[1]);
				put_str(STDERR_FILENO, ": numeric argument required\n");
				*last_status = 2;
			}
			else
				*last_status = ft_atoi(parsed_list->next->cmd_list[1]);
		}
		free_in_exitcmd(parsed_list, env, history, true);
		exit(*last_status);
	}
}

void	exit_child(t_cmd_invoke *parsed_list, t_cmd_invoke *temp_ptr,
		char ***env, int last_status)
{
	if (ft_strcmp(temp_ptr->cmd_list[0], "exit") == 0)
	{
		if (temp_ptr->cmd_list[1] && temp_ptr->cmd_list[2])
		{
			put_str(STDERR_FILENO, "exit: too many arguments\n");
			last_status = 1;
		}
		else if (temp_ptr->cmd_list[1])
		{
			if (!is_numeric(temp_ptr->cmd_list[1])
				|| !is_within_long(temp_ptr->cmd_list[1]))
			{
				put_str(STDERR_FILENO, "exit: ");
				put_str(STDERR_FILENO, temp_ptr->cmd_list[1]);
				put_str(STDERR_FILENO, ": numeric argument required\n");
				last_status = 2;
			}
			else
				last_status = ft_atoi(temp_ptr->cmd_list[1]);
		}
		free_all(&parsed_list);
		free_env(*env);
		exit(last_status);
	}
}
