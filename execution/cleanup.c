/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 19:03:01 by hmoukit           #+#    #+#             */
/*   Updated: 2024/11/13 11:58:08 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tree(t_parser *ast)
{
	if (!ast)
		return ;
	if (ast->id->ident)
	{
		free(ast->id->ident);
		ast->id->ident = NULL;
	}
	free(ast->id);
	ast->id = NULL;
	free_tree(ast->left);
	free_tree(ast->right);
	free(ast->left);
	ast->left = NULL;
	free(ast->right);
	ast->right = NULL;
}

 void	free_env(t_env **env)
{
	t_env	*tmp;
	t_env	*current;

	if (!env || !*env)
		return ;
	current = *env;
	while (current)
	{
		tmp = current;
		current = current->next;
		free(tmp->data);
		tmp->data = NULL;
		free(tmp);
		tmp = NULL;
	}
	*env = NULL;
}

void	free_line(char **line)
{
	free(*line);
	*line = NULL;
}

void	cleanup_mini(t_minishell *mini)
{
	free_env(&(mini->exp->env));
	mini->exp->env = NULL;
	free(mini->exp);
	mini->exp = NULL;
	free(mini);
	mini = NULL;
}
