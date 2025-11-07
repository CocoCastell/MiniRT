/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/11/07 20:04:08 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_ray	get_camera_ray(float y, float x, t_v_port *v_port, t_vec3 cam_pos)
{
	t_vec3	offset;
	t_vec3	direction;

	offset = add_vector(
			scale_vector(v_port->right_vec, x - WIN_WIDTH / 2.0f),
			scale_vector(v_port->up_vec, WIN_HEIGHT / 2.0f - y));
	direction = add_vector(v_port->v_port_center, offset);
	direction = normalize(vector_from_to(cam_pos, direction));
	return (make_ray(cam_pos, direction));
}

void	scene_intersect(t_hit_info *hit, t_ray ray, t_scene *scene)
{
	int	i;

	i = -1;
	while (++i < scene->sphere.count)
		sphere_intersect(hit, ray, &scene->sphere, i);
	i = -1;
	while (++i < scene->plane.count && scene->settings.plane_on == true)
		plane_intersect(hit, ray, &scene->plane, i);
	i = -1;
	while (++i < scene->cylinder.count)
		cylinder_intersect(hit, ray, &scene->cylinder, i);
	i = -1;
	/* while (++i < scene->triangle.count) */
	/* 	triangle_intersect(hit, ray, scene->triangle, i); */
}

t_color	antialias_trace(t_scene *scene, int pix[2], int i)
{
	t_hit_info	hit;
	t_color		color;
	t_ray		ray;

	color = create_color(0.0f, 0.0f, 0.0f);
	while (++i < SAMPLE_PER_PIX)
	{
		ray = get_camera_ray(rand_offset(pix[0]), rand_offset(pix[1]), \
				&scene->v_port, scene->camera.pos);
		init_ray(&hit, false);
		scene_intersect(&hit, ray, scene);
		if (hit.has_hit == true)
		{
			hit.incident_ray = ray.direction;
			hit.point = ray_at(ray.origin, ray.direction, hit.distance);
			apply_reflections(scene, &hit, DEPTH);
		}
		else
			hit.color = scene->background;
		color = add_color_no_limit(color, hit.color);
	}
	scene->selection.type_grid[pix[0]][pix[1]] = hit.type;
	scene->selection.index_grid[pix[0]][pix[1]] = hit.ent_index;
	return (color);
}

t_color	trace(t_scene *scene, int pix[2])
{
	t_hit_info	hit;
	t_ray		ray;

	ray = get_camera_ray(pix[0], pix[1], &scene->v_port, scene->camera.pos);
	init_ray(&hit, false);
	scene_intersect(&hit, ray, scene);
	if (hit.has_hit == true)
	{
		hit.incident_ray = ray.direction;
		hit.point = add_vector(
				ray.origin, scale_vector(ray.direction, hit.distance));
		apply_reflections(scene, &hit, DEPTH);
	}
	else
		hit.color = scene->background;
	scene->selection.type_grid[pix[0]][pix[1]] = hit.type;
	scene->selection.index_grid[pix[0]][pix[1]] = hit.ent_index;
	return (hit.color);
}

void	raytracing(t_minirt *minirt)
{
	int		pix[2];
	t_color	pix_color;

	pix[0] = -1;
	update_v_port(minirt->scene);
	while (++pix[0] < WIN_HEIGHT)
	{
		pix[1] = -1;
		while (++pix[1] < WIN_WIDTH)
		{
			if (minirt->scene->settings.antialias_on)
			{
				pix_color = antialias_trace(minirt->scene, pix, -1);
				mean_color(&pix_color, SAMPLE_PER_PIX);
			}
			else
				pix_color = trace(minirt->scene, pix);
			if (minirt->scene->settings.gamma_on == true)
				pix_color = gamma_correct(pix_color);
			put_pixel(pix[1], pix[0], &minirt->img, \
					float_color_to_int(pix_color));
		}
	}
	mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->img.img, 0, 0);
}
