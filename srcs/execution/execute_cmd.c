/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarakoto <sarakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:30:15 by sarakoto          #+#    #+#             */
/*   Updated: 2024/12/21 14:54:55 by sarakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	execute_if_builtins(char **token, t_env *my_env)
{
	pid_t	pid;

	if (!check_redirection(token))
	{
		execute_builtins(token, &my_env);
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (handle_redirection(token, my_env) == -1)
				clean_and_exit(token, my_env);
			execute_builtins(token, &my_env);
			clean_and_exit(token, my_env);
		}
		else if (pid < 0)
			error_process(my_env);
		else
			wait_process(my_env, pid);
	}
}

void	free_after_exec(char **token, t_env *my_env)
{
	ft_free(token);
	cleanup_my_env(my_env);
	ft_free_env(my_env);
}

void	execute_not_builtins(char **token, t_env *my_env)
{
	struct stat	path_stat;
	char		*command_path;

	if (handle_redirection(token, my_env) == -1)
		clean_and_exit(token, my_env);
	if (token[0] && (!(token[0][0] == '<' && token[0][1] == '<'
		&& token[0][2] == '\0')))
	{
		if ((ft_strncmp(token[0], "./", 2) == 0 || (ft_strncmp(token[0], "/",
						1) == 0) || ft_strncmp(token[0], "../", 3) == 0))
			execve(token[0], token, my_env->vars);
		if (stat(token[0], &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
			is_directory(token, my_env);
		command_path = find_command_path(token[0], my_env);
		if (!command_path)
			cmd_not_found(token, my_env, command_path);
		execve(command_path, token, my_env->vars);
		free(command_path);
		free_after_exec(token, my_env);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	free_success(token, my_env);
}
