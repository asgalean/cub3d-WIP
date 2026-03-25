/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuello <mcuello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:03:45 by mcuello           #+#    #+#             */
/*   Updated: 2026/03/25 16:08:26 by mcuello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define RES_WIDTH 1024
# define RES_HEIGHT 1024
# define TILE_SIZE 1
# define DISTANCE 32
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
# define MAX_RAY_ITERATION 1000
# define FOV 60

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stddef.h>
# include <math.h>
# include "MLX/include/MLX42/MLX42.h"
# include "libft/libft.h"

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
	int		player;
	int		pos_x;
	int		pos_y;
}	t_map;

typedef struct s_fd
{
	int		height;
	int		elements;
	int		map_start;
	char	**line;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	char	*floor_color;
	char	*ceiling_color;
	t_map	*map;
}	t_fd;

typedef struct s_player
{
	double	y;
	double	x;
	double	angle;
	double	speed;
}	t_player;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_map		*map;
	t_player	player;
	void		*text_n;
	void		*text_s;
	void		*text_w;
	void		*text_e;
	uint32_t	floor;
	uint32_t	ceiling;
}	t_game;

typedef struct s_ray
{
	double	dist;
	double	wall_percent;
	double	collision_x;
	double	collision_y;
	char	face;
}	t_ray;

int		check_extension(char *str);
int		read_fd(char *filename, t_fd *fd_data);
int		parse_fd(char *filename, t_fd *fd_data);
void	get_rgb(char *line, t_fd *fd_data);
void	get_path(char *line, t_fd *fd_data);
int		parse_map(t_fd *fd_data, int start);
int		is_valid_map(t_map *map);
void	free_fd(t_fd *fd_data);
void	free_map(char **map);
char	**map_copy(t_map *map);
int		flood_fill(char **map, int x, int y);
int		set_game(t_fd *fd, t_game *game);

int		ft_error(char *str);

void	loop_func(void *param);
void	ft_hook(t_game *data);
double	v_collision(double angle, t_game *data, t_ray *v_ray);
double	h_collision(double angle, t_game *data, t_ray *h_ray);
t_ray	cast_ray(double angle, t_game *data);

int		validate_mlx(t_game *game, t_fd *fd);
void	clean_and_close(t_game *data);

#endif
