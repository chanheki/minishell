/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 22:40:58 by yena              #+#    #+#             */
/*   Updated: 2022/07/21 12:07:05 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	if (!s1)
		return (0);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (*(s1 + start) && ft_strchr(set, (int)(*(s1 + start))))
		start++;
	while (end && ft_strchr(set, (int)(*(s1 + end))))
		end--;
	if (end < start)
		return ((char *)ft_calloc(1, sizeof(char)));
	return (ft_substr(s1, start, (end - start + 1)));
}
