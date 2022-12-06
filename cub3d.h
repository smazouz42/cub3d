/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smazouz <smazouz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:37:17 by moulmado          #+#    #+#             */
/*   Updated: 2022/12/05 19:02:17 by smazouz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H
#include <mlx.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include <stdlib.h>

#define BLOCK_SIZE 16
#define FOV_ANGLE 60 * (M_PI / 180)
#define SIZEMINIMAP 2

static int a = 10;

enum sprite
{
	HOLD,
	FRAM0,
	FRAM1,
	FRAM2,
	FRAM3,
	FRAM4,
	FRAM5,
	FRAM6,
	FRAM7,
	FRAM8,
	FRAM9,
	FRAM10
};

enum ray_type
{
	HORZ,
	VERT
};

enum wall_type
{
	NO,
	SO,
	WE,
	EA,
	DOOR
};

enum keys
{
	W = 13,
	A = 0,
	S = 1,
	D = 2,
	UP = 126,
	DOWN = 125,
	RIGHT = 124,
	LEFT = 123,
	ESC = 53,
	FIRE = 49
};

/***************_MAP_****************/
typedef struct s_item
{
	char **map;
	int floor_colors[4];
	int ceiling_colors[4];
	char *NO;
	char *SO;
	char *WE;
	char *EA;
	char player_dir;
	int player_x;
	int player_y;
	int map_height;
	int map_width;
} t_item;
/*----------------------------------*/

/************_IMG_DATA-**************/
typedef struct s_data
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
	int img_height;
	int img_width;
	int *colors;
} t_data;
/*----------------------------------*/

/************_PLAYER_DATA************/
typedef struct s_p_data
{
	double rotation_angle;
	double x;
	double y;
	int turn_direction;
	double walk_angle;
	int walk_direction;
	double move_speed;
	double rotation_speed;
	int mouse_position;
} t_p_data;
/*----------------------------------*/

/**************_RAYS_****************/
typedef struct s_ray
{
	double angle;
	double wallHitX;
	double wallHitY;
	double dst;
	int type;
	int isFacingUp;
	int isFacingDown;
	int isFacingLeft;
	int isFacingRight;
	int	door_hit;
} t_ray;
/*----------------------------------*/

/**************_CUB3D_***************/
typedef struct s_cub
{
	void *mlx;
	void *mlx_window;
	int win_width;
	int win_height;
	int num_rays;
	t_data *walls;
	t_p_data *player;
	t_data *map_img;
	t_data *rend3D;
	t_ray *rays;
	t_item *map_items;
	t_data *sprite;
	int sprite_ndx;
} t_cub;
/*----------------------------------*/

/**_LITERALLY CAUSE OF NORMINETTE_***/
typedef struct s_ratio
{
	double x;
	double y;
} t_ratio;

typedef struct s_m_cords
{
	double xinter;
	double yinter;
	double xstep;
	double ystep;
	double wallhitx;
	double wallhity;
	double dst;
} t_m_cords;
/*----------------------------------*/

/********************************_INIT_*********************************/
void cub_init(t_cub *cub);
int map_init(t_cub *cub);
void rend3R_init(t_cub *cub);
void sprite_init(t_cub *cub);
/*---------------------------------------------------------------------*/

/********************************_DRAW_*********************************/
void my_mlx_pixel_put(t_data *data, int x, int y, int color);
void draw_line(t_cub *cub, double x2, double y2);
void draw_vert_line(t_cub *cub, double y1, double y2, int ndx);
void fill_floor_nd_ceiling(t_cub *cub, int c_color, int f_color);
// tools
int get_color(int *c_arr);
/*---------------------------------------------------------------------*/

/*******************************_EVENTS_*******-************************/
int key_press(int keycode, t_cub *cub);
int key_release(int keycode, t_cub *cub);
void pos_update(t_cub *cub);
void angle_update(t_cub *cub);
int mouse_move(int x, int y, t_cub *cub);
/*---------------------------------------------------------------------*/

/*****************************_RAY_CASTING******************************/
int ray_cast(t_cub *cub, int ndx);
void upload_rays(t_cub *cub);
// MATH
double mod(double n1, double n2);
double distance(double x1, double y1, double x2, double y2);
// REND3D
void rend3r_walls(t_cub *cub, int ndx);
/*---------------------------------------------------------------------*/

/*********************************_MAP_*********************************/
int map_has_wall_at(t_cub *cub, double x, double y);
int is_same_block(t_cub *cub, int grid_i, int grid_j);
int door_check(t_cub *cub, double x, double y, int ndx);
/*---------------------------------------------------------------------*/

/******************************_PARCING_********************************/
t_item	*parser(void);
void	map_full_check(t_item *item);
int is_empty(char *str);
int is_line(char *str);
int is_wall(char *str);
int is_color(char *str);
int get_colors(t_item *map_items, char *colors);
void take_walls(t_item *map_items, char *walls);
void fix_map(t_item *map_items);
void get_ceiling_rgb(char **c_first, char **c_second, t_item *map_items);
// tools
char **map_clone(char **str);
char *ft_strchr(const char *s, int c);
size_t ft_strlen(const char *str);
int ft_atoi(const char *str);
char *ft_strdup(const char *s1);
char *ft_strjoin(char const *s1, char const *s2);
char **ft_split(char const *s, char c);
void	protect(void *p);
// free?
void free_map_items(t_item *item);
void free_str(char **tab);
/*---------------------------------------------------------------------*/

#endif