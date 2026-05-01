/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarakoto <sarakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:58:44 by sarakoto          #+#    #+#             */
/*   Updated: 2024/12/21 14:58:47 by sarakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_from_exported(t_env **my_env, char *var, int len)
{
	int	i;
	int	last_index;

	i = 0;
	while (i < (*my_env)->export_count)
	{
		if (ft_strncmp((*my_env)->exported[i], var, len) == 0
			&& (*my_env)->exported[i][len] == '\0')
		{
			free((*my_env)->exported[i]);
			last_index = --(*my_env)->export_count;
			(*my_env)->exported[i] = (*my_env)->exported[last_index];
			break ;
		}
		i++;
	}
}

void	update_in_vars_or_add(t_env **my_env, char *var, int len)
{
	int	i;

	i = 0;
	while (i < (*my_env)->count)
	{
		if (ft_strncmp((*my_env)->vars[i], var, len) == 0
			&& (*my_env)->vars[i][len] == '=')
		{
			free((*my_env)->vars[i]);
			(*my_env)->vars[i] = ft_strdup(var);
			return ;
		}
		i++;
	}
	add_back(my_env, var);
}

bool	variable_name_in_export(char *name)
{
	int	i;

	i = 1;
	if (!name || !*name)
		return (true);
	if ((!ft_isalpha(name[0]) && name[0] != '_'))
		return (true);
	while (name[i] && name[i] != '=')
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (true);
		i++;
	}
	return (false);
}

void	add_new_export(t_env **my_env, char *var)
{
	int	i;

	i = 0;
	while (i < (*my_env)->export_count)
	{
		if (ft_strcmp((*my_env)->exported[i], var) == 0)
			return ;
		i++;
	}
	add_back_exported(my_env, var);
}

void	add_back_exported(t_env **my_env, char *new_var)
{
	char	**new_exported;
	int		i;

	i = 0;
	if (!new_var || !*new_var)
		return ;
	new_exported = malloc(sizeof(char *) * ((*my_env)->export_count + 2));
	if (!new_exported)
		return ;
	while (i < (*my_env)->export_count)
	{
		new_exported[i] = (*my_env)->exported[i];
		i++;
	}
	new_exported[i] = ft_strdup(new_var);
	new_exported[i + 1] = NULL;
	ft_free((*my_env)->exported);
	(*my_env)->exported = new_exported;
	(*my_env)->export_count++;
}
