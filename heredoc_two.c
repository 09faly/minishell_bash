/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarakoto <sarakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 11:33:24 by frakotov          #+#    #+#             */
/*   Updated: 2024/12/21 14:54:46 by sarakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_fd_heredoc(t_env *my_env)
{
	if (my_env->fd_heredoc)
	{
		free(my_env->fd_heredoc);
		my_env->fd_heredoc = NULL;
	}
}

void	init_fd_heredoc(t_env *my_env, int h)
{
	my_env->fd_heredoc = (int *)malloc(sizeof(int) * (h + 1));
	if (my_env->fd_heredoc)
		my_env->fd_heredoc[h] = -2;
}

void	free_hd(t_env *my_env, char **token)
{
	free_fd_heredoc(my_env);
	ft_free(token);
	return ;
}

void	process_tokens(char *cmd, t_env *my_env, int *k)
{
	char	**token;
	int		h;
	int		fd;

	token = tokenize(cmd);
	if (!token)
	{
		free_fd_heredoc(my_env);
		return ;
	}
	h = 0;
	while (token[h])
	{
		if (ft_strcmp(token[h], "<<") == 0 && !(token[h + 1] == NULL
				|| check_file_redirection(token[h + 1])))
		{
			fd = handle_heredoc(token[h + 1], my_env);
			if (fd < 0)
				free_hd(my_env, token);
			my_env->fd_heredoc[(*k)++] = fd;
		}
		h++;
	}
	ft_free(token);
}

void	fd_hrdoc(char **cmd, t_env *my_env, int hd)
{
	int		k;
	int		i;
	int		h;

	(void)hd;
	free_fd_heredoc(my_env);
	h = ft_strlen_hrd(cmd);
	init_fd_heredoc(my_env, h);
	k = 0;
	i = 0;
	while (cmd[i])
	{
		process_tokens(cmd[i], my_env, &k);
		i++;
	}
}
