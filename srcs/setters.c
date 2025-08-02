/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/06/23 16:29:07 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void  set_hit_normal(t_hit_info *hit, t_scene *scene)
{ 
  if (hit->type == SPHERE)
    hit->normal = normalize(vector_from_to(scene->sphere.center[hit->ent_index], hit->point));
  if (hit->type == PLANE)
    hit->normal = scene->plane.normal[hit->ent_index]; 
  // if (hit->type == CYLINDER)
  // hit->normal = normalize();
}

void  set_hit_color(t_hit_info *hit, t_scene *scene)
{ 
  if (hit->type == SPHERE)
		hit->color = scene->sphere.color[hit->ent_index];
  if (hit->type == PLANE)
		hit->color = scene->plane.color[hit->ent_index];
  // if (hit->type == CYLINDER)
		// hit->color = scene->cylinder.color[hit->ent_index];
}

void	set_light_data(t_hit_info *hit, t_scene *scene, int i)
{
  t_ray		light_ray;
	t_vec3	light_vec;
	t_vec3	shadow_bias_pos;

	light_vec = vector_from_to(hit->point, scene->light.pos[i]);
  hit->light_dir = normalize(light_vec);
	shadow_bias_pos = add_vector(hit->point, scale_vec(hit->normal, 0.01f));
	light_ray = make_ray(shadow_bias_pos, hit->light_dir);
	hit->in_shadow = false;
  if (is_in_shadow(light_ray, scene, hit, vector_sq_length(light_vec)))
	{
		hit->in_shadow = true;
		return ;
	}
	hit->dist_attenuation = distance_attenuation(light_vec);
}