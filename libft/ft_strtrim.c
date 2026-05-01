/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frakotov < frakotov@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 12:09:30 by frakotov          #+#    #+#             */
/*   Updated: 2024/08/24 12:09:30 by frakotov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	lens1;
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	while (ft_strchr(set, s1[i]) && s1[i] != '\0')
		i++;
	lens1 = ft_strlen((char *)s1);
	while (ft_strchr(set, s1[lens1 - 1]) && lens1 != 0)
		lens1--;
	return (ft_substr((char *)s1, i, lens1 - i));
}
