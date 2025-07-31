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

#include "../includes/miniRT.h"

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

float get_shininess(t_scene *scene, t_hit_info *hit)
{
  if (hit->type == SPHERE)
    return (scene->sphere.shininess[hit->ent_index]);
  // else if (hit->type == PLANE)
  //   return (scene->plane.shininess[hit->ent_index]);
  // else if (hit->type == CYLINDER)
  //   return (scene->cylinder.shininess[hit->ent_index]);
  return (0.0f);
}

float get_spec_force(t_scene *scene, t_hit_info *hit)
{
  if (hit->type == SPHERE)
    return (scene->sphere.spec_force[hit->ent_index]);
  // else if (hit->type == PLANE)
  //   return (scene->plane.spec_force[hit->ent_index]);
  // else if (hit->type == CYLINDER)
  //   return (scene->cylinder.spec_force[hit->ent_index]);
  return (0.0f);
}

t_vec3 get_reflected_vec(t_vec3 incident_vec, t_vec3 normal)
{
    t_vec3 scaled_normal;

    scaled_normal = scale_vec(normal, 2.0f * dot(normal, incident_vec));
    return (vector_from_to(scaled_normal, incident_vec));
}

void  fill_hit_normal(t_hit_info *hit, t_scene *scene)
{ 
  if (hit->type == SPHERE)
    hit->normal = normalize(vector_from_to(scene->sphere.center[hit->ent_index], hit->point));
  // if (hit->type == PLANE)
  // hit->normal = normalize();
  // if (hit->type == CYLINDER)
  // hit->normal = normalize();
}

float distance_attenuation(t_vec3 vector)
{
  float a = 1.0f;
  float b = 0.05f;
  float c = 0.001f;

  return (1.0f / (a + b*vector_length(vector) + c*vector_sq_length(vector)));
}

void	fill_light_data(t_hit_info *hit, t_scene *scene, int i)
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