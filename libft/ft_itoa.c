/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 23:01:06 by yena              #+#    #+#             */
/*   Updated: 2022/12/18 19:37:44 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_itoa_len(long long n)
{
	size_t	length;

	length = 0;
	if (n <= 0)
		length++;
	while (n)
	{
		length++;
		n /= 10;
	}
	return (length);
}

static char	*fill_ascii(char *ascii, unsigned int idx, long long n, int sign)
{
	if (n == 0)
		return (ascii);
	ascii = fill_ascii(ascii, idx - 1, n / 10, sign);
	*(ascii + idx) = (n % 10) * sign + '0';
	return (ascii);
}

char	*ft_itoa(long long n)
{
	size_t	ascii_len;
	int		sign;
	char	*ascii;

	ascii_len = get_itoa_len(n);
	sign = 1;
	ascii = (char *)malloc(sizeof(char) * (ascii_len + 1));
	if (!ascii)
		return (0);
	if (n <= 0)
	{
		if (n < 0)
			*(ascii) = '-';
		else
			*(ascii) = '0';
		sign = -1;
	}
	ascii = fill_ascii(ascii, ascii_len - 1, n, sign);
	*(ascii + ascii_len) = '\0';
	return (ascii);
}
