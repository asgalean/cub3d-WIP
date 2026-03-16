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
# define FOV 90

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
double h_collision(double angle, t_data *data)//data->player and map
{
	double constant_increment_x = tile_size * ((angle >= PIH && angle <= PI3H) ? -1 : 1); //
	double constant_increment_y = tile_size * fabs(tan(angle)) * ((angle >= 0 && angle <= PI) ? -1 : 1);
	
	double collision_x = ((int)(data->player.X/tile_size) + (angle < PIH || angle > PI3H)) * tile_size;
	double collision_y = data->player.Y - (collision_x - data->player.X) * tan(angle);
	
	int i = -1;
	while (++i < MAX_RAY_ITERATION)
	{
		int matrix_x = (int)(collision_x / tile_size);
		int matrix_y = (int)(collision_y / tile_size);
		
		if (matrix_x >= 0 && matrix_x < MAP_WIDTH
			&& matrix_y >= 0 && matrix_y < MAP_HEIGHT
			&& data->map[matrix_y][matrix_x - (constant_increment_x < 0)] == '1')
				return (pitagoras(collision_x, collision_y, data));
		collision_x += constant_increment_x;
		collision_y += constant_increment_y;
	}
	return (pitagoras(collision_x, collision_y, data));
}

//vertical collision, ray goes in Y axis
double v_collision(double angle, t_data *data)//data->player and map
{
	double constant_increment_y = tile_size * ((angle >= 0 && angle <= PI) ? -1 : 1);
	double constant_increment_x = tile_size / fabs(tan(angle)) * ((angle >= PIH && angle <= PI3H) ? -1 : 1);
	
	double collision_y = ((int)(data->player.Y/tile_size) + (angle > PI && angle < (2 * PI))) * tile_size;
	double collision_x = data->player.X - (collision_y - data->player.Y) / tan(angle);
	
	int i = -1;
	while (++i < MAX_RAY_ITERATION)
	{
		int matrix_x = (int)(collision_x / tile_size);
		int matrix_y = (int)(collision_y / tile_size);
		
		if (matrix_x >= 0 && matrix_x < MAP_WIDTH
			&& matrix_y >= 0 && matrix_y < MAP_HEIGHT
			&& data->map[matrix_y - (constant_increment_y < 0)][matrix_x] == '1')
				return (pitagoras(collision_x, collision_y, data));
		collision_x += constant_increment_x;
		collision_y += constant_increment_y;
	}
	return (pitagoras(collision_x, collision_y, data));
}

double cast_ray(double angle, t_data *data) //data->player and map
{
	double rad_angle = angle * ANGLE_TO_RADIAN;
	return(fmin(h_collision(rad_angle, data), v_collision(rad_angle, data)));

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
	return (0);
}

void loop_func(void *param)
{
	t_data *data = (t_data *)param;
	// cast rays, print, etc.
	ft_hook(data);

	double ray_angle = fmod(data->player.angle + FOV / 2 , 360);
	//double rays[WIDTH]; para luego si eso saber que muro, tal vez necestiemos esto
	int i = 0;
	while (i < WIDTH)
	{
		//printf("Angle: %d  Radians: %f  Distance: ", angle, data->player.angle);
		if(ray_angle < 0)
			ray_angle += 360;
		//rays[i] = cast_ray(ray_angle) * cos((ray_angle - data->player.angle) * ANGLE_TO_RADIAN);
		double dist = cast_ray(ray_angle, data) * cos((ray_angle - data->player.angle) * ANGLE_TO_RADIAN);

	//prnitign pixels for each ray
		int wall_size = (int)(HEIGHT / (dist * 3));
		if (wall_size > HEIGHT)
			wall_size = HEIGHT;
		int top = (HEIGHT - wall_size) / 2;

		int y = 0;
		while (y < top)                  // sky
			mlx_put_pixel(data->img, i, y++, 0x87CEEBFF);
		while (y < top + wall_size)      // wall
			mlx_put_pixel(data->img, i, y++, 0xFF0000FF);
		while (y < HEIGHT)               // floor
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
			.Y = 3.5,
			.angle = 90.0204
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

