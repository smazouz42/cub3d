#include"cub3d.h"

static size_t	ft_strlcpy(char *dst, const char *src, size_t destsize)
{
	size_t			i;
	unsigned int	l;

	i = 0;
	l = 0;
	while (src[l] != '\0')
		l++;
	if (destsize == 0)
		return (l);
	while (src[i] != '\0' && i < (destsize - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (l);
}
static char	**free_tab(char	**tab)
{
	int	x;

	x = 0;
	while (tab[x])
	{
		free(tab[x]);
		x++;
	}
	free(tab);
	return (NULL);
}

static char	*get_next_word(char *s, char c, int *len)
{
	int				x;
	unsigned int	y;
	unsigned int	start;

	x = 0;
	y = 0;
	start = *len;
	while (s[start] == c)
		start++;
	while (s[x + start] != '\0' && s[x + start] != c)
		x++;
	*len = x;
	return (s + start);
}

static int	ft_word_count(const char *str, char c)
{
	size_t	x;
	size_t	y;

	y = 0;
	x = 0;
	if (str[x] == c && c != '\0')
		x++;
	while (str[x])
	{
		if (str[x] == c)
		{
			if (str[x - 1] != c)
				y++;
		}
		x++;
	}
	if (str[x - 1] != c && str[x - 1] != '\0')
		y++;
	return (y);
}

char	**ft_split(char const *s, char c)
{
	char			**str;
	char			*temp;
	int				*len2;
	int				k;
	int				i;

	if (!s)
		return (NULL);
	i = -1;
	k = 0;
	temp = (char *)s;
	str = (char **)malloc((ft_word_count(s, c) + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	len2 = &k;
	while (ft_word_count(s, c) > ++i)
	{
		temp = get_next_word(temp, c, len2);
		str[i] = (char *)malloc((*len2 + 1) * sizeof(char));
		if (!str[i])
			return (free_tab(str));
		ft_strlcpy(str[i], temp, (*(len2) + 1));
	}
	str[i] = NULL;
	return (str);
}