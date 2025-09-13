/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minirt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/06/23 16:29:07 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	init_mlx(t_minirt *minirt)
{
	minirt->mlx = mlx_init();
	if (minirt->mlx == NULL)
		exit_error("Mlx init error\n", 1);
	minirt->win = mlx_new_window(minirt->mlx, WIN_WIDTH, WIN_HEIGHT, "Mini Raytracer");
	minirt->array1 = NULL;
	if (minirt->win == NULL)
		free_error(minirt, "Win init error\n", 1);
	minirt->img.img = mlx_new_image(minirt->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (minirt->img.img == NULL)
		free_error(minirt, "Img init error\n", 1);
	minirt->img.addr = mlx_get_data_addr(minirt->img.img, &minirt->img.bpp, \
			&minirt->img.line_length, &minirt->img.endian);
	if (minirt->img.addr == NULL)
		free_error(minirt, "Img addr init error\n", 1);
}

void	init_obj_struct(t_scene *scene, t_obj_counter counter)
{
	init_sphere(scene, counter.sphere);
	init_plane(scene, counter.plane);
	init_cylinder(scene, counter.cylinder);
	init_triangle(scene, counter.triangle);
	init_light(scene, counter.light);
}

void	init_all_objects(int fd, t_minirt *minirt, char *file)
{
	char					*line;
	int						is_eof;
	t_obj_counter	counter;
	
	is_eof = 0;
  counter = count_objects(fd, minirt);
	init_obj_struct(minirt->scene, counter);
	fd = get_fd_file(file, minirt);
	minirt->fd = fd;
	while (true)
	{
		line = get_next_line(fd, &is_eof);
		if (line == NULL && is_eof == -1)
        free_error(minirt, "Get_next_line error\n", 1);
    if (line == NULL)
        break ;
		put_object_in_structure(line, minirt);
	}
	close(fd);
	minirt->fd = -1;
}

void init_settings(t_settings *settings)
{
	settings->mirror_on = false;
	settings->plane_on = true;
	settings->gamma_on = false;
	settings->sphere_on = true;
	settings->antialias_on = false;
	settings->checkered_on = true;
}

void	init_minirt(t_minirt *minirt, char *file)
{
	t_scene			*scene;
	int					fd;

	if (has_rt_extension(file) == 0)
		free_error(minirt, "Not an .rt file.\n", 1);
	init_mlx(minirt);
	fd = get_fd_file(file, minirt);
	minirt->fd = fd;
	scene = malloc(sizeof(t_scene));
	if (scene == NULL)
		free_error(minirt, "Error malloc in init scene\n", 1);
	minirt->scene = scene;
	init_all_objects(fd, minirt, file);
	// init_pixel_offsets(scene);
	scene->background = create_color(0.3f, 0.5f, 0.7f);
	scene->selection.sel_type = CAMERA;
	scene->selection.sel_index = 0;
	init_settings(&scene->settings);
}





void	init_objects(t_scene *scene)
{
	t_sphere		sphere;
	// t_plane			plane;
	// t_cylinder	cylinder;

	// ATTENTION convertir diam en rayon
	sphere.count = 1;
	sphere.radius = malloc(sizeof(float) * sphere.count);
	sphere.color = malloc(sizeof(t_color) * sphere.count);
	sphere.center = malloc(sizeof(t_vec3) * sphere.count);
	sphere.shininess = malloc(sizeof(float) * sphere.count);
	sphere.spec_force = malloc(sizeof(float) * sphere.count);
	sphere.reflectivity = malloc(sizeof(float) * sphere.count);
	// sphere[0] = create_sphere(vec3(0.9, -0.6, -2), 0.6, create_color(0.9f, 0.0f, 0.0f));
	// sphere[1] = create_sphere(vec3(-0.8, -0.5, -4), 0.6, create_color(0.0f, 0.0f, 0.9f));
	sphere.radius[0] = 1.5f;
	sphere.color[0] = create_color(0.3f, 0.9f, 0.05f);
	sphere.shininess[0] = 40.0f;
	sphere.spec_force[0] = 0.3;
	sphere.center[0] = vec3(-1.0f, 0.0f, 5.0f); 
	sphere.reflectivity[0] = 0.00f; 
	scene->sphere = sphere;
/* 	sphere.radius[1] = 0.5;
	sphere.color[1] = create_color(0.0f, 0.0f, 0.9f);
	sphere.center[1] = vec3(-0.5, 0, -3); 
	sphere.shininess[1] = 40.0f;
	sphere.spec_force[1] = 0.5;
	sphere.reflectivity[1] = 0.1f; 
	sphere.radius[2] = 1.0f;
	sphere.color[2] = create_color(0.7f, 0.7f, 0.0f);
	sphere.center[2] = vec3(0.2, -1, -4); 
	sphere.shininess[2] = 90.0f;
	sphere.spec_force[2] = 0.9;
	sphere.reflectivity[2] = 0.15f;
	scene->sphere = sphere;

	plane.count = 2;
	plane.point = malloc(sizeof(t_vec3) * plane.count);
	plane.normal= malloc(sizeof(t_vec3) * plane.count);
	plane.color = malloc(sizeof(t_color) * plane.count);
	plane.shininess = malloc(sizeof(float) * plane.count);
	plane.spec_force = malloc(sizeof(float) * plane.count);
	plane.reflectivity = malloc(sizeof(float) * plane.count);
	plane.point[0] = vec3(0, 3, 0);
	plane.normal[0] = vec3(0, 1, -0.1);
	plane.color[0] = create_color(0.3f, 0.1f, 0.8f);
	plane.reflectivity[0] = 0.0f; 
	plane.point[1] = vec3(1, 0, 0);
	plane.normal[1] = vec3(1, 0, 0);
	plane.color[1] = create_color(0.6f, 0.0f, 0.5f);
	plane.reflectivity[1] = 0.0f; 
	scene->plane = plane;

	cylinder.count = 1;
	cylinder.radius = malloc(sizeof(float) * cylinder.count);
	cylinder.height = malloc(sizeof(float) * cylinder.count);
	cylinder.axis = malloc(sizeof(t_vec3) * cylinder.count);
	cylinder.center = malloc(sizeof(t_vec3) * cylinder.count);
	cylinder.color = malloc(sizeof(t_color) * cylinder.count);
	cylinder.shininess = malloc(sizeof(float) * cylinder.count);
	cylinder.spec_force = malloc(sizeof(float) * cylinder.count);
	cylinder.reflectivity = malloc(sizeof(float) * cylinder.count);
	cylinder.radius[0] = 1.0f;
	cylinder.height[0] = 0.1f;
	cylinder.axis[0] = vec3(0, 1, 0);
	cylinder.center[0] = vec3(0, 0, -6); 
	cylinder.color[0] = create_color(0.8f, 0.8f, 0.3f);
	cylinder.shininess[0] = 30.0f;
	cylinder.spec_force[0] = 0.5f;
	cylinder.reflectivity[0] = 0.1f;
	scene->cylinder = cylinder */;
}

void	init_lights(t_scene *scene)
{
	t_light	light;

	light.count = 2;
	light.pos = malloc(sizeof(t_vec3) * light.count);
	light.color = malloc(sizeof(t_color) * light.count);
	light.intensity = malloc(sizeof(float) * light.count);
	light.pos[0] = vec3(0, 3, -1);
	light.color[0] = create_color(0.9f, 0.9f, 0.9f);
	light.intensity[0] = 0.5f;
	light.pos[1] = vec3(0, -3, -1);
	light.color[1] = create_color(0.0f, 0.0f, 0.0f);
	light.intensity[1] = 0.8f;
	scene->light = light;
}