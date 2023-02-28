/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 21:50:52 by yena              #+#    #+#             */
/*   Updated: 2022/07/15 02:00:15 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*uc_s1;
	unsigned char	*uc_s2;
	size_t			i;

	uc_s1 = (unsigned char *)s1;
	uc_s2 = (unsigned char *)s2;
	i = 0;
	while (i < n && (*(uc_s1 + i) || *(uc_s2 + i)))
	{
		if (*(uc_s1 + i) != *(uc_s2 + i))
			return ((int)(*(uc_s1 + i) - *(uc_s2 + i)));
		i++;
	}
	return (0);
}
