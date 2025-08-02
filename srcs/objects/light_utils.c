/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/06/23 16:29:07 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

bool	is_in_shadow(t_ray ray, t_scene *scene, t_hit_info *hit, float max_dist)
{
	t_hit_info	light_hit;
	int      i;

	i = -1;
  while (++i < scene->sphere.count)
	{
		if (hit->type == SPHERE && hit->ent_index == i)
			continue ;
    light_hit = sphere_intersect(ray, scene->sphere, i);
		if (light_hit.has_hit == true && light_hit.distance * light_hit.distance <= max_dist)
			return (true);
	}
	return (false);
}

float distance_attenuation(t_vec3 vector)
{
  float a = 1.0f;
  float b = 0.05f;
  float c = 0.001f;

  return (1.0f / (a + b*vector_length(vector) + c*vector_sq_length(vector)));
}