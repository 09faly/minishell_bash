/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utilis_two.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarakoto <sarakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:06:40 by sarakoto          #+#    #+#             */
/*   Updated: 2024/12/20 09:33:17 by sarakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_remove_quote(char *str, char *cleaned)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
				cleaned[j++] = str[i++];
			if (str[i] == quote)
				i++;
		}
		else
			cleaned[j++] = str[i++];
	}
	cleaned[j] = '\0';
}

char	*remove_quotes(char *str)
{
	char	*cleaned;

	if (!str)
		return (NULL);
	cleaned = malloc(ft_strlen(str) + 1);
	if (!cleaned)
		return (NULL);
	process_remove_quote(str, cleaned);
	return (cleaned);
}

bool	check_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (false);
	if ((str[i] == '-' || str[i] == '+'))
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}
