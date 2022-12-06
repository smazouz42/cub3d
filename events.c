/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 09:40:33 by moulmado          #+#    #+#             */
/*   Updated: 2022/12/05 16:06:38 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int mouse_move(int x, int y, t_cub *cub)
{
	// mlx_clear_window(cub->mlx, cub->mlx_window);
    (void)y;
    if(cub->player->mouse_position != -1e9)
    {
        if(x >=0  && x <=cub->win_width && y >=0 && y<=cub->win_height)
        {
            cub->player->turn_direction = -(cub->player->mouse_position - x/BLOCK_SIZE);
            angle_update(cub);
            map_init(cub);
			mlx_loop_hook(cub->mlx, map_init, cub);
        }
    }
    cub->player->mouse_position = x/BLOCK_SIZE;
    return(0);
}

void	spray(t_cub *cub)
{
	static int update;

	if (update % 2)
	{
		cub->sprite_ndx++;
		cub->sprite_ndx %= 12;
	}
	update++;
}

static void	key_press_bonus(int keycode, t_cub *cub)
{
	if (keycode == S)
	{
		cub->player->walk_direction = -1;
		cub->sprite_ndx = 0;
	}
	if (keycode == W)
	{
		cub->player->walk_direction = 1;
		cub->sprite_ndx = 0;
	}
	if (keycode == RIGHT)
	{
		cub->player->turn_direction = 1;
		cub->sprite_ndx = 0;
	}
	if (keycode == LEFT)
	{
		cub->player->turn_direction = -1;
		cub->sprite_ndx = 0;
	}
	if (keycode == FIRE)
		spray(cub);
}

int key_press(int keycode, t_cub *cub)
{
	mlx_clear_window(cub->mlx, cub->mlx_window);
	if (keycode == ESC)
		exit(0);
	if (keycode == A)
	{
		cub->player->walk_direction = 1;
		cub->player->walk_angle = -M_PI_2;
		cub->sprite_ndx = 0;
	}
	if (keycode == D)
	{
		cub->player->walk_direction = 1;
		cub->player->walk_angle = M_PI_2;
		cub->sprite_ndx = 0;
	}
	key_press_bonus(keycode, cub);
	pos_update(cub);
	angle_update(cub);
	map_init(cub);
	mlx_loop_hook(cub->mlx, map_init, cub);
	return (0);
}

int key_release(int keycode, t_cub *cub)
{
	if (keycode == A || keycode == S || keycode == D || keycode == W)
	{
		cub->player->walk_direction = 0;
		cub->player->walk_angle = 0;
	}
	if (keycode == RIGHT || keycode == LEFT)
		cub->player->turn_direction = 0;
	if (keycode == FIRE)
		cub->sprite_ndx = 0;
	mlx_loop_hook(cub->mlx, map_init, cub);
	return (0);
}