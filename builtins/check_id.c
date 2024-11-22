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

int is_valid_id(char *key)
{
    int i;

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
