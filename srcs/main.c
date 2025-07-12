/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/06/23 16:29:07 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	put_pixel(int x, int y, t_data_img *img, int color)
{
	char	*dst;

	if (x >= 0 && x < WIN_WIDTH && y < WIN_HEIGHT && y >= 0)
	{
		dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

t_ray make_ray(int pixel_index[2], t_scene *scene)
{
	t_ray		ray;
	t_vec3	viewport_point;

	viewport_point = add_vector(
		scalar_mult(scene->right_vec, pixel_index[0]), 
		scalar_mult(scene->up_vec, -pixel_index[1])
	);
	viewport_point.x -= VIEWPORT_WIDTH / 2.0f;
	viewport_point.y += scene->viewport_height / 2.0f; 
	// viewport_point.x = (pixel_index[0] + HALF_PIX) * PIXEL_RATIO - VIEWPORT_WIDTH / 2.0f;
	// viewport_point.y = -((pixel_index[1] + HALF_PIX) * PIXEL_RATIO - scene->viewport_height / 2.0f); 
	viewport_point.z = VIEWPORT_DIST;
	ray.origin = scene->camera.pos;
	ray.direction = normalise_vector(sub_vector(scene->camera.pos, viewport_point));
	return (ray);
}

t_hit_info intersection(t_ray ray, t_scene *scene)
{
	t_hit_info	hit_info[3];
	t_obj				*object;

	object = scene->objs;
	hit_info[0].has_hit = false;
	hit_info[0].point = vec3(100, 100, 100); 
	while (object != NULL)
	{
		if (object->obj_type == SPHERE)
			hit_info[1] = hit_sphere(ray, object->obj.sphere);
		if (hit_info[1].has_hit == true && vector_sq_length(hit_info[1].point) < vector_sq_length(hit_info[0].point))
			hit_info[0] = hit_info[1];
		object = object->next;
	}
	return (hit_info[0]);
}

t_hit_info	trace(t_scene *scene, t_ray ray)
{
	t_hit_info	hit_info;

	hit_info = intersection(ray, scene);
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

void	update_positions(t_scene *scene)
{
	scene->right_vec =;
	scene->up_vec = ;
}

void	raytracing(t_miniRt *minirt)
{
	int		pixel_index[2];
	t_hit_info	hit_info;
	t_color		color;
	t_ray	ray;

	update_positions(minirt);
	pixel_index[0] = -1;
	while (++pixel_index[0] < WIN_WIDTH)
	{
		pixel_index[1] = -1;
		while (++pixel_index[1] < WIN_HEIGHT)
		{
			ray = make_ray(pixel_index, minirt->scene);
			hit_info = trace(minirt->scene, ray);
			color = get_color(ray, hit_info);
			put_pixel(pixel_index[0], pixel_index[1], &minirt->img, convert_int_color(color));
		}
	}
	mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->img.img, 0, 0);
}

int main()
{
	t_miniRt	minirt;

	init_minirt(&minirt);
	event_manager(&minirt);
	printf("Starting raytring algo...\n");
	raytracing(&minirt);
	printf("Finished.\n");
	mlx_loop(minirt.mlx);
	return (0);
}