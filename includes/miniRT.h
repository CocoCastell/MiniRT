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

// Consts
# define WIN_WIDTH			1100
# define WIN_HEIGHT			650
# define v_port_WIDTH 2.0f
# define v_port_DIST	1 
# define PIXEL_RATIO		(v_port_WIDTH / WIN_WIDTH)
# define M_PIF					3.1415927f
# define STEP						0.3
# define ZOOM						0.1
# define SAMPLE_PER_PIX	1
#	define DEPTH					2

// Control keys
# define ESC						65307
# define LEFT_CLICK 		1
# define WHEEL					2
# define RIGHT_CLICK 		3
# define SCROLL_UP 			4
# define SCROLL_DOWN 		5
# define KEY_1					49
# define KEY_2					50
# define KEY_3					51
# define KEY_4					52
# define SPACE					32
# define SHIFT					65505	
# define CTRL						65307
# define W_KEY					119
# define S_KEY					115
# define A_KEY					97
# define D_KEY					100
# define Q_KEY					113	
# define E_KEY					101
#	define LEFT_K					65361
# define RIGHT_K				65363
# define UP_K						65362
# define DOWN_K					65364

// ==== STRUCTURE UTILS ====
typedef struct s_vec3
{
	float x;
	float y;
	float z;
}	t_vec3;

typedef struct s_color
{
	float r;
	float g;
	float b;
	float a;
}	t_color;

typedef struct s_plane_eq
{
	t_vec3	O;
	t_vec3	D;
	t_vec3	n;
	float		d;
}	t_plane_eq;

typedef struct s_quad_eq
{
	float	h;
	float	a;
	float	c;
	float	delta;
}	t_quad_eq;

// ==== ENTITIES ==== 
typedef enum e_ent_type
{
	CAMERA,
	LIGHT,
	PLANE,
	SPHERE,
	CYLINDER,
	TRIANGLE
}	t_ent_type;

typedef struct s_sphere
{
	float		*radius;
	t_vec3	*center;
	t_color	*color;
	float		*shininess;
	float		*spec_force;	
	int			count;
}	t_sphere;

typedef struct s_plane
{
	t_color	*color;
	t_vec3	*point;
	t_vec3	*normal;
	int			count;
}	t_plane;

typedef struct s_cylinder
{
	float		*diameter;
	float		*height;
	t_vec3	*center;
	t_color	*color;
	int			count;
}	t_cylinder;

typedef struct s_camera
{
	t_vec3				pos;
	t_vec3				right;
	t_vec3				up;
	t_vec3				forward;
	t_vec3				world_up;
	unsigned char	fov;
}	t_camera;

typedef struct s_light
{
	t_vec3	*pos;
	t_color	*color;
	float		*intensity;
	int	count;
}	t_light;

typedef struct s_ray
{
	t_vec3 origin;
	t_vec3 direction;
}	t_ray;

// ==== RAYTRACING ====
typedef struct s_selection 
{
	t_ent_type	type;
	int			index;
} t_selection;

typedef struct s_hit_info
{
	bool				has_hit;
	bool				in_shadow;
	t_ray				*ray;
	int			ent_index;
	t_ent_type	type;
	float				distance;
	t_vec3			point;
	t_vec3			normal;
	t_vec3			light_dir;
	t_vec3			light_vec;
	t_color			color;
	float				dist_attenuation;
}	t_hit_info;

typedef struct s_v_port
{
	t_vec3		up_vec;
	t_vec3		right_vec;
	t_vec3		v_port_center;
	float			v_port_width;
	float			v_port_height;
	float			x_offsets[WIN_WIDTH];
	float			y_offsets[WIN_HEIGHT];
}	t_v_port;

typedef struct s_scene
{
	t_camera		camera;
	t_sphere		sphere;
	t_cylinder	cylinder;
	t_plane			plane;
	t_light			light;
	t_color			amb_color;
	float				amb_ratio;
	t_v_port		v_port;
	t_selection	selection_grid[WIN_HEIGHT][WIN_WIDTH];
	t_selection	entity_selected;
	float				pixel_grid[WIN_HEIGHT][WIN_WIDTH];
}	t_scene;

// ==== MLX ====
typedef struct s_data_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		frame_count;
}	t_data_img;

typedef struct s_miniRt
{
	void				*mlx;
	void				*win;
	t_data_img	img;
	t_scene			*scene;
}	t_miniRt;

// ===== FUNCTIONS =====

// Raytracing
void				raytracing(t_miniRt *minirt);
t_hit_info	scene_intersect(t_ray ray, t_scene *scene, t_vec3 max_dist);
t_ray				get_reflect_ray(t_hit_info *hit, t_scene *scene);

// Raytracing Utils
void	init_ray(t_hit_info *hit, t_vec3 max_distance);
void	fill_hit_data(t_hit_info *hit, t_ray *ray, t_color color, int i);
t_ray	make_ray(t_vec3 origin, t_vec3 direction);

// Light
t_color	ambient_reflection(t_scene *scene, t_color color);
void 		specular_reflection(t_hit_info *hit, t_light light, int i, t_scene *scene);
void  	lambert_diffuse_reflection(t_hit_info *hit, t_light light, int i);
void		apply_reflections(t_scene *scene, t_hit_info *hit, unsigned int depth);

// Light Utils
t_vec3  get_reflected_vec(t_vec3 incident_vec, t_vec3 normal);
void		fill_light_data(t_hit_info *hit, t_scene *scene, int i);
void 		fill_hit_normal(t_hit_info *hit, t_scene *scene);
bool		is_in_shadow(t_ray ray, t_scene *scene, t_hit_info*hit, float max_dist);
float		distance_attenuation(t_vec3 vector);
float		get_spec_force(t_scene *scene, t_hit_info *hit);
float		get_shininess(t_scene *scene, t_hit_info *hit);

// Transformations 
void  update_v_port(t_scene *scene);
void  side_movement(int keycode, t_scene *scene);
void  move_entity(t_scene *scene, t_vec3 dest, float step);
void  rotation(int keycode, t_scene *scene);
void  scale_entity(t_scene *scene, int button);

// Plane
t_hit_info	plane_intersect(t_ray ray, t_plane plane, int i);

// Sphere
t_sphere		create_sphere(t_vec3 center, float radius, t_color color);
t_hit_info	sphere_intersect(t_ray ray, t_sphere sph, int i);
t_vec3			calculate_sphere_hit_point(float dir_scalar, t_ray ray, int i);

// Colors
t_color	linear_gradient(t_color color1, t_color color2, float a);
t_color	get_color(t_ray ray, t_hit_info hit_info, t_scene *scene);
t_color create_color(float r, float g, float b);
t_color scale_color(t_color color, float scalar);
t_color color_mult(t_color col1, t_color col2);
t_color	add_color(t_color color1, t_color color2);
int			float_color_to_int(t_color color);

// Init
void	init_scene(t_miniRt *minirt);
void	init_mlx(t_miniRt *minirt);
void	init_minirt(t_miniRt *minirt);

// Events
void	event_manager(t_miniRt *minirt);
int		key_pressed(int keycode, t_miniRt *minirt);
int   my_close(t_miniRt *minirt);

// Vector operation
float		max(float a, float b);
t_vec3  cross(t_vec3 vec1, t_vec3 vec2);
t_vec3  scale_vec(t_vec3 vector, float scalar);
t_vec3  normalize(t_vec3 vector);
t_vec3	vector_from_to(t_vec3 origin_point, t_vec3 dest_point);
t_vec3  add_vector(t_vec3 vector1, t_vec3 vector2);
t_vec3  vec3(float x, float y, float z);
t_vec3  scale_vector(t_vec3 vector, float scale_factor);
float   dot(t_vec3 vector1, t_vec3 vector2);
float		vector_length(t_vec3 vect);
float 	vector_sq_length(t_vec3 vect);
float   to_radian(float degree);
t_vec3  apply_rotation(t_vec3 vector, float  R[3][3]);
bool		is_shorter_vec(t_vec3 main_vec, t_vec3 vec_to_compare, t_vec3 origin_point);
t_vec3  vec_mult(t_vec3 vecA, t_vec3 vecB);
void		fill_axis_angle_matrix(float matrix[3][3], t_vec3 axis, float angle);
t_vec3  negate_vec(t_vec3 vector);

// Error
void	exit_error(char *msg, int error);
void	free_mlx(t_miniRt *minirt);
void	free_error(t_miniRt *minirt, char *msg, int error);

// Utils
void	put_pixel(int x, int y, t_data_img *img, int color);

#endif