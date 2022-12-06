/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 13:16:33 by moulmado          #+#    #+#             */
/*   Updated: 2022/12/04 13:04:55 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int map_has_wall_at(t_cub *cub, double x, double y)
{
	int grid_i;
	int grid_j;

	grid_i = y / BLOCK_SIZE;
	grid_j = x / BLOCK_SIZE;
	return (cub->map_items->map[grid_i][grid_j] - '0');
}

int is_same_block(t_cub *cub, int grid_i, int grid_j)
{
	int o_i;
	int o_j;

	o_i = cub->player->y / BLOCK_SIZE;
	o_j = cub->player->x / BLOCK_SIZE;
	if (o_i == grid_i && o_j == grid_j)
		return (1);
	return (0);
}

int door_check(t_cub *cub, double x, double y, int ndx)
{
	int grid_i;
	int grid_j;
	int dst;

	grid_i = y / BLOCK_SIZE;
	grid_j = x / BLOCK_SIZE;
	dst = distance(cub->player->x, cub->player->y, x, y);
	cub->rays[ndx].door_hit = cub->map_items->map[grid_i][grid_j] - '0'
			&& dst > BLOCK_SIZE * 2;
	return (cub->rays[ndx].door_hit);
}