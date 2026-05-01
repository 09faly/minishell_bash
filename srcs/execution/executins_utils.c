/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executins_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarakoto <sarakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:25:58 by sarakoto          #+#    #+#             */
/*   Updated: 2024/12/20 16:40:57 by sarakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	wait_process(t_env *my_env, pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		my_env->last_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		my_env->last_exit_status = 128 + WTERMSIG(status);
	else
		my_env->last_exit_status = 1;
}

void	error_process(t_env *my_env)
{
	perror("fork");
	my_env->last_exit_status = 1;
	return ;
}

void	clean_and_exit(char **token, t_env *my_env)
{
	ft_free(token);
	cleanup_my_env(my_env);
	ft_free_env(my_env);
	exit(EXIT_FAILURE);
}

int	handle_syntax_error(t_env *my_env)
{
	printf("minishell: syntax error near unexpected token `|'\n");
	my_env->last_exit_status = 2;
	return (2);
}

char	*get_expand_input(char *input, t_env *my_env, int is_heredoc)
{
	char	*expand_input;

	if (!is_heredoc)
	{
		expand_input = expand(input, my_env);
	}
	else
		expand_input = ft_strdup(input);
	if (!expand_input || *expand_input == '\0')
	{
		free(expand_input);
		return (NULL);
	}
	return (expand_input);
}
