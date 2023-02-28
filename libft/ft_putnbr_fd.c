/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 23:17:06 by yena              #+#    #+#             */
/*   Updated: 2022/07/15 02:40:26 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	recursive_putnbr_fd(int n, int fd, int sign)
{
	if (n == 0)
		return ;
	recursive_putnbr_fd(n / 10, fd, sign);
	write(fd, &"0123456789"[(n % 10) * sign], 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	int	sign;

	sign = 1;
	if (n < 0)
	{
		write(fd, "-", 1);
		sign = -1;
	}
	if (n == 0)
		write(fd, "0", 1);
	recursive_putnbr_fd(n, fd, sign);
}
