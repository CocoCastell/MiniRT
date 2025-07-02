/* ************************************************************************** */ /*                                                                            */
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

t_vec3 vec3(t_vec3 origin_point, t_vec3 dest_point)
{
	t_vec3 vector;

	vector.x = dest_point.x - origin_point.x;
	vector.y = dest_point.y - origin_point.y;
	vector.z = dest_point.z - origin_point.z;
	return (vector);
}

t_ray make_ray(int pixel_index[2], t_scene *scene)
{
	t_ray	ray;
	t_vec3	viewport_point;

	viewport_point.x = pixel_index[0] * PIXEL_RATIO + PIXEL_RATIO / 2;
	viewport_point.y = -(pixel_index[1] * PIXEL_RATIO + PIXEL_RATIO / 2); 
	viewport_point.z = VIEWPORT_DIST;
	ray.origin = scene->camera;
	ray.direction = normalise_vector(vec3(scene->camera, viewport_point));
	return (ray);
}

t_hit_info intersection(t_ray ray, t_scene *scene)
{
	t_hit_info hit_info;

	

	return (hit_info);
}

void	trace(t_scene *scene, t_data_img img, t_ray ray, int pixel_index[2])
{
	int			i;
	t_color		pix_color;
	t_hit_info	hit_info;
	// t_hit_info	closest_hit;

	i = -1;
	// while (++i < scene->nb_of_objects)
	// {
		// hit_info = intersection(ray, scene->object[i]);
		// if (hit_info.point.z < closest_hit.point.z)
		// 	closest_hit = hit_info;
	// }
	// pix_color = render_color(closest_hit);
	hit_info = intersection(ray, NULL);
	pix_color = create_color(ray.direction, 255);
	put_pixel(pixel_index[0], pixel_index[1], &img, convert_int_color(pix_color));
	(void)scene;
	(void)ray;
}

void	raytracing(t_miniRt *minirt)
{
	int		pixel_index[2];
	t_ray	ray;

	pixel_index[0] = -1;
	while (++pixel_index[0] < WIN_WIDTH)
	{
		pixel_index[1] = -1;
		while (++pixel_index[1] < WIN_HEIGHT)
		{
			ray = make_ray(pixel_index, minirt->scene);
			trace(minirt->scene, minirt->img, ray, pixel_index);	
		}
	}
	mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->img.img, 0, 0);
}

int main()
{
	t_miniRt minirt;

	init_minirt(&minirt);
	event_manager(&minirt);
	printf("Starting raytring algo...\n");
	raytracing(&minirt);
	printf("Finished...\n");
	mlx_loop(minirt.mlx);

	return (0);
}