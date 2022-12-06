/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smazouz <smazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 13:02:24 by moulmado          #+#    #+#             */
/*   Updated: 2022/12/06 04:29:47 by smazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_str(char **tab)
{
	int	x;

	x = 0;
	if (!tab)
		return ;
	while (tab[x])
		free(tab[x++]);
	free(tab);
}

void	free_map_items(t_item *item)
{
	free_str(item->map);
}
