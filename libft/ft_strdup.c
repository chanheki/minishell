/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 22:19:41 by yena              #+#    #+#             */
/*   Updated: 2022/07/14 23:39:12 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	s1_len;
	size_t	idx;
	char	*dup;

	s1_len = ft_strlen(s1);
	idx = 0;
	dup = (char *)malloc(sizeof(char) * (s1_len + 1));
	if (!dup)
		return (0);
	while (idx < s1_len)
	{
		*(dup + idx) = *(s1 + idx);
		idx++;
	}
	*(dup + idx) = '\0';
	return (dup);
}
