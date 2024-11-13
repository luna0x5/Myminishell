/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:29:02 by hmoukit           #+#    #+#             */
/*   Updated: 2024/11/12 02:00:03 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	executer(t_minishell *mini)
{
	if (mini->ast->id->id_type == PIPELINE)
	{
		mini->s_stdin = dup(STDIN_FILENO);
		traverse_and_handle_heredocs(mini, mini->ast);
		ft_pipelines(mini, mini->ast);
		return ;
	}
	else if (mini->ast->id->id_type == REDIRECTION)
	{
		mini->s_stdin = dup(STDIN_FILENO);
		handle_exec_redirections(mini, mini->ast);
		return ;
	}
	else if (mini->ast->id->id_type == CMD)
	{
		handle_exec_simple_cmd(mini, mini->ast, 0);
	}
	free_args(mini->args);
}
