/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:42:53 by hmoukit           #+#    #+#             */
/*   Updated: 2024/11/10 00:50:00 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"

int	ft_isvalid(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

char	*expand_var(char *arg, t_expander *exp)
{
	char	*env_var;
	char	*result;

	if (!arg && !(*arg))
		return ("$");
	env_var = ft_getenv(arg, exp);
	if (!env_var)
		return (ft_strdup(""));
	result = ft_strdup(env_var);
	free(env_var);
	env_var = NULL;
	return (result);
}

char	*append_string(char *result, const char *to_append)
{
	char	*new_result;

	new_result = ft_strjoin(result, to_append);
	free(result);
	result = NULL;
	return (new_result);
}

void	initialize_quote(t_quote *quote, int *i, char **result, char *arg)
{
	*i = 0;
	*result = ft_strdup("");
	quote->result = result;
	quote->arg = arg;
	quote->i = i;
	quote->quote_type = '\0';
}

void	append_single_char(t_quote *quote, int *i, char **result)
{
	char	single_char[2];

	single_char[0] = quote->arg[*i];
	single_char[1] = '\0';
	*result = append_string(*result, single_char);
	(*i)++;
}
