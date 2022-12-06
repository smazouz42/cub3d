/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smazouz <smazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 04:45:28 by smazouz           #+#    #+#             */
/*   Updated: 2022/12/06 04:49:50 by smazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*map_read(int fd)
{
	char	line[1000000] = "";
	char	buf[2] = "";
	int		i;
	int		n;

	if (fd < 0)
		return (NULL);
	i = 0;
	n = 0;
	while ((n = read(fd, buf, 1)) > 0)
	{
		buf[n] = '\0';
		line[i] = buf[0];
		if (buf[0] == '\n')
		{
			line[i + 1] = '\0';
			return (ft_strdup(line));
		}
		i++;
	}
	line[i] = '\0';
	if (n < 0)
		return (NULL);
	if (line[0] == '\0')
		return (NULL);
	return (ft_strdup(line));
}

static char	*make_colors(char *colors, char *map, char *line, char *walls)
{
	static int	rows;
	char		*tmp;

	if (rows < 2)
	{
		if (!colors)
			colors = ft_strdup(line);
		else
		{
			tmp = colors;
			colors = ft_strjoin(colors, line);
			free(tmp);
		}
	}
	else
	{
		printf("Error:\n Duplicated color row.\n");
		free(map);
		free(walls);
		free(colors);
		free(line);
		exit(1);
	}
	rows++;
	return (colors);
}

static char	*make_walls(char *colors, char *map, char *line, char *walls)
{
	char		*tmp;
	static int	rows;

	if (rows < 4)
	{
		if (!walls)
			walls = ft_strdup(line);
		else
		{
			tmp = walls;
			walls = ft_strjoin(walls, line);
			free(tmp);
		}
	}
	else
	{
		printf("Error:\n Duplicated walls.\n");
		free(map);
		free(walls);
		free(colors);
		free(line);
		exit(1);
	}
	rows++;
	return (walls);
}

static char	*make_map_row(char *map, char *line, int *flag)
{
	char	*tmp;

	*(flag) = 1;
	if (line[0] == '\n' || is_empty(line) == 1)
	{
		printf("Error:\n Empty line\n");
		exit(0);
	}
	if (!map)
		map = ft_strdup(line);
	else
	{
		tmp = map;
		map = ft_strjoin(map, line);
		free(tmp);
	}
	return (map);
}

static	void make_matrix_utils(char *map, t_item *map_items, char *colors, char *walls)
{
	if (map == NULL)
	{
		printf("Error\n");
		exit(1);
	}
	map_items->map = ft_split(map, '\n');
	if (get_colors(map_items, colors) == 3)
	{
		free(map);
		free(colors);
		free(walls);
		free_str(map_items->map);
		exit(1);
	}
	take_walls(map_items, walls);
	free(map);
	free(colors);
	free(walls);
}

void	make_matrix(int fd, t_item *map_items)
{
	char	*str;
	int		flag;
	char	*map;
	char	*walls;
	char	*colors;

	map = NULL;
	walls  = NULL;
	colors = NULL;
	flag = 0;
	str = map_read(fd);
	while (str)
	{
		if (is_color(str) == 1 && flag == 0)
			colors = make_colors(colors, map, str, walls);
		else if (is_wall(str) == 1 && flag == 0)
			walls = make_walls(colors, map, str, walls);
		else if (flag == 1 || is_line(str) == 1)
			map = make_map_row(map, str, &flag);
		else if (!is_empty(str))
		{
			free(str);
			printf("Error : \n undefined row\n");
			exit(0);
		}
		free(str);
		str = map_read(fd);
	}
	make_matrix_utils(map, map_items, colors, walls);
}

t_item	*parser(void)
{
	t_item	*item;
	int		fd;

	item = (t_item *)calloc(1, sizeof(t_item));
	fd = open("map", O_RDONLY);
	make_matrix(fd, item);
	map_full_check(item);
	fix_map(item);
	return (item);
}
