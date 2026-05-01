/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarakoto <sarakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 08:33:53 by sarakoto          #+#    #+#             */
/*   Updated: 2024/12/20 16:46:59 by sarakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	built_pwd(char **token)
{
	char	pwd[1024];

	if ((getcwd(pwd, sizeof(pwd)) != NULL) && (!check_redirection(token)))
		printf("%s\n", pwd);
	else
	{
		perror("getcwd");
		return (1);
	}
	return (0);
}
