/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipelines_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:35:37 by hmoukit           #+#    #+#             */
/*   Updated: 2024/11/28 04:12:19 by hmoukit          ###   ########.fr       */
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
		perror("pipe");
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

void	traverse_and_handle_heredocs(t_minishell *mini, t_parser *node)
{
	if (!node)
		return ;
	if (node->id->id_type == REDIRECTION && node->io_type == HEREDOC)
	{
		mini->s_stdin = dup(STDIN_FILENO);
		if (!handle_heredoc(node))
		{
			perror("Failed to handle heredoc");
			return ;
		}
		dup2(mini->s_stdin, STDIN_FILENO);
		close(mini->s_stdin);
	}
	traverse_and_handle_heredocs(mini, node->left);
	traverse_and_handle_heredocs(mini, node->right);
}
