/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 04:35:00 by hmoukit           #+#    #+#             */
/*   Updated: 2024/12/01 13:05:48 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_sigint_handler(int num)
{
	(void)num;
	// ft_putstr_fd("\n", 1);
	// rl_replace_line("", 0);
	// rl_on_new_line();
	rl_redisplay();
}

void	ft_sigint_handler_heredoc(int num)
{
	(void)num;
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	// rl_redisplay();
	exit (1);
}

// #include "minishell.h"

// void ft_sigint_handler(int num)
// {
// 	(void)num;
//     ft_putstr_fd("\n", 1);
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	rl_redisplay();
// }

// void ft_sigint_handler(int signum)
// {
//     (void)signum;
//     if (rl_on_new_line() == -1) // Reset readline buffer
//         return;
//     rl_replace_line("", 0);    // Clear the current input line
//     rl_redisplay();           // Refresh the prompt
//     write(1, "\n", 1);         // Move to a new line
// }


// void ft_eof_handler(void)
// {
//     // Handle EOF here, such as breaking out of the loop in the main shell
//     printf("\nEOF encountered\n");
//     exit(0);  // Optionally exit the shell or handle differently
// }


void	ft_sigquit_handler(int num)
{
	(void)num;
}

void	ft_eof_handler(void)
{
	write(1, "exit\n", 5);
	exit(0);
}
