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

t_ray get_camera_ray(const int y, const int x, t_v_port *v_port, t_vec3 cam_pos)
{
	t_vec3	offset;
	t_vec3	v_port_point;
	t_vec3	norm_vector;

	// offset = (add_vector(
	// 	scale_vec(scene->v_port.right_vec, scene->v_port.x_offsets[pix_index[1]]),
		// scale_vec(scene->v_port.up_vec, scene->v_port.y_offsets[pix_index[0]]))); 
	offset = (add_vector(
		scale_vec(v_port->right_vec, x - WIN_WIDTH / 2.0f),
		scale_vec(v_port->up_vec, WIN_HEIGHT / 2.0f - y))); 
	v_port_point = add_vector(v_port->v_port_center, offset);
	norm_vector = normalize(vector_from_to(cam_pos, v_port_point));
	return (make_ray(cam_pos, norm_vector));
}

void	scene_intersect(t_hit_info *hit, t_ray ray, t_scene *scene, t_vec3 max_dist)
{
	int      i;

	i = -1;
	init_ray(hit, max_dist);
 	while (++i < scene->sphere.count && scene->settings.sphere_on == true)
    sphere_intersect(hit, ray, scene->sphere, i);
	i = -1;
	while (++i < scene->plane.count && scene->settings.plane_on == true)
		plane_intersect(hit, ray, scene->plane, i);
	// i = -1;
	// while (++i < scene->cylinder.count)
	// 	cylinder_intersect(hit, ray, scene->cylinder, i);
	// i = -1;
	// while (++i < scene->triangle.count)
	// 	triangle_intersect(hit, ray, scene->triangle, i);
}

t_color	trace(t_scene *scene, t_ray ray, const int pix_index[2])
{
	t_hit_info	hit;

	scene_intersect(&hit, ray, scene, vec3(100, 100, 100)); //const
	scene->selection.type_grid[pix_index[0]][pix_index[1]] = hit.type;
	scene->selection.index_grid[pix_index[0]][pix_index[1]] = hit.ent_index;
	if (hit.has_hit == true)
	{
  	hit.incident_ray = ray.direction; 
  	hit.point = add_vector(ray.origin, scale_vec(ray.direction, hit.distance));
		apply_reflections(scene, &hit, DEPTH);
	}	
	else
		hit.color = scene->background; 
	return (hit.color);
}

void	raytracing(t_miniRt *minirt)
{
	int		      pix[2];
	t_color			color;
	t_ray       ray;
	t_scene			*scene;

	pix[0] = -1;
	scene = minirt->scene;
	update_v_port(scene);
	while (++pix[0] < WIN_HEIGHT)
	{
		pix[1] = -1;
		while (++pix[1] < WIN_WIDTH)
		{
			ray = get_camera_ray(pix[0], pix[1], &scene->v_port, scene->camera.pos);
      color = trace(scene, ray, pix);
			if (scene->settings.gamma_on == true)
				color = gamma_correct(color);
			put_pixel(pix[1], pix[0], &minirt->img, float_color_to_int(color));
		}
	}
	mlx_put_image_to_window(minirt->mlx, minirt->win, minirt->img.img, 0, 0);
}