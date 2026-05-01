/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarakoto <sarakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 08:31:55 by sarakoto          #+#    #+#             */
/*   Updated: 2024/12/20 08:31:55 by sarakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char	*take_home_in_env(t_env *my_env)
{
	int	i;

	i = 0;
	while (i < my_env->count && my_env->vars[i])
	{
		if (ft_strncmp(my_env->vars[i], "HOME=", 5) == 0)
			return (my_env->vars[i] + 5);
		i++;
	}
	return (NULL);
}

static int	handle_too_many_arguments(char **token, t_env *my_env)
{
	int	i;

	i = 0;
	while (token[i])
		i++;
	if (i >= 3)
	{
		printf("minishell: cd: too many arguments\n");
		my_env->last_exit_status = 1;
		return (1);
	}
	return (0);
}

static int	handle_home_directory(char **token, t_env *my_env, char *home_dir)
{
	if (token[1] == NULL || (ft_strncmp(token[1], "~", 2) == 0))
	{
		if (!home_dir || *home_dir == '\0')
		{
			printf("minishell: cd: HOME not found\n");
			my_env->last_exit_status = 1;
			return (1);
		}
		if (home_dir && chdir(home_dir) == -1)
		{
			perror("cd");
			my_env->last_exit_status = 1;
			return (1);
		}
	}
	else if (chdir(token[1]) != 0)
	{
		my_env->last_exit_status = 1;
		perror("cd");
		return (1);
	}
	return (0);
}

static int	update_pwd_variables(t_env *my_env, char *old_pwd, char *new_pwd)
{
	char	*pwd_var;

	pwd_var = malloc((ft_strlen("PWD=") + ft_strlen(new_pwd) + 1)
			* sizeof(char));
	if (!pwd_var)
		return (1);
	ft_strcpy(pwd_var, "PWD=");
	ft_strcat(pwd_var, new_pwd);
	built_export_with_argument(&my_env, pwd_var);
	free(pwd_var);
	if (old_pwd)
	{
		pwd_var = malloc((ft_strlen("OLDPWD=") + ft_strlen(old_pwd) + 1)
				* sizeof(char));
		if (!pwd_var)
			return (1);
		ft_strcpy(pwd_var, "OLDPWD=");
		ft_strcat(pwd_var, old_pwd);
		built_export_with_argument(&my_env, pwd_var);
		free(pwd_var);
	}
	return (0);
}

int	built_cd(char **token, t_env *my_env)
{
	char	*new_pwd;
	char	*old_pwd;
	char	*home_dir;

	if (handle_too_many_arguments(token, my_env))
		return (1);
	home_dir = take_home_in_env(my_env);
	if (handle_home_directory(token, my_env, home_dir))
		return (1);
	old_pwd = get_env_value("PWD", my_env);
	if (!old_pwd)
		old_pwd = getcwd(NULL, 0);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		perror("getcwd");
		return (1);
	}
	if (update_pwd_variables(my_env, old_pwd, new_pwd))
		return (1);
	free(new_pwd);
	free(old_pwd);
	my_env->last_exit_status = 0;
	return (0);
}
