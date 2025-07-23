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

t_ray make_ray(int pixel_index[2], t_scene *scene)
{
	t_ray		ray;
	t_vec3	offset;
	t_vec3	viewport_point;

	offset = (add_vector(
		scalar_mult(scene->right_vec, pixel_index[1] - WIN_WIDTH / 2.0f), 
		scalar_mult(scene->up_vec, WIN_HEIGHT / 2.0f - pixel_index[0] ))
	);
	viewport_point = add_vector(scene->viewport_center, offset);
	ray.origin = scene->camera.pos;
	ray.direction = normalise_vector(sub_vector(scene->camera.pos, viewport_point));
	return (ray);
}

t_hit_info intersection(t_ray ray, t_scene *scene)
{
	t_hit_info	hit_info[2];
	t_sphere    sphere;

  sphere = scene->sphere;
	init_ray(hit_info, &scene->camera);
	size_t i = 0;
  while (i < sphere.count)
	{
    hit_info[1] = hit_sphere(ray, sphere, i);
    hit_info[1].type = SPHERE;
    hit_info[1].ent_index = i;
		if (hit_info[1].has_hit == true && is_shorter_vec(hit_info[1].point, hit_info[0].point, scene->camera.pos) == true)
		  hit_info[0] = hit_info[1];
    i++;
  }
	return (hit_info[0]);
}

t_hit_info	trace(t_scene *scene, t_ray ray, int pixel_index[2])
{
	t_hit_info	hit_info;

	hit_info = intersection(ray, scene);
	scene->selection_grid[pixel_index[0]][pixel_index[1]].type = hit_info.type;
	scene->selection_grid[pixel_index[0]][pixel_index[1]].index = hit_info.ent_index;
	return (hit_info);
}

t_color	get_color(t_ray ray, t_hit_info hit_info)
{
	t_color pix_color;

	if (hit_info.has_hit == false)
	{
		if (ray.direction.y > -0.1)
			pix_color = create_color2(0.5f, 0.5f, 0.9f);
		else
			pix_color = create_color2(0.0f, 0.5f, 0.0f);
	}
	else
		pix_color = hit_info.color;
	return (pix_color);
}

void	raytracing(t_miniRt *minirt)
{
	int		pixel_index[2];
	t_hit_info	hit_info;
	t_color		color;
	t_ray	ray;

	update_viewport(minirt->scene);
	pixel_index[0] = -1;
	while (++pixel_index[0] < WIN_HEIGHT)
	{
		pixel_index[1] = -1;
		while (++pixel_index[1] < WIN_WIDTH)
		{
			ray = make_ray(pixel_index, minirt->scene); hit_info = trace(minirt->scene, ray, pixel_index);
			color = get_color(ray, hit_info);
			put_pixel(pixel_index[1], pixel_index[0], &minirt->img, convert_int_color(color));
		}
	}
	mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->img.img, 0, 0);
}
