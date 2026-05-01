/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarakoto <sarakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 11:13:46 by sarakoto          #+#    #+#             */
/*   Updated: 2024/12/21 13:57:21 by sarakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_tk(t_token *tk, char *command, char *current, char **tokens)
{
	if (tk->j > 0)
	{
		current[tk->j] = '\0';
		if ((ft_strnstr(command, "$", ft_strlen(command)) != NULL)
			&& (ft_strnstr(command, "\'", ft_strlen(command)) != NULL))
			tokens[tk->k++] = ft_strdup(current);
		else
			tokens[tk->k++] = handle_quotes(current);
		tk->j = 0;
	}
}

void	redir(t_token *tk, char *command, char *current, char **tokens)
{
	if (tk->j > 0)
	{
		current[tk->j] = '\0';
		tokens[tk->k++] = ft_strdup(current);
		tk->j = 0;
	}
	current[tk->j++] = command[tk->i++];
	if (command[tk->i] == '>' || command[tk->i] == '<')
		current[tk->j++] = command[tk->i++];
	current[tk->j] = '\0';
	tokens[tk->k++] = ft_strdup(current);
	tk->j = 0;
}

void	final(t_token *tk, char *command, char *current, char **tokens)
{
	current[tk->j] = '\0';
	if ((ft_strnstr(command, "$", ft_strlen(command)) != NULL)
		&& (ft_strnstr(command, "\'", ft_strlen(command)) != NULL))
		tokens[tk->k++] = ft_strdup(current);
	else
		tokens[tk->k++] = handle_quotes(current);
}

void	init(t_token *tk, char *command, char **current, char ***tokens)
{
	tk->i = 0;
	tk->j = 0;
	tk->k = 0;
	tk->sq = 0;
	tk->dq = 0;
	*current = malloc(ft_strlen(command) + 1);
	*tokens = malloc(sizeof(char *) * 256);
	if (!(*current) || !(*tokens))
		return ;
}

char	**tokenize(char *command)
{
	t_token	tk;
	char	**tokens;
	char	*current;

	init(&tk, command, &current, &tokens);
	while (command[(tk.i)])
	{
		toggle_quotes(command[tk.i], &tk.sq, &tk.dq);
		if (command[tk.i] == ' ' && !tk.sq && !tk.dq)
			append_tk(&tk, command, current, tokens);
		else if ((command[tk.i] == '>' || command[tk.i] == '<') && !tk.sq
			&& !tk.dq)
		{
			redir(&tk, command, current, tokens);
			continue ;
		}
		else
			current[tk.j++] = command[tk.i];
		tk.i++;
	}
	if (tk.j > 0)
		final(&tk, command, current, tokens);
	tokens[tk.k] = NULL;
	free(current);
	return (tokens);
}
