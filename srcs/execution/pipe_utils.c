/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarakoto <sarakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:42:57 by sarakoto          #+#    #+#             */
/*   Updated: 2024/12/21 14:54:25 by sarakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	clean_all(int pipefd[2], char **tokens, char **commands, t_env *my_env)
{
	printf("%s: command not found\n", tokens[0]);
	ft_free(tokens);
	ft_free(commands);
	cleanup_my_env(my_env);
	ft_free_env(my_env);
	close(pipefd[0]);
	close(pipefd[1]);
	exit(127);
}

void	do_cmd(int pipefd[2], char **tokens, char **commands, t_env *my_env)
{
	if (handle_redirection(tokens, my_env) == -1)
		clean_redir(pipefd, tokens, commands, my_env);
	if (is_builtins(tokens[0]))
		execute_builtin_pipe(pipefd, tokens, commands, my_env);
	else
		execute_exec(pipefd, tokens, commands, my_env);
}

void	wait_pipe(t_env *my_env)
{
	int	status;

	if (my_env->fd_in != 0)
		close(my_env->fd_in);
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			my_env->last_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			my_env->last_exit_status = 128 + WTERMSIG(status);
	}
	qqc(NULL, 0);
}

void	pipe_error(t_env *my_env)
{
	perror("pipe");
	my_env->last_exit_status = 1;
	return ;
}

void	execute_pipe(char **commands, t_env *my_env)
{
	my_env->fd_in = 0;
	fd_hrdoc(commands, my_env, my_env->hd);
	pipe_loop(commands, my_env);
	wait_pipe(my_env);
}
