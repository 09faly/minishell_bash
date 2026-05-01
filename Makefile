# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sarakoto <sarakoto@student.42antananari    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/04 09:31:54 by sarakoto          #+#    #+#              #
#    Updated: 2024/12/21 14:50:23 by sarakoto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT = ./libft/libft.a

NAME = minishell

SRCS = srcs/core/minishell.c \
		srcs/core/signal.c \
		srcs/parsing/parsing.c \
		srcs/parsing/handle_quotes.c \
		srcs/parsing/expand.c \
		srcs/parsing/expand_utils.c \
		srcs/parsing/tokenize.c \
		srcs/parsing/split_by_pipe.c \
		srcs/parsing/check.c \
		srcs/builtins/built_env.c \
		srcs/builtins/builtins_utils.c \
		srcs/builtins/builtins_utilis_two.c \
		srcs/builtins/built_export.c \
		srcs/builtins/export_utils.c \
		srcs/builtins/built_cd.c \
		srcs/builtins/built_exit.c \
		srcs/builtins/built_echo.c \
		srcs/builtins/built_pwd.c \
		srcs/builtins/built_unset.c \
		srcs/builtins/execute_builtins.c \
		srcs/execution/executing.c \
		srcs/execution/find_path.c \
		srcs/execution/executins_utils.c \
		srcs/execution/execute_cmd.c \
		srcs/execution/execute_pipe.c \
		srcs/execution/pipe.c \
		srcs/execution/pipe_utils.c \
		srcs/redirection/heredoc.c \
		srcs/redirection/heredoc_two.c \
		srcs/redirection/input_redir.c \
		srcs/redirection/output_redir.c \
		srcs/redirection/redirection.c \
		srcs/utils/mini_utils.c \
		srcs/utils/ms_utilis.c \
		srcs/utils/free_all.c

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I.

LDFLAGS = -lreadline

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
		@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -L./libft -lft -o $(NAME)

$(LIBFT):
		@$(MAKE) -C ./libft

clean:
		@$(MAKE) clean -C ./libft
		@rm -f $(OBJS)

fclean: clean
		@$(MAKE) fclean -C ./libft
		@rm -f $(NAME)

re: fclean all

.PHONY = all clean fclean re
