/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarakoto <sarakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 08:32:24 by sarakoto          #+#    #+#             */
/*   Updated: 2024/12/20 09:56:30 by sarakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	built_env(t_env *my_env, char **token)
{
	int	i;

	i = 0;
	while (i < my_env->count && !check_redirection(token))
	{
		printf("%s\n", my_env->vars[i]);
		i++;
	}
}
