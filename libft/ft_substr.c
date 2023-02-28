/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 22:22:19 by yena              #+#    #+#             */
/*   Updated: 2022/07/15 01:00:59 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_substr_len(char const *s, unsigned int start, size_t len)
{
	size_t	substr_len;

	if (start >= ft_strlen(s))
		substr_len = 0;
	else
	{
		if (ft_strlen(s + start) < len)
			substr_len = ft_strlen(s + start);
		else
			substr_len = len;
	}
	return (substr_len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	substr_len;
	size_t	i;
	char	*substr;

	if (!s)
		return (0);
	substr_len = get_substr_len(s, start, len);
	substr = (char *)malloc(sizeof(char) * (substr_len + 1));
	if (!substr)
		return (0);
	i = 0;
	while (i < substr_len)
	{
		*(substr + i) = *(s + start + i);
		i++;
	}
	*(substr + i) = '\0';
	return (substr);
}
