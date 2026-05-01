/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarakoto <sarakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 08:22:46 by frakotov          #+#    #+#             */
/*   Updated: 2024/12/20 16:45:54 by sarakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*saved_str;
	char		*token_start;

	if (str != NULL)
		saved_str = str;
	if (saved_str == NULL)
		return (NULL);
	while (*saved_str && ft_strchr(delim, *saved_str))
		saved_str++;
	if (*saved_str == '\0')
		return (NULL);
	token_start = saved_str;
	while (*saved_str && !(ft_strchr(delim, *saved_str)))
		saved_str++;
	if (*saved_str)
	{
		*saved_str = '\0';
		saved_str++;
	}
	return (token_start);
}

void	remove_tokens(char **tokens, int index, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(tokens[index + i]);
		i++;
	}
	i = index;
	while (tokens[i + count])
	{
		tokens[i] = tokens[i + count];
		i++;
	}
	while (tokens[i])
		tokens[i++] = NULL;
}

char	*take_path_in_env(t_env *my_env)
{
	int	i;

	i = 0;
	while (i < my_env->count && my_env->vars[i])
	{
		if (ft_strncmp(my_env->vars[i], "PATH=", 5) == 0)
			return (my_env->vars[i]);
		i++;
	}
	return (NULL);
}
