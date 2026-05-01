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

SRCS = minishell.c \
		parsing.c \
		handle_quotes.c \
		built_env.c \
		builtins_utils.c \
		executing.c \
		find_path.c \
		expand.c \
		signal.c \
		heredoc.c \
		mini_utils.c \
		built_export.c \
		export_utils.c \
		built_cd.c \
		built_exit.c \
		built_echo.c \
		built_pwd.c \
		builtins_utilis_two.c \
		ms_utilis.c \
		built_unset.c \
		execute_builtins.c \
		check.c \
		free_all.c \
		pipe.c \
		executins_utils.c  \
		execute_cmd.c \
		expand_utils.c \
		execute_pipe.c \
		tokenize.c \
		split_by_pipe.c \
		input_redir.c \
		output_redir.c \
		heredoc_two.c \
		redirection.c \
		pipe_utils.c 

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

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
