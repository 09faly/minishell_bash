/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarakoto <sarakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:21:23 by sarakoto          #+#    #+#             */
/*   Updated: 2024/12/21 09:53:35 by sarakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	free_success(char **token, t_env *my_env)
{
	ft_free(token);
	ft_free_env(my_env);
	exit(EXIT_SUCCESS);
}

void	ft_free(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	cleanup_my_env(t_env *my_env)
{
	int	i;

	i = 0;
	if (my_env->fd_heredoc)
	{
		while (my_env->fd_heredoc[i] != -2)
		{
			if (my_env->fd_heredoc[i] >= 0)
				close(my_env->fd_heredoc[i]);
			i++;
		}
		free(my_env->fd_heredoc);
		my_env->fd_heredoc = NULL;
	}
}

void	ft_close(t_env *my_env)
{
	int	i;

	i = 0;
	while (my_env->fd_heredoc[i] != -2)
	{
		if (my_env->fd_heredoc[i] >= 0)
		{
			close(my_env->fd_heredoc[i]);
			my_env->fd_heredoc[i] = -1;
		}
		i++;
	}
}

void	ft_free_env(t_env *my_env)
{
	int	i;

	i = 0;
	while (i < my_env->count)
	{
		free(my_env->vars[i]);
		i++;
	}
	free(my_env->vars);
	free(my_env);
}
