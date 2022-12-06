/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 12:06:50 by moulmado          #+#    #+#             */
/*   Updated: 2022/12/05 14:37:24 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void add_hsteps_till_wall(t_m_cords *horz, t_cub *cub, int ndx)
{
	horz->wallhitx = 1e18;
	horz->wallhity = 1e18;
	while (horz->xinter >= 0 && horz->xinter <= cub->map_img->img_width &&
		   horz->yinter >= 0 && horz->yinter <= cub->map_img->img_height)
	{
		if (map_has_wall_at(cub, horz->xinter,
							horz->yinter - cub->rays[ndx].isFacingUp))
		{
			horz->wallhitx = horz->xinter;
			horz->wallhity = horz->yinter;
			break;
		}
		else
		{
			horz->xinter += horz->xstep;
			horz->yinter += horz->ystep;
		}
	}
}

static t_m_cords get_horz_cords(t_cub *cub, int ndx)
{
	t_m_cords horz;

	horz.yinter = floor(cub->player->y / BLOCK_SIZE) * BLOCK_SIZE;
	if (cub->rays[ndx].isFacingDown)
		horz.yinter += BLOCK_SIZE;
	horz.xinter = cub->player->x + (horz.yinter - cub->player->y) / tan(cub->rays[ndx].angle);
	horz.ystep = BLOCK_SIZE;
	if (cub->rays[ndx].isFacingUp)
		horz.ystep *= -1;
	horz.xstep = BLOCK_SIZE / tan(cub->rays[ndx].angle);
	if (cub->rays[ndx].isFacingLeft && horz.xstep > 0)
		horz.xstep *= -1;
	if (cub->rays[ndx].isFacingRight && horz.xstep < 0)
		horz.xstep *= -1;
	add_hsteps_till_wall(&horz, cub, ndx);
	return (horz);
}

static void add_vsteps_till_wall(t_m_cords *vert, t_cub *cub, int ndx)
{
	vert->wallhitx = 1e18;
	vert->wallhity = 1e18;
	while (vert->xinter >= 0 && vert->xinter <= cub->map_img->img_width && vert->yinter >= 0 && vert->yinter <= cub->map_img->img_height)
	{
		if (map_has_wall_at(cub, vert->xinter - cub->rays[ndx].isFacingLeft, vert->yinter))
		{
			vert->wallhitx = vert->xinter;
			vert->wallhity = vert->yinter;
			break;
		}
		else
		{
			vert->xinter += vert->xstep;
			vert->yinter += vert->ystep;
		}
	}
}

static t_m_cords get_vert_cords(t_cub *cub, int ndx)
{
	t_m_cords vert;

	vert.xinter = floor(cub->player->x / BLOCK_SIZE) * BLOCK_SIZE;
	if (cub->rays[ndx].isFacingRight)
		vert.xinter += BLOCK_SIZE;
	vert.yinter = cub->player->y + (vert.xinter - cub->player->x) * tan(cub->rays[ndx].angle);
	vert.xstep = BLOCK_SIZE;
	if (cub->rays[ndx].isFacingLeft)
		vert.xstep *= -1;
	vert.ystep = BLOCK_SIZE * tan(cub->rays[ndx].angle);
	if (cub->rays[ndx].isFacingUp && vert.ystep > 0)
		vert.ystep *= -1;
	if (cub->rays[ndx].isFacingDown && vert.ystep < 0)
		vert.ystep *= -1;
	add_vsteps_till_wall(&vert, cub, ndx);
	return (vert);
}

int ray_cast(t_cub *cub, int ndx)
{
	t_m_cords horz;
	t_m_cords vert;

	cub->rays[ndx].angle = mod(cub->rays[ndx].angle, 2 * M_PI);
	cub->rays[ndx].dst = 0;
	cub->rays[ndx].wallHitX = 0;
	cub->rays[ndx].wallHitY = 0;
	cub->rays[ndx].door_hit = 0;
	cub->rays[ndx].isFacingDown =
		cub->rays[ndx].angle > 0 && cub->rays[ndx].angle < M_PI;
	cub->rays[ndx].isFacingUp = !cub->rays[ndx].isFacingDown;
	cub->rays[ndx].isFacingLeft =
		cub->rays[ndx].angle > M_PI_2 && cub->rays[ndx].angle < 3 * M_PI_2;
	cub->rays[ndx].isFacingRight = !cub->rays[ndx].isFacingLeft;
	horz = get_horz_cords(cub, ndx);
	vert = get_vert_cords(cub, ndx);
	horz.dst = distance(cub->player->x, cub->player->y,
						horz.wallhitx, horz.wallhity);
	vert.dst = distance(cub->player->x, cub->player->y,
						vert.wallhitx, vert.wallhity);
	if (horz.dst < vert.dst)
		return (cub->rays[ndx].dst = horz.dst, HORZ);
	return (cub->rays[ndx].dst = vert.dst, VERT);
}
