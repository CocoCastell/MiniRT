/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/06/23 16:29:07 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	init_ray(t_hit_info *hit, t_vec3 max_distance, bool in_shadow)
{
	hit->has_hit = false;
	hit->point = max_distance; //depth limit a mettre dans structure car const 
	hit->type = CAMERA;
	hit->distance = 999;
	hit->ent_index = 0;
  hit->in_shadow = in_shadow;
}

t_ray	make_ray(t_vec3 origin, t_vec3 direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

t_color gamma_correct(t_color color)
{
    return create_color(pow(color.r, 1.0 / 2.2),
                pow(color.g, 1.0 / 2.2),
                pow(color.b, 1.0 / 2.2));
}

float	rand_offset(float value)
{
   return (value + ((float)rand() / (float)RAND_MAX) - 0.5f);
}

void  update_v_port(t_scene *scene)
{
  t_camera  *camera;
  t_v_port  *viewport;
  float     vec_w;
  float     vec_h;

  viewport = &scene->v_port;
 	camera = &scene->camera;
  viewport->v_port_height = 2.0f * tan(to_radian(camera->fov) / 2.0f) * v_port_DIST;
  viewport->v_port_width = WIN_WIDTH * viewport->v_port_height / WIN_HEIGHT;
  viewport->v_port_center = add_vector(camera->pos, scale_vector(camera->forward, v_port_DIST));
  vec_w = viewport->v_port_width / WIN_WIDTH;
	vec_h = viewport->v_port_height/ WIN_HEIGHT;
	viewport->right_vec = scale_vector(camera->right, vec_w);
	viewport->up_vec = scale_vector(camera->up, vec_h);
}

