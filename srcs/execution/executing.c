/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarakoto <sarakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:11:33 by sarakoto          #+#    #+#             */
/*   Updated: 2024/12/20 15:30:58 by sarakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	execut_extern_cmd(char **token, t_env *my_env)
{
	pid_t	pid;

	if (is_invalid_redirection(token))
	{
		my_env->last_exit_status = 2;
		return (2);
	}
	if (!token || !token[0])
	{
		my_env->last_exit_status = 127;
		return (127);
	}
	if (is_builtins(token[0]))
	{
		execute_if_builtins(token, my_env);
		return (my_env->last_exit_status);
	}
	pid = fork();
	if (pid == 0)
		execute_not_builtins(token, my_env);
	else if (pid < 0)
		error_process(my_env);
	wait_process(my_env, pid);
	return (my_env->last_exit_status);
}

int	handle_single_pipe(char **pipe_cmd, t_env *my_env)
{
	char	**token;

	token = tokenize(pipe_cmd[0]);
	fd_hrdoc(pipe_cmd, my_env, 0);
	ft_free(pipe_cmd);
	if (!token[0])
	{
		ft_free(token);
		return (2);
	}
	execut_extern_cmd(token, my_env);
	ft_free(token);
	ft_close(my_env);
	return (my_env->last_exit_status);
}

int	handle_heredoc_and_syntax(char *input, t_env *my_env, int *is_heredoc)
{
	*is_heredoc = ft_strnstr(input, "<<", ft_strlen(input)) != NULL;
	if (!validate_pipe_syntax(input))
		return (handle_syntax_error(my_env));
	return (0);
}

int	handle_pipe_commands(char **pipe_cmd, t_env *my_env)
{
	int	i;

	i = 0;
	while (pipe_cmd[i])
	{
		if (ft_strlen(pipe_cmd[i]) > 0)
			break ;
		if (!pipe_cmd[i + 1])
		{
			ft_free(pipe_cmd);
			return (handle_syntax_error(my_env));
		}
		i++;
	}
	if (!pipe_cmd[1])
		return (handle_single_pipe(pipe_cmd, my_env));
	execute_pipe(pipe_cmd, my_env);
	ft_free(pipe_cmd);
	return (0);
}

int	execute_command(char *input, t_env *my_env)
{
	int		is_heredoc;
	char	**pipe_cmd;
	char	*expand_input;

	if (handle_heredoc_and_syntax(input, my_env, &is_heredoc))
		return (my_env->last_exit_status);
	expand_input = get_expand_input(input, my_env, is_heredoc);
	if (!expand_input)
	{
		free(expand_input);
		return (0);
	}
	pipe_cmd = split_by_pipe(expand_input, my_env);
	free(expand_input);
	if (!pipe_cmd || !pipe_cmd[0])
	{
		ft_free(pipe_cmd);
		return (handle_syntax_error(my_env));
	}
	if (handle_pipe_commands(pipe_cmd, my_env))
		return (my_env->last_exit_status);
	ft_close(my_env);
	free(my_env->fd_heredoc);
	my_env->fd_heredoc = NULL;
	return (my_env->last_exit_status);
}
