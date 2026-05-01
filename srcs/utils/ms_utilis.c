/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utilis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarakoto <sarakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 08:30:53 by sarakoto          #+#    #+#             */
/*   Updated: 2024/12/21 14:47:06 by sarakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	length;

	i = 0;
	length = 0;
	while (dest[length] != '\0')
		length++;
	while (src[i] != '\0')
	{
		dest[length + i] = src[i];
		i++;
	}
	dest[length + i] = '\0';
	return (dest);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	init_token(char ***tokens, int *i, char **commands, t_env *my_env)
{
	*tokens = tokenize(commands[*i]);
	if (*i == 0)
		my_env->hd = 0;
}

void	pipe_loop(char **commands, t_env *my_env)
{
	int		i;
	pid_t	pid;
	int		pipefd[2];
	char	**tokens;

	i = -1;
	while (commands[++i] != NULL)
	{
		if (pipe(pipefd) == -1)
			pipe_error(my_env);
		init_token(&tokens, &i, commands, my_env);
		pid = fork();
		if (pid == 0)
		{
			dup_proces(pipefd, commands, my_env, &i);
			do_cmd(pipefd, tokens, commands, my_env);
		}
		else if (pid < 0)
			error_process(my_env);
		else
		{
			after_exe(pipefd, &i, commands, my_env);
			ft_free(tokens);
		}
	}
}
