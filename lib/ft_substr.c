/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:44:37 by chanheki          #+#    #+#             */
/*   Updated: 2022/09/14 18:08:21 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	size;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	if (size <= start || len == 0)
		return (ft_strdup(""));
	if (len > size - start)
		len = size - start;
	result = (char *)malloc(sizeof(char) * len + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, s + start, len + 1);
	return (result);
}
