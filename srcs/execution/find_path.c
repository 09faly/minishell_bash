/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarakoto <sarakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:02:30 by sarakoto          #+#    #+#             */
/*   Updated: 2024/12/20 15:37:44 by sarakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	concatenation(char *full_path, char *token, char *cmd)
{
	ft_strlcpy(full_path, token, ft_strlen(token) + 1);
	ft_strlcat(full_path, "/", ft_strlen(full_path) + 2);
	ft_strlcat(full_path, cmd, ft_strlen(full_path) + ft_strlen(cmd) + 1);
}

char	*get_paths_from_env(t_env *my_env)
{
	char	*path_env;

	path_env = take_path_in_env(my_env);
	if (!path_env || ft_strlen(path_env) <= 5)
	{
		my_env->last_exit_status = 127;
		return (NULL);
	}
	return (ft_strdup(path_env));
}

char	*build_full_path(char *path, char *cmd)
{
	char	*full_path;

	full_path = malloc(ft_strlen(path) + ft_strlen(cmd) + 2);
	if (!full_path)
		return (NULL);
	concatenation(full_path, path, cmd);
	return (full_path);
}

char	*find_command_in_paths(char *cmd, char *paths)
{
	char	*token;
	char	*full_path;

	token = ft_strtok(paths, ":");
	while (token != NULL)
	{
		full_path = build_full_path(token, cmd);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		token = ft_strtok(NULL, ":");
	}
	return (NULL);
}

char	*find_command_path(char *cmd, t_env *my_env)
{
	char	*paths;
	char	*full_path;

	paths = get_paths_from_env(my_env);
	if (!paths)
		return (NULL);
	full_path = find_command_in_paths(cmd, paths);
	free(paths);
	return (full_path);
}
