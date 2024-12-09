/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:52:26 by hmoukit           #+#    #+#             */
/*   Updated: 2024/12/09 01:25:23 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_token_tree(t_minishell *mini, char **line)
{
	free_line(line);
	token_clear(&(mini->tokens));
	free_tree(mini->ast);
	free(mini->ast);
	mini->ast = NULL;
}

int	mini_init(t_minishell **mini, char **line)
{
	*line = NULL;
	*mini = malloc(sizeof(t_minishell));
	if (!*mini)
		return (0);
	(*mini)->exp = malloc(sizeof(t_exp));
	if (!(*mini)->exp)
		return (0);
	(*mini)->exp->env = make_env();
	if (!(*mini)->exp->env)
		return (0);
	(*mini)->pwd = ft_strdup(ft_getenv("PWD", (*mini)->exp));
	if (!(*mini)->pwd)
		return (0);
	(*mini)->oldpwd = ft_strdup(ft_getenv("OLDPWD", (*mini)->exp));
	if (!(*mini)->oldpwd)
		return (0);
	(*mini)->path = ft_strdup("/Users/hmoukit/bin:/Users/hmoukit/homebrew/bin"
			":/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki"
			":/Library/Apple/usr/bin:/Users/hmoukit/bin"
			":/Users/hmoukit/homebrew/bin");
	if (!(*mini)->path)
		return (0);
	(*mini)->args = NULL;
	(*mini)->ast = NULL;
	(*mini)->tokens = NULL;
}

int	build_mini(t_minishell *mini, char **line, char *tmp)
{
	mini->tokens = make_tokens(&tmp);
	if (!mini->tokens)
	{
		free_line(line);
		mini->exp->exit_s = 2;
		return (0);
	}
	mini->ast = make_ast(mini->tokens);
	if (!mini->ast)
	{
		free_line(line);
		token_clear(&(mini->tokens));
		return (0);
	}
	if (!expand_ast(mini->ast, mini->exp))
	{
		free_token_tree(mini, line);
		return (0);
	}
	executer(mini);
	free_token_tree(mini, line);
	return (1);
}

int	main(void)
{
	char		*line;
	char		*tmp;
	t_minishell	*mini;

	mini = NULL;
	if (!mini_init(&mini, &line))
		return (1);
	mini->exp->exit_s = 0;
	mini->args = NULL;
	mini->ast = NULL;
	mini->tokens = NULL;
	signal(SIGINT, ft_sigint_handler);
	signal(SIGQUIT, ft_sigquit_handler);
	while (1)
	{
		line = readline("SHELL:$");
		tmp = line;
		if (!tmp)
			ft_eof_handler();
		if (*tmp)
		{
			add_history(tmp);
			build_mini(mini, &line, tmp);
		}
		free_line(&line);
	}
	cleanup_mini(mini);
	rl_clear_history();
	return (0);
}
