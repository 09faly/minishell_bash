/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frakotov < frakotov@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 12:06:35 by frakotov          #+#    #+#             */
/*   Updated: 2024/08/24 12:06:35 by frakotov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s1;
	unsigned char	b;
	size_t			i;

	i = 0;
	s1 = (unsigned char *)s;
	b = (unsigned char)c;
	while (i < n)
	{
		if (s1[i] == b)
			return ((void *)(s + i));
		i++;
	}
	return (0);
}
