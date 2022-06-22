#ifndef CUB3D_H
#define CUB3D_H

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <fcntl.h>

char	**ft_split(char const *s, char c);
typedef struct s_item
{
    char    **map;
    int     floor_colors[4];
    int     ceiling_colors[4];
    char    *NO;
    char    *SO;
    char    *WE;
    char    *EA;
    int     player_x;
    int     player_y;
}           t_item;
#endif