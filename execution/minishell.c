/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 17:52:26 by hmoukit           #+#    #+#             */
/*   Updated: 2024/11/27 10:54:57 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// const char *n_type(t_identifier type)
// {
// 	switch (type)
// 	{
// 		case CMD: return "CMD";
// 		case ARG: return "ARG";
// 		case REDIRECTION: return "REDIRECTION";
// 		case RFILE: return "RFILE";
// 		case PIPELINE: return "PIPE";
// 		default: return "UNKNOWN";
// 	}
// }
// void print_ast(t_parser *node, int level, char *position)
// {
// 	if (node == NULL)
// 	{
// 		printf("%*s%s: NULL\n", level * 4, "", position);
// 		return;
// 	}
// 	printf("%*s%s: %s", level * 4, "", position, n_type(node->id->id_type));
// 	if (node->id->id_type == REDIRECTION)
// 		printf(": %d", node->io_type);
// 	if (node->id->ident)
// 		printf(": %s", node->id->ident);
// 	printf("\n");
// 	print_ast(node->left, level + 1, "Left");
// 	print_ast(node->right, level + 1, "Right");
// }
void	free_token_tree(t_minishell *mini, char **line)
{
	free_line(line);
	token_clear(&(mini->tokens));
	free_tree(mini->ast);
	free(mini->ast);
	mini->ast = NULL;
}

void	signals_init(void)
{
	signal(SIGINT, ft_sigint_handler);
	signal(SIGQUIT, ft_sigquit_handler);
}

void	mini_init(t_minishell **mini, char **line)
{
	signals_init();
	*line = NULL;
	*mini = malloc(sizeof(t_minishell));
	(*mini)->exp = malloc(sizeof(t_expander));
	(*mini)->exp->env = make_env();
	(*mini)->pwd = ft_strdup(ft_getenv("PWD", (*mini)->exp));
	(*mini)->oldpwd = ft_strdup(ft_getenv("OLDPWD", (*mini)->exp));
	(*mini)->home = ft_strdup(ft_getenv("HOME", (*mini)->exp));
	(*mini)->exp->exit_s = 0;
}

int	build_mini(t_minishell *mini, char **line, char *tmp)
{
	mini->tokens = make_tokens(&tmp);
	if (!mini->tokens)
	{
		free_line(line);
		return (0);
	}
	mini->ast = make_ast(mini->tokens);
	if (!mini->ast)
	{
		free_line(line);
		token_clear(&(mini->tokens));
		return (0);
	}
	expand_ast(mini->ast, mini->exp);
	// print_ast(mini->ast, 0, "ROOT");
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
	mini_init(&mini, &line);
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
		// system("leaks minishell");
	}
	cleanup_mini(mini);
	rl_clear_history();
	return (0);
}
