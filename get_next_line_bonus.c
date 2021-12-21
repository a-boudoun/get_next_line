/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 15:29:36 by aboudoun          #+#    #+#             */
/*   Updated: 2021/12/21 15:30:09 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_line(char **s)
{
	char	*line;
	char	*to_free;
	int		i;

	to_free = *s;
	i = 0;
	while ((*s)[i] != '\n' && (*s)[i] != '\0')
		i++;
	if ((*s)[i] == '\n')
	{
		line = ft_substr(*s, 0, i + 1);
		*s = ft_strdup(*s + i + 1);
	}
	else
	{
		line = ft_strdup(*s);
		*s = NULL;
	}
	free (to_free);
	return (line);
}

int	ft_str(int fd, char **s)
{
	char	*bufer;
	char	*to_free;
	int		byte_read;

	bufer = (char *) malloc(BUFFER_SIZE + 1);
	if (!bufer)
		return (-1);
	byte_read = 4;
	while (!ft_strchr(*s, '\n') && byte_read)
	{
		byte_read = read(fd, bufer, BUFFER_SIZE);
		if (byte_read < 0)
		{
			free (bufer);
			return (-1);
		}
		bufer[byte_read] = '\0';
		to_free = *s;
		*s = ft_strjoin(*s, bufer);
		free(to_free);
	}
	free (bufer);
	return (byte_read);
}

char	*get_next_line(int fd)
{
	static char	*s[1024];	
	char		*line;
	int			byte_read;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (NULL);
	if (!s[fd])
		s[fd] = ft_strdup("");
	byte_read = ft_str(fd, &s[fd]);
	line = ft_line(&s[fd]);
	if (byte_read <= 0 && line[0] == '\0')
	{
		free (line);
		return (NULL);
	}
	return (line);
}
