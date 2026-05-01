/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarakoto <sarakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 08:32:16 by sarakoto          #+#    #+#             */
/*   Updated: 2024/12/20 08:32:16 by sarakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_flags(char **token, int *newline)
{
	int	i;
	int	j;

	i = 1;
	while (token[i] && token[i][0] == '-' && token[i][1] == 'n')
	{
		j = 2;
		while (token[i][j] == 'n')
			j++;
		if (token[i][j] == '\0')
		{
			*newline = 0;
			i++;
		}
		else
			break ;
	}
	return (i);
}

static void	print_token(char *token, t_env *my_env)
{
	char	*literal;
	char	*expanded;

	if (token[0] == '\'' && token[ft_strlen(token) - 1] == '\'')
	{
		literal = ft_substr(token, 1, ft_strlen(token) - 2);
		printf("%s", literal);
		free(literal);
	}
	else
	{
		expanded = expand(token, my_env);
		if (expanded)
		{
			printf("%s", expanded);
			free(expanded);
		}
	}
}

void	built_echo(char **token, t_env *my_env)
{
	int	i;
	int	newline;

	newline = 1;
	i = parse_flags(token, &newline);
	while (token[i])
	{
		print_token(token[i], my_env);
		if (token[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	my_env->last_exit_status = 0;
}
