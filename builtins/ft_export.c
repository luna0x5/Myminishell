/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:38:26 by hmoukit           #+#    #+#             */
/*   Updated: 2024/11/23 12:38:18 by hmoukit          ###   ########.fr       */
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

// static void change_env_value(t_env **env, t_env *node)
// {
//     t_env   *current;

//     current = *env;
//     while (current && current->next && ft_strcmp(current->next->key, node->key))
//         current = current->next;
//     current->value = ft_strdup(node->value);
// }

static void change_env_value(t_env **env, t_env *node)
{
    t_env *current;

    current = *env;
    while (current)
    {
        if (current->key && strcmp(current->key, node->key) == 0)
        {
            free(current->value);
            current->value = strdup(node->value);
            printf("current->value ====== {%s}\n", current->value);
            current = *env;
            while (current)
            {
                printf("{%s}\n", current->data);
                current = current->next;
            }
            return ;
        }
        current = current->next;
    }
}

static int  process_arg(t_expander *exp, char *s)
{
    t_env   *node;

    node = ft_lstnew(s);
    if (!node)
        return (0);
    node->key = extract_env_key(s);
    if (!node->key)
        return (0);
    node->value = get_value(s);
    if (!node->value)
        return (0);
    if (node->value[0] == '\0')
    {
        free(node->value);
        node->value = NULL;
    }
    if (!ft_getenv(node->key, exp))
        ft_lstadd_back(&exp->env, node);
    else
        change_env_value(&exp->env, node);
    return (1);
}

int ft_export(t_minishell *mini)
{
    int i;

    i = 1;
    if (!mini->args[i])
        ft_exported_list(mini->exp);
    while (mini->args[i])
    {
        if (!process_arg(mini->exp, mini->args[i]))
            return (1);
        i++;
    }
    return (0);
}
