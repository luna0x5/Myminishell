/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quoted_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 00:08:25 by hmoukit           #+#    #+#             */
/*   Updated: 2024/11/28 02:26:27 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"

void	handle_single_quote(char *arg, char **result, int *i)
{
	int		start;
	char	*new_val;

	start = (*i)++;
	while (arg[*i] && arg[*i] != '\'')
		(*i)++;
	new_val = ft_substr(arg, start + 1, (*i) - start - 1);
	*result = ft_strjoin(*result, new_val);
	free(new_val);
	new_val = NULL;
	(*i)++;
}

void	handle_double_quote(char *arg, char **result, int *i, t_expander *exp)
{
	int		start;
	char	*expand;

	start = (*i)++;
	while (arg[*i] && arg[*i] != '"')
	{
		if (arg[*i] == '$')
		{
			expand = handle_variable_expansion(arg, i, exp);
			*result = append_string(*result, expand);
			free(expand);
			expand = NULL;
		}
		else
			append_single_char(arg, i, result);
	}
	(*i)++;
}
