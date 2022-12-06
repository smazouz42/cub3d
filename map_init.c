/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 18:19:06 by moulmado          #+#    #+#             */
/*   Updated: 2022/12/05 15:50:37 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void map_wall_put(t_cub *cub, int x, int y)
// {
// 	int i;
// 	int j;

// 	i = -1;
// 	while (++i < BLOCK_SIZE)
// 	{
// 		j = -1;
// 		while (++j < BLOCK_SIZE)
// 			my_mlx_pixel_put(cub->map_img, x + j, y + i, 0);
// 	}
// }

// static void map_field(t_cub *cub, int x, int y)
// {
// 	int i;
// 	int j;

// 	i = -1;
// 	while (++i < BLOCK_SIZE)
// 	{
// 		j = -1;
// 		if (i == BLOCK_SIZE - 1)
// 		{
// 			while (++j < BLOCK_SIZE)
// 				my_mlx_pixel_put(cub->map_img, x + j, y + i, 0);
// 		}
// 		else
// 		{
// 			while (++j < BLOCK_SIZE)
// 			{
// 				if (j == BLOCK_SIZE - 1)
// 					my_mlx_pixel_put(cub->map_img, x + j, y + i, 0);
// 				else
// 					my_mlx_pixel_put(cub->map_img, x + j, y + i, 0xFFFFFF);
// 			}
// 		}
// 	}
// }

// static void map_empty(t_cub *cub, int x, int y)
// {
// 	int i;
// 	int j;

// 	i = -1;
// 	while (++i < BLOCK_SIZE)
// 	{
// 		j = -1;
// 		while (++j < BLOCK_SIZE)
// 			my_mlx_pixel_put(cub->map_img, x + j, y + i, 0xFF000000);
// 	}
// }

static void set_dot(t_cub *cub)
{
	int x1;
	int y1;
	int r;

	r = 4;
	x1 = 0;
	while (x1 < r)
	{
		y1 = 0;
		while (y1 < r)
		{
			my_mlx_pixel_put(cub->map_img, 12 * BLOCK_SIZE - 2 + x1,
							 7 * BLOCK_SIZE - 2 + y1, 0x0004FD);
			y1++;
		}
		x1++;
	}
}

// void map_init(t_cub *cub)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	cub->map_img->img = mlx_new_image(cub->mlx, cub->map_img->img_width,
// 									  cub->map_img->img_height);
// 	if (!cub->map_img->img)
// 		exit(1);
// 	cub->map_img->addr = mlx_get_data_addr(cub->map_img->img, &cub->map_img->bits_per_pixel,
// 										   &cub->map_img->line_length, &cub->map_img->endian);
// 	if (!cub->map_img->addr)
// 		exit(1);
// 	while (cub->map_items->map[i])
// 	{
// 		j = 0;
// 		while (cub->map_items->map[i][j])
// 		{
// 			if (cub->map_items->map[i][j] == '1')
// 				map_wall_put(cub, j * BLOCK_SIZE, i * BLOCK_SIZE);
// 			else if (cub->map_items->map[i][j] == ' ')
// 				map_empty(cub, j * BLOCK_SIZE, i * BLOCK_SIZE);
// 			else
// 				map_field(cub, j * BLOCK_SIZE, i * BLOCK_SIZE);
// 			j++;
// 		}
// 		i++;
// 	}
// 	set_dot(cub);
// 	upload_rays(cub);
// 	mlx_put_image_to_window(cub->mlx, cub->mlx_window,
// 							cub->map_img->img, 0, 0);
// 	mlx_destroy_image(cub->mlx, cub->map_img->img);
// }

int map_init(t_cub *cub)
{
    int y = cub->player->y - (7 * BLOCK_SIZE);
    int x;
    char **map = map_clone(cub->map_items->map);
    cub->map_img->img = mlx_new_image(cub->mlx, 24 * 16 + 2,
            14 * 16 + 2);
    protect(cub->map_img->img);
    cub->map_img->addr = mlx_get_data_addr(cub->map_img->img, &cub->map_img->bits_per_pixel,
                                           &cub->map_img->line_length, &cub->map_img->endian);
    protect(cub->map_img->addr);
    for(int i = 0 ; i < 14*BLOCK_SIZE;i++)
    {
        x = cub->player->x - (12 * BLOCK_SIZE);
        for(int j = 0; j < 24*BLOCK_SIZE;j++)
        {
            if(x < 0 || y < 0 || x >= (cub->map_items->map_width * BLOCK_SIZE) || y >= (cub->map_items->map_height * BLOCK_SIZE))
                my_mlx_pixel_put(cub->map_img, j , i, 0xFF000000);
            else if(map[(int)y/BLOCK_SIZE][(int)x/BLOCK_SIZE] == '1')
                my_mlx_pixel_put(cub->map_img, j , i, 0);
            else if(map[(int)y/BLOCK_SIZE][(int)x/BLOCK_SIZE] == '0')
                my_mlx_pixel_put(cub->map_img, j , i, 0xFFFFFF);
            else if(map[(int)y/BLOCK_SIZE][(int)x/BLOCK_SIZE] == '#')
                my_mlx_pixel_put(cub->map_img, j, i, 0xFF000000);
            x++;
        }
        y++;
    }
    set_dot(cub);
    upload_rays(cub);
    mlx_put_image_to_window(cub->mlx, cub->mlx_window,
                            cub->map_img->img, 0, 0);
    mlx_destroy_image(cub->mlx, cub->map_img->img);
    return (0);
}