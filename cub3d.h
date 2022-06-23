#ifndef CUB3D_H
#define CUB3D_H

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <fcntl.h>
#include <mlx.h>

#define SIZEMINIMAP 2

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}   t_img;

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
    // mlx vars
    void	*mlx;
    void	*mlx_win;
    // img
    t_img	img;
}           t_item;
//utils
char	**ft_split(char const *s, char c);
size_t  ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);
int	    ft_atoi(const char *str);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
//parsing
void map_parser(t_item *item);
int fisrt_last_line(char *line);
char    *new_line(char *str, int max);
char **map_clone(char **map);
int    take_color(t_item *map_items, char *colors);
void    take_walls(t_item *map_items,char *walls);
int     is_color(char *str);
int     is_wall(char *str);
int     is_line(char *str);
int     is_empty(char *str);
//leaks
void    free_str(char **tab);
void free_map_items(t_item *item);
#endif