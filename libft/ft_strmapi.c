/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 23:09:48 by yena              #+#    #+#             */
/*   Updated: 2022/07/14 23:11:31 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	s_len;
	size_t	i;
	char	*s_dup;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	i = 0;
	s_dup = ft_strdup(s);
	if (!s_dup)
		return (0);
	while (i < s_len)
	{
		*(s_dup + i) = f(i, *(s + i));
		i++;
	}
	return (s_dup);
}
