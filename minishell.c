/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarakoto <sarakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 08:51:53 by sarakoto          #+#    #+#             */
/*   Updated: 2024/12/20 17:17:00 by sarakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

static void	handle_signals_and_history(char *input, t_env *my_env)
{
	signals_for_run_cmd();
	if (g_signal)
	{
		my_env->last_exit_status = 128 + g_signal;
		g_signal = 0;
	}
	if (ft_strlen(input) != 0)
		add_history(input);
}

static int	process_input(char *input, t_env *my_env)
{
	int	ret;

	if (ft_strlen(input) == 0)
	{
		free(input);
		return (1);
	}
	if (check_unclosed_quotes(input))
	{
		printf("Error: unclosed quotes detected\n");
		free(input);
		return (1);
	}
	ret = execute_command(input, my_env);
	if (ret != 0)
		my_env->last_exit_status = ret;
	free(input);
	return (0);
}

static void	minishell_loop(t_env *my_env)
{
	char	*input;

	while (1)
	{
		signals_for_wait_cmd();
		input = readline("➜  Minishell> ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		handle_signals_and_history(input, my_env);
		if (process_input(input, my_env))
			continue ;
	}
}

int	main(int ac, char **av, char **env)
{
	t_env	*my_env;

	(void)ac;
	(void)av;
	my_env = init_env(env);
	minishell_loop(my_env);
	cleanup_my_env(my_env);
	ft_free(my_env->exported);
	ft_free_env(my_env);
	rl_clear_history();
	return (0);
}
