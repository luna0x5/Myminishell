/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:24:43 by hmoukit           #+#    #+#             */
/*   Updated: 2024/11/11 18:45:59 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*ft_lstlast(t_env *lst)
{
	t_env	*current;
	t_env	*last;

	if (!lst)
		return (NULL);
	current = lst;
	last = NULL;
	while (current != NULL)
	{
		last = current;
		current = current -> next;
	}
	return (last);
}

t_env	*ft_lstnew(void *content)
{
	t_env	*list;

	list = (t_env *)malloc(sizeof(t_env));
	if (list == NULL)
		return (NULL);
	list -> data = ft_strdup(content);
	list->has_value = 1;
	list -> next = NULL;
	return (list);
}

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (lst == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast(*lst);
	last -> next = new;
}

t_env	*make_env(void)
{
	extern char	**environ;
	t_env		*env;
	t_env		*new_node;
	int			i;

	env = NULL;
	i = 0;
	while (environ[i])
	{
		new_node = ft_lstnew(environ[i]);
		ft_lstadd_back(&env, new_node);
		i++;
	}
	return (env);
}
