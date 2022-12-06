/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:47:43 by moulmado          #+#    #+#             */
/*   Updated: 2022/12/02 18:07:06 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void mem_alloc(t_cub *cub)
{
	cub->player = (t_p_data *)calloc(1, sizeof(t_p_data));
	protect(cub->player);
	cub->map_img = (t_data *)calloc(1, sizeof(t_data));
	protect(cub->map_img);
	cub->rays = (t_ray *)calloc(cub->num_rays, sizeof(t_ray));
	protect(cub->rays);
	cub->rend3D = (t_data *)calloc(1, sizeof(t_data));
	protect(cub->rend3D);
	cub->walls = (t_data *)calloc(4, sizeof(t_data));
	protect(cub->walls);
}

static double find_rotation_angle(t_cub *cub)
{
	if (cub->map_items->player_dir == 'N')
		return (3 * M_PI_2);
	if (cub->map_items->player_dir == 'S')
		return (M_PI_2);
	if (cub->map_items->player_dir == 'W')
		return (M_PI);
	return (0);
}

static void imgs_init(t_cub *cub)
{
	cub->walls[NO].img = mlx_xpm_file_to_image(cub->mlx, cub->map_items->NO,
			&cub->walls[NO].img_width, &cub->walls[NO].img_height);
	protect(cub->walls[NO].img);
	cub->walls[SO].img = mlx_xpm_file_to_image(cub->mlx, cub->map_items->SO,
			&cub->walls[SO].img_width, &cub->walls[SO].img_height);
	protect(cub->walls[SO].img);
	cub->walls[WE].img = mlx_xpm_file_to_image(cub->mlx, cub->map_items->WE,
			&cub->walls[WE].img_width, &cub->walls[WE].img_height);
	protect(cub->walls[WE].img);
	cub->walls[EA].img = mlx_xpm_file_to_image(cub->mlx, cub->map_items->EA,
			&cub->walls[EA].img_width, &cub->walls[EA].img_height);
	protect(cub->walls[EA].img);
}

static void	img_addr_init(t_cub *cub)
{
	cub->walls[NO].colors = (int *)mlx_get_data_addr(cub->walls[NO].img,
			&cub->walls[NO].bits_per_pixel, &cub->walls[NO].line_length,
			&cub->walls[NO].endian);
	protect(cub->walls[NO].colors);
	cub->walls[SO].colors = (int *)mlx_get_data_addr(cub->walls[SO].img,
			&cub->walls[SO].bits_per_pixel, &cub->walls[SO].line_length,
			&cub->walls[SO].endian);
	protect(cub->walls[SO].colors);
	cub->walls[WE].colors = (int *)mlx_get_data_addr(cub->walls[WE].img,
			&cub->walls[WE].bits_per_pixel, &cub->walls[WE].line_length,
			&cub->walls[WE].endian);
	protect(cub->walls[WE].colors);
	cub->walls[EA].colors = (int *)mlx_get_data_addr(cub->walls[EA].img,
			&cub->walls[EA].bits_per_pixel, &cub->walls[EA].line_length,
			&cub->walls[EA].endian);
	protect(cub->walls[EA].colors);
}

void cub_init(t_cub *cub)
{
	cub->win_width = 1080;
	cub->win_height = 720;
	cub->num_rays = cub->win_width;
	mem_alloc(cub);
	cub->map_img->img_width = cub->map_items->map_width * BLOCK_SIZE;
	cub->map_img->img_height = cub->map_items->map_height * BLOCK_SIZE;
	cub->player->x = (BLOCK_SIZE * cub->map_items->player_y) + BLOCK_SIZE / 2;
	cub->player->y = (BLOCK_SIZE * cub->map_items->player_x) + BLOCK_SIZE / 2;
	cub->player->rotation_angle = find_rotation_angle(cub);
	cub->player->walk_direction = 0;
	cub->player->turn_direction = 0;
	cub->player->walk_angle = 0;
	cub->player->move_speed = 3;
	cub->player->rotation_speed = 3 * (M_PI / 180);
	cub->player->mouse_position = -1e9;
	cub->sprite_ndx = 0;
	cub->mlx = mlx_init();
	protect(cub->mlx);
	cub->mlx_window = mlx_new_window(cub->mlx, cub->win_width,
									 cub->win_height, "cub3D");
	protect(cub->mlx_window);
	imgs_init(cub);
	img_addr_init(cub);
}
