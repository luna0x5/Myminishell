/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 13:00:47 by hmoukit           #+#    #+#             */
/*   Updated: 2024/11/24 09:45:39 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int cd_home(t_minishell *mini)
{
    if (chdir(mini->home) < 0)
    {
        perror("chdir ");
        return (1);
    }
    free(mini->oldpwd);
    mini->oldpwd = ft_strdup(mini->pwd);
    free(mini->pwd);
    mini->pwd = ft_strdup(mini->home);
    return (0);
}

static int  cd_pwd(t_minishell *mini)
{
    char    *tmp;

    if (chdir(mini->oldpwd) < 0)
    {
        perror("chdir ");
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

int cd_wd(t_minishell *mini)
{
	free(mini->oldpwd);
	mini->oldpwd = ft_strdup(mini->pwd);
	return (0);
}

int	cd_parent(t_minishell *mini)
{
	int		len;
	char    *tmp;
	char	*slash;

	slash = ft_strrchr(mini->pwd, '/');
    if (slash == NULL)
    {
        perror("cd ..: No parent directory (at root)");
        return (1);
    }
    len = slash - mini->pwd;
	tmp = ft_substr(mini->pwd, 0, len);
	if (chdir(tmp) < 0)
    {
        perror("chdir ");
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

int cd_chdir(char *path, t_minishell *mini)
{
    if (chdir(path) < 0)
    {
        perror("chdir ");
        return (1);
    }
    free(mini->oldpwd);
    mini->oldpwd = ft_strdup(mini->pwd);
    free(mini->pwd);
    mini->pwd = ft_strdup(path);
    return (0);
}

int ft_cd(t_minishell *mini)
{
    if (!mini->args[1] || mini->args[1][0] == '~')
        return (cd_home(mini));
    if (mini->args[1][0] == '-')
        return (cd_pwd(mini));
	if (!ft_strcmp(mini->args[1], ".."))
		return (cd_parent(mini));
	if (mini->args[1][0] == '.')
		return (cd_wd(mini));
    cd_chdir(mini->args[1], mini);
    return (0);
}
