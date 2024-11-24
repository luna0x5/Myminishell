/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 23:26:48 by hmoukit           #+#    #+#             */
/*   Updated: 2024/11/17 15:37:42 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int 	is_str_nbr(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if(!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
// should I add the checking for parents and children for writing exit ??
int ft_exit(t_minishell *mini)
{
	if (mini->args[1])
	{
		write(2, "exit\n", 5);
		if (!is_str_nbr(mini->args[1]))
		{
			write(2, "exit: numeric argument required\n", 32);
			mini->exp->exit_s = 2;
			exit(mini->exp->exit_s);
		}
		if (mini->args[2])
		{
			write(2, "exit: too many arguments\n", 25);
			mini->exp->exit_s = 1;
			return (1);
		}
		else
		{
			mini->exp->exit_s = (unsigned char)ft_atoi(mini->args[1]);
			exit(mini->exp->exit_s);
		}
	}
	mini->exp->exit_s = 0;
	exit(mini->exp->exit_s);
	return (0);
}
