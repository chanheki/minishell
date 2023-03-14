/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 09:38:15 by yena              #+#    #+#             */
/*   Updated: 2022/07/21 12:09:32 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	int	i;

	i = 0;
	if (!src && !dst)
		return (0);
	while (n)
	{
		*((unsigned char *)dst + i) = *((unsigned char *)src + i);
		n--;
		i++;
	}
	return (dst);
}
