/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarakoto <sarakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 08:32:33 by sarakoto          #+#    #+#             */
/*   Updated: 2024/12/21 14:31:57 by sarakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static void	cleanup_and_exit(t_env *my_env, char **input, int exit_code)
{
	free(my_env->fd_heredoc);
	ft_free(my_env->exported);
	ft_free_env(my_env);
	ft_free(input);
	exit(exit_code);
}

static int	handle_no_arguments(t_env *my_env, char **input)
{
	if (!input[1])
	{
		printf("exit\n");
		cleanup_and_exit(my_env, input, 0);
	}
	return (0);
}

static int	handle_too_many_arguments(char **input, t_env *my_env,
		char *cleaning_input)
{
	if (input[2])
	{
		printf("minishell: exit: too many arguments\n");
		my_env->last_exit_status = 1;
		free(cleaning_input);
		return (1);
	}
	return (0);
}

static void	handle_non_numeric_argument(char *arg, t_env *my_env, char **input,
		char *cleaning_input)
{
	printf("minishell: exit: %s: numeric argument required\n", arg);
	free(cleaning_input);
	cleanup_and_exit(my_env, input, 2);
}

void	built_exit(char **input, t_env *my_env)
{
	int		exit_code;
	char	*cleaning_input;

	if (handle_no_arguments(my_env, input))
		return ;
	cleaning_input = remove_quotes(input[1]);
	if (check_numeric(cleaning_input))
	{
		exit_code = ft_atoi(cleaning_input);
		if (handle_too_many_arguments(input, my_env, cleaning_input))
			return ;
		free(cleaning_input);
		cleanup_and_exit(my_env, input, exit_code);
	}
	else
		handle_non_numeric_argument(input[1], my_env, input, cleaning_input);
}
