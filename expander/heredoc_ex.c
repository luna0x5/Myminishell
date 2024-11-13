/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_ex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 01:49:58 by hmoukit           #+#    #+#             */
/*   Updated: 2024/11/11 18:30:37 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander.h"

static void	check_sign_quote(char *arg, int *i, int *quote)
{
	if (arg[0] == '$' && arg[1] == '\'')
	{
		*quote = 1;
		*i = 2;
	}
	else if (arg[0] == '$' && arg[1] == '"')
	{
		*quote = 2;
		*i = 2;
	}
	else
	{
		*quote = ft_isquote(arg[*i]);
		if (*quote)
			(*i)++;
	}
}

static char	*remove_quotes(char *arg)
{
	char	*unquoted;
	int		quote;
	int		i;
	int		j;

	if (!arg)
		return (NULL);
	unquoted = malloc(ft_strlen(arg) + 1);
	if (!unquoted)
		return (NULL);
	i = 0;
	j = 0;
	check_sign_quote(arg, &i, &quote);
	while (arg[i])
	{
		if ((quote == 1 && arg[i] == '\'') || (quote == 2 && arg[i] == '"'))
			break ;
		else
			unquoted[j++] = arg[i++];
	}
	unquoted[j] = '\0';
	free(arg);
	arg = NULL;
	return (unquoted);
}

void	handle_heredoc_ex(t_parser *ast, t_expander *exp)
{
	char	*unquoted;

	if (ast->right && ast->right->id)
	{
		unquoted = remove_quotes(ast->right->id->ident);
		if (unquoted)
			ast->right->id->ident = unquoted;
	}
	if (ast->left)
	{
		ast = ast->left;
		if (ast->right)
			ast = ast->right;
		if (ast->id && (ast->id->id_type == ARG || ast->id->id_type == RFILE))
			process_string(ast, exp);
	}
}
