/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarakoto <sarakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:51:43 by frakotov          #+#    #+#             */
/*   Updated: 2024/12/21 14:41:35 by sarakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	process_redirections(char **tokens, t_env *my_env, int *input_fd,
		int *output_fd)
{
	int	i;
	int	ret;

	i = 0;
	while (tokens[i] != NULL)
	{
		ret = 0;
		if (ft_strcmp(tokens[i], "<<") == 0)
			ret = handle_heredoc_redirection(tokens, i, my_env, input_fd);
		else if (ft_strcmp(tokens[i], ">>") == 0)
			ret = handle_append_redirection(tokens, i, output_fd);
		else if (ft_strcmp(tokens[i], ">") == 0)
			ret = handle_truncate_redirection(tokens, i, output_fd);
		else if (ft_strcmp(tokens[i], "<") == 0)
			ret = handle_input_redirection(tokens, i, input_fd);
		else
			i++;
		if (ret < 0)
			return (-1);
	}
	return (0);
}

int	handle_redirection(char **tokens, t_env *my_env)
{
	int	input_fd;
	int	output_fd;

	input_fd = -1;
	output_fd = -1;
	if (process_redirections(tokens, my_env, &input_fd, &output_fd) < 0)
		return (-1);
	if (input_fd != -1)
	{
		if (dup2(input_fd, STDIN_FILENO) < 0)
		{
			perror("dup2");
			close(input_fd);
			return (-1);
		}
		my_env->fd_in = input_fd;
		close(input_fd);
	}
	cleanup_my_env(my_env);
	return (0);
}
