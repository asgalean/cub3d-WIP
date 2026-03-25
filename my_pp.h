/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pp.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgalean <asgalean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:12:55 by asgalean          #+#    #+#             */
/*   Updated: 2026/03/25 17:12:56 by asgalean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <MLX42/MLX42.h>

#define DISTANCE 32

# define MAX_DEPTH 25

# define PI 3.14159265358979323846

# define PIH 1.57079632679489661923

# define PI3H 4.71238898038468985769

# define PI2 WIP

# define SOUTH PI3H
# define NORTH PIH
# define EAST 0
# define WEST PI

# define ANGLE_TO_RADIAN 0.0174533

# define MAX_RAY_ITERATION 10

# define MAP_WIDTH 9
# define MAP_HEIGHT 10

//wasll ight look a vit curve, that's cuz of the 90º FOV. 60º FOV is good
# define FOV 60 //180+ segfault

//t_player player;

#define WIDTH 1024
#define HEIGHT 1024



typedef struct s_pixel_col
{
	int			tex_x;
	int			wall_size;
	int			real_wall_size;
	int			top;
	int			draw_start;
	int			draw_end;
	double		tex_pos_start;
	double		tex_pos;
	int			tex_y;
	int			idx;
	uint32_t	color;

}	t_pixel_col;

typedef struct s_map
{
	char	**map;
	int		width;
	int		height;
	
	
	
} t_map;



typedef struct s_player
{
	double X;
	double Y;
	double angle;
	double speed;

}  t_player;

typedef struct s_ray
{
    double  dist;
    double  wall_percent;  // fractional hit position (0.0 to 1.0)
    double	collision_x;
    double	collision_y;
    char	face;    //NSWE
}   t_ray;

typedef struct s_data
{
    mlx_t           *mlx;
    mlx_image_t     *img;
    t_player        player;   // no need for pointer, just embed it
    char      	    map[10][10];      // same
    mlx_texture_t   *tex_n;
    mlx_texture_t   *tex_s;
    mlx_texture_t   *tex_e;
    mlx_texture_t   *tex_w;
}   t_data;

void	loop_func(void *param);
double	v_collision(double angle, t_data *data, t_ray *v_ray);
double	h_collision(double angle, t_data *data, t_ray *h_ray);
t_ray	cast_ray(double angle, t_data *data);
void	ft_hook(t_data *data);




