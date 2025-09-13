#ifndef PROTOTYPES_H 
# define PROTOTYPES_H

# include "miniRT.h"

// ==== CONTROLS ====
// Rotations
void  rotation(int keycode, t_scene *scene);

// Translations
void  click_move_object(int x, int y, t_scene *scene);
void  side_movement(int keycode, t_scene *scene);
void  key_move_entity(t_scene *scene, t_vec3 dest, float step);
void  scale_entity(t_scene *scene, int button);

// Events
void  event_manager(t_minirt *minirt);
int		key_pressed(int keycode, t_minirt *minirt);
int   my_close(t_minirt *minirt);

// Control Utils
void  set_opposite_bool(bool *bool_to_set);
bool  is_movement_key(int keycode);
bool  is_rotation_key(int keycode);
bool  is_setting_key(int keycode);

// ==== LIGHT ====
// Light
void  ambient_reflection(t_scene *scene, t_hit_info *hit);
void  lambert_diffuse_reflection(t_hit_info *hit, t_light light, int i);
void 	specular_reflection(t_hit_info *hit, t_light light, int i, t_scene *scene);
void	mirror_reflection(t_hit_info *hit, t_scene *scene, unsigned int depth);
void	apply_reflections(t_scene *scene, t_hit_info *hit, unsigned int depth);

// Setters
void	set_light_data(t_hit_info *hit, t_scene *scene, int i);
void 	set_hit_normal(t_hit_info *hit, t_scene *scene);
void  set_hit_color(t_hit_info *hit, t_scene *scene);

// Getters
t_vec3  get_reflected_vec(t_vec3 incident_vec, t_vec3 normal);
float		get_spec_force(t_scene *scene, t_hit_info *hit);
float		get_shininess(t_scene *scene, t_hit_info *hit);
float		get_reflectivity(t_hit_info *hit, t_scene *scene);

// Light Utils
bool	is_in_shadow(t_ray ray, t_scene *scene, float max_dist);
bool	pre_shadow_calcul(t_hit_info *hit, t_ray ray);
float distance_attenuation(t_vec3 vector);
void  checkered_pattern(t_hit_info *hit, t_scene *scene);

// ==== OBJECTS ====
// Sphere
t_vec3  calculate_sphere_hit_point(float dir_scalar, t_ray ray, int i);
void		add_sphere(t_parse_data data, t_sphere sphere, int i);
void		sphere_intersect(t_hit_info *hit, t_ray ray, t_sphere *sph, int i);

// Plane
void		plane_intersect(t_hit_info *hit, t_ray ray, t_plane *plane, int i);
void		add_plane(t_parse_data data, t_plane plane, int i);

// Cylinder
t_hit_info  cylinder_intersect(t_ray ray, t_cylinder cyl, int i);
void				add_cylinder(t_parse_data data, t_cylinder cylinder, int i);

// Triangle
void  add_triangle(t_parse_data data, t_triangle triangle, int i);

// ==== INIT ====
// Init
void	init_mlx(t_minirt *minirt);
void	init_obj_struct(t_scene *scene, t_obj_counter counter);
void	init_all_objects(int fd, t_minirt *minirt, char *file);
void	init_minirt(t_minirt *minirt, char *file);

// Init Utils
bool	has_rt_extension(const char *filename);
void	init_pixel_offsets(t_scene *scene);
int		get_fd_file(char *file, t_minirt *minirt);

// Init object structure
void  init_light(t_scene *scene, int light_nb);
void	init_cylinder(t_scene *scene, int cylinder_nb);
void	init_plane(t_scene *scene, int plane_nb);
void	init_sphere(t_scene *scene, int sphere_nb);
void	init_triangle(t_scene *scene, int triangle_nb);

// Parse
void	parse_ambient(t_minirt *minirt, char **data);
void	parse_camera(t_minirt *minirt, char **data);
void  parse_light(t_minirt *minirt, char **data);
int		put_object_in_structure(char *line, t_minirt *minirt);

// Parse Objects
void  parse_sphere(t_minirt *minirt, char **data);
void  parse_plane(t_minirt *minirt, char **data);
void  parse_cylinder(t_minirt *minirt, char **data);

// Parse Utils
t_color parse_color(char *str, t_minirt *minirt);
t_vec3  parse_coordinates(char *str, t_minirt *minirt);
t_vec3  parse_normal_vec(char *str, t_minirt *minirt);
void		parse_material_properties(int nb_of_data, t_parse_data *values, char **data, t_minirt *minirt);

// Count
t_obj_counter count_objects(int fd, t_minirt *minirt);
void 					compute_count(char *token, t_obj_counter *counter, t_minirt *minirt);
void  				init_counter(t_obj_counter *counter);

// ==== MATHS ====
// Vector operations
t_vec3  cross(t_vec3 vec1, t_vec3 vec2);
t_vec3  scale_vector(t_vec3 vector, float scalar);
t_vec3  normalize(t_vec3 vector);
float   dot(t_vec3 vector1, t_vec3 vector2);

// Simple operations
float	max(float a, float b);
float	vector_length(t_vec3 vect);
float vector_sq_length(t_vec3 vect);
float to_radian(float degree);

// Angles
t_vec3  apply_rotation(t_vec3 vector, float  R[3][3]);
void		set_axis_angle_matrix(float matrix[3][3], t_vec3 axis, float angle);

// Create vectors
t_vec3	vector_from_to(t_vec3 origin_point, t_vec3 dest_point);
t_vec3  add_vector(t_vec3 vector1, t_vec3 vector2);
t_vec3  vec3(float x, float y, float z);
t_vec3  negate_vec(t_vec3 vector);

// ==== ROOT ====
// Raytracing
t_ray get_camera_ray(float y, float x, t_v_port *v_port, t_vec3 cam_pos);
void	scene_intersect(t_hit_info *hit, t_ray ray, t_scene *scene);
void	raytracing(t_minirt *minirt);

// Raytracing Utils
t_color gamma_correct(t_color color);
t_ray		make_ray(t_vec3 origin, t_vec3 direction);
float		rand_offset(float value);
void    init_ray(t_hit_info *hit, t_vec3 max_distance, bool in_shadow);
void		update_v_port(t_scene *scene);

// Colors
t_color create_color(float r, float g, float b);
t_color scale_color(t_color color, float scalar);
t_color color_mult(t_color col1, t_color col2);
t_color	add_color(t_color color1, t_color color2);
t_color	add_color_no_limit(t_color color1, t_color color2);
void		mean_color(t_color *color, int ratio);
int			float_color_to_int(t_color color);

// Error
void	exit_error(char *msg, int error);
void	free_mlx(t_minirt *minirt);
void	free_error(t_minirt *minirt, char *msg, int error);

// Utils
void	put_pixel(int x, int y, t_data_img *img, int color);

// Create scene file
void	put_data_in_file(t_scene *scene);

#endif