/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frakotov < frakotov@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 12:07:09 by frakotov          #+#    #+#             */
/*   Updated: 2024/08/24 12:07:10 by frakotov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	if (!s && !c)
		return (NULL);
	while (i < n)
	{
		*(unsigned char *)(s + i) = (unsigned char)c;
		i++;
	}
	return (s);
}
