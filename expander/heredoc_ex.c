/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_ex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 01:49:58 by hmoukit           #+#    #+#             */
/*   Updated: 2024/12/02 20:24:01 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"
#include <stdio.h>
char	*remove_quotes(char	*delim)
{
	char	*unquoted;
	int		i;
	int		quote_type;

	i = 1;
	quote_type = ft_isquote(*delim);
	if (quote_type == 0)
	{
		unquoted = ft_strdup(delim);
		return (unquoted);
	}
	while (delim[i])
	{
		if (quote_type == 1 && delim[i] == '\'')
			break ;
		if (quote_type == 2 && delim[i] == '"')
			break ;
		i++;
	}
	unquoted = ft_substr(delim, 1, i - 1);
	return (unquoted);
}

char	*get_expanded(t_parser *node, int *i, t_expander *exp)
{
	char	*expand;
	char	*value;
	int		start;

	start = ++(*i);
	while (node->id->ident[*i] && ft_isvalid(node->id->ident[*i]))
		(*i)++;
	value = ft_substr(node->id->ident, start, *i - start);
	expand = expand_var(value, exp);
	free(value);
	value = NULL;
	if (expand)
		return (expand);
	return (ft_strdup(""));
}

void	heredoc_expand_helper(t_parser *node, char *result)
{
	free(node->id->ident);
	node->id->ident = NULL;
	if (!result)
	{
		node->id->ident = ft_strdup("");
		return ;
	}
	node->id->ident = ft_strdup(result);
	free(result);
	result = NULL;
}

void	heredoc_expand(t_parser *node, t_expander *exp)
{
	char	*expanded;
	char	*result;
	int		i;

	i = 0;
	expanded = NULL;
	result = NULL;
	if (ft_isquote(node->id->ident[i]) == 1)
		return ;
	while (node->id->ident[i])
	{
		if (node->id->ident[i] == '$' && ft_isvalid(node->id->ident[i + 1]))
		{
			expanded = get_expanded(node, &i, exp);
			result = append_string(result, expanded);
		}
		else if (node->id->ident[i] != '$' || (node->id->ident[i] == '$' && !ft_isvalid(node->id->ident[i + 1])))
			append_single_char(node->id->ident, &i, &result);
		else
			i++;
	}
	heredoc_expand_helper(node, result);
}

void	handle_heredoc_ex(t_parser *ast, t_expander *exp)
{
	if (ast->left)
	{
		ast = ast->left;
		if (ast->right)
			ast = ast->right;
		if (ast->id && (ast->id->id_type == ARG || ast->id->id_type == RFILE))
			process_string(ast, exp);
	}
}
