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
# define WIN_WIDTH				800
# define WIN_HEIGHT				500
# define v_port_WIDTH 		2.0f
# define v_port_DIST			1 
# define PIXEL_RATIO			(v_port_WIDTH / WIN_WIDTH)
# define M_PIF						3.1415927f
# define STEP							0.3
# define ZOOM							0.1
# define SAMPLE_PER_PIX		1
#	define DEPTH						2
# define MATERIAL_PROPERTIES	3

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
# define PLUS_KEY				43	
# define MINUS_KEY			45
# define K_1						49
# define K_2						50
# define K_3						51
# define K_4						52
# define K_5						53
# define K_6						54
# define W_KEY					119
# define S_KEY					115
# define A_KEY					97
# define D_KEY					100
# define Q_KEY					113
# define R_KEY					114
# define E_KEY					101
#	define LEFT_K					65361
# define RIGHT_K				65363
# define UP_K						65362
# define DOWN_K					65364

// Color
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define WHITE "\033[1;37m"
# define BLACK "\033[1;30m"
# define BL "\033[94m"
# define DEF "\033[0m"

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

// ==== PARSING ====
typedef struct s_obj_counter
{
    int sphere;
    int plane;
    int cylinder;
    int light;
    int camera;
    int ambient;
} t_obj_counter;

typedef struct s_parse_data
{
	float		radius;
	t_vec3	center;
	t_color	color;
	t_vec3	normal;
	t_vec3	point;
	float		height;
	float		shininess;
	float		spec_force;
	float		reflectivity;	
	int			count;
}	t_parse_data;

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
	float		*reflectivity;	
	int			count;
}	t_sphere;

typedef struct s_plane
{
	t_color	*color;
	t_vec3	*point;
	t_vec3	*normal;
	float		*shininess;
	float		*spec_force;
	float		*reflectivity;	
	int			count;
}	t_plane;

typedef struct s_cylinder
{
	float		*radius;
	float		*height;
	t_vec3	*axis;
	t_vec3	*center;
	t_color	*color;
	float		*shininess;
	float		*spec_force;
	float		*reflectivity;	
	int			count;
}	t_cylinder;

typedef struct s_camera
{
	t_vec3				pos;
	t_vec3				right;
	t_vec3				up;
	t_vec3				forward;
	t_vec3				world_up;
	unsigned int	fov;
}	t_camera;

typedef struct s_light
{
	t_vec3	*pos;
	t_color	*color;
	float		*intensity;
	int			count;
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
	int					index;
} t_selection;

typedef struct s_hit_info
{
	bool				has_hit;
	bool				in_shadow;
	t_ray				*ray;
	int					ent_index;
	t_ent_type	type;
	float				distance;
	t_vec3			point;
	t_vec3			normal;
	t_vec3			light_dir;
	t_vec3			light_vec;
	t_vec3			incident_ray;
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

typedef struct s_settings
{
	bool				mirror_on;
	bool				gamma_on;
	bool				plane_on;
	bool				sphere_on;
} t_settings;

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
	t_settings	settings;
	// float				pixel_grid[WIN_HEIGHT][WIN_WIDTH];
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
	char				**array1;
}	t_miniRt;

// ===== FUNCTIONS =====

// == Controls ==

// Transformations 
void  update_v_port(t_scene *scene);
void  side_movement(int keycode, t_scene *scene);
void  move_entity(t_scene *scene, t_vec3 dest, float step);
void  rotation(int keycode, t_scene *scene);
void  scale_entity(t_scene *scene, int button);

// Events
void	event_manager(t_miniRt *minirt);
int		key_pressed(int keycode, t_miniRt *minirt);
int   my_close(t_miniRt *minirt);

// Control Utils
void    set_opposite_bool(bool *bool_to_set);
bool    is_movement_key(int keycode);
bool    is_rotation_key(int keycode);
bool    is_setting_key(int keycode);

// == Objects ==

// Light
t_color	ambient_reflection(t_scene *scene, t_color color);
void  	lambert_diffuse_reflection(t_hit_info *hit, t_light light, int i);
void 		specular_reflection(t_hit_info *hit, t_light light, int i, t_scene *scene);
void		mirror_reflection(t_hit_info *hit, t_scene *scene, unsigned int depth);
void		apply_reflections(t_scene *scene, t_hit_info *hit, unsigned int depth);

// Light Utils
bool		is_in_shadow(t_ray ray, t_scene *scene, t_hit_info*hit, float max_dist);
float		distance_attenuation(t_vec3 vector);

// Plane
t_hit_info	plane_intersect(t_ray ray, t_plane plane, int i);
void				add_plane(t_parse_data data, t_plane plane, int i);

// Cylinder
t_hit_info	cylinder_intersect(t_ray ray, t_cylinder cyl, int i);
void				add_cylinder(t_parse_data data, t_cylinder cylinder, int i);

// Sphere
void				add_sphere(t_parse_data data, t_sphere sphere, int i);
t_hit_info	sphere_intersect(t_ray ray, t_sphere sph, int i);
t_vec3			calculate_sphere_hit_point(float dir_scalar, t_ray ray, int i);

// == Maths ==

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
void		set_axis_angle_matrix(float matrix[3][3], t_vec3 axis, float angle);
t_vec3  negate_vec(t_vec3 vector);

// Raytracing
void				raytracing(t_miniRt *minirt);
t_hit_info	scene_intersect(t_ray ray, t_scene *scene, t_vec3 max_dist);

// Raytracing Utils
void		init_ray(t_hit_info *hit, t_vec3 max_distance);
t_ray		make_ray(t_vec3 origin, t_vec3 direction);
t_color gamma_correct(t_color color);

// Setters
void		set_light_data(t_hit_info *hit, t_scene *scene, int i);
void 		set_hit_normal(t_hit_info *hit, t_scene *scene);
void 		set_hit_color(t_hit_info *hit, t_scene *scene);

// Getters
float		get_spec_force(t_scene *scene, t_hit_info *hit);
float		get_shininess(t_scene *scene, t_hit_info *hit);
float		get_reflectivity(t_hit_info *hit, t_scene *scene);
t_vec3  get_reflected_vec(t_vec3 incident_vec, t_vec3 normal);

// Colors
t_color create_color(float r, float g, float b);
t_color scale_color(t_color color, float scalar);
t_color color_mult(t_color col1, t_color col2);
t_color	add_color(t_color color1, t_color color2);
int			float_color_to_int(t_color color);

// == Init ==

// Init
void	init_mlx(t_miniRt *minirt);
void	init_obj_struct(t_scene *scene, t_obj_counter counter);
void	init_all_objects(int fd, t_miniRt *minirt, char *file);
void	init_minirt(t_miniRt *minirt, char *file);

// Init Utils
int		get_fd_file(char *file, t_miniRt *minirt);
bool	has_rt_extension(const char *filename);
void	init_pixel_offsets(t_scene *scene);

// Init object structure
void  init_light(t_scene *scene, int light_nb);
void	init_cylinder(t_scene *scene, int cylinder_nb);
void	init_plane(t_scene *scene, int plane_nb);
void	init_sphere(t_scene *scene, int sphere_nb);

// Parse
void	parse_ambient(t_miniRt *minirt, char **data);
void	parse_camera(t_miniRt *minirt, char **data);
void  parse_light(t_miniRt *minirt, char **data);
int		put_object_in_structure(char *line, t_miniRt *minirt);

// Parse Objects
void  parse_sphere(t_miniRt *minirt, char **data);
void  parse_plane(t_miniRt *minirt, char **data);
void  parse_cylinder(t_miniRt *minirt, char **data);

// Parse Utils
t_color parse_color(char *str, t_miniRt *minirt);
t_vec3  parse_coordinates(char *str, t_miniRt *minirt);
t_vec3  parse_normal_vec(char *str, t_miniRt *minirt);
void		parse_material_properties(int nb_of_data, t_parse_data *values, char **data, t_miniRt *minirt);

// Count
t_obj_counter count_objects(int fd, t_miniRt *minirt);
void 					compute_count(char *token, t_obj_counter *counter, t_miniRt *minirt);
void  				init_counter(t_obj_counter *counter);

// Error
void	exit_error(char *msg, int error);
void	free_mlx(t_miniRt *minirt);
void	free_error(t_miniRt *minirt, char *msg, int error);

// Utils
void	put_pixel(int x, int y, t_data_img *img, int color);

// Create scene file
void	put_data_in_file(t_scene *scene);

#endif