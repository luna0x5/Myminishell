/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:43:59 by hmoukit           #+#    #+#             */
/*   Updated: 2024/11/10 01:03:29 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static int	count_equal_len(char *data)
{
	int	i;

	i = 0;
	if (!data || !data[i])
		return (0);
	while (data[i] != '=')
		i++;
	return (i);
}

static int	count_value_len(char *data)
{
	int	i;
	int	j;

	i = 0;
	if (!data || !data[i])
		return (0);
	while (data[i] != '=')
		i++;
	i++;
	j = 0;
	while (data[i])
	{
		j++;
		i++;
	}
	return (j);
}

static char	*get_value(char *data)
{
	char	*value;
	int		equal_len;
	int		value_len;

	equal_len = count_equal_len(data);
	equal_len++;
	value_len = count_value_len(data);
	value = ft_substr(data, equal_len, value_len);
	return (value);
}

char	*ft_getenv(char *name, t_expander *exp)
{
	t_env	*tmp;

	tmp = exp->env;
	if (!tmp)
		return (NULL);
	while (tmp)
	{
		if (!ft_strncmp(name, tmp->data, count_equal_len(tmp->data)))
		{
			return (get_value(tmp->data));
		}
		tmp = tmp->next;
	}
	return (NULL);
}
