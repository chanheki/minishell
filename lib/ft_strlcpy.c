/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 12:14:17 by chanheki          #+#    #+#             */
/*   Updated: 2022/07/11 18:59:00 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	size;

	size = ft_strlen(src);
	if (!dst || !src)
		return (0);
	if (dstsize == 0)
		return (size);
	while (*src && (dstsize--) != 1)
		*dst++ = *src++;
	*dst = 0;
	return (size);
}
