/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarakoto <sarakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:34:31 by sarakoto          #+#    #+#             */
/*   Updated: 2024/12/21 14:27:35 by sarakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	len1 = 0;
	len2 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	if (s2)
		len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (!result)
	{
		if (s1)
			free(s1);
		return (NULL);
	}
	if (s1)
		ft_strcpy(result, s1);
	if (s2)
		ft_strcpy(result + len1, s2);
	if (s1)
		free(s1);
	return (result);
}

char	*get_env_value(char *var_name, t_env *my_env)
{
	size_t	len;
	int		i;

	i = 0;
	len = ft_strlen(var_name);
	while (i < my_env->count)
	{
		if (ft_strncmp(my_env->vars[i], var_name, len) == 0
			&& my_env->vars[i][len] == '=')
		{
			return (ft_strdup(my_env->vars[i] + len + 1));
		}
		i++;
	}
	return (NULL);
}

void	toggle_quotes(char c, int *in_single_quote, int *in_double_quote)
{
	if (c == '\'' && !*in_double_quote)
		*in_single_quote = !*in_single_quote;
	else if (c == '"' && !*in_single_quote)
		*in_double_quote = !*in_double_quote;
}

char	*expand_exit_status(char *expanded, t_env *my_env, int *i)
{
	char	*exit_status;

	exit_status = ft_itoa(my_env->last_exit_status);
	expanded = ft_strjoin_free(expanded, exit_status);
	free(exit_status);
	(*i)++;
	return (expanded);
}

char	*expand_alnum(t_expand_context *ctx)
{
	char	*var_name;
	char	*env_value;

	var_name = NULL;
	env_value = NULL;
	ctx->start = ctx->i;
	while (ft_isalnum(ctx->cmd[ctx->i]) || ctx->cmd[ctx->i] == '_')
		(ctx->i)++;
	var_name = ft_substr(ctx->cmd, ctx->start, ctx->i - ctx->start);
	if (!var_name)
		return (ctx->expanded);
	env_value = get_env_value(var_name, ctx->my_env);
	if (env_value)
	{
		ctx->expanded = ft_strjoin_free(ctx->expanded, env_value);
		free(env_value);
	}
	else
		ctx->expanded = ft_strjoin_free(ctx->expanded, "");
	free(var_name);
	return (ctx->expanded);
}
