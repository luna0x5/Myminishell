/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quoted_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 00:08:25 by hmoukit           #+#    #+#             */
/*   Updated: 2024/11/30 17:54:56 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"

void	handle_single_quote(char *arg, char **result, int *i, int check)
{
	int		start;
	char	*new_val;
	char	*tmp;

	start = (*i)++;
	while (arg[*i] && arg[*i] != '\'')
		(*i)++;
	if (!check)
		new_val = ft_substr(arg, start + 1, (*i) - start - 1);
	if (check)
		new_val = ft_substr(arg, start, (*i) - start + 1);
	tmp = *result;
	*result = ft_strjoin(tmp, new_val);
	free(tmp);
	tmp = NULL;
	free(new_val);
	new_val = NULL;
	(*i)++;
}

int	closer_quote(char *str, int j)
{
	int i;

	i = j;
	i++;
	while (str[i] && str[i] != '\'')
		i++;
	if (!str[i])
		return (0);
	return (1);
}

void	handle_double_quote(char *arg, char **result, int *i, t_expander *exp)
{
    char	*expand;

	(*i)++;
	if (arg[*i] == '"')
		*result = append_string(*result, "");
    while (arg[*i] && arg[*i] != '"')
    {
        if (arg[*i] == '$')
        {
			if (arg[*i + 1] && arg[*i + 1] == '"')
			{
				*result = append_string(*result, "$");
				break ;
			}
			else if (arg[*i + 1] && arg[*i + 1] == '\'' && closer_quote(arg, *i + 1))
			{
				(*i)++;
				*result = append_string(*result, "$");
				handle_single_quote(arg, result, i, 1);
				break;
			}
            expand = handle_variable_expansion(arg, i, exp);
            *result = append_string(*result, expand);
            free(expand);
            expand = NULL;
        }
		else if (arg[*i] == '\'' && closer_quote(arg, *i))
			handle_single_quote(arg, result, i, 1);
		else
            append_single_char(arg, i, result);
    }
	if (arg[*i])
	    (*i)++;
}
