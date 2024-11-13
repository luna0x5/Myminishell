/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 04:37:15 by hmoukit           #+#    #+#             */
/*   Updated: 2024/11/07 04:46:23 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	check_redir(t_token_type type)
{
	if (type == LESS || type == D_LESS || type == GREAT || type == D_GREAT)
		return (1);
	return (0);
}

int	check_redir_beg(t_token *tokens)
{
	if (tokens && check_redir(tokens->token_type) && !tokens->next)
	{
		write(2, "No Redirection File\n", 20);
		return (0);
	}
	return (1);
}

int	check_pipe_beg(t_token *tokens)
{
	if (tokens && *(tokens->token) == '|' && !tokens->next)
	{
		write(2, "PIPE in the beginning\n", 22);
		return (0);
	}
	return (1);
}

int	check_syntax(t_token **list)
{
	t_token	*tmp;

	tmp = *list;
	if (tmp->token_type == PIPE)
	{
		write(2, "PIPE in the beginning\n", 22);
		token_clear(list);
		return (0);
	}
	while (tmp)
	{
		if (tmp && !check_redir_beg(tmp))
		{
			token_clear(list);
			return (0);
		}
		if (tmp && !check_pipe_beg(tmp))
		{
			token_clear(list);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}
