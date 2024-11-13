/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 16:07:22 by hmoukit           #+#    #+#             */
/*   Updated: 2023/11/14 09:29:59 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*s;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	s = (char *)malloc((s1len + s2len + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	ft_strlcpy(s, s1, s1len + 1);
	ft_strlcpy(s + s1len, s2, s2len + 1);
	return (s);
}
