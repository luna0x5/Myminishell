/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:44:37 by hmoukit           #+#    #+#             */
/*   Updated: 2024/11/12 01:20:24 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	single_redirection(t_parser *node)
{
	if (!handle_type_redirection(node, node->io_type))
		return ;
}

void	multiple_in_redirections(t_minishell *mini, t_parser *node)
{
	static int	first;

	if (!node)
		return ;
	if (node->id->id_type == REDIRECTION)
	{
		if (node->io_type == INPUT || node->io_type == HEREDOC)
		{
			if (!first)
			{
				single_redirection(node);
				first = 1;
			}
			if (first && node->left && node->left->id->id_type == REDIRECTION)
			{
				if (!open_in_files(mini, node->left))
					return ;
			}
		}
		multiple_in_redirections(mini, node->left);
		first = 0;
	}
}

void	multiple_out_redirections(t_minishell *mini, t_parser *node)
{
	static int	first;

	if (!node)
		return ;
	if (node->id->id_type == REDIRECTION)
	{
		if (node->io_type == OUTPUT || node->io_type == APPEND)
		{
			if (!first)
			{
				single_redirection(node);
				first = 1;
			}
			if (first && node->left && node->left->id->id_type == REDIRECTION)
			{
				if (!open_out_files(mini, node->left))
					return ;
			}
		}
		multiple_out_redirections(mini, node->left);
		first = 0;
	}
}

void	handle_exec_redirections(t_minishell *mini, t_parser *node)
{
	int	pid;
	int	status;

	pid = fork();
	status = 0;
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	else if (pid == 0)
	{
		multiple_in_redirections(mini, node);
		multiple_out_redirections(mini, node);
		find_execute_cmd(mini, node);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		mini->exp->exit_s = get_exit_status(status);
	}
}
