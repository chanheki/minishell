/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 12:14:12 by chanheki          #+#    #+#             */
/*   Updated: 2022/09/14 16:56:17 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	index;

	index = 0;
	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (dstsize < dstlen + 1)
		return (srclen + dstsize);
	while (dstlen + index + 1 < dstsize && *(src + index))
	{
		*(dst + dstlen + index) = *(src + index);
		index++;
	}
	*(dst + dstlen + index) = '\0';
	return (dstlen + srclen);
}
