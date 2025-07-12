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

# define WIN_WIDTH 1100
# define WIN_HEIGHT 700
# define VIEWPORT_WIDTH 2.0f
# define VIEWPORT_DIST 1 
# define HALF_PIX 0.5
# define PIXEL_RATIO (VIEWPORT_WIDTH / WIN_WIDTH)
# define SAMPLE_PER_PIXEL 1
# define ESC 65307
# define LEFT_CLICK 1
# define WHEEL 2
# define RIGHT_CLICK 3
# define SCROLL_UP 4
# define SCROLL_DOWN 5
# define KEY_1 49
# define KEY_2 50
# define KEY_3 51
# define KEY_4 52
# define SPACE 32
# define W_KEY 119
# define S_KEY 115
# define A_KEY 97
# define D_KEY 100

// Structure Utils
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

typedef struct s_quad_data
{
	float	h;
	float	a;
	float	c;
	float	delta;
}	t_quad_data;

// Objects

typedef enum e_obj_type
{
	PLANE,
	SPHERE,
	CYLINDER,
	TRIANGLE
}	t_obj_type;

typedef struct s_sphere
{
	float		radius;
	t_vec3	center;
	t_color	color;
}	t_sphere;

typedef struct s_plane
{
	t_color	color;
}	t_plane;

typedef struct s_cylinder
{
	float		diameter;
	float		height;
	t_vec3	center;
	t_color	color;
}	t_cylinder;

typedef union u_obj
{
	t_plane			plane;
	t_sphere		sphere;
	t_cylinder	cylinder;
}	t_obj_union;

typedef struct s_obj
{
	t_obj_type		obj_type;
	t_obj_union		obj;
	struct s_obj	*next;
}	t_obj;

// Algo
typedef struct s_hit_info
{
	bool		has_hit;
	bool		front_side;
	t_vec3	point;
	t_vec3	normal;
	t_color	color;
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

typedef struct s_camera
{
	t_vec3				pos;
	t_vec3				right;
	t_vec3				up;
	t_vec3				forward;
	t_vec3				world_up;
	unsigned char	fov;
}	t_camera;

typedef struct s_viewport
{
	t_vec3		up_vec;
	t_vec3		right_vec;
	float			viewport_width;
	float			viewport_height;
}	t_viewport;

typedef struct s_scene
{
	t_camera	camera;
	t_color		color;
	t_obj			*objs;
	t_vec3		up_vec;
	t_vec3		right_vec;
	float			viewport_width;
	float			viewport_height;
}	t_scene;

typedef struct s_miniRt
{
	void		*mlx;
	void		*win;
	t_data_img	img;
	t_scene		*scene;
}	t_miniRt;


// Main
void	raytracing(t_miniRt *minirt);

// Camera
void  camera_side_mouvement(int keycode, t_miniRt *minirt);

// Sphere
t_hit_info	hit_sphere(t_ray ray, t_sphere sph);
t_sphere		create_sphere(t_vec3 center, float radius, t_color color);
t_vec3			calculate_sphere_hit_point(float dir_scalar, t_ray ray);
float				calculate_sphere_delta(t_ray ray, t_sphere sph);

// Colors
t_color	linear_gradient(t_color color1, t_color color2, float a);
t_color create_color(t_vec3 rgb, int alpha);
t_color create_color2(float r, float g, float b);
int			convert_int_color(t_color color);

// Init
void	init_scene(t_miniRt *minirt);
void	init_mlx(t_miniRt *minirt);
void	init_minirt(t_miniRt *minirt);

// Events
void	event_manager(t_miniRt *minirt);
int		key_pressed(int keycode, t_miniRt *minirt);
int     my_close(t_miniRt *minirt);

// Vector operation
t_vec3  cross(t_vec3 vec1, t_vec3 vec2);
t_vec3  scalar_mult(t_vec3 vector, float scalar);
t_vec3  normalise_vector(t_vec3 vector);
t_vec3	sub_vector(t_vec3 origin_point, t_vec3 dest_point);
t_vec3  add_vector(t_vec3 vector1, t_vec3 vector2);
t_vec3  vec3(float x, float y, float z);
float   dot(t_vec3 vector1, t_vec3 vector2);
float		vector_length(t_vec3 vect);
float 	vector_sq_length(t_vec3 vect);

// Error
void	exit_error(char *msg, int error);
void	free_mlx(t_miniRt *minirt);
void	free_error(t_miniRt *minirt, char *msg, int error);

#endif
