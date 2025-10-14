/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minirt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/09/29 19:11:53 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	init_mlx(t_minirt *minirt)
{
	minirt->mlx = mlx_init();
	minirt->fd = -1;
	if (minirt->mlx == NULL)
		exit_error("Mlx init error\n", 1);
	minirt->win = mlx_new_window(minirt->mlx, WIN_WIDTH, WIN_HEIGHT, "MiniRT");
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
	char			*line;
	int				is_eof;
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

void	init_settings(t_settings *settings)
{
	settings->mirror_on = false;
	settings->plane_on = true;
	settings->gamma_on = false;
	settings->antialias_on = false;
	settings->checkered_on = false;
	settings->scene_creation_on = true;
}

void	init_minirt(t_minirt *minirt, char *file)
{
	t_scene	*scene;
	int		fd;

	if (has_rt_extension(file) == 0)
		exit_error("Not an .rt file.\n", 1);
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

/*
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
}*/
