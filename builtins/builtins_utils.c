/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:40:48 by hmoukit           #+#    #+#             */
/*   Updated: 2024/12/01 17:23:15 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_env(t_minishell *mini, char *key, char *new_value)
{
	t_env		*node;
	char		*tmp;

	node = mini->exp->env;
	while (node)
	{
		if (!strcmp(node->key, key))
		{
			if (node->value)
				free(node->value);
			node->value = ft_strdup(new_value);
			if (node->data)
				free(node->data);
			tmp = ft_strjoin(key, "=");
			node->data = ft_strjoin(tmp, new_value);
			free(tmp);
			tmp = NULL;
			break ;
		}
		node = node->next;
	}
}

int	is_valid_id(char *key)
{
	int	i;

	i = 0;
	if (!ft_isalpha(key[i]) && key[i] != '_')
		return (0);
	i++;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	is_str_nbr(char *str)
{
	int	i;

	if (!check_long(str))
		return (0);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
