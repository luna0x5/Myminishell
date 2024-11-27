/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 04:35:00 by hmoukit           #+#    #+#             */
/*   Updated: 2024/11/27 00:59:27 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_sigint_handler(int num)
{
	(void)num;
	// 3e9li 3la stdout
	// close stdout when ctrl + c
	// reopen strdout after execution
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
