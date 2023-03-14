/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 02:41:04 by chanheki          #+#    #+#             */
/*   Updated: 2022/07/25 19:10:22 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		div;
	int		mod;

	div = n / 10;
	mod = n % 10;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		div = -div;
		mod = -mod;
	}
	if (div)
		ft_putnbr_fd(div, fd);
	ft_putchar_fd(mod + '0', fd);
}
