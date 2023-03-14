/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanheki <chanheki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 20:21:43 by chanheki          #+#    #+#             */
/*   Updated: 2022/12/19 21:00:04 by chanheki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_new_line(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (NO_NEW_LINE);
}

static char	*get_one_line(char **save)
{
	char	*line;
	char	*new_temp;
	int		len;

	line = NULL;
	len = find_new_line(*save);
	if (len == NO_NEW_LINE)
	{
		if (*save[0] != '\0')
			line = ft_strndup(*save, 0, ft_strlen(*save));
		free(*save);
		*save = NULL;
	}
	else
	{
		line = ft_strndup(*save, 0, len + 1);
		new_temp = ft_strndup(*save, len + 1, ft_strlen(*save) - len);
		free(*save);
		*save = new_temp;
	}
	return (line);
}

static char	*ft_readsize(int fd, char **save, char *buf)
{
	int		index;
	int		len;
	char	*temp;

	index = read(fd, buf, BUFFER_SIZE);
	while (index > 0)
	{
		buf[index] = '\0';
		temp = ft_strjoin(*save, buf);
		free(*save);
		*save = temp;
		len = find_new_line(*save);
		if (len != NO_NEW_LINE)
			return (get_one_line(save));
		index = read(fd, buf, BUFFER_SIZE);
	}
	return (get_one_line(save));
}

char	*get_next_line(int fd)
{
	static char	*save[49152];
	char		buf[BUFFER_SIZE + 1];

	if (fd > 49152 || fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (read(fd, buf, 0) == -1)
	{
		if (save[fd] != NULL)
		{
			free(save[fd]);
			save[fd] = NULL;
		}
		return (NULL);
	}
	if (save[fd] != NULL && find_new_line(save[fd]) != NO_NEW_LINE)
		return (get_one_line(&save[fd]));
	if (save[fd] == NULL)
		save[fd] = ft_strndup("", 0, 0);
	return (ft_readsize(fd, &save[fd], buf));
}
