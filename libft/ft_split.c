/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yena <yena@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 22:49:57 by yena              #+#    #+#             */
/*   Updated: 2022/07/15 02:30:50 by yena             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	get_word_count(char const *s, char c)
{
	unsigned int	count;
	unsigned int	idx_s;
	unsigned int	is_sep;

	count = 0;
	idx_s = 0;
	is_sep = 0;
	while (*(s + idx_s))
	{
		if (*(s + idx_s) == c)
		{
			if (!is_sep)
				count++;
			is_sep = 1;
		}
		else
			is_sep = 0;
		idx_s++;
		if (!*(s + idx_s) && !is_sep)
			count++;
	}
	return (count);
}

static size_t	get_word_length(char const *s, char c)
{
	unsigned int	length;

	length = 0;
	while (*(s + length) && *(s + length) != c)
		length++;
	return (length);
}

static unsigned int	skip_seperator(char const *s, char c)
{
	unsigned int	idx_s;

	idx_s = 0;
	while (*(s + idx_s) && *(s + idx_s) == c)
		idx_s++;
	return (idx_s);
}

static char	**free_all(char **words)
{
	unsigned int	idx_w;

	idx_w = 0;
	while (*(words + idx_w))
	{
		free(words + idx_w);
		idx_w++;
	}
	free(words);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	unsigned int	idx_s;
	unsigned int	idx_w;
	unsigned int	word_cnt;
	char			**words;
	size_t			word_len;

	if (!s)
		return (0);
	idx_s = skip_seperator(s, c);
	idx_w = 0;
	word_cnt = get_word_count(s + idx_s, c);
	words = (char **)malloc(sizeof(char *) * (word_cnt + 1));
	if (!words)
		return (0);
	while (idx_w < word_cnt)
	{
		word_len = get_word_length(s + idx_s, c);
		*(words + idx_w) = ft_substr(s + idx_s, 0, word_len);
		if (!*(words + idx_w))
			return (free_all(words));
		idx_s += skip_seperator(s + idx_s + word_len, c) + word_len;
		idx_w++;
	}
	*(words + idx_w) = 0;
	return (words);
}
