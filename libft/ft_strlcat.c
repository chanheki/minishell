/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:06:04 by yena              #+#    #+#             */
/*   Updated: 2022/07/21 12:09:25 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	length;

	i = 0;
	length = ft_strlen(dst);
	if (dstsize <= length)
		return (ft_strlen(src) + dstsize);
	while ((i + 1 < dstsize - length) && src[i])
	{
		dst[length + i] = src[i];
		i++;
	}
	dst[length + i] = '\0';
	return (length + ft_strlen(src));
}
