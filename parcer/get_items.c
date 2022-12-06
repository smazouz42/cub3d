/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_items.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smazouz <smazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 11:56:16 by moulmado          #+#    #+#             */
/*   Updated: 2022/12/06 04:39:00 by smazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	map_size(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return (0);
	while (map[i])
		i++;
	return (i);
}

static void	check_color_range(char **rgb_tab)
{
	int	index;

	index = 0;
	while (rgb_tab[index])
	{
		if (ft_atoi(rgb_tab[index]) < 0 || ft_atoi(rgb_tab[index]) > 255)
		{
			printf("Error : \n color value out of range");
			exit(0);
		}
		index++;
	}
}

static void	check_color_validity(char *first_color, char *second_color)
{
	int	index;

	index = 1;
	if (first_color[0] == ',' || first_color[ft_strlen(first_color) - 1] == ','
		|| second_color[0] == ','
		|| second_color[ft_strlen(second_color) - 1] == ',')
	{
		printf("Error:\n Flawed floor or ceiling color\n");
		exit(0);
	}
	while (index < ft_strlen(first_color) - 1)
	{
		if (first_color[index] == ',' && first_color[index + 1] == ',')
		{
			printf("Error:\n Flawed floor or ceiling color\n");
			exit(0);
		}
		index++;
	}
	index = 1;
	while (index < ft_strlen(second_color) - 1)
	{
		if (second_color[index] == ',' && second_color[index + 1] == ',')
		{
			printf("Error:\n Flawed floor or ceiling color\n");
			exit(0);
		}
		index++;
	}
}

void	get_ceiling_rgb(char **c_first, char **c_second, t_item *map_items)
{
	char	**tmp;

	tmp = c_first;
	c_first = ft_split(c_first[1], ',');
	free_str(tmp);
	check_color_range(c_first);
	tmp = c_second;
	c_second = ft_split(c_second[1], ',');
	free_str(tmp);
	check_color_range(c_second);
	if (map_size(c_first) != 3 || map_size(c_second) != 3)
	{
		printf("Error:\n Flawed floor or ceiling color\n");
		free_str(c_first);
		free_str(c_second);
		exit(3);
	}
	map_items->ceiling_colors[0] = ft_atoi(c_first[0]);
	map_items->ceiling_colors[1] = ft_atoi(c_first[1]);
	map_items->ceiling_colors[2] = ft_atoi(c_first[2]);
	map_items->floor_colors[0] = ft_atoi(c_second[0]);
	map_items->floor_colors[1] = ft_atoi(c_second[1]);
	map_items->floor_colors[2] = ft_atoi(c_second[2]);
	free(c_first);
	free(c_second);
}

static void	get_floor_rgb(char **c_first, char **c_second, t_item *map_items)
{
	char	**tmp;

	tmp = c_first;
	c_first = ft_split(c_first[1], ',');
	check_color_range(c_first);
	free_str(tmp);
	tmp = c_second;
	c_second = ft_split(c_second[1], ',');
	check_color_range(c_second);
	free_str(tmp);
	if (map_size(c_first) != 3 || map_size(c_second) != 3)
	{
		printf("Error:\n Flawed floor or ceiling color\n");
		free_str(c_first);
		free_str(c_second);
		exit(3);
	}
	map_items->ceiling_colors[0] = ft_atoi(c_second[0]);
	map_items->ceiling_colors[1] = ft_atoi(c_second[1]);
	map_items->ceiling_colors[2] = ft_atoi(c_second[2]);
	map_items->floor_colors[0] = ft_atoi(c_first[0]);
	map_items->floor_colors[1] = ft_atoi(c_first[1]);
	map_items->floor_colors[2] = ft_atoi(c_first[2]);
	free(c_first);
	free(c_second);
}

int	get_colors(t_item *map_items, char *colors)
{
	char	**c_table;
	char	**c_first;
	char	**c_second;
	int		i;
	char	**tmp;

	i = 0;
	c_table = ft_split(colors, '\n');
	if (map_size(c_table) != 2)
	{
		printf("Error : \n couldn't find all colors needed");
		exit(0);
	}
	c_first = ft_split(c_table[0], ' ');
	c_second = ft_split(c_table[1], ' ');
	free_str(c_table);
	if (ft_strlen(c_first[0]) > 1 || ft_strlen(c_second[0]) > 1)
	{
		printf("Error\n undefined row ");
		free_str(c_first);
		free_str(c_second);
		free(colors);
		exit(1);
	}
	if (c_first[0][0] == c_second[0][0])
	{
		printf("Error:\n Duplicated color row.\n");
		free_str(c_first);
		free_str(c_second);
		free(colors);
		exit(3);
	}
	check_color_validity(c_first[1], c_second[1]);
	if (c_first[0][0] == 'C' || c_second[0][10] == 'C')
		get_ceiling_rgb(c_first, c_second, map_items);
	else
		get_floor_rgb(c_first, c_second, map_items);
	map_items->floor_colors[3] = '\0';
	map_items->ceiling_colors[3] = '\0';
	return (0);
}

void	take_walls(t_item *map_items, char *walls)
{
	int		i;
	char	**wall_array;
	char	**tmp;

	i = 0;
	wall_array = ft_split(walls, '\n');
	while (wall_array[i])
	{
		tmp = ft_split(wall_array[i], ' ');
		if (map_size(tmp) != 2)
		{
			printf("Error\n couldn't foud texture");
			free_str(wall_array);
			exit(1);
		}
		if (ft_strlen(tmp[0]) > 2)
		{
			printf("Error\n undefined row ");
			free_str(wall_array);
			exit(1);
		}
		if (tmp[0][0] == 'N')
			map_items->NO = ft_strdup(tmp[1]);
		else if (tmp[0][0] == 'S')
			map_items->SO = ft_strdup(tmp[1]);
		else if (tmp[0][0] == 'E')
			map_items->EA = ft_strdup(tmp[1]);
		else if (tmp[0][0] == 'W')
			map_items->WE = ft_strdup(tmp[1]);
		i++;
		free_str(tmp);
	}
	if (!map_items->EA || !map_items->SO || !map_items->NO || !map_items->WE)
	{
		printf("Error\n couldn't foud texture");
		free_str(wall_array);
		exit(1);
	}
	free_str(wall_array);
}