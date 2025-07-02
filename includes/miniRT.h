#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <math.h>
# include "../mlx_linux/mlx.h"
# include "../mlx_linux/mlx_int.h"
# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line_bonus.h"
# include "../libft/includes/ft_printf_bonus.h"

# define WIN_WIDTH 1400
# define WIN_HEIGHT 800
# define VIEWPORT_WIDTH 2.0f
# define VIEWPORT_DIST 1 
# define PIXEL_RATIO (VIEWPORT_WIDTH / WIN_WIDTH)
# define ESC 65307

typedef struct s_vec3
{
	float x;
	float y;
	float z;
}	t_vec3;

typedef struct s_color
{
	int r;
	int g;
	int b;
	int a;
}	t_color;

typedef struct s_hit_info
{
	bool has_hit;
	t_vec3 point;
	t_vec3 normal;
}	t_hit_info;

typedef struct s_data_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		frame_count;
}	t_data_img;

typedef struct s_ray
{
	t_vec3 origin;
	t_vec3 direction;
}	t_ray;

typedef struct s_scene
{
	t_vec3	camera;
	t_color	color;
	int		nb_of_objects;
	float	viewport_width;
	float	viewport_height;
	float	pixel_ratio;
}	t_scene;

typedef struct s_miniRt
{
	void		*mlx;
	void		*win;
	t_data_img	img;
	t_scene		*scene;
}	t_miniRt;


// Colors
t_color create_color(t_vec3 rgb, int alpha);
int		convert_int_color(t_color color);

// Init
void	init_scene(t_miniRt *minirt);
void	init_mlx(t_miniRt *minirt);
void	init_minirt(t_miniRt *minirt);

// Events
void	event_manager(t_miniRt *minirt);
int		key_pressed(int keycode, t_miniRt *minirt);
int     my_close(t_miniRt *minirt);

// Vector operation
float	vector_length(t_vec3 vect);
t_vec3  normalise_vector(t_vec3 vector);

// Error
void	exit_error(char *msg, int error);
void	free_mlx(t_miniRt *minirt);
void	free_error(t_miniRt *minirt, char *msg, int error);

#endif
