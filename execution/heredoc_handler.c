/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 03:45:17 by hmoukit           #+#    #+#             */
/*   Updated: 2024/12/01 12:59:34 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	create_pipe(int pipefd[2])
{
	if (pipe(pipefd) < 0)
	{
		perror("SHELL: pipe: Error creating pipe for heredoc");
		return (0);
	}
	return (1);
}

static int	write_to_pipe(int pipefd[2], const char *line)
{
	if (write(pipefd[1], line, ft_strlen(line)) < 0)
	{
		perror("SHELL: pipe: Error writing to pipe");
		return (0);
	}
	if (write(pipefd[1], "\n", 1) < 0)
	{
		perror("SHELL: pipe: Error writing newline to pipe");
		return (0);
	}
	return (1);
}

static int	handle_duplication(int pipefd[2])
{
	if (dup2(pipefd[0], STDIN_FILENO) < 0)
	{
		perror("SHELL: dup: Error duplicating file descriptor for heredoc");
		close(pipefd[0]);
		return (0);
	}
	close(pipefd[0]);
	return (1);
}

int	read_input(t_parser *node, char **line)
{
	*line = readline("heredoc> ");
	if (!line || !*line)
		return (0);
	if (node->right->id->ident && ft_strcmp(*line, node->right->id->ident) == 0)
	{
		free(*line);
		*line = NULL;
		return (-1);
	}
	return (1);
}

int	handle_heredoc(t_minishell *mini, t_parser *node)
{
	// (void)mini;
	char	*line;
	int		pipefd[2];

	line = NULL;
	mini->is_heredoc = 1;
	signal(SIGINT, SIG_IGN);
	if (!create_pipe(pipefd))
		return (0);
	while (1)
	{
		signal(SIGINT, ft_sigint_handler_heredoc);
		// signal(SIGQUIT, ft_sigquit_handler);
		if (read_input(node, &line) != 1)
			break ;
		if (!write_to_pipe(pipefd, line))
		{
			free(line);
			line = NULL;
			close(pipefd[1]);
			signal(SIGINT, SIG_DFL);
			return (0);
		}
		free(line);
		line = NULL;
	}
	return (close(pipefd[1]), handle_duplication(pipefd));
}


// int handle_heredoc(t_minishell *mini, t_parser *node)
// {
// 	(void)node;
//     char    *line;
//     int     pipefd[2];

//     line = NULL;
//     mini->is_heredoc = 1; // Set heredoc mode
//     signals_init(1);      // Set signal handlers for heredoc
//     if (!create_pipe(pipefd))
//         return (0);
//     while (1)
//     {
//         line = readline("heredoc> "); // Read user input for heredoc
//         if (!line) // Detect Ctrl+D
//         {
//             mini->is_heredoc = 0; // Exit heredoc mode
//             break;
//         }
//         if (!*line) // Handle empty input
//         {
//             free(line);
//             continue;
//         }
//         if (!write_to_pipe(pipefd, line)) // Write input to pipe
//         {
//             free(line);
//             close(pipefd[1]);
//             mini->is_heredoc = 0; // Reset heredoc mode
//             return (0);
//         }
//         free(line);
//     }
//     mini->is_heredoc = 0; // Reset heredoc mode
//     signals_init(0);      // Restore default signal handlers
//     return (close(pipefd[1]), handle_duplication(pipefd));
// }
