/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_pascer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smazouz <smazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 09:11:05 by smazouz           #+#    #+#             */
/*   Updated: 2022/06/23 16:40:19 by smazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
int array_size_(char **map, int *max)
{
    int i = 0;
    *max  = 0;
    while(map[i])
    {
         if((int)ft_strlen(map[i]) > *max)
            *max = (int)ft_strlen(map[i]);
        i++;
    }
    return(i);
}
char    *new_line(char *str, int max)
{
    char *ret;
    ret = (char *)malloc(max + 1);

    int  i = 0;
    while(str[i])
    {
        if(str[i] != ' ')
            ret[i] = str[i];
        else
            ret[i] = '#';
        i++;
    }
    while(i < max)
    {
        ret[i] = '#';
        i++;
    }
    ret[i] = '\0';
    return(ret);
}
char **map_clone(char **map)
{
    int size;
    int max_line;
    int i = 0;
    size = array_size_(map,&max_line);
    char **new_map = malloc((size + 1) * sizeof(char *));
    while(map[i])
    {
        new_map[i] = new_line(map[i], max_line);
        i++;
    }
    new_map[i] = NULL;
    return(new_map);
}
void    map_characters(t_item *item)
{
    int i;
    int j;
    int S = 0;
    int N = 0;
    int W = 0;
    int E = 0;
    int cout  = 0;
    i = 0;
    while(item->map[i])
    {
        j = 0;
        while(item->map[i][j])
        {
            if(item->map[i][j] != ' ' && item->map[i][j] != '1' && item->map[i][j] != '0')
            {
                if(item->map[i][j]== 'E' || item->map[i][j]== 'W' || item->map[i][j]== 'S' || item->map[i][j]== 'N')
                {
                    if(cout == 0)
                    {
                        item->player_x = i;
                        item->player_y = j;
                        cout++;
                    }
                    else
                    {
                        printf("Error:\n Too many players.\n");
                        exit(0);
                    }
                }
                else
                {
                    printf("Error:\n Undefined character.\n");
                    exit(0);
                }
            }
            j++;
        }
        i++;
    }
}
int fisrt_last_line(char *line)
{
    int i = 0;
    while(line[i])
    {
        if(line[i] !=' ' && line[i] != '1' && line[i] != '#')
        {
            printf("Error:\n Corrupted first and last wall\n");
            return(0);
        }
        i++;
    }
    return(1);
}
void map_parser(t_item *item)
{
    int i = 0;
    int j = 0;
    map_characters(item);
    char **new =  map_clone(item->map);
    while(new[i])
    {
        if(i == 0 || new[i + 1] == NULL)
        {
            if(fisrt_last_line(new[i]) == 0)
            {
                free_str(new);
                free_str(item->map);
                exit(1);
            }
        }
        else
        {
            j = 0;
            while(new[i][j])
            {
                if(new[i][j]== '0')
                {
                    if(j == 0 ||  j == ft_strlen(new[i]) - 1)
                    {
                        printf("Error:\n Unclosed walls.\n");
                        free_str(new);
                        free_str(item->map);
                        exit(0);
                    }
                    if(!ft_strchr("1NSEW0",new[i][j - 1])|| !ft_strchr("1NSEW0",new[i][j + 1]) || !ft_strchr("1NSEW0",new[i - 1][j]) || !ft_strchr("1NSEW0",new[i + 1][j]))
                    {
                        printf("Error:\n Unclosed walls.\n");
                        free_str(new);
                        free_str(item->map);
                        exit(0);
                    }
                }
                j++;
            }
        }
        i++;
    }
    free_str(new);
}
