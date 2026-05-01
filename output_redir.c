/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarakoto <sarakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 10:21:48 by frakotov          #+#    #+#             */
/*   Updated: 2024/12/21 13:14:05 by sarakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_append_redirection(char **tokens, int i, int *fd)
{
	if (tokens[i + 1] == NULL || check_file_redirection(tokens[i + 1]))
	{
		printf("bash: syntax error near unexpected token `newline`\n");
		return (-1);
	}
	*fd = open(tokens[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (*fd < 0)
	{
		perror("open");
		return (-1);
	}
	if (dup2(*fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		close(*fd);
		return (-1);
	}
	close(*fd);
	remove_tokens(tokens, i, 2);
	return (0);
}

int	handle_truncate_redirection(char **tokens, int i, int *fd)
{
	if (tokens[i + 1] == NULL || check_file_redirection(tokens[i + 1]))
	{
		printf("bash: syntax error near unexpected token `newline`\n");
		return (-1);
	}
	*fd = open(tokens[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd < 0)
	{
		perror("open");
		return (-1);
	}
	if (dup2(*fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		close(*fd);
		return (-1);
	}
	close(*fd);
	remove_tokens(tokens, i, 2);
	return (0);
}
