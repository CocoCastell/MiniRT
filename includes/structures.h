/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:38:53 by cochatel          #+#    #+#             */
/*   Updated: 2025/09/13 17:53:18 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "miniRT.h"

// ==== STRUCTURE UTILS ====
typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct s_color
{
	float	r;
	float	g;
	float	b;
	float	a;
}	t_color;

typedef struct s_plane_eq
{
	t_vec3	O;
	t_vec3	D;
	t_vec3	n;
	float	d;
}	t_plane_eq;

typedef struct s_quad_eq
{
	float	a;
	float	b;
	float	c;
	float	delta;
}	t_quad_eq;

// ==== PARSING ====
typedef struct s_obj_counter
{
	int	sphere;
	int	plane;
	int	cylinder;
	int	triangle;
	int	light;
	int	camera;
	int	ambient;
}	t_obj_counter;

typedef struct s_parse_data
{
	t_vec3	center;
	t_color	color;
	t_vec3	normal;
	t_vec3	point;
	t_vec3	point2;
	t_vec3	point3;
	float	radius;
	float	height;
	float	shininess;
	float	spec_force;
	float	reflectivity;	
	int		count;
}	t_parse_data;

// ==== ENTITIES ==== 
typedef enum e_ent_type
{
	CAMERA,
	LIGHT,
	PLANE,
	SPHERE,
	CYLINDER,
	CYLINDER_CAP,
	TRIANGLE
}	t_ent_type;

typedef struct s_sphere
{
	int		count;
	float	*radius;
	t_vec3	*center;
	t_color	*color;
	float	*shininess;
	float	*spec_force;
	float	*reflectivity;	
}	t_sphere;

typedef struct s_plane
{
	int		count;
	t_color	*color;
	t_vec3	*point;
	t_vec3	*normal;
	float	*shininess;
	float	*spec_force;
	float	*reflectivity;	
}	t_plane;

typedef struct s_cylinder
{
	int		count;
	float	*radius;
	float	*height;
	t_vec3	*axis;
	t_vec3	*center;
	t_color	*color;
	float	*shininess;
	float	*spec_force;
	float	*reflectivity;	
}	t_cylinder;

typedef struct s_camera
{
	t_vec3			pos;
	t_vec3			right;
	t_vec3			up;
	t_vec3			forward;
	t_vec3			world_up;
	unsigned int	fov;
}	t_camera;

typedef struct s_triangle
{
	int		count;
	t_vec3	*pointA;
	t_vec3	*pointB;
	t_vec3	*pointC;
	t_color	*color;
	float	*shininess;
	float	*spec_force;
	float	*reflectivity;
}	t_triangle;

typedef struct s_light
{
	t_vec3	*pos;
	t_color	*color;
	float	*intensity;
	int		count;
}	t_light;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;

// ==== RAYTRACING ====
typedef struct s_selection
{
	t_ent_type	sel_type;
	int			sel_index;
	int			x_mouse;
	int			y_mouse;
	t_ent_type	type_grid[WIN_HEIGHT][WIN_WIDTH];
	int			index_grid[WIN_HEIGHT][WIN_WIDTH];
}	t_selection;


typedef struct s_cylinder_hit
{
    float   t;
    int     is_cap;
    t_vec3  normal;
}   t_cyl_hit;

typedef struct s_hit_info
{
	bool		has_hit;
	bool		in_shadow;
	t_ray		*ray;
	int			ent_index;
	t_ent_type	type;
	float		distance;
	t_vec3		point;
	t_vec3		normal;
	t_vec3		light_dir;
	t_vec3		light_vec;
	t_vec3		incident_ray;
	t_color		color;
	t_color		material_color;
	float		dist_attenuation;
}	t_hit_info;

typedef struct s_v_port
{
	t_vec3	up_vec;
	t_vec3	right_vec;
	t_vec3	v_port_center;
	float	v_port_width;
	float	v_port_height;
	float	x_offsets[WIN_WIDTH];
	float	y_offsets[WIN_HEIGHT];
}	t_v_port;

typedef struct s_settings
{
	bool	mirror_on;
	bool	gamma_on;
	bool	plane_on;
	bool	antialias_on;
	bool	checkered_on;
	bool	scene_creation_on;
}	t_settings;

typedef struct s_scene
{
	t_camera	camera;
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
	t_triangle	triangle;
	t_light		light;
	t_color		background;
	t_color		amb_color;
	float		amb_ratio;
	t_v_port	v_port;
	t_selection	selection;
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
	void		*mlx;
	void		*win;
	t_data_img	img;
	t_scene		*scene;
	char		**array1;
	int			fd;
}	t_minirt;

#endif
