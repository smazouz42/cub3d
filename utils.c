/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smazouz <smazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 09:16:49 by smazouz           #+#    #+#             */
/*   Updated: 2022/06/23 09:18:18 by smazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"
char	*ft_strchr(const char *s, int c)
{
	while (*s || c == '\0')
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}
size_t  ft_strlen(const char *str)
{
    int len;

    len = 0;
    while(str[len])
        len++;
    return(len);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	i;
	int	count;

	res = 0;
	i = 0;
	count = 1;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n')
		|| (str[i] == '\v') || (str[i] == '\r') || (str[i] == '\f'))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			count = -1;
		i++;
	}
	while (str[i] && (str[i] >= '0') && (str[i] <= '9'))
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	if (count == -1)
		return (-res);
	else
		return (res);
}

char	*ft_strdup(const char *s1)
{
	unsigned int	s;
	unsigned int	i;
	char			*dst;

	i = 0;
	s = 0;
	while (s1[s] != '\0')
		s++;
	dst = (char *)malloc((s + 1) * sizeof(*dst));
	if (dst == 0)
		return (NULL);
	while (i < s)
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*dst;
	unsigned int	len;
	unsigned int	j;
	unsigned int	i;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = -1;
	len = (ft_strlen(s1)) + (ft_strlen(s2));
	dst = (char *)malloc((len + 1) * sizeof(*dst));
	if (dst == 0)
		return (NULL);
	while (s1[i] != '\0')
	{
		dst[i] = s1[i];
		i++;
	}
	while (s2[++j])
	{
		dst[i] = s2[j];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}