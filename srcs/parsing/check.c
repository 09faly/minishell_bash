/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarakoto <sarakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:17:41 by sarakoto          #+#    #+#             */
/*   Updated: 2024/12/21 14:53:55 by sarakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	is_invalid_redirection(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if ((ft_strcmp(tokens[i], ">>") == 0 || ft_strcmp(tokens[i], ">") == 0
				|| ft_strcmp(tokens[i], "<<") == 0 || ft_strcmp(tokens[i],
					"<") == 0))
		{
			if (tokens[i + 1] == NULL || ft_strcmp(tokens[i + 1], ">") == 0
				|| ft_strcmp(tokens[i + 1], ">>") == 0 || ft_strcmp(tokens[i
						+ 1], "<") == 0 || ft_strcmp(tokens[i + 1], "<<") == 0)
			{
				printf("minishell: syntax error near unexpected token `%s`\n",
					tokens[i + 1]);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	validate_redirections(char **tokens, t_env *my_env)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (ft_strncmp(tokens[i], ">", 2) == 0 || ft_strncmp(tokens[i], ">>",
				3) == 0 || ft_strncmp(tokens[i], "<", 2) == 0
			|| ft_strncmp(tokens[i], "<<", 3) == 0)
		{
			if (!tokens[i + 1] || ft_strncmp(tokens[i + 1], ">", 2) == 0
				|| ft_strncmp(tokens[i + 1], ">>", 3) == 0
				|| ft_strncmp(tokens[i + 1], "<", 2) == 0 || ft_strncmp(tokens[i
						+ 1], "<<", 3) == 0)
			{
				printf("ms: syntax error near unexpected token newline \n");
				my_env->last_exit_status = 2;
				return (-1);
			}
		}
		i++;
	}
	return (0);
}

void	cmd_not_found(char **token, t_env *my_env, char *command_path)
{
	printf("%s: command not found\n", token[0]);
	free(my_env->fd_heredoc);
	free(command_path);
	ft_free(token);
	ft_free_env(my_env);
	exit(127);
}

void	is_directory(char **token, t_env *my_env)
{
	printf("%s: is a directory\n", token[0]);
	ft_free(token);
	close(my_env->hd);
	ft_free_env(my_env);
	exit(126);
}

int	check_redirection(char **token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if ((ft_strcmp(token[i], ">") == 0) || ft_strcmp(token[i], "<") == 0
			|| ft_strcmp(token[i], ">>") == 0 || ft_strcmp(token[i], "<<") == 0)
			return (1);
		i++;
	}
	return (0);
}
