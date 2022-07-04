/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpimenta <mpimenta@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 15:16:45 by mpimenta          #+#    #+#             */
/*   Updated: 2022/07/04 11:33:36 by mpimenta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	count;

	count = 0;
	while (s[count] != '\0')
	{
		count++;
	}
	return (count);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dest;
	const char	*source;

	dest = (char *)dst;
	source = (char *)src;
	if (!dst && !src)
		return (0);
	while (n--)
	{
		*dest++ = *source++;
	}
	return (dst);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	if (ft_strlen(src) + 1 < dstsize)
		ft_memcpy(dst, src, ft_strlen(src) + 1);
	else if (dstsize > 0)
		ft_memcpy(dst, src, dstsize - 1);
	dst[dstsize - 1] = '\0';
	return (ft_strlen(src));
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	ret;

	j = 0;
	i = ft_strlen(dst);
	if (dstsize > i)
		ret = i + ft_strlen(src);
	else
		ret = ft_strlen(src) + dstsize;
	while (src[j] != '\0' && i + 1 < dstsize)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (ret);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s3;
	size_t	len_s1;
	size_t	len_s2;

	if (!s2)
		return (0);
	else if (!s1 && s2)
	{
		s3 = malloc(sizeof(char) * (ft_strlen(s2) + 1));
		if (!s3)
			return (NULL);
		ft_strlcpy(s3, s2, ft_strlen(s2) + 1);
		return (s3);
	}
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	s3 = malloc(sizeof(char) * (len_s1 + len_s2));
	if (!s3)
		return (0);
	ft_strlcpy(s3, s1, ft_strlen(s1) + 1);
	ft_strlcat(s3, s2, ft_strlen(s3) + ft_strlen(s2) + 1);
	return (s3);
}
