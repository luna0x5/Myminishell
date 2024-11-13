/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quoted_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 00:08:25 by hmoukit           #+#    #+#             */
/*   Updated: 2024/11/10 00:57:17 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"

static void	append_substring_to_result(char **res, char *arg, int star, int end)
{
	char	*temp;

	temp = ft_substr(arg, star, end - star);
	*res = append_string(*res, temp);
	free(temp);
}

static void	handle_dollar_expansion(t_quote *q, t_expander *exp, int *start)
{
	char	*temp;

	if (q->arg[*(q->i) + 1] == '$')
	{
		(*(q->i))++;
		*(q->result) = append_string(*(q->result), "$");
		(*(q->i))++;
		*start = *(q->i);
	}
	else if (!q->arg[*(q->i) + 1] || !ft_isvalid(q->arg[*(q->i) + 1]))
	{
		(*(q->i))++;
		*(q->result) = append_string(*(q->result), "");
	}
	else
	{
		temp = handle_variable_expansion(q->arg, q->i, exp);
		*(q->result) = append_string(*(q->result), temp);
		free(temp);
		*start = *(q->i);
	}
}

static void	process_quoted_string(t_quote *q, t_expander *exp, int *start)
{
	while (q->arg[*(q->i)] && q->arg[*(q->i)] != q->quote_type)
	{
		if (q->quote_type == '"' && q->arg[*(q->i)] == '$')
		{
			if (*(q->i) > *start)
				append_substring_to_result(q->result, q->arg, *start, *(q->i));
			handle_dollar_expansion(q, exp, start);
		}
		else
			(*(q->i))++;
	}
}

void	handle_quoted_string(t_quote *q, t_expander *exp)
{
	int	start;

	start = ++(*(q->i));
	process_quoted_string(q, exp, &start);
	if (*(q->i) > start)
		append_substring_to_result(q->result, q->arg, start, *(q->i));
	(*(q->i))++;
}
