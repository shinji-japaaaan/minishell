/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sishizaw <sishizaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 10:40:24 by sishizaw          #+#    #+#             */
/*   Updated: 2025/02/08 11:13:54 by sishizaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int change_directory(char *path, char **args) {
    if (args[1] && args[2]) {
        write(STDERR_FILENO, "cd: too many arguments\n", 23);
        return 1;
    }
    if (!path || ft_strcmp(path, "~") == 0) {
        path = getenv("HOME");
        if (!path) {
            write(STDERR_FILENO, "cd failed: HOME not set\n", 24);
            return 1;
        }
    }
    if (ft_strcmp(path, "$PWD") == 0) {
        path = getenv("PWD");
    }
    if (chdir(path) == -1) {
        perror("cd failed");
        return 1;
    }
    return 0;
}

void exit_shell(char **args)
{
    int exit_code = 0;

    if (args[1] && args[2])
    {
        put_str(STDERR_FILENO, "exit: too many arguments\n");
        exit(1);
    }

    if (args[1])
    {
        if (!is_numeric(args[1]))
        {
            put_str(STDERR_FILENO, "exit: ");
            put_str(STDERR_FILENO, args[1]);
            put_str(STDERR_FILENO, ": numeric argument required\n");
            exit(2);
        }
        exit_code = ft_atoi(args[1]);
    }
    exit(exit_code);
}

void echo_command(char **args)
{
    if (!args || !args[0]) {
        return;
    }

    int no_newline = 0;
    int i = 1;

    while (args[i] && ft_strncmp(args[i], "-n", 2) == 0 && ft_strlen(args[i]) == 2) {
        no_newline = 1;
        i++;
    }

    while (args[i]) {
        printf("%s", args[i]);
        if (args[i + 1]) {
            printf(" ");
        }
        i++;
    }
    if (!no_newline) {
        printf("\n");
    }
}

int print_working_directory() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
        return (0);
    } else {
        perror("pwd failed");
        return (1);
    }
}

void print_environment(char **env) {
    char **env_ptr = env;
    while (*env_ptr) {
        printf("%s\n", *env_ptr);
        env_ptr++;
    }
}

int export_variable(char ***env, char *arg) {
    int i;
    size_t name_len;

    if (!arg)
        return print_and_return(*env);

    if (!is_valid_identifier(arg))
        return handle_invalid_identifier(arg);

    if (!ft_strchr(arg, '='))
        return 0;

    i = 0;
    name_len = ft_strchr(arg, '=') - arg;
    while ((*env)[i]) {
        if (ft_strncmp((*env)[i], arg, name_len) == 0 &&
            (*env)[i][name_len] == '=')
            return handle_existing_variable(env, arg, i);
        i++;
    }
    return add_new_variable(env, arg, i);
}

int unset_variable(char ***env, char *arg) {
    if (arg == NULL) {
        return 0;
    }
    int i = 0, j = 0;
    for (; (*env)[i]; i++) {
        if (ft_strncmp((*env)[i], arg, ft_strlen(arg)) == 0 && (*env)[i][ft_strlen(arg)] == '=') {
            free((*env)[i]);
        } else {
            (*env)[j++] = (*env)[i];
        }
    }
    (*env)[j] = NULL;
    return 0;
}