/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:47:37 by hmoukit           #+#    #+#             */
/*   Updated: 2024/11/13 11:53:41 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	handle_builtin(t_minishell *node)
// {
// 	if (node && node->ast && node->ast->id->id_type == CMD && node->cmd)
// 	{
// 		if (is_builtin(node->cmd))
// 			return (free(node->cmd) ,exec_builtin(node));
// 	}
// 	return (-1);
// }

int	fork_and_exec(char *path, char **args, char **env_2d)
{
	int	pid;
	int	status;

	status = 0;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(path);
		return (1);
	}
	else if (pid == 0)
	{
		if (execve(path, args, env_2d) == -1)
		{
			perror("execve");
			free(path);
			exit(1);
		}
	}
	else
		waitpid(pid, &status, 0);
	return (status);
}

int	exec_simple_cmd(t_minishell *node, char **env_2d)
{
	char	*path;
	int		status;

	path = get_path(node->cmd);
	free(node->cmd);
	node->cmd = NULL;
	if (!path)
	{
		write(2, "path not found\n", 16);
		return (127);
	}
	status = fork_and_exec(path, node->args, env_2d);
	free(path);
	path = NULL;
	return (get_exit_status(status));
}

void	exec_no_fork(t_minishell *node, char **env_2d, char *path)
{
	// if (handle_builtin(node) == -1)
	// {
		path = get_path(node->cmd);
		if (execve(path, node->args, env_2d) == -1)
		{
			free_args(env_2d);
			perror("execve");
			free(path);
			exit(1);
		}
	// }
}
