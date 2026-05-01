/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarakoto <sarakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:33:58 by frakotov          #+#    #+#             */
/*   Updated: 2024/12/20 15:52:50 by sarakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_unclosed_quotes(const char *line)
{
	int	single_quote_open;
	int	double_quote_open;
	int	i;

	single_quote_open = 0;
	double_quote_open = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'' && double_quote_open == 0)
			single_quote_open = !single_quote_open;
		else if (line[i] == '"' && single_quote_open == 0)
			double_quote_open = !double_quote_open;
		i++;
	}
	return (single_quote_open || double_quote_open);
}

char	*handle_quotes(const char *line)
{
	char	*result;
	int		i;
	int		j;
	int		single_quote_open;
	int		double_quote_open;

	i = 0;
	j = 0;
	single_quote_open = 0;
	double_quote_open = 0;
	result = malloc((ft_strlen(line) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (line[i] != '\0')
	{
		if (line[i] == '\'' && double_quote_open == 0)
			single_quote_open = !single_quote_open;
		else if (line[i] == '"' && single_quote_open == 0)
			double_quote_open = !double_quote_open;
		else
			result[j++] = line[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}
