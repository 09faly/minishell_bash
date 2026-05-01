/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarakoto <sarakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 10:18:04 by frakotov          #+#    #+#             */
/*   Updated: 2024/12/21 14:07:17 by sarakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_heredoc_redirection(char **tokens, int i, t_env *my_env,
		int *input_fd)
{
	if (tokens[i + 1] == NULL || check_file_redirection(tokens[i + 1]))
	{
		printf("minishell: syntax error near unexpected token `newline`\n");
		my_env->last_exit_status = 2;
		return (-1);
	}
	*input_fd = my_env->fd_heredoc[my_env->hd++];
	if (*input_fd < 0)
		return (-1);
	remove_tokens(tokens, i, 2);
	return (0);
}

int	handle_input_redirection(char **tokens, int i, int *input_fd)
{
	if (tokens[i + 1] == NULL || check_file_redirection(tokens[i + 1]))
	{
		printf("bash: syntax error near unexpected token `newline`\n");
		return (-1);
	}
	*input_fd = open(tokens[i + 1], O_RDONLY);
	if (*input_fd < 0)
	{
		perror("open");
		return (-1);
	}
	remove_tokens(tokens, i, 2);
	return (0);
}
