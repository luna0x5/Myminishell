/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_id.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:40:48 by hmoukit           #+#    #+#             */
/*   Updated: 2024/11/18 13:55:03 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_env(t_minishell *mini, const char *key, const char *new_value)
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
	if (!ft_isalpha(key[i]) || key[i] != '_')
		return (0);
	i++;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) || key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
