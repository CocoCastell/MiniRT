/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelon      +#+  +:+       +#+        */
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

void	init_scene(t_miniRt *minirt)
{
	t_scene *scene;

	scene = malloc(sizeof(t_scene));
	if (scene == NULL)
		free_error(minirt, "Error malloc in init scene\n", 1);
	scene->camera.x = 0;
	scene->camera.y = 0;
	scene->camera.z = 0;
	scene->nb_of_objects = 0;
	scene->viewport_width = VIEWPORT_WIDTH;
	scene->viewport_height = WIN_HEIGHT * VIEWPORT_WIDTH / WIN_WIDTH;
	minirt->scene = scene;
}

// void	init_objects(t_scene *scene)
// {
	
// }

void	init_minirt(t_miniRt *minirt)
{
	init_mlx(minirt);
	init_scene(minirt);
	// init_objects();
}