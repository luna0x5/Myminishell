/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_ex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 01:49:58 by hmoukit           #+#    #+#             */
/*   Updated: 2024/12/09 22:08:29 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"

static int	unquoted_string(char **line, int *i, char **result)
{
	// error , need free result
	int		check;
	int		start;
	char	*unquoted;
	check = ft_isquote((*line)[*i]);
	if (check)
		(*i)++;
	start = *i;
	if (check == 1)
	{
		while ((*line)[*i] && (*line)[*i] != '\'')
			(*i)++;
		if ((*line)[*i] != '\'')
			return (write(2, "SHELL: SYNTAX ERROR: closing quote\n", 35), 0);
		unquoted = ft_substr(*line, start, *i - start);
		*result = ft_strjoin(*result, unquoted);
	}
	else if (check == 2)
	{
		while ((*line)[*i] && (*line)[*i] != '"')
			(*i)++;
		if ((*line)[*i] != '"')
			return (write(2, "SHELL: SYNTAX ERROR: closing quote\n", 35), 0);
		unquoted = ft_substr(*line, start, *i - start);
		*result = ft_strjoin(*result, unquoted);
	}
	else
	{
		while ((*line)[*i] && !ft_isquote((*line)[*i]))
			(*i)++;
		unquoted = ft_substr(*line, start, *i - start);
		*result = ft_strjoin(*result, unquoted);
	}
	return (1);
}

char	*remove_quotes(char *delim)
{
	char	*result;
	int		i;
	int		quote_type;

	quote_type = ft_isquote(*delim);
	if (quote_type == 0)
	{
		result = ft_strdup(delim);
		return (result);
	}
	result = ft_strdup("");
	i = 0;
	while (delim[i])
	{
		if (!unquoted_string(&delim, &i, &result))
			return (NULL);
		if (delim[i])
			i++;
	}
	return (result);
}

char	*get_expanded(t_parser *node, int *i, t_exp *exp)
{
	char	*expand;
	char	*value;
	int		start;

	start = ++(*i);
	while (node->id->ident[*i] && ft_isvalid(node->id->ident[*i]))
		(*i)++;
	value = ft_substr(node->id->ident, start, *i - start);
	if (!value)
		return (NULL);
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

void	heredoc_expand(t_parser *node, t_exp *exp)
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
		else if (node->id->ident[i] != '$' || (node->id->ident[i] == '$'
				&& !ft_isvalid(node->id->ident[i + 1])))
			append_single_char(node->id->ident, &i, &result);
		else
			i++;
	}
	heredoc_expand_helper(node, result);
}

void	handle_heredoc_ex(t_parser *ast, t_exp *exp)
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
