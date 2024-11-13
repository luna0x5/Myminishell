/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 04:35:00 by hmoukit           #+#    #+#             */
/*   Updated: 2024/11/09 20:25:28 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_sigint_handler_herd(int num)
// {
// 	(void)num;
// 	ft_putstr_fd("\n", 1);
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	// rl_redisplay();
// }

void	ft_sigint_handler(int num)
{
	(void)num;
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_sigquit_handler(int num)
{
	(void)num;
}

void	ft_eof_handler(void)
{
	write(1, "exit\n", 5);
	exit(0);
}
