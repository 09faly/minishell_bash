/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frakotov < frakotov@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 12:10:06 by frakotov          #+#    #+#             */
/*   Updated: 2024/08/24 12:10:06 by frakotov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;

	if (ft_strlen(s) <= start)
	{
		new = malloc(sizeof(char));
		new[0] = '\0';
		return (new);
	}
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	ft_memcpy(new, s + start, len + 1);
	new[len] = '\0';
	return (new);
}
/*
int main()
{
	char s[] = "ipsum_dolor";
	printf("%s", ft_substr(s, 4, 3));
}*/
