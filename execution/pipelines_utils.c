/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelines_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:35:37 by hmoukit           #+#    #+#             */
/*   Updated: 2024/12/05 14:59:42 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_redirections_in_process(t_minishell *mini, t_parser *node)
{
	if (!multiple_in_redirections(mini, node))
		return (0);
	if (!multiple_out_redirections(mini, node))
		return (0);
	find_execute_cmd(mini, node);
	return (1);
}

int	setup_pipe(int pfds[2])
{
	if (pipe(pfds) == -1)
	{
		perror("SHELL: pipe");
		return (-1);
	}
	return (0);
}

void	wait_for_children(int pid_left, int pid_right, unsigned char *exit)
{
	int	status;

	status = 0;
	waitpid(pid_left, &status, 0);
	waitpid(pid_right, &status, 0);
	*exit = get_exit_status(status);
}

void	handle_fork(int pid, int *status, t_minishell *mini, t_parser *node)
{
	if (pid == 0)
	{
		if (!handle_heredoc(node, mini->exp))
			exit(1);
		exit(0);
	}
	else
	{
		waitpid(pid, status, 0);
		get_exit_status(*status);
		mini->exp->exit_s = *status;
	}
}

void	traverse_and_handle_heredocs(t_minishell *mini, t_parser *node)
{
	pid_t	pid;
	int		status;

	if (!node)
		return ;
	status = 0;
	if (node->id->id_type == REDIRECTION && node->io_type == HEREDOC)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("SHELL: heredoc: Failed to fork");
			return ;
		}
		handle_fork(pid, &status, mini, node);
	}
	traverse_and_handle_heredocs(mini, node->left);
	traverse_and_handle_heredocs(mini, node->right);
}
