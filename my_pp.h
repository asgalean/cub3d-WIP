#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

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


}  t_player;



typedef struct s_textures
{

} t_textures;


typedef struct s_datass
{
	t_map	*map;
	t_player *player;


} t_datass;

