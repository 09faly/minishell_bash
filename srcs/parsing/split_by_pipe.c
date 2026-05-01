/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarakoto <sarakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 12:48:57 by sarakoto          #+#    #+#             */
/*   Updated: 2024/12/21 14:40:21 by sarakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	update_quote_status(char c, int *single_quote_open,
		int *double_quote_open)
{
	if (c == '\'' && *double_quote_open == 0)
		*single_quote_open = !(*single_quote_open);
	else if (c == '"' && *single_quote_open == 0)
		*double_quote_open = !(*double_quote_open);
}

void	add_command(char **commands, char *current, t_p *p)
{
	current[p->j] = '\0';
	commands[p->k++] = ft_strdup(current);
	p->j = 0;
}

void	init_pipe(t_p *p, char *input, char **current, char ***commands)
{
	p->sq = 0;
	p->dq = 0;
	p->i = 0;
	p->j = 0;
	p->k = 0;
	*commands = malloc(sizeof(char *) * 256);
	*current = malloc(ft_strlen(input) + 1);
	if (!(*current) || !(*commands))
		return ;
}

char	**split_by_pipe(char *input, t_env *my_env)
{
	t_p		p;
	char	**commands;
	char	*current;

	init_pipe(&p, input, &current, &commands);
	(void)my_env;
	while (input[p.i])
	{
		update_quote_status(input[p.i], &p.sq, &p.dq);
		if (input[p.i] == '|' && !p.sq && !p.dq)
			add_command(commands, current, &p);
		else
			current[p.j++] = input[p.i];
		p.i++;
	}
	if (p.j > 0)
		add_command(commands, current, &p);
	commands[p.k] = NULL;
	free(current);
	return (commands);
}
