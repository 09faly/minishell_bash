/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarakoto <sarakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 08:31:36 by sarakoto          #+#    #+#             */
/*   Updated: 2024/12/20 15:48:16 by sarakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	update_existing_variable(t_env **my_env, char *var, int len)
{
	remove_from_exported(my_env, var, len);
	update_in_vars_or_add(my_env, var, len);
}

int	built_export_with_argument(t_env **my_env, char *var)
{
	int		len;
	char	*equal_sign;

	equal_sign = ft_strchr(var, '=');
	if (equal_sign != NULL)
		len = equal_sign - var;
	else
		len = ft_strlen(var);
	if (variable_name_in_export(var))
	{
		printf("export: '%s': not a valid identifier\n", var);
		(*my_env)->last_exit_status = 1;
		return (1);
	}
	if (equal_sign != NULL)
		update_existing_variable(my_env, var, len);
	else
		add_new_export(my_env, var);
	return (0);
}

void	built_export_without_argument(t_env *my_env)
{
	int		i;
	int		name_len;
	char	*equal_sign;

	i = 0;
	while (i < my_env->count)
	{
		printf("declare -x ");
		equal_sign = ft_strchr(my_env->vars[i], '=');
		if (equal_sign)
		{
			name_len = equal_sign - my_env->vars[i];
			printf("%.*s=\"%s\"\n", name_len, my_env->vars[i], equal_sign + 1);
		}
		else
			printf("%s\n", my_env->vars[i]);
		i++;
	}
	i = 0;
	while (i < my_env->export_count)
	{
		printf("declare -x %s\n", my_env->exported[i]);
		i++;
	}
}

void	built_export_multiple(t_env **my_env, char **vars)
{
	int	i;

	i = 1;
	while (vars[i])
	{
		built_export_with_argument(my_env, vars[i]);
		i++;
	}
}
