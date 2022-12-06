/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smazouz <smazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 13:13:54 by moulmado          #+#    #+#             */
/*   Updated: 2022/12/06 04:44:16 by smazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	find_new_str_len(char **map)
{
	int	len;
	int	ndx;

	len = 0;
	ndx = 0;
	while (map[ndx])
	{
		if (len < ft_strlen(map[ndx]))
			len = ft_strlen(map[ndx]);
		ndx++;
	}
	return (len);
}

static char	*fixed_str(char *s, int len, t_item *map_items)
{
	char	*re;
	int		ndx;

	re = (char *)calloc(len + 1, sizeof(char));
	ndx = -1;
	while (s[++ndx])
	{
		if (s[ndx] == 'S' || s[ndx] == 'N' || s[ndx] == 'W' || s[ndx] == 'E')
		{
			map_items->player_dir = s[ndx];
			s[ndx] = '0';
		}
		re[ndx] = s[ndx];
	}
	while (ndx < len)
		re[ndx++] = ' ';
	re[ndx] = '\0';
	free(s);
	return (re);
}

static int	map_size(char **map)
{
	int	size;

	size = 0;
	while (map[size])
		size++;
	return (size);
}

void	fix_map(t_item *map_items)
{
	int	len;
	int	ndx;

	len = find_new_str_len(map_items->map);
	ndx = -1;
	while (map_items->map[++ndx])
		map_items->map[ndx] = fixed_str(map_items->map[ndx], len, map_items);
	map_items->map_height = map_size(map_items->map);
	map_items->map_width = len;
}
