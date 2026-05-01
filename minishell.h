/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarakoto <sarakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 09:54:10 by sarakoto          #+#    #+#             */
/*   Updated: 2024/12/21 14:52:16 by sarakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_env
{
	char						**vars;
	int							count;
	char						**exported;
	int							export_count;
	int							last_exit_status;
	int							*fd_heredoc;
	int							hd;
	int							fd_in;
	int							count_fd_heredoc;
}								t_env;

typedef struct s_expand_context
{
	char						*cmd;
	int							i;
	int							start;
	t_env						*my_env;
	char						*expanded;
}								t_expand_context;

typedef struct s_token
{
	int							sq;
	int							dq;
	int							i;
	int							j;
	int							k;

}								t_token;

typedef struct s_p
{
	int							sq;
	int							dq;
	int							i;
	int							j;
	int							k;

}								t_p;

extern volatile sig_atomic_t	g_signal;

void							ft_free(char **split);
char							**tokenize(char *command);
void							execute_pipe(char **commands, t_env *my_env);
char							**split_by_pipe(char *input, t_env *my_env);
char							*ft_strtok(char *str, const char *delim);
char							*find_command_path(char *cmd, t_env *my_env);
int								check_unclosed_quotes(const char *line);
char							*handle_quotes(const char *line);
int								execute_builtins(char **token, t_env **my_env);
int								is_builtins(char *cmd);
int								handle_redirection(char **tokens,
									t_env *my_env);
char							*ft_strcpy(char *dest, char *src);
int								ft_strcmp(char *s1, char *s2);
char							*process_cmd(char *token, t_env *my_env);
int								qqc(char *command, int set);
char							*take_path_in_env(t_env *my_env);
void							ft_free_env(t_env *my_env);
char							*find_command_path(char *cmd, t_env *my_env);
t_env							*init_env(char **env);
bool							variable_name_in_export(char *name);
void							add_back(t_env **my_env, char *new_variable);
int								check_redirection(char **token);
int								built_cd(char **token, t_env *my_env);
int								built_pwd(char **token);
void							built_echo(char **token, t_env *my_env);
void							built_exit(char **input, t_env *my_env);
char							*remove_quotes(char *str);
void							built_env(t_env *my_env, char **token);
void							built_export_without_argument(t_env *my_env);
int								built_export_with_argument(t_env **my_env,
									char *var);
void							built_export_multiple(t_env **my_env,
									char **vars);
int								built_unset(t_env *my_env, char *name);
void							add_back_exported(t_env **my_env,
									char *new_var);
void							add_new_export(t_env **my_env, char *var);
void							update_in_vars_or_add(t_env **my_env, char *var,
									int len);
void							remove_from_exported(t_env **my_env, char *var,
									int len);
int								execute_builtins(char **token, t_env **my_env);
int								execut_extern_cmd(char **token, t_env *my_env);
int								execute_command(char *input, t_env *my_env);
void							signals_for_run_cmd(void);
void							signals_for_wait_cmd(void);
char							*expand(char *cmd, t_env *my_env);
char							*replace_env_variables(char *command,
									t_env *my_env);
int								check_if_cmd(char *path, char *cmd,
									t_env *my_env);
int								handle_heredoc(char *delimiter, t_env *my_env);
void							remove_tokens(char **tokens, int index,
									int count);
void							fd_hrdoc(char **tokens, t_env *my_env, int hd);
int								ft_strlen_hrd(char **command);
void							close_all_heredoc_fds(t_env *my_env);
void							cleanup_my_env(t_env *my_env);
char							*ft_strcat(char *dest, char *src);
bool							check_numeric(char *str);
void							built_unset_multiple(char **token,
									t_env **my_env);
int								builtins(char **token, t_env **my_env);
int								execute_builtins(char **token, t_env **my_env);
int								is_invalid_redirection(char **tokens);
int								validate_redirections(char **tokens,
									t_env *my_env);
void							cmd_not_found(char **token, t_env *my_env,
									char *command_path);
void							is_directory(char **token, t_env *my_env);
void							free_success(char **token, t_env *my_env);
void							wait_process(t_env *my_env, pid_t pid);
void							error_process(t_env *my_env);
void							execute_if_builtins(char **token,
									t_env *my_env);
void							execute_not_builtins(char **token,
									t_env *my_env);
void							ft_close(t_env *my_env);
bool							validate_pipe_syntax(char *input);
void							toggle_quotes(char c, int *in_single_quote,
									int *in_double_quote);
int								handle_syntax_error(t_env *my_env);
char							*get_expand_input(char *input, t_env *my_env,
									int is_heredoc);

void							execute_not_builtins(char **token,
									t_env *my_env);
void							execute_if_builtins(char **token,
									t_env *my_env);
int								handle_single_pipe(char **pipe_cmd,
									t_env *my_env);
int								handle_heredoc_and_syntax(char *input,
									t_env *my_env, int *is_heredoc);
int								handle_pipe_commands(char **pipe_cmd,
									t_env *my_env);

char							*ft_strjoin_free(char *s1, char *s2);
char							*get_env_value(char *var_name, t_env *my_env);
char							*expand_exit_status(char *expanded,
									t_env *my_env, int *i);
char							*expand_alnum(t_expand_context *ctx);
void							clean_and_exit(char **token, t_env *my_env);
void							toggle_quotes(char c, int *in_single_quote,
									int *in_double_quote);

int								handle_heredoc_redirection(char **tokens, int i,
									t_env *my_env, int *input_fd);
int								handle_input_redirection(char **tokens, int i,
									int *input_fd);
int								handle_truncate_redirection(char **tokens,
									int i, int *fd);
int								handle_append_redirection(char **tokens, int i,
									int *fd);
int								check_file_redirection(char *token);
void							wait_pipe(t_env *my_env);
void							pipe_error(t_env *my_env);
void							pipe_loop(char **commands, t_env *my_env);
void							clean_all(int pipefd[2], char **tokens,
									char **commands, t_env *my_env);
void							do_cmd(int pipefd[2], char **tokens,
									char **commands, t_env *my_env);
void							init_token(char ***tokens, int *i,
									char **commands, t_env *my_env);
void							pipe_loop(char **commands, t_env *my_env);
void							dup_proces(int pipefd[2], char **commands,
									t_env *my_env, int *i);
void							after_exe(int pipefd[2], int *i,
									char **commands, t_env *my_env);
void							clean_redir(int pipefd[2], char **tokens,
									char **commands, t_env *my_env);
void							execute_exec(int pipefd[2], char **tokens,
									char **commands, t_env *my_env);
void							execute_builtin_pipe(int pipefd[2],
									char **tokens, char **commands,
									t_env *my_env);
#endif