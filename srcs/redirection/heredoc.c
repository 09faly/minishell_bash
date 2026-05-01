/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarakoto <sarakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 08:00:15 by frakotov          #+#    #+#             */
/*   Updated: 2024/12/21 13:09:56 by sarakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static void	process_heredoc(char *delimiter, int *pipefd, t_env *my_env)
{
	char	*line;
	char	*expanded_line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		expanded_line = expand(line, my_env);
		free(line);
		if (expanded_line)
		{
			write(pipefd[1], expanded_line, ft_strlen(expanded_line));
			write(pipefd[1], "\n", 1);
			free(expanded_line);
		}
	}
	close(pipefd[1]);
}

static void	heredoc_sigint_handler(int signo)
{
	(void)signo;
	ft_putchar_fd('\n', STDOUT_FILENO);
}

int	handle_heredoc(char *delimiter, t_env *my_env)
{
	int					pipefd[2];
	struct sigaction	sa;
	struct sigaction	old_sa;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	sa.sa_handler = heredoc_sigint_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, &old_sa);
	process_heredoc(delimiter, pipefd, my_env);
	sigaction(SIGINT, &old_sa, NULL);
	close(pipefd[1]);
	return (pipefd[0]);
}
