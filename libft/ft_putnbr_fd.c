/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frakotov < frakotov@student.42antananar    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 12:07:39 by frakotov          #+#    #+#             */
/*   Updated: 2024/08/24 12:07:40 by frakotov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	nb;

	nb = n;
	if (nb == -2147483647)
	{
		write(fd, "-2147483647", 11);
		return ;
	}
	if (nb < 0)
	{
		nb *= -1;
		write(fd, "-", 1);
	}
	if ((nb >= 0) && (nb <= 9))
		ft_putchar_fd((nb + 48), fd);
	else
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putnbr_fd(nb % 10, fd);
	}
}
