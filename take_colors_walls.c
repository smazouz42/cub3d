/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_colors_walls.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smazouz <smazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 09:32:01 by smazouz           #+#    #+#             */
/*   Updated: 2022/06/23 16:48:37 by smazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3d.h"

static int array_size(char **str)
{
    int i = 0;
    while(str[i])
        i++;
    return(i);
}
int    take_color(t_item *map_items, char *colors)
{
    char **c_table;
    char **c_first;
    char **c_second;
    int i;
    char **tmp;

    i = 0;
    c_table = ft_split(colors,'\n');
    c_first = ft_split(c_table[0],' ');
    c_second = ft_split(c_table[1],' ');
    free_str(c_table);
    if(c_first[0][0] == c_second[0][0])
    {
        printf("Error:\n Duplicated color row.\n");
            free_str(c_first);
            free_str(c_second);
            return(3);
    }
    if(c_first[0][0] == 'C')
    {
        tmp = c_first;
        c_first = ft_split(c_first[1],',');
        free_str(tmp);
        tmp = c_second;
        c_second = ft_split(c_second[1],',');
        free_str(tmp);
        if(array_size(c_first) != 3 || array_size(c_second) != 3)
        {
            printf("Error:\n Flawed floor or ceiling color\n");
            free_str(c_first);
            free_str(c_second);
            return(3);
        }
        map_items->ceiling_colors[0] =  ft_atoi(c_first[0]);
        map_items->ceiling_colors[1] =  ft_atoi(c_first[1]);
        map_items->ceiling_colors[2] =  ft_atoi(c_first[2]);
        map_items->floor_colors[0] =  ft_atoi(c_second[0]);
        map_items->floor_colors[1] =  ft_atoi(c_second[1]);
        map_items->floor_colors[2] =  ft_atoi(c_second[2]);
    }
    else
    {
        tmp = c_first;
        c_first = ft_split(c_first[1],',');
        free_str(tmp);
        tmp = c_second;
        c_second = ft_split(c_second[1],',');
        free_str(tmp);
         if(array_size(c_first) != 3 || array_size(c_second) != 3)
         {
            printf("Error:\n Flawed floor or ceiling color\n");
            free_str(c_first);
            free_str(c_second);
            return(3);
         }
        map_items->ceiling_colors[0] =  ft_atoi(c_second[0]);
        map_items->ceiling_colors[1] =  ft_atoi(c_second[1]);
        map_items->ceiling_colors[2] =  ft_atoi(c_second[2]);
        map_items->floor_colors[0] =  ft_atoi(c_first[0]);
        map_items->floor_colors[1] =  ft_atoi(c_first[1]);
        map_items->floor_colors[2] =  ft_atoi(c_first[2]);
    }
        map_items->floor_colors[3] =  '\0';
        map_items->ceiling_colors[3] =  '\0';
    free_str(c_first);
    free_str(c_second);
    return(0);

}
void    take_walls(t_item *map_items,char *walls)
{
    int     i = 0;
    char    **wall_array;
    char    **tmp;

    wall_array = ft_split(walls,'\n');
    while(wall_array[i])
    {
        tmp = ft_split(wall_array[i],' ');
        if(tmp[0][0] == 'N')
            map_items->NO = tmp[1];
        else if(tmp[0][0] == 'S')
            map_items->SO = tmp[1];
        else if(tmp[0][0] == 'E')
            map_items->EA = tmp[1];
        else if(tmp[0][0] == 'W')
            map_items->WE = tmp[1];
        i++;
       free_str(tmp);
    }
    if(!map_items->EA || !map_items->SO || !map_items->NO || !map_items->WE)
    {
        printf("Error\n");
        free_str(wall_array);
        exit(1);
    }
    free_str(wall_array);
}