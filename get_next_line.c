/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:43:22 by aboudoun          #+#    #+#             */
/*   Updated: 2021/12/06 14:27:44 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"

char *ft_line(char **s)
{
    char *line;
    int i;
    
    i = 0;
    while((*s)[i] != '\n' && (*s)[i] != '\0')
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
    return (line);
}

char *get_next_line(int fd)
{
    static char *s = NULL;
    char *line;
    int byte_read;
    char *bufer;
	char *forfree;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;
	if (!s)
		s = ft_strdup("");
    
    byte_read = 4;
    while(!ft_strchr(s, '\n') && byte_read)
    {
		bufer = (char *) malloc(BUFFER_SIZE + 1);
    	if(!bufer)
        	return (NULL);
		if ((byte_read = read(fd, bufer, BUFFER_SIZE)) < 0)
		{
			free (bufer);
			return (NULL);
		}
        bufer[byte_read] = '\0';
		forfree = s;
        s = ft_strjoin(s, bufer);
		free(forfree);
		free (bufer);
    }
    line = ft_line(&s);
	if (byte_read == 0 && line[0] == '\0')
	{
		free (line);
		return (NULL);
	}
    return(line);
}
