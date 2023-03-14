/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 02:16:10 by chanheki          #+#    #+#             */
/*   Updated: 2022/07/25 20:06:08 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	word_count(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (*s != c && (*(s + 1) == c || *(s + 1) == '\0'))
			count++;
		s++;
	}
	return (count);
}

static char	*copy_one(char const *s, char c)
{
	size_t	len;
	char	*word;

	len = ft_strlen(s);
	if (ft_strchr(s, c))
		len = (size_t)(ft_strchr(s, c) - s);
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	ft_strlcpy(word, s, len + 1);
	return (word);
}

static void	free_all(char **words)
{
	char	**ptr;

	ptr = words;
	while (*ptr)
		free(*(ptr++));
	free(words);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	char	**words;

	if (!s)
		return (NULL);
	words = (char **)ft_calloc(word_count(s, c) + 1, sizeof(char *));
	i = 0;
	while (words && *s)
	{
		if (*s == c)
			s++;
		else
		{
			*(words + i) = copy_one(s, c);
			if (*(words + i) == NULL)
			{
				free_all(words);
				return (NULL);
			}
			s += ft_strlen(*(words + i));
			i++;
		}
	}
	return (words);
}
