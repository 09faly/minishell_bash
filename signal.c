/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frakotov <frakotov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:02:57 by frakotov          #+#    #+#             */
/*   Updated: 2024/12/18 15:00:18 by frakotov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	new_line(int signo)
{
	g_signal = signo;
	rl_on_new_line();
	rl_replace_line("", 0);
}

static void	reset_prompt(int signo)
{
	g_signal = signo;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signals_for_wait_cmd(void)
{
	signal(SIGINT, reset_prompt);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_for_run_cmd(void)
{
	signal(SIGINT, new_line);
	signal(SIGQUIT, new_line);
}
