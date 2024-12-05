/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 13:00:47 by hmoukit           #+#    #+#             */
/*   Updated: 2024/12/05 15:03:42 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	cd_pwd(t_minishell *mini)
{
	char	*tmp;

	if (chdir(mini->oldpwd) < 0)
	{
		perror("SHELL: chdir");
		return (1);
	}
	tmp = ft_strdup(mini->pwd);
	free(mini->pwd);
	mini->pwd = ft_strdup(mini->oldpwd);
	free(mini->oldpwd);
	mini->oldpwd = ft_strdup(tmp);
	free(tmp);
	tmp = NULL;
	return (0);
}

static int	cd_parent(t_minishell *mini)
{
	int		len;
	char	*tmp;
	char	*slash;

	slash = ft_strrchr(mini->pwd, '/');
	if (slash == NULL)
	{
		write(2, "SHELL: cd ..: No parent directory (at root)\n", 44);
		return (1);
	}
	len = slash - mini->pwd;
	tmp = ft_substr(mini->pwd, 0, len);
	if (chdir(tmp) < 0)
	{
		perror("SHELL: chdir");
		free(tmp);
		return (1);
	}
	free(mini->oldpwd);
	mini->oldpwd = ft_strdup(mini->pwd);
	free(mini->pwd);
	mini->pwd = ft_strdup(tmp);
	free(tmp);
	tmp = NULL;
	return (0);
}

static int	cd_chdir(char *path, t_minishell *mini)
{
	char	*cwd;

	if (chdir(path) < 0)
	{
		perror("SHELL: chdir");
		return (1);
	}
	free(mini->oldpwd);
	mini->oldpwd = ft_strdup(mini->pwd);
	free(mini->pwd);
	cwd = NULL;
	mini->pwd = getcwd(cwd, 0);
	if (!mini->pwd)
	{
		perror("SHELL: getcwd");
		return (1);
	}
	return (0);
}

int	ft_cd(t_minishell *mini)
{
	int	i;

	i = 0;
	if (mini->args[1][0] == '-')
		i = cd_pwd(mini);
	else if (!ft_strcmp(mini->args[1], ".."))
		i = cd_parent(mini);
	else if (mini->args[1][0] == '.')
	{
		free(mini->oldpwd);
		mini->oldpwd = ft_strdup(mini->pwd);
		i = 0;
	}
	else if (!ft_strcmp(mini->args[1], "..."))
	{
		write(2, "SHELL: cd: No such file or directory\n", 37);
		return (1);
	}
	else
		i = cd_chdir(mini->args[1], mini);
	update_env(mini, "PWD", mini->pwd);
	update_env(mini, "OLDPWD", mini->oldpwd);
	return (i);
}
