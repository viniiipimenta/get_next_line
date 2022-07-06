/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpimenta <mpimenta@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 17:56:50 by mpimenta          #+#    #+#             */
/*   Updated: 2022/07/06 10:31:39 by mpimenta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_cleaning_read_line(char *line)
{
	int		i;
	int		j;
	char	*line_ret;

	i = 0;
	j = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (!line[i])
	{
		free(line);
		return (NULL);
	}
	line_ret = (char *)malloc(sizeof(char) * (ft_strlen(line) - i + 1));
	if (!line_ret)
		return (NULL);
	while (line[i] != '\0')
	{
		line_ret[j++] = line[++i];
	}
	line_ret[j] = '\0';
	free(line);
	return (line_ret);
}

static char	*ft_getting_line(char *line)
{
	char	*ret;
	size_t	len;

	if (!*line)
		return (NULL);
	len = 0;
	while (line[len] && line[len] != '\n')
		len++;
	ret = malloc(sizeof(char) * (len + 2));
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, line, len + 1);
	if (line[len] == '\n')
		ret[len] = '\n';
	ret[len + 1] = '\0';
	return (ret);
}

static char	*ft_reading_line(int fd, char *line)
{
	int		doing;
	char	*buffer;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	doing = 1;
	while (doing != 0 && !ft_strchr(line, '\n'))
	{
		doing = read(fd, buffer, BUFFER_SIZE);
		if (doing == -1)
		{
			free(buffer);
			return (0);
		}
		buffer[doing] = '\0';
		if (!line)
		{
			line = malloc(sizeof(char));
			line[0] = '\0';
		}
		line = ft_strjoin(line, buffer);
	}
	free(buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_reading_line(fd, line);
	if (!line)
		return (NULL);
	ret = ft_getting_line(line);
	line = ft_cleaning_read_line(line);
	return (ret);
}
