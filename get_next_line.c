/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpimenta <mpimenta@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 13:47:48 by mpimenta          #+#    #+#             */
/*   Updated: 2022/07/03 21:05:09 by mpimenta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	char	looking;

	looking = (char) c;
	str = (char *)s;
	while (*str != looking)
	{
		if (*str == '\0' && looking != '\0')
			return (NULL);
		str++;
	}
	return (str);
}

static char	ft_cleaning_read_line(char *line)
{
	int	i;
	int	j;
	char	line_ret;

	i = 0;
	j = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (!line[i])
	{
		free(line);
		return (NULL);
	}
	line_ret = malloc(sizeof(char) * (ft_strlen(line) - i + 1));
	if (!line_ret)
		return (NULL);
	while (line[i] != '\0')
	{
		line_ret[j] = line[i];
		j++;
		i++;
	}
	line_ret[j + 1] = '\0';
	free(line);
	return (line_ret);
}

static char	*ft_getting_line(char *line)
{
	char	ret;
	size_t	len;

	if (!line)
		return (NULL);
	len = 0;
	while (line[len] && line[len] != '\n')
		len++;
	ret = malloc(sizeof(char) * (len + 2));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, line, len + 1);
	if (line[len] == '\n')
		ret[len + 1] = '\n';
	ret[len] = '\0';
	return (ret);
}

static char	*ft_reading_line(int fd, char *line)
{
	int	doing;
	char	*buffer;
	char	*swap;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	doing = 1;
	while (doing != 0 && !ft_strchr(line, '\n'))
	{
		doing = read(fd, buffer, BUFFER_SIZE);
		if (doing == -1)
		{
			free(line);
			free(buffer);
			return (0);
		}
		buffer[doing] = '\0';
		swap = line;
		line = ft_strjoin(swap, buffer);
		free(swap);
	}
	free(buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (!line)
	{
		line = malloc(sizeof(char));
		line[0] = '\0';
	}
	line = ft_reading_line(fd, line);
	if (!line)
		return (0);
	ret = ft_getting_line(line);
	line = ft_cleaning_read_line(line);
	return (ret);
}
