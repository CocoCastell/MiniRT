/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/06/23 16:29:07 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	init_mlx(t_miniRt *minirt)
{
	minirt->mlx = mlx_init();
	if (minirt->mlx == NULL)
		exit_error("Mlx init error\n", 1);
	minirt->win = mlx_new_window(minirt->mlx, WIN_WIDTH, WIN_HEIGHT, "Mini Raytracer");
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

void init_pixel_offsets(t_scene *scene)
{
    int i;
    
    for (i = 0; i < WIN_WIDTH; i++)
        scene->v_port.x_offsets[i] = i - WIN_WIDTH / 2.0f;
    for (i = 0; i < WIN_HEIGHT; i++)
        scene->v_port.y_offsets[i] = WIN_HEIGHT / 2.0f - i;
}

void	init_camera(t_scene *scene)
{
	t_camera	camera;

	camera.pos = vec3(0, 0, 0);
	camera.world_up = vec3(0, 1, 0);
	camera.forward = vec3(0, 0, -1);
	camera.right = normalize(cross(camera.forward, camera.world_up));
	camera.up = normalize(cross(camera.right, camera.forward));
	camera.fov = 60;
	scene->camera = camera;
}

void	init_objects(t_scene *scene)
{
	t_sphere		sphere;
	t_plane			plane;

	sphere.count = 3;
	sphere.radius = malloc(sizeof(float) * sphere.count);
	sphere.color = malloc(sizeof(t_color) * sphere.count);
	sphere.center = malloc(sizeof(t_vec3) * sphere.count);
	sphere.shininess = malloc(sizeof(float) * sphere.count);
	sphere.spec_force = malloc(sizeof(float) * sphere.count);
	// sphere[0] = create_sphere(vec3(0.9, -0.6, -2), 0.6, create_color(0.9f, 0.0f, 0.0f));
	// sphere[1] = create_sphere(vec3(-0.8, -0.5, -4), 0.6, create_color(0.0f, 0.0f, 0.9f));
	sphere.radius[0] = 0.4;
	sphere.color[0] = create_color(0.9f, 0.0f, 0.0f);
	sphere.shininess[0] = 40.0f;
	sphere.spec_force[0] = 0.5;
	sphere.center[0] = vec3(1, 0, -5); 
	sphere.radius[1] = 0.5;
	sphere.color[1] = create_color(0.0f, 0.0f, 0.9f);
	sphere.center[1] = vec3(-0.5, 0, -3); 
	sphere.shininess[1] = 40.0f;
	sphere.spec_force[1] = 0.5;
	sphere.radius[2] = 1.0f;
	sphere.color[2] = create_color(0.7f, 0.7f, 0.0f);
	sphere.center[2] = vec3(0.2, -1, -4); 
	sphere.shininess[2] = 40.0f;
	sphere.spec_force[2] = 0.5;
	scene->sphere = sphere;

	plane.count = 1;
	plane.point = malloc(sizeof(t_vec3) * plane.count);
	plane.normal= malloc(sizeof(t_vec3) * plane.count);
	plane.color = malloc(sizeof(t_color) * plane.count);
	plane.point[0] = vec3(0, 2, 0);
	plane.normal[0] = vec3(0, 1, 0);
	plane.color[0] = create_color(0.3f, 0.8f, 0.5f);
	scene->plane = plane;
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

void	init_minirt(t_miniRt *minirt)
{
	t_scene			*scene;
	t_selection	entity_selected;

	init_mlx(minirt);
	scene = malloc(sizeof(t_scene));
	if (scene == NULL)
		free_error(minirt, "Error malloc in init scene\n", 1);
	init_camera(scene);
	init_objects(scene);
	init_lights(scene);
	// init_pixel_offsets(scene);
	scene->amb_color = create_color(1.0f, 1.0f, 1.0f);
	scene->amb_ratio = 0.7f;
	entity_selected.type = CAMERA;
	entity_selected.index = 0;
	scene->entity_selected = entity_selected;
	minirt->scene = scene;
}