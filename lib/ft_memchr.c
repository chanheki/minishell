/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 21:46:33 by chanheki          #+#    #+#             */
/*   Updated: 2022/07/06 22:00:41 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_dst;
	unsigned char	find;

	find = c;
	s_dst = (unsigned char *)s;
	while (n--)
	{
		if (*s_dst == find)
			return (s_dst);
		s_dst++;
	}
	return (0);
}
