/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:38:26 by hmoukit           #+#    #+#             */
/*   Updated: 2024/11/18 19:24:17 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void ft_exported_list(t_expander *exp)
{
    t_env   *current;

    current = exp->env;
    while (current)
    {
        if (ft_strcmp("_", current->key))
        {
            write(1, "declare -x ", 11);
            ft_putstr_fd(current->data, 1);
            write(1, "\n", 1);
        }
        current = current->next;
    }
}

int ft_export(t_minishell *mini)
{
    int i;

    i = 1;
    if (!mini->args[i])
        ft_exported_list(mini->exp);
    while (mini->args[i])
    {
        i++;
    }
    return (0);
}
