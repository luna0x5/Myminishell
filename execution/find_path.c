/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:39:22 by hmoukit           #+#    #+#             */
/*   Updated: 2024/10/23 02:34:29 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	free_dir(char **dir)
{
	int	j;

	j = 0;
	while (dir[j])
	{
		free(dir[j]);
		j++;
	}
	free(dir);
}

static char	*find_path(char **dir, char **path, char *cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	while (dir[i])
	{
		tmp = ft_strjoin(dir[i], "/");
		if (!tmp)
			return (free_dir(dir), NULL);
		*path = ft_strjoin(tmp, cmd);
		if (!*path)
			return (free_dir(dir), free(tmp), NULL);
		if (access(*path, X_OK) == 0)
		{
			free_dir(dir);
			free(tmp);
			return (*path);
		}
		free(tmp);
		free(*path);
		i++;
	}
	free_dir(dir);
	return (NULL);
}

char	*get_path(char *cmd)
{
	char	*path;
	char	**dir;

	if (!cmd || *cmd == '\0')
		return (NULL);
	path = getenv("PATH");
	if (!path)
		return (NULL);
	dir = ft_split(path, ':');
	if (!dir)
		return (free(cmd), NULL);
	path = NULL;
	return (find_path(dir, &path, cmd));
}
