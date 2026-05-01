/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarakoto <sarakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 09:58:45 by sarakoto          #+#    #+#             */
/*   Updated: 2024/12/21 14:17:08 by sarakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_file_redirection(char *token)
{
	if (!token || *token == '\0')
		return (1);
	if (ft_strchr("<>|", *token))
		return (1);
	return (0);
}

int	qqc(char *command, int set)
{
	int			i;
	static int	ret = 0;
	char		**token;

	i = 0;
	if (!set)
	{
		ret = 0;
		return (0);
	}
	token = tokenize(command);
	while (token[i])
	{
		if (ft_strcmp(token[i], "<<") == 0 && !(token[i + 1] == NULL
				|| check_file_redirection(token[i + 1])))
			ret++;
		i++;
	}
	ft_free(token);
	return (ret);
}

int	ft_strlen_hrd(char **command)
{
	int		h;
	int		i;
	int		j;
	char	**token;

	h = 0;
	i = 0;
	j = 0;
	while (command[i])
	{
		token = tokenize(command[i]);
		if (!token)
			return (j);
		h = 0;
		while (token[h])
		{
			if (ft_strcmp(token[h], "<<") == 0)
				j++;
			h++;
		}
		ft_free(token);
		i++;
	}
	return (j);
}
