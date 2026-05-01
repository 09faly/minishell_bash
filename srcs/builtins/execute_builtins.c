/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarakoto <sarakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 09:58:01 by sarakoto          #+#    #+#             */
/*   Updated: 2024/12/20 16:48:37 by sarakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	builtins(char **token, t_env **my_env)
{
	if ((ft_strncmp(token[0], "env", 4) == 0))
	{
		built_env(*my_env, token);
		return (0);
	}
	else if ((ft_strncmp(token[0], "unset", 6) == 0))
	{
		built_unset_multiple(token, my_env);
		return (0);
	}
	else if ((ft_strncmp(token[0], "export", 4) == 0))
	{
		if (token[1] == NULL)
			built_export_without_argument(*my_env);
		else
			built_export_multiple(my_env, token);
		return (0);
	}
	return (1);
}

int	execute_builtins(char **token, t_env **my_env)
{
	if (token == NULL || token[0] == NULL)
		return (1);
	if ((ft_strncmp(token[0], "cd", 3) == 0))
	{
		(*my_env)->last_exit_status = built_cd(token, *my_env);
		return (0);
	}
	else if ((ft_strncmp(token[0], "exit", 4) == 0))
	{
		built_exit(&token[0], *my_env);
		return (0);
	}
	else if ((ft_strncmp(token[0], "pwd", 4) == 0))
	{
		built_pwd(token);
		return (0);
	}
	else if (ft_strncmp(token[0], "echo", 5) == 0)
	{
		built_echo(token, *my_env);
		return (0);
	}
	builtins(token, my_env);
	return (1);
}
