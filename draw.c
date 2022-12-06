/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:43:50 by moulmado          #+#    #+#             */
/*   Updated: 2022/11/30 14:50:11 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void draw_line(t_cub *cub, double x2, double y2)
{
	double step;
	double xin;
	double yin;
	int k;

	if (fabs(x2 - cub->player->x) >= fabs(y2 - cub->player->y))
		step = fabs(x2 - cub->player->x);
	else
		step = fabs(y2 - cub->player->y);
	xin = (float)(x2 - cub->player->x) / step;
	yin = (float)(y2 - cub->player->y) / step;
	x2 = cub->player->x;
	y2 = cub->player->y;
	k = 0;
	while (k++ < step)
	{
		x2 += xin;
		y2 += yin;
		my_mlx_pixel_put(cub->map_img, x2, y2, 0xFD0000);
	}
}

static double find_x_of_wall(t_cub *cub, int ndx)
{
	if (cub->rays[ndx].type == NO)
		return (mod(cub->rays[ndx].wallHitX, BLOCK_SIZE));
	else if (cub->rays[ndx].type == SO)
		return (BLOCK_SIZE - mod(cub->rays[ndx].wallHitX, BLOCK_SIZE));
	else if (cub->rays[ndx].type == EA)
		return (mod(cub->rays[ndx].wallHitY, BLOCK_SIZE));
	else
		return (BLOCK_SIZE - mod(cub->rays[ndx].wallHitY, BLOCK_SIZE));
}

void draw_vert_line(t_cub *cub, double y1, double y2, int ndx)
{
	double y;
	double x;
	t_ratio r;
	int j;
	int i;

	r.x = cub->walls[cub->rays[ndx].type].img_width / (BLOCK_SIZE);
	r.y = cub->walls[cub->rays[ndx].type].img_height / (y2 - y1);
	y = 0;
	if (y1 < 0)
	{
		y = -y1;
		y1 = 0;
	}
	if (y2 > cub->win_height)
		y2 = cub->win_height;
	x = find_x_of_wall(cub, ndx);
	while (y1 < y2)
	{
		j = (float)y * r.y;
		i = (float)x * r.x;
		my_mlx_pixel_put(cub->rend3D, ndx, y1++,
						 cub->walls[cub->rays[ndx].type].colors[j * cub->walls[cub->rays[ndx].type].img_width + i]);
		y++;
	}
}

void fill_floor_nd_ceiling(t_cub *cub, int c_color, int f_color)
{
	int ndx;
	int jdx;

	ndx = 0;
	while (ndx < (cub->win_height / 2))
	{
		jdx = 0;
		while (jdx < cub->win_width)
			my_mlx_pixel_put(cub->rend3D, jdx++, ndx, f_color);
		ndx++;
	}
	ndx = cub->win_height / 2;
	while (ndx < cub->win_height)
	{
		jdx = 0;
		while (jdx < cub->win_width)
			my_mlx_pixel_put(cub->rend3D, jdx++, ndx, c_color);
		ndx++;
	}
}
