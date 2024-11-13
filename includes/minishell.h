/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 12:08:39 by souchane          #+#    #+#             */
/*   Updated: 2024/11/13 11:58:00 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <limits.h>
#include <signal.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <fcntl.h>
#include <stdarg.h>
# include <stdio.h>
# include <readline/history.h>
#include <readline/readline.h>
# include "../includes/expander.h"

typedef struct s_minishell
{
	int			s_stdin;
	t_env		*env;
	char		*cmd;
	char		**args;
	t_expander	*exp;
	t_parser	*ast;
	t_token		*tokens;
}				t_minishell;

char	*get_path(char *cmd);
int		get_exit_status(int status);
t_env	*make_env(void);
int		count_arg(t_parser *ast);
char	**make_env_2d(t_env *env);

void	handle_exec_simple_cmd(t_minishell *node, t_parser *ast, int check);
void	ft_pipelines(t_minishell *mini, t_parser *ast);
void	handle_exec_redirections(t_minishell *mini, t_parser *node);
int		handle_builtin(t_minishell *node);

void	executer(t_minishell *mini);

int		handle_input(t_parser *node);
int		handle_output(t_parser *node);
int		handle_append(t_parser *node);
int		handle_heredoc(t_parser *node);

int		open_out(t_parser *n);
int		open_append(t_parser *n);

int		handle_type_redirection(t_parser *node, t_red_type type);
void	find_execute_cmd(t_minishell *mini, t_parser *node);
int		open_in_files(t_minishell *mini, t_parser *node);
int		open_out_files(t_minishell *mini, t_parser *node);
void	traverse_and_handle_heredocs(t_minishell *mini, t_parser *node);


void	multiple_in_redirections(t_minishell *mini, t_parser *node);
void	multiple_out_redirections(t_minishell *mini, t_parser *node);

void	free_node(t_minishell *mini, t_env *env);

void	ft_sigint_handler(int num);
void	ft_eof_handler(void);
void	ft_sigquit_handler(int num);

void	handle_redirections_in_process(t_minishell *mini, t_parser *node);
int		setup_pipe(int pfds[2]);
void	wait_for_children(int pid_left, int pid_right, unsigned int *exit);
void	traverse_and_handle_heredocs(t_minishell *mini, t_parser *node);

int	handle_builtin(t_minishell *node);
int	fork_and_exec(char *path, char **args, char **env_2d);
int	exec_simple_cmd(t_minishell *node, char **env_2d);
void	exec_no_fork(t_minishell *node, char **env_2d, char *path);

void	free_tree(t_parser *ast);
void	free_env(t_env **env);
void	cleanup_mini(t_minishell *mini);
void	free_line(char **line);

#endif