/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/06/23 16:29:07 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_ray get_camera_ray(int pix_index[2], t_scene *scene)
{
	t_vec3	offset;
	t_vec3	v_port_point;
	t_vec3	norm_vector;

	// offset = (add_vector(
	// 	scale_vec(scene->v_port.right_vec, scene->v_port.x_offsets[pix_index[1]]),
		// scale_vec(scene->v_port.up_vec, scene->v_port.y_offsets[pix_index[0]]))); 
	offset = (add_vector(
		scale_vec(scene->v_port.right_vec, pix_index[1] - WIN_WIDTH / 2.0f),
		scale_vec(scene->v_port.up_vec, WIN_HEIGHT / 2.0f - pix_index[0] ))); 
	v_port_point = add_vector(scene->v_port.v_port_center, offset);
	norm_vector = normalize(vector_from_to(scene->camera.pos, v_port_point));
	return (make_ray(scene->camera.pos, norm_vector));
}

t_hit_info scene_intersect(t_ray ray, t_scene *scene, t_vec3 max_dist)
{
	t_hit_info	hit[2];
	int      i;

	i = -1;
	init_ray(&hit[0], max_dist);
  while (++i < scene->sphere.count)
	{
    hit[1] = sphere_intersect(ray, scene->sphere, i);
		if (hit[1].has_hit == true && hit[0].distance > hit[1].distance)
			hit[0] = hit[1];
		// if (hit[1].has_hit == true)
		// 	fill_hit_data(&hit[1], &ray, scene->sphere.color[i], i);
		// if (hit[1].has_hit == true && is_shorter_vec(hit[1].point, hit[0].point, scene->camera.pos) == true)
		// 	hit[0] = hit[1];
	}
	// fill_hit_data(&hit[0], &ray, scene->sphere.color[i], i);
	/* i = -1;
	while (++i < scene->plane.count)
	{
		hit[1] = plane_intersect(ray, scene->plane, i);
		if (hit[1].has_hit == true)
			fill_hit_data(&hit[1], &ray, scene->plane.color[i], i);
		if (hit[1].has_hit == true && is_shorter_vec(hit[1].point, hit[0].point, scene->camera.pos) == true)
			hit[0] = hit[1];
	} */
	// hit[0].ray = &ray;
	return (hit[0]);
}

t_color	trace(t_scene *scene, t_ray ray, int pix_index[2])
{
	t_hit_info	hit;

	hit = scene_intersect(ray, scene, vec3(100, 100, 100)); //const
	scene->selection_grid[pix_index[0]][pix_index[1]].type = hit.type;
	scene->selection_grid[pix_index[0]][pix_index[1]].index = hit.ent_index;
	if (hit.has_hit == true)
	{
  	hit.point = add_vector(ray.origin, scale_vec(ray.direction, hit.distance));
		hit.color = scene->sphere.color[hit.ent_index];
		apply_reflections(scene, &hit, DEPTH);
	}	
	else
		hit.color = create_color(0.3f, 0.5f, 0.7f);
	return (hit.color);
}

void	raytracing(t_miniRt *minirt)
{
	int		      pix_index[2];
	t_color			color;
	t_ray       ray;

	update_v_port(minirt->scene);
	pix_index[0] = -1;
	while (++pix_index[0] < WIN_HEIGHT)
	{
		pix_index[1] = -1;
		while (++pix_index[1] < WIN_WIDTH)
		{
			ray = get_camera_ray(pix_index, minirt->scene);
      color = trace(minirt->scene, ray, pix_index);
			// color = get_color(ray, hit_info, minirt->scene);
			put_pixel(pix_index[1], pix_index[0], &minirt->img, float_color_to_int(color));
		}
	}
	mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->img.img, 0, 0);
}