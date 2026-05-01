/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarakoto <sarakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 09:55:59 by sarakoto          #+#    #+#             */
/*   Updated: 2024/12/21 09:52:20 by sarakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	built_unset(t_env *my_env, char *name)
{
	int	i;
	int	j;

	i = 0;
	if (name == NULL || *name == '\0' || ft_strchr(name, '=') != NULL)
		return (-1);
	while (i < my_env->count)
	{
		if ((ft_strncmp(my_env->vars[i], name, ft_strlen(name)) == 0
				&& my_env->vars[i][ft_strlen(name)] == '='))
		{
			free(my_env->vars[i]);
			j = i;
			while (j < my_env->count - 1)
			{
				my_env->vars[j] = my_env->vars[j + 1];
				j++;
			}
			my_env->vars[my_env->count - 1] = NULL;
			my_env->count--;
			return (0);
		}
		i++;
	}
	return (-1);
}

void	built_unset_multiple(char **token, t_env **my_env)
{
	int	i;

	i = 0;
	while (token[i])
	{
		built_unset(*my_env, token[i]);
		i++;
	}
}
