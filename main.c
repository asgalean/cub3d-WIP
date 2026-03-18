#include "my_pp.h"


/*
char map[5][6] = {
	"10111",
	"11101",
	"10001",
	"100N1",
	"11111"
};*/

# define MAP_WIDTH 9
# define MAP_HEIGHT 10
# define tile_size 1

//wasll ight look a vit curve, that's cuz of the 90º FOV. 60º FOV is good
# define FOV 60 //180+ segfault

//t_player player;

#include <MLX42/MLX42.h>

#define WIDTH 1024
#define HEIGHT 1024

//static mlx_image_t* image;


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


//******************************************************************************
//******************************************************************************

void ft_hook(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE) || mlx_is_key_down(data->mlx, MLX_KEY_Q))
		mlx_close_window(data->mlx);
	//if (mlx_is_key_down(mlx, MLX_KEY_UP))
		//image->instances[0].y -= 5;
	//if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		//image->instances[0].y += 5;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->player.angle += 1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->player.angle -= 1;

		
	double rad = data->player.angle * ANGLE_TO_RADIAN;
	double speed = 0.1; //ANOTHER data->player STAT

	
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		if (data->map[(int)(data->player.Y - sin(rad) * speed)][(int)(data->player.X)] != '1')
			data->player.Y -= sin(rad) * speed;
		if (data->map[(int)(data->player.Y)][(int)(data->player.X + cos(rad) * speed)] != '1')
			data->player.X += cos(rad) * speed;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		if (data->map[(int)(data->player.Y + sin(rad) * speed)][(int)(data->player.X)] != '1')
			data->player.Y += sin(rad) * speed;
		if (data->map[(int)(data->player.Y)][(int)(data->player.X - cos(rad) * speed)] != '1')
			data->player.X -= cos(rad) * speed;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		if (data->map[(int)(data->player.Y - cos(rad) * speed)][(int)(data->player.X)] != '1')
			data->player.Y -= cos(rad) * speed;
		if (data->map[(int)(data->player.Y)][(int)(data->player.X - sin(rad) * speed)] != '1')
			data->player.X -= sin(rad) * speed;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		if (data->map[(int)(data->player.Y + cos(rad) * speed)][(int)(data->player.X)] != '1')
			data->player.Y += cos(rad) * speed;
		if (data->map[(int)(data->player.Y)][(int)(data->player.X + sin(rad) * speed)] != '1')
			data->player.X += sin(rad) * speed;
	}
}



//******************************************************************************
//******************************************************************************



double pitagoras(double collision_x, double collision_y, t_data *data)
{
	double hypotenuse;
	
	hypotenuse = sqrt(
	(collision_x - data->player.X) * (collision_x - data->player.X) +
	(collision_y - data->player.Y) * (collision_y - data->player.Y));
	
	return (hypotenuse);
}

/*
RAYS NEEDS:
	tile_size
	data->player.angle
	data->player.X
	data->player.Y
*/


//horizontal collision, ray goes in X axis
double h_collision(double angle, t_data *data, t_ray *h_ray)//data->player and map
{
	double constant_increment_x = tile_size * ((angle >= PIH && angle <= PI3H) ? -1 : 1); //
	double constant_increment_y = tile_size * fabs(tan(angle)) * ((angle >= 0 && angle <= PI) ? -1 : 1);
	
	h_ray->collision_x = ((int)(data->player.X/tile_size) + (angle < PIH || angle > PI3H)) * tile_size;
	h_ray->collision_y = data->player.Y - (h_ray->collision_x - data->player.X) * tan(angle);
	
	int i = -1;
	while (++i < MAX_RAY_ITERATION)
	{
		int matrix_x = (int)(h_ray->collision_x / tile_size);
		int matrix_y = (int)(h_ray->collision_y / tile_size);
		
		if (matrix_x >= 0 && matrix_x < MAP_WIDTH
			&& matrix_y >= 0 && matrix_y < MAP_HEIGHT
			&& data->map[matrix_y][matrix_x - (constant_increment_x < 0)] == '1')
				return (pitagoras(h_ray->collision_x, h_ray->collision_y, data));
		h_ray->collision_x += constant_increment_x;
		h_ray->collision_y += constant_increment_y;
	}
	return (pitagoras(h_ray->collision_x, h_ray->collision_y, data));
}

//vertical collision, ray goes in Y axis
double v_collision(double angle, t_data *data, t_ray *v_ray)//data->player and map
{
	double constant_increment_y = tile_size * ((angle >= 0 && angle <= PI) ? -1 : 1);
	double constant_increment_x = tile_size / fabs(tan(angle)) * ((angle >= PIH && angle <= PI3H) ? -1 : 1);
	
	v_ray->collision_y = ((int)(data->player.Y/tile_size) + (angle > PI && angle < (2 * PI))) * tile_size;
	v_ray->collision_x = data->player.X - (v_ray->collision_y - data->player.Y) / tan(angle);
	
	int i = -1;
	while (++i < MAX_RAY_ITERATION)
	{
		int matrix_x = (int)(v_ray->collision_x / tile_size);
		int matrix_y = (int)(v_ray->collision_y / tile_size);
		
		if (matrix_x >= 0 && matrix_x < MAP_WIDTH
			&& matrix_y >= 0 && matrix_y < MAP_HEIGHT
			&& data->map[matrix_y - (constant_increment_y < 0)][matrix_x] == '1')
				return (pitagoras(v_ray->collision_x, v_ray->collision_y, data));
		v_ray->collision_x += constant_increment_x;
		v_ray->collision_y += constant_increment_y;
	}
	return (pitagoras(v_ray->collision_x, v_ray->collision_y, data));
}

t_ray cast_ray(double angle, t_data *data) //data->player and map
{
	double rad_angle = angle * ANGLE_TO_RADIAN;
	t_ray h_ray;
	t_ray v_ray;
	t_ray final_ray;
	
	h_ray.dist = h_collision(rad_angle, data, &h_ray);
	v_ray.dist = v_collision(rad_angle, data, &v_ray);
	if (h_ray.dist < v_ray.dist)
	{
		final_ray.dist = h_ray.dist * cos((angle - data->player.angle) * ANGLE_TO_RADIAN);
		final_ray.wall_percent = h_ray.collision_y - (int)h_ray.collision_y; //el rayo al ser a la derecha, veremos el muro con y variante
		if (rad_angle > PIH && rad_angle < PI3H)
			final_ray.face = 'W';
		else
			final_ray.face = 'E';
	}
	else
	{
		final_ray.dist = v_ray.dist * cos((angle - data->player.angle) * ANGLE_TO_RADIAN);
		final_ray.wall_percent = v_ray.collision_x - (int)v_ray.collision_x; //el rayo al ser en hroizontal, veremos el muro con y variante
		if (rad_angle > 0 && rad_angle < PI)
			final_ray.face = 'N';
		else
			final_ray.face = 'S';
	}
	
	if (final_ray.face == 'S' || final_ray.face == 'W') //para que los muros no se impirmanal reves
    	final_ray.wall_percent = 1.0 - final_ray.wall_percent;

	if (final_ray.dist < 0.01) //para no meterse en muros (temp. en lugar de chekear las colisiones)
	    final_ray.dist = 0.01;
	//return(fmin(h_collision(rad_angle, data), v_collision(rad_angle, data)));
	//temp
	return (final_ray);
}

int validate_mlx(t_data *data)
{
	if (!(data->mlx = mlx_init(WIDTH, HEIGHT, "CUB3D", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(1);
	}
	if (!(data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		return(1);
	}
	if (mlx_image_to_window(data->mlx, data->img, 0, 0) == -1)
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		return(1);
	}
	//textures
	data->tex_n = mlx_load_png("textures/north.png");
	if (!data->tex_n)
	{
		puts(mlx_strerror(mlx_errno));
		return (1);
	}
	data->tex_s = mlx_load_png("textures/south.png");
	if (!data->tex_n)
	{
		puts(mlx_strerror(mlx_errno));
		return (1);
	}
	data->tex_e = mlx_load_png("textures/east.png");
	if (!data->tex_n)
	{
		puts(mlx_strerror(mlx_errno));
		return (1);
	}
	data->tex_w = mlx_load_png("textures/west.png");
	if (!data->tex_n)
	{
		puts(mlx_strerror(mlx_errno));
		return (1);
	}
	return (0);
}

void loop_func(void *param)
{
	t_data *data = (t_data *)param;
	// cast rays, print, etc.
	ft_hook(data);

	mlx_texture_t *tex;




	double ray_angle = fmod(data->player.angle + FOV / 2 , 360);
	//double rays[WIDTH]; para luego si eso saber que muro, tal vez necestiemos esto
	int i = 0;
	while (i < WIDTH)
	{
		//printf("Angle: %d  Radians: %f  Distance: ", angle, data->player.angle);
		if(ray_angle < 0)
			ray_angle += 360;
		//rays[i] = cast_ray(ray_angle) * cos((ray_angle - data->player.angle) * ANGLE_TO_RADIAN);
		t_ray ray = cast_ray(ray_angle, data);

		if (ray.face == 'N') tex = data->tex_n;
		else if (ray.face == 'S') tex = data->tex_s;
		else if (ray.face == 'E') tex = data->tex_e;
		else tex = data->tex_w;
		int tex_x = (int)(ray.wall_percent * tex->width);
		
	//prnitign pixels for each ray
		int wall_size = (int)(HEIGHT / (ray.dist * 3));
		int real_wall_size = wall_size;          // keep real value
		if (wall_size > HEIGHT) wall_size = HEIGHT;
		int top = (HEIGHT - real_wall_size) / 2; // use real size for centering
		int draw_start = top < 0 ? 0 : top;
		int draw_end = (top + real_wall_size) > HEIGHT ? HEIGHT : top + real_wall_size;
		double tex_pos_start = top < 0 ? (double)(-top) / real_wall_size : 0.0;

		int y = 0;
		while (y < draw_start)
			mlx_put_pixel(data->img, i, y++, 0x87CEEBFF);
		while (y < draw_end)
		{
			double tex_pos = tex_pos_start + (double)(y - draw_start) / real_wall_size;
			int tex_y = (int)(tex_pos * tex->height);
			int idx = (tex_y * tex->width + tex_x) * 4;
			uint32_t color = (tex->pixels[idx] << 24 |
				              tex->pixels[idx + 1] << 16 |
				              tex->pixels[idx + 2] << 8 |
				              tex->pixels[idx + 3]);
			mlx_put_pixel(data->img, i, y++, color);
		}
		while (y < HEIGHT)
			mlx_put_pixel(data->img, i, y++, 0x654321FF);
		
		ray_angle -= (double)FOV/WIDTH; //tiene que castearse asi, si no, se queda en int
		i++;
	}




}

int	main(int argc, char *argv[])
{
	//t_data	data;
	(void)argv;
	(void)argc;
	
	t_data data = {
		.map = {
			"111111111",
			"100000001",
			"1000N0001",
			"100000001",
			"100000001",
			"101000001",
			"100001001",
			"100000001",
			"100000001",
			"111111111"
		},
		.player = {
			.X = 3.5,
			.Y = 1.5,
			.angle = 90.035 //.0204 if distance is more than 0.5
		}
	};
	
	if (validate_mlx(&data))
		return (623);
	
	//le decimos a la mlx que llame a esta funcion a cada frame, y el tercer argumento es el parametro para la funcion
	mlx_loop_hook(data.mlx, loop_func, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
		
		//////////////////////////////
	
	return (0);
}

