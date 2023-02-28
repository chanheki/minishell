/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 22:07:22 by yena              #+#    #+#             */
/*   Updated: 2022/07/22 11:05:53 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	idx_h;
	size_t	idx_n;

	if (!*needle)
		return ((char *)haystack);
	if ((!haystack && !needle) || (!len))
		return (0);
	idx_h = 0;
	while (*(haystack + idx_h) && idx_h < len)
	{
		idx_n = 0;
		while (*(needle + idx_n) && idx_h + idx_n < len)
		{
			if (*(haystack + idx_h + idx_n) == *(needle + idx_n))
				idx_n++;
			else
				break ;
		}
		if (!*(needle + idx_n))
			return ((char *)(haystack + idx_h));
		idx_h++;
	}
	return (0);
}
