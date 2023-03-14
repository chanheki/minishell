/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 22:36:13 by yena              #+#    #+#             */
/*   Updated: 2022/07/15 01:45:01 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	join_len;
	int		idx_s;
	int		idx_j;

	if (!s1 || !s2)
		return (0);
	join_len = ft_strlen(s1) + ft_strlen(s2);
	join = (char *)malloc(sizeof(char) * (join_len + 1));
	if (!join)
		return (0);
	idx_s = 0;
	idx_j = 0;
	while (*(s1 + idx_s))
		*(join + idx_j++) = *(s1 + idx_s++);
	idx_s = 0;
	while (*(s2 + idx_s))
		*(join + idx_j++) = *(s2 + idx_s++);
	*(join + idx_j) = '\0';
	return (join);
}
