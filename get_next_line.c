/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:43:22 by aboudoun          #+#    #+#             */
/*   Updated: 2021/11/27 15:39:20 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define BUFER_SIZE 8
#include<fcntl.h>
#include<stdio.h>
#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s)

{
	char	*dest;
	int		i;

	dest = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	while (*str != (char)c)
	{
		if (*str == '\0')
			return (NULL);
		str++;
	}
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*str;

	i = 0;
	str = (char *)malloc(sizeof(char) * len + 1);
	if (str == NULL)
		return (NULL);
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

//................................................................................
char *ft_line(char **s)
{
    char *line;
    int i;
    
    i = 0;
    while(*s[i] != '\0')
    {
        if (*s[i] == '\n')
            break ;
        i++;
    }
    if (line[i] == '\n')
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
    static char *s;
    char *line;
    int byte_read;
    char *bufer;

    if (fd < 0 || BUFER_SIZE <= 0)
        return NULL;
    bufer = (char *) malloc(BUFER_SIZE + 1);
    if(!bufer)
        return (NULL);
 //   *s = ft_strdup("");
    byte_read = 4;
    while(!ft_strchr(s, '\n') && byte_read)
    {
        byte_read = read(fd, bufer, BUFER_SIZE);
        bufer[byte_read] = '\0';
        s = ft_strjoin(s, bufer);
    }
    free (bufer);
    line = ft_line(&s);
    return(line);
}
int main()
{
    int fd;
    char *lin;
    fd = open("test.txt", O_RDONLY);
    printf("%d", fd);
    lin = get_next_line(fd);
    printf("%s", lin);
}