/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 01:28:15 by chanheki          #+#    #+#             */
/*   Updated: 2022/07/25 22:24:44 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	if (!*needle)
		return ((char *)haystack);
	while (*haystack)
	{
		i = 0;
		while (*(needle + i))
		{
			if (i >= len)
				return (NULL);
			if (*(needle + i) != *(haystack + i))
				break ;
			i++;
		}
		if (!*(needle + i))
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}
