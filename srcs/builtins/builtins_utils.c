/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarakoto <sarakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:09:26 by sarakoto          #+#    #+#             */
/*   Updated: 2024/12/20 15:33:48 by sarakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	init_struct(t_env *my_env)
{
	my_env->count = 0;
	my_env->export_count = 0;
	my_env->exported = NULL;
	my_env->last_exit_status = 0;
	my_env->fd_heredoc = NULL;
	my_env->hd = 0;
}

void	dup_env(t_env *my_env, char **env)
{
	int	i;

	i = 0;
	while (i < my_env->count)
	{
		my_env->vars[i] = ft_strdup(env[i]);
		if (!my_env->vars[i])
		{
			ft_free(my_env->vars);
			ft_free_env(my_env);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

t_env	*init_env(char **env)
{
	t_env	*my_env;

	my_env = (t_env *)malloc(sizeof(t_env));
	if (!my_env)
		exit(EXIT_FAILURE);
	init_struct(my_env);
	while (env[my_env->count])
		my_env->count++;
	my_env->vars = (char **)malloc((my_env->count + 1) * sizeof(char *));
	if (!my_env->vars)
	{
		ft_free_env(my_env);
		exit(EXIT_FAILURE);
	}
	dup_env(my_env, env);
	my_env->vars[my_env->count] = NULL;
	return (my_env);
}

void	add_back(t_env **my_env, char *new_variable)
{
	char	**new_var;
	int		i;

	if (!new_variable || !*new_variable)
		return ;
	new_var = malloc(sizeof(char *) * ((*my_env)->count + 2));
	if (!new_var)
		return ;
	i = 0;
	while (i < (*my_env)->count)
	{
		new_var[i] = (*my_env)->vars[i];
		i++;
	}
	new_var[i] = ft_strdup(new_variable);
	new_var[i + 1] = NULL;
	free((*my_env)->vars);
	(*my_env)->vars = new_var;
	(*my_env)->count++;
}

int	is_builtins(char *cmd)
{
	if ((ft_strncmp(cmd, "cd", 3) == 0))
		return (1);
	else if ((ft_strncmp(cmd, "exit", 4) == 0))
		return (1);
	else if ((ft_strncmp(cmd, "export", 7) == 0))
		return (1);
	else if ((ft_strncmp(cmd, "unset", 6) == 0))
		return (1);
	else if ((ft_strncmp(cmd, "pwd", 4) == 0))
		return (1);
	else if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	else if ((ft_strncmp(cmd, "env", 4) == 0))
		return (1);
	return (0);
}
