/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rend3R.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:08:07 by moulmado          #+#    #+#             */
/*   Updated: 2022/12/02 18:08:52 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void rend3r_walls(t_cub *cub, int ndx)
{
	double dst_2_plan;
	double wall_height;
	double correct_dst;

	correct_dst = cub->rays[ndx].dst * cos(cub->rays[ndx].angle - cub->player->rotation_angle);
	dst_2_plan = (cub->win_width / 2) / tan(FOV_ANGLE / 2);
	wall_height = (BLOCK_SIZE / correct_dst) * dst_2_plan;
	draw_vert_line(cub, (cub->win_height / 2) - (wall_height / 2),
		(cub->win_height / 2) + (wall_height / 2), ndx);
}

void rend3R_init(t_cub *cub)
{
	cub->rend3D->img = mlx_new_image(cub->mlx, cub->win_width,
									 cub->win_height);
	protect(cub->rend3D->img);
	cub->rend3D->addr = mlx_get_data_addr(cub->rend3D->img,
										  &cub->rend3D->bits_per_pixel, &cub->rend3D->line_length,
										  &cub->rend3D->endian);
	protect(cub->rend3D->addr);
	fill_floor_nd_ceiling(cub, get_color(cub->map_items->ceiling_colors),
						  get_color(cub->map_items->floor_colors));
}