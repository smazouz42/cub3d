/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 10:48:30 by moulmado          #+#    #+#             */
/*   Updated: 2022/11/30 21:09:14 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void angle_update(t_cub *cub)
{
	cub->player->rotation_angle +=
		cub->player->turn_direction * cub->player->rotation_speed;
	cub->player->rotation_angle =
		mod(cub->player->rotation_angle, 2 * M_PI);
}

static int check_sides(t_cub *cub)
{
	double move_step;
	int grid_i;
	int grid_j;

	move_step = cub->player->walk_direction * cub->player->move_speed;
	grid_i = (cub->player->y +
			  sin(cub->player->rotation_angle + cub->player->walk_angle + M_PI_2) * move_step) /
			 BLOCK_SIZE;
	grid_j = (cub->player->x +
			  cos(cub->player->rotation_angle + cub->player->walk_angle + M_PI_2) * move_step) /
			 BLOCK_SIZE;
	if (cub->map_items->map[grid_i][grid_j] != '1')
		return (1);
	grid_i = (cub->player->y +
			  sin(cub->player->rotation_angle + cub->player->walk_angle - M_PI_2) * move_step) /
			 BLOCK_SIZE;
	grid_j = (cub->player->x +
			  cos(cub->player->rotation_angle + cub->player->walk_angle - M_PI_2) * move_step) /
			 BLOCK_SIZE;
	if (cub->map_items->map[grid_i][grid_j] != '1')
		return (1);
	return (0);
}

void pos_update(t_cub *cub)
{
	double move_step;
	int grid_i;
	int grid_j;

	move_step = cub->player->walk_direction * cub->player->move_speed;
	grid_i = (cub->player->y +
			  sin(cub->player->rotation_angle + cub->player->walk_angle) * move_step) /
			 BLOCK_SIZE;
	grid_j = (cub->player->x +
			  cos(cub->player->rotation_angle + cub->player->walk_angle) * move_step) /
			 BLOCK_SIZE;
	if (is_same_block(cub, grid_i, grid_j))
	{
		cub->player->x += cos(cub->player->rotation_angle + cub->player->walk_angle) * move_step;
		cub->player->y += sin(cub->player->rotation_angle + cub->player->walk_angle) * move_step;
	}
	else if (cub->map_items->map[grid_i][grid_j] == '0' && check_sides(cub))
	{
		cub->player->x += cos(cub->player->rotation_angle + cub->player->walk_angle) * move_step;
		cub->player->y += sin(cub->player->rotation_angle + cub->player->walk_angle) * move_step;
	}
}
