/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 08:12:05 by sishizaw          #+#    #+#             */
/*   Updated: 2025/02/09 12:18:56 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

History	*init_history(int max_size)
{
	History	*history;

	history = malloc(sizeof(History));
	if (!history)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	history->entries = malloc(max_size * sizeof(char *));
	if (!history->entries)
	{
		free(history);
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	history->count = 0;
	history->max_size = max_size;
	return (history);
}

void	add_to_history(History *history, const char *line)
{
	int	i;

	if (history->count == history->max_size)
	{
		free(history->entries[0]);
		i = 0;
		while (i < history->count - 1)
		{
			history->entries[i] = history->entries[i + 1];
			i++;
		}
		history->count--;
	}
	history->entries[history->count++] = ft_strdup(line);
}

void	save_history_to_file(const char *filename, History *history)
{
	int	fd;
	int	i;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open");
		return ;
	}
	i = 0;
	while (i < history->count)
	{
		write(fd, history->entries[i], ft_strlen(history->entries[i]));
		write(fd, "\n", 1);
		i++;
	}
	close(fd);
}

void	process_line(char *start, char *end, History *history)
{
	char	*line;

	*end = '\0';
	line = (char *)ft_calloc(sizeof(char), (ft_strlen(start) + 1));
	if (line != NULL)
	{
		ft_strcpy(line, start);
		add_to_history(history, line);
		add_history(line);
		free(line);
	}
}

void	load_history_from_file(const char *filename, History *history)
{
	int		fd;
	ssize_t	bytes;
	char	buffer[BUFFER_SIZE + 1];
	char	*start;
	char	*end;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return ;
	while ((bytes = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[bytes] = '\0';
		start = buffer;
		while ((end = ft_strchr(start, '\n')) != NULL)
		{
			process_line(start, end, history);
			start = end + 1;
		}
	}
	close(fd);
}

void	free_history(History *history)
{
	for (int i = 0; i < history->count; i++)
	{
		free(history->entries[i]);
	}
	free(history->entries);
	free(history);
}
