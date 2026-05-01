/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarakoto <sarakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 07:52:17 by sarakoto          #+#    #+#             */
/*   Updated: 2024/12/21 14:27:41 by sarakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_variable(t_expand_context *ctx)
{
	if (ctx->cmd[ctx->i] == '?')
		ctx->expanded = expand_exit_status(ctx->expanded, ctx->my_env, &ctx->i);
	else if (ft_isalnum(ctx->cmd[ctx->i]) || ctx->cmd[ctx->i] == '_')
		ctx->expanded = expand_alnum(ctx);
	ctx->start = ctx->i;
	return (ctx->expanded);
}

char	*expand_append_literal(t_expand_context *ctx)
{
	char	*tmp;

	if (ctx->i > ctx->start)
	{
		tmp = ft_substr(ctx->cmd, ctx->start, ctx->i - ctx->start);
		ctx->expanded = ft_strjoin_free(ctx->expanded, tmp);
		free(tmp);
	}
	return (ctx->expanded);
}

char	*dollar(t_expand_context *ctx)
{
	ctx->expanded = expand_append_literal(ctx);
	(ctx->i)++;
	ctx->expanded = expand_variable(ctx);
	return (ctx->expanded);
}

char	*expand(char *cmd, t_env *my_env)
{
	t_expand_context	ctx;
	int					in_double_quote;
	int					in_single_quote;

	in_double_quote = 0;
	in_single_quote = 0;
	ctx.cmd = cmd;
	ctx.i = 0;
	ctx.start = 0;
	ctx.my_env = my_env;
	ctx.expanded = ft_strdup("");
	while (ctx.cmd[ctx.i])
	{
		toggle_quotes(ctx.cmd[ctx.i], &in_single_quote, &in_double_quote);
		if (in_single_quote)
		{
			ctx.i++;
			continue ;
		}
		if (ctx.cmd[ctx.i] == '$')
			ctx.expanded = dollar(&ctx);
		else
			ctx.i++;
	}
	return (expand_append_literal(&ctx));
}
