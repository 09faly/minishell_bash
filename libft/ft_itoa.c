/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frakotov < frakotov@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 12:06:27 by frakotov          #+#    #+#             */
/*   Updated: 2024/08/24 12:06:28 by frakotov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nb_size(long nb)
{
	int	nbnb;

	nbnb = 0;
	if (nb <= 0)
		nbnb++;
	while (nb != 0)
	{
		nb /= 10;
		nbnb++;
	}
	return (nbnb);
}

char	*ft_itoa(int n)
{
	char	*dst;
	int		i;

	i = nb_size(n);
	dst = malloc(sizeof(char) * (i + 1));
	if (!dst)
		return (NULL);
	dst[i--] = '\0';
	if (n == 0)
	{
		dst[0] = '0';
		return (dst);
	}
	if (n < 0)
		dst[0] = '-';
	while (n != 0)
	{
		if (n < 0)
			dst[i--] = '0' + -(n % 10);
		else
			dst[i--] = '0' + (n % 10);
		n = n / 10;
	}
	return (dst);
}
