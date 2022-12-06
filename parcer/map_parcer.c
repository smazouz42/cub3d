/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parcer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smazouz <smazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:24:07 by moulmado          #+#    #+#             */
/*   Updated: 2022/12/06 04:45:09 by smazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	array_size_(char **map, int *max)
{
	int	i;

	i = 0;
	*max = 0;
	if (!map)
		return (0);
	while (map[i])
	{
		if ((int)ft_strlen(map[i]) > *max)
			*max = (int)ft_strlen(map[i]);
		i++;
	}
	return (i);
}

char	*new_line(char *str, int max)
{
	char	*ret;
	int		i;

	i = 0;
	ret = (char *)calloc(max + 1, sizeof(char));
	while (str[i])
	{
		if (str[i] != ' ')
			ret[i] = str[i];
		else
			ret[i] = '#';
		i++;
	}
	while (i < max)
	{
		ret[i] = '#';
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	**map_clone(char **map)
{
	int		size;
	int		max_line;
	int		i;
	char	**new_map;

	i = 0;
	size = array_size_(map, &max_line);
	new_map = calloc((size + 1), sizeof(char *));
	while (map[i])
	{
		new_map[i] = new_line(map[i], max_line);
		i++;
	}
	new_map[i] = NULL;
	return (new_map);
}

static void	check_map_validity_utils(t_item *item, int i, int j, int *players)
{
	if (item->map[i][j] == 'E' || item->map[i][j] == 'W'
		|| item->map[i][j] == 'S' || item->map[i][j] == 'N')
	{
		if ((*players) == 0)
		{
			item->player_x = i;
			item->player_y = j;
			item->player_dir = item->map[i][j];
			item->map[i][j] = '0';
			(*players)++;
		}
		else
		{
			printf("Error:\n Too many players.\n");
			exit(0);
		}
	}
	else if (item->map[i][j] != 'D')
	{
		printf("Error:\n Undefined character.\n");
		exit(0);
	}
}

void	check_map_validity(t_item *item)
{
	int	i;
	int	j;
	int	players;

	i = 0;
	players = 0;
	while (item->map[i])
	{
		j = 0;
		while (item->map[i][j])
		{
			if (item->map[i][j] != ' ' && item->map[i][j] != '1'
				&& item->map[i][j] != '0')
				check_map_validity_utils(item, i, j, &players);
			j++;
		}
		i++;
	}
	if (!players)
	{
		printf("Error\n No Player");
		exit(0);
	}
}

int	fisrt_last_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '1' && line[i] != '#')
		{
			printf("Error:\n Corrupted first and last wall\n");
			return (0);
		}
		i++;
	}
	return (1);
}

static void	map_full_check_utils(int column, char **c_map, t_item *item)
{
	int	row;

	row = 0;
	while (c_map[column][row])
	{
		if (c_map[column][row] == '0' || c_map[column][row] == 'D')
		{
			if (row == 0 || row == ft_strlen(c_map[column]) - 1)
			{
				printf("Error:\n Unclosed walls.\n");
				free_str(c_map);
				free_str(item->map);
				exit(0);
			}
			if (c_map[column][row] == 'D' && ((c_map[column][row - 1] != '1'
				|| c_map[column][row + 1] != '1')))
			{
				printf("Error:\n door mfaki.\n");
				free_str(c_map);
				free_str(item->map);
				exit(0);
			}
			if (!ft_strchr("1NSEW0D", c_map[column][row - 1])
				|| !ft_strchr("1NSEW0D", c_map[column][row + 1]) ||
				!ft_strchr("1NSEW0", c_map[column - 1][row])
				|| !ft_strchr("1NSEW0", c_map[column + 1][row]))
			{
				printf("Error:\n Unclosed walls.\n");
				free_str(c_map);
				free_str(item->map);
				exit(0);
			}
		}
		row++;
	}
}

void	map_full_check(t_item *item)
{
	int		column;
	char	**c_map;

	column = 0;
	check_map_validity(item);
	c_map = map_clone(item->map);
	while (c_map[column])
	{
		if (column == 0 || c_map[column + 1] == NULL)
		{
			if (fisrt_last_line(c_map[column]) == 0)
			{
				free_str(c_map);
				free_str(item->map);
				exit(1);
			}
		}
		else
			map_full_check_utils(column, c_map, item);
		column++;
	}
	free_str(c_map);
}