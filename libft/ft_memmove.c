/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 10:36:57 by yena              #+#    #+#             */
/*   Updated: 2022/07/14 23:28:03 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*temp;
	size_t			i;

	i = 0;
	if (!dst && !src)
		return (0);
	if (dst > src)
	{
		temp = (unsigned char *)src;
		while (i < len)
		{
			*((unsigned char *)dst + len - 1 - i) = *(temp + len - 1 - i);
			i++;
		}
		return (dst);
	}
	else
		return (ft_memcpy(dst, src, len));
}
