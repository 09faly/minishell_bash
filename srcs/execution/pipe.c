/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarakoto <sarakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 10:27:25 by sarakoto          #+#    #+#             */
/*   Updated: 2024/12/21 09:52:41 by sarakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

bool	is_whitespace(char c)
{
	return (c == ' ');
}

int	skip_whitespace(char *input, int i)
{
	while (input[i] && is_whitespace(input[i]))
		i++;
	return (i);
}

bool	is_invalid_pipe(char *input, int *i, bool *found_pipe)
{
	(*i)++;
	*i = skip_whitespace(input, *i);
	if (input[*i] == '\0' || input[*i] == '|')
		return (true);
	*found_pipe = true;
	return (false);
}

bool	validate_pipe_syntax(char *input)
{
	int		i;
	int		single_quote_open;
	int		double_quote_open;
	bool	found_pipe;

	i = skip_whitespace(input, 0);
	if (input[i] == '|')
		return (false);
	single_quote_open = 0;
	double_quote_open = 0;
	found_pipe = false;
	while (input[i])
	{
		toggle_quotes(input[i], &single_quote_open, &double_quote_open);
		if (input[i] == '|' && !single_quote_open && !double_quote_open)
		{
			if (found_pipe || is_invalid_pipe(input, &i, &found_pipe))
				return (false);
		}
		else
			found_pipe = false;
		i++;
	}
	return (true);
}
