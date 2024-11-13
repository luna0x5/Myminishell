/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoukit <hmoukit@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:10:30 by hmoukit           #+#    #+#             */
/*   Updated: 2024/10/03 18:55:49 by hmoukit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	n;
	char			*a;
	size_t			i;

	n = (unsigned char)c;
	a = (char *)b;
	i = 0;
	while (i < len)
	{
		a[i] = n;
		i++;
	}
	return (b);
}

static void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*s;
	size_t	tmp;

	tmp = count * size;
	if (count && (tmp / count != size))
		return (NULL);
	s = malloc(count * size);
	if (s == NULL)
		return (NULL);
	ft_bzero(s, count * size);
	return (s);
}
