/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 18:47:31 by chanheki          #+#    #+#             */
/*   Updated: 2022/07/25 20:26:07 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	str_length;
	char	*dest;

	str_length = ft_strlen(s1);
	dest = (char *) malloc(sizeof(char) * str_length + 1);
	if (!dest)
		return (NULL);
	*(dest + str_length) = 0;
	ft_memcpy(dest, s1, str_length);
	return (dest);
}
