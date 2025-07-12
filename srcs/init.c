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

void	init_camera(t_camera *camera)
{
	camera->pos = vec3(0, 0, 0);
	camera->world_up = vec3(0, 1, 0);
	camera->forward = vec3(0, 0, -1);
	camera->right = normalise_vector(cross(camera->forward, camera->world_up));
	camera->up = normalise_vector(cross(camera->right, camera->forward));
}

void	init_scene(t_miniRt *minirt)
{
	t_scene *scene;

	scene = malloc(sizeof(t_scene));
	if (scene == NULL)
		free_error(minirt, "Error malloc in init scene\n", 1);
	scene->objs = NULL;
	init_camera(&scene->camera);
	scene->viewport_width = VIEWPORT_WIDTH;
	scene->viewport_height = WIN_HEIGHT * VIEWPORT_WIDTH / WIN_WIDTH;
	float r = scene->viewport_width / WIN_WIDTH;
	float u = scene->viewport_height/ WIN_HEIGHT;
	scene->right_vec = scalar_mult(scene->camera.right, r);
	scene->up_vec = scalar_mult(scene->camera.up, u);
	minirt->scene = scene;
	// init_viewport(&scene->viewport);
}

void	init_objects(t_scene *scene)
{
	t_sphere		sph1;
	t_sphere		sph2;
	t_obj				*obj1;
	t_obj				*obj2;
	
	obj1 = malloc(sizeof(t_obj));
	obj2 = malloc(sizeof(t_obj));
	// while ()
	// {
	//		créer liste
	// }
	sph1 = create_sphere(vec3(0, -0.6, 2), 0.6, create_color2(0.9f, 0.0f, 0.0f));
	sph2 = create_sphere(vec3(-0.8, -0.5, 4), 0.6, create_color2(0.0f, 0.0f, 0.9f));
	obj1->obj.sphere = sph1;
	obj1->obj_type = SPHERE;
	obj2->obj.sphere = sph2;
	obj2->obj_type = SPHERE;
	obj2->next = NULL;
	obj1->next = obj2;
	scene->objs = obj1;
}

void	init_minirt(t_miniRt *minirt)
{
	init_mlx(minirt);
	init_scene(minirt);
	init_objects(minirt->scene);
}