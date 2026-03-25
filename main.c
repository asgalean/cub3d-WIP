#include "my_pp.h"


/*
char map[5][6] = {
	"10111",
	"11101",
	"10001",
	"100N1",
	"11111"
};*/



//static mlx_image_t* image;





//******************************************************************************
//******************************************************************************




//******************************************************************************
//******************************************************************************


/*
RAYS NEEDS:
	tile_size
	data->player.angle
	data->player.X
	data->player.Y
*/

//******************************************************************************
//******************************************************************************



//******************************************************************************
//******************************************************************************





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
	if (!data->tex_s)
	{
		puts(mlx_strerror(mlx_errno));
		return (1);
	}
	data->tex_e = mlx_load_png("textures/east.png");
	if (!data->tex_e)
	{
		puts(mlx_strerror(mlx_errno));
		return (1);
	}
	data->tex_w = mlx_load_png("textures/west.png");
	if (!data->tex_w)
	{
		puts(mlx_strerror(mlx_errno));
		return (1);
	}
	return (0);
}

//******************************************************************************
//******************************************************************************



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
			.X = 4.5,
			.Y = 1.5,
			.angle = 90.05, //.0204 if distance is more than 0.5
			.speed = 0.1
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

