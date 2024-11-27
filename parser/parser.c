/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 08:46:43 by hmoukit           #+#    #+#             */
/*   Updated: 2024/11/27 01:45:25 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

static t_parser	*parse_expression(int prec_level, t_token **tokens)
{
	t_parser	*left;
	t_parser	*right;
	t_token		*operator;

	left = parse_primary(tokens);
	if (!left)
	{
		operator = *tokens;
		if (check_redir(operator->token_type))
		{
			if (!handle_redir(&left, tokens))
				left = NULL;
		}
	}
	while (*tokens && assign_prec(*tokens) >= prec_level)
	{
		operator = *tokens;
		if (check_redir(operator->token_type))
		{
			if (!handle_redir(&left, tokens))
			{
				left = NULL;
				break ;
			}
		}
		else
		{
			*tokens = (*tokens)->next;
			right = parse_expression(assign_prec(operator) + 1, tokens);
			left = create_node(operator, left, right);
			if (!left)
			{
				left = NULL;
				break ;
			}
		}
	}
	return (left);
}

t_parser	*make_ast(t_token *tokens)
{
	t_parser	*ast;

	if (!tokens)
		return (NULL);
	ast = parse_expression(1, &tokens);
	return (ast);
}
