/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 20:55:23 by chanheki          #+#    #+#             */
/*   Updated: 2022/12/19 20:55:32 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *src, int start, int num)
{
	char	*p;
	int		i;
	int		j;

	p = (char *)(malloc(sizeof(char) * (sizeof(char) * (num + 1))));
	if (!p)
		return (NULL);
	i = 0;
	j = 0;
	while (src[i] && j < num)
	{
		p[i] = src[start + j];
		i++;
		j++;
	}
	p[i] = '\0';
	return (p);
}
