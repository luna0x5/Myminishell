/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 01:31:09 by hmoukit           #+#    #+#             */
/*   Updated: 2024/11/30 17:54:47 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"

void	check_quote(char *arg, int *i, char **result, t_expander *exp)
{
	if (ft_isquote(arg[*i]) == 1)
		handle_single_quote(arg, result, i, 0);
	else if (ft_isquote(arg[*i]) == 2)
		handle_double_quote(arg, result, i, exp);
}
char	*get_expanded_value(char *arg, int *i, t_expander *exp)
{
	int		start;
	char	*value;
	char	*expand;

	start = *i;
	expand = NULL;
	if (ft_isdigit(arg[*i]) || arg[*i] == '@')
	{
		(*i)++;
		return (ft_strdup(""));
	}
	if (arg[*i] == '?' && exp)
	{
		(*i)++;
		return (ft_itoa(exp->exit_s));
	}
	if (ft_isquote(arg[*i]))
	{
		check_quote(arg, i, &value, exp);
		return (value);
	}
	while (arg[*i] && !ft_isquote(arg[*i]) && arg[*i] != '$' && ft_isvalid(arg[*i]))
		(*i)++;
	value = ft_substr(arg, start, *i - start);
	expand = expand_var(value, exp);
	free(value);
	if (expand)
		return (expand);
	else
		return (ft_strdup(""));
}

char	*handle_variable_expansion(char *arg, int *i, t_expander *exp)
{
	if (arg[*i + 1] && arg[*i + 1] != '?' && !ft_isquote(arg[*i + 1]) && !ft_isvalid(arg[*i + 1]))
	{
		(*i)++;
		return (ft_strdup("$"));
	}
	(*i)++;
	if (!arg[*i])
		return (ft_strdup("$"));
	if (arg[*i] == '$' && arg[*i + 1] && ft_isvalid(arg[*i + 1]))
	{
		(*i)++;
		return (ft_strdup("$"));
	}
	return (get_expanded_value(arg, i, exp));
}

void	update_ident(t_parser *ast, char *result)
{
	free(ast->id->ident);
	ast->id->ident = NULL;
	ast->id->ident = result;
}

void	process_string(t_parser *ast, t_expander *exp)
{
	int		i;
	char	*result;
	char	*expand;

	result = NULL;
	i = 0;
	while (ast->id->ident[i])
	{
		if (ast->id->ident[i] == '$')
		{
			expand = handle_variable_expansion(ast->id->ident, &i, exp);
			result = append_string(result, expand);
			free(expand);
			expand = NULL;
		}
		else if (ft_isquote(ast->id->ident[i]))
			check_quote(ast->id->ident, &i, &result, exp);
		else
			append_single_char(ast->id->ident, &i, &result);
	}
	update_ident(ast, result);
}
