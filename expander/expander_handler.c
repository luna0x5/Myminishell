/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 01:31:09 by hmoukit           #+#    #+#             */
/*   Updated: 2024/11/17 12:45:25 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"

char	*get_expanded_value(char *arg, int *i, t_expander *exp)
{
	int		start;
	char	*value;
	char	*expand;

	start = *i;
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
	while (arg[*i] && ft_isvalid(arg[*i]))
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
	(*i)++;
	if (arg[*i] == '\0')
		return (ft_strdup("$"));
	if (arg[*i] == '$')
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
	t_quote	quote;

	result = NULL;
	initialize_quote(&quote, &i, &result, ast->id->ident);
	while (quote.arg[i])
	{
		if (quote.arg[i] == '$')
		{
			expand = handle_variable_expansion(ast->id->ident, &i, exp);
			result = append_string(result, expand);
			free(expand);
			expand = NULL;
		}
		else if (ft_isquote(quote.arg[i]))
		{
			quote.quote_type = quote.arg[i];
			handle_quoted_string(&quote, exp);
		}
		else
			append_single_char(&quote, &i, &result);
	}
	update_ident(ast, result);
}
