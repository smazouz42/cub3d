/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smazouz <smazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 11:05:57 by smazouz           #+#    #+#             */
/*   Updated: 2022/06/23 12:43:20 by smazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"

void    free_str(char **tab)
{
    int x = 0;
    while(tab[x])
        free(tab[x++]);
    free(tab);
}
void free_map_items(t_item *item)
{
    free_str(item->map);
}