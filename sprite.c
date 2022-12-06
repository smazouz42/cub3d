/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moulmado <moulmado@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 15:01:15 by moulmado          #+#    #+#             */
/*   Updated: 2022/12/02 18:11:51 by moulmado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void imgs_open_1(t_cub *cub, t_data *imgs)
{
	imgs[HOLD].img = mlx_xpm_file_to_image(cub->mlx, "./sprite/hold.xpm",
			&imgs[HOLD].img_width, &imgs[HOLD].img_height);
	protect(imgs[HOLD].img);
	imgs[FRAM0].img = mlx_xpm_file_to_image(cub->mlx, "./sprite/frame00.xpm",
			&imgs[FRAM0].img_width, &imgs[FRAM0].img_height);
	protect(imgs[FRAM0].img);
	imgs[FRAM1].img = mlx_xpm_file_to_image(cub->mlx, "./sprite/frame01.xpm",
			&imgs[FRAM1].img_width, &imgs[FRAM1].img_height);
	protect(imgs[FRAM1].img);
	imgs[FRAM2].img = mlx_xpm_file_to_image(cub->mlx, "./sprite/frame02.xpm",
			&imgs[FRAM2].img_width, &imgs[FRAM2].img_height);
	protect(imgs[FRAM2].img);
	imgs[FRAM3].img = mlx_xpm_file_to_image(cub->mlx, "./sprite/frame03.xpm",
			&imgs[FRAM3].img_width, &imgs[FRAM3].img_height);
	protect(imgs[FRAM3].img);
	imgs[FRAM4].img = mlx_xpm_file_to_image(cub->mlx, "./sprite/frame04.xpm",
			&imgs[FRAM4].img_width, &imgs[FRAM4].img_height);
	protect(imgs[FRAM4].img);
}

static void imgs_open_2(t_cub *cub, t_data *imgs)
{
	imgs[FRAM5].img = mlx_xpm_file_to_image(cub->mlx, "./sprite/frame05.xpm",
			&imgs[FRAM5].img_width, &imgs[FRAM5].img_height);
	protect(imgs[FRAM5].img);
	imgs[FRAM6].img = mlx_xpm_file_to_image(cub->mlx, "./sprite/frame06.xpm",
			&imgs[FRAM6].img_width, &imgs[FRAM6].img_height);
	protect(imgs[FRAM6].img);
	imgs[FRAM7].img = mlx_xpm_file_to_image(cub->mlx, "./sprite/frame07.xpm",
			&imgs[FRAM7].img_width, &imgs[FRAM7].img_height);
	protect(imgs[FRAM7].img);
	imgs[FRAM8].img = mlx_xpm_file_to_image(cub->mlx, "./sprite/frame08.xpm",
			&imgs[FRAM8].img_width, &imgs[FRAM8].img_height);
	protect(imgs[FRAM8].img);
	imgs[FRAM9].img = mlx_xpm_file_to_image(cub->mlx, "./sprite/frame09.xpm",
			&imgs[FRAM9].img_width, &imgs[FRAM9].img_height);
	protect(imgs[FRAM9].img);
	imgs[FRAM10].img = mlx_xpm_file_to_image(cub->mlx, "./sprite/frame10.xpm",
			&imgs[FRAM10].img_width, &imgs[FRAM10].img_height);
	protect(imgs[FRAM10].img);
}

void	sprite_init(t_cub *cub)
{
	
	cub->sprite = (t_data *)calloc(12, sizeof(t_data));
	protect(cub->sprite);
	imgs_open_1(cub, cub->sprite);
	imgs_open_2(cub, cub->sprite);
}