/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarakoto <sarakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 10:05:35 by sarakoto          #+#    #+#             */
/*   Updated: 2024/12/21 14:47:04 by sarakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	execute_exec(int pipefd[2], char **tokens, char **commands,
		t_env *my_env)
{
	char	*commands_path;

	close(pipefd[0]);
	commands_path = find_command_path(tokens[0], my_env);
	if (!commands_path)
		clean_all(pipefd, tokens, commands, my_env);
	execve(commands_path, tokens, my_env->vars);
	ft_free(tokens);
	free(commands_path);
	ft_free(commands);
	cleanup_my_env(my_env);
	ft_free_env(my_env);
	close(pipefd[1]);
	perror("execve");
	exit(EXIT_FAILURE);
}

void	after_exe(int pipefd[2], int *i, char **commands, t_env *my_env)
{
	close(pipefd[1]);
	if (my_env->fd_in != 0)
		close(my_env->fd_in);
	my_env->fd_in = pipefd[0];
	my_env->hd = qqc(commands[*i], 1);
}

void	execute_builtin_pipe(int pipefd[2], char **tokens, char **commands,
		t_env *my_env)
{
	execute_builtins(tokens, &my_env);
	ft_free(tokens);
	cleanup_my_env(my_env);
	ft_free_env(my_env);
	ft_free(commands);
	close(pipefd[0]);
	close(pipefd[1]);
	exit(EXIT_FAILURE);
}

void	clean_redir(int pipefd[2], char **tokens, char **commands,
		t_env *my_env)
{
	ft_free(commands);
	ft_free(tokens);
	close(pipefd[0]);
	close(pipefd[1]);
	cleanup_my_env(my_env);
	ft_free_env(my_env);
	exit(EXIT_FAILURE);
}

void	dup_proces(int pipefd[2], char **commands, t_env *my_env, int *i)
{
	if (my_env->fd_in != 0)
	{
		dup2(my_env->fd_in, STDIN_FILENO);
		close(my_env->fd_in);
	}
	if (commands[(*i) + 1] != NULL)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
}
