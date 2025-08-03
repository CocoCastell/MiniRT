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

/**
 * @brief Determine if a point is in shadow relative to a light source.
 * 
 * Casts a ray from the hit point toward the light and checks if any object
 * (sphere, plane, cylinder) intersects the ray before reaching the light.
 * Ignores the object that generated the hit to avoid self-shadowing.
 * 
 * @param ray Ray from the hit point to the light source.
 * @param scene Pointer to the scene containing all objects.
 * @param hit Pointer to the hit information of the original intersection.
 * @param max_dist Maximum distance to consider for intersections (distance to light).
 * @return true if the ray is occluded by any object before reaching the light.
 * @return false if the ray reaches the light without obstruction.
 */
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
	i = -1;
	while (++i < scene->plane.count)
	{
		if (hit->type == SPHERE && hit->ent_index == i)
			continue ;
    light_hit = plane_intersect(ray, scene->plane, i);
		if (light_hit.has_hit == true && light_hit.distance * light_hit.distance <= max_dist)
			return (true);
	}
	i = -1;
	/* while (++i < scene->cylinder.count)
	{
		if (hit->type == SPHERE && hit->ent_index == i)
			continue ;
    light_hit = cylinder_intersect(ray, scene->cylinder, i);
		if (light_hit.has_hit == true && light_hit.distance * light_hit.distance <= max_dist)
			return (true);
	} */
	return (false);
}

/**
 * @brief Computes distance attenuation factor based on vector length.
 *
 * Models light intensity drop-off using a quadratic attenuation formula:
 * 1 / (a + b * distance + c * distance^2)
 *
 * @param vector Vector from light to point.
 * @return Attenuation factor (0 < factor <= 1).
 */
float distance_attenuation(t_vec3 vector)
{
  float	a;
  float	b;
  float c;

	a = 1.0f;
	b = 0.01f;
	c = 0.00025f;
  return (1.0f / (a + b*vector_length(vector) + c*vector_sq_length(vector)));
}