/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 01:20:51 by chanheki          #+#    #+#             */
/*   Updated: 2022/07/16 08:37:50 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_num_len(long long n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		++len;
		n *= -1;
	}
	else if (n == 0)
		return (1);
	while (n != 0)
	{
		++len;
		n /= 10;
	}
	return (len);
}

static char	*storage_num(long long n, char *result)
{
	if (n / 10 != 0)
		result = storage_num(n / 10, result);
	*result++ = n % 10 + '0';
	*result = '\0';
	return (result);
}

char	*ft_itoa(int n)
{
	char		*result;
	long long	nb;
	size_t		size_nb;

	nb = (long long)n;
	size_nb = ft_num_len(nb);
	result = (char *)malloc((sizeof(char) * size_nb) + 1);
	if (!result)
		return (NULL);
	if (nb < 0)
	{
		*result++ = '-';
		nb *= -1;
	}
	result = storage_num(nb, result);
	result -= size_nb;
	return (result);
}
