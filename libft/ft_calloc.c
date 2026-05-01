/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frakotov < frakotov@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 12:05:39 by frakotov          #+#    #+#             */
/*   Updated: 2024/08/24 12:05:41 by frakotov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t elcount, size_t size)
{
	void	*mal;

	mal = (void *)malloc(elcount * size);
	if (mal == NULL)
		return (NULL);
	ft_bzero(mal, (elcount * size));
	return (mal);
}
