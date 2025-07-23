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

void	init_camera(t_scene *scene)
{
	t_camera	camera;

	camera.pos = vec3(0, 0, 0);
	camera.world_up = vec3(0, 1, 0);
	camera.forward = vec3(0, 0, -1);
	camera.right = normalise_vector(cross(camera.forward, camera.world_up));
	camera.up = normalise_vector(cross(camera.right, camera.forward));
	camera.fov = 60;
	scene->camera = camera;
}

void	init_objects(t_scene *scene)
{
	t_sphere		sphere;

	sphere.count = 2;
	sphere.radius = malloc(sizeof(float) * sphere.count);
	sphere.color = malloc(sizeof(t_color) * sphere.count);
	sphere.center = malloc(sizeof(t_vec3) * sphere.count);
	// sphere[0] = create_sphere(vec3(0.9, -0.6, -2), 0.6, create_color2(0.9f, 0.0f, 0.0f));
	// sphere[1] = create_sphere(vec3(-0.8, -0.5, -4), 0.6, create_color2(0.0f, 0.0f, 0.9f));a
	sphere.radius[0] = 0.4;
	sphere.color[0] = create_color2(0.9f, 0.0f, 0.0f);
	sphere.center[0] = vec3(1, 0, -4); 
	sphere.radius[1] = 0.5;
	sphere.color[1] = create_color2(0.0f, 0.0f, 0.9f);
	sphere.center[1] = vec3(-0.5, 0, -2); 
	scene->sphere = sphere;
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
	entity_selected.type = CAMERA;
	entity_selected.index= CAMERA;
	scene->entity_selected = entity_selected;
	minirt->scene = scene;
}