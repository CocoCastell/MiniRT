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
 * @brief Determine if apoint is in shadow relative to a light source.
 * 
 * Casts a ray from the hit point toward the light and checks if any object
 * (sphere, plane, cylinder) intersects the ray before reaching the light.
 * Ignores the object that generated the hit to avoid self-shadowing.
 * 
 * @param ray Ray from the hit point to the light source.
 * @param scene Pointer to the scene containing all objects.
 * @param max_dist Maximum distance to consider for intersections (distance to light).
 * @return true if the ray is occluded by any object before reaching the light.
 * @return false if the ray reaches the light without obstruction.
 */
bool	is_in_shadow(t_ray ray, t_scene *scene, float max_dist)
{
	t_hit_info	light_hit;
	int      i;

	i = -1;
	light_hit.has_hit = false;
	light_hit.distance = max_dist;

  while (++i < scene->sphere.count && scene->settings.sphere_on == true)
	{
    sphere_intersect(&light_hit, ray, &scene->sphere, i);
		if (light_hit.has_hit == true && light_hit.distance * light_hit.distance <= max_dist)
			return (true);
	}
	i = -1;
	while (++i < scene->plane.count && scene->settings.plane_on == true)
	{
    plane_intersect(&light_hit, ray, &scene->plane, i);
		if (light_hit.has_hit == true && light_hit.distance * light_hit.distance <= max_dist)
			return (true);
	}
	i = -1;
	/* while (++i < scene->cylinder.count)
	{
    light_hit = cylinder_intersect(ray, scene->cylinder, i);
		if (light_hit.has_hit == true && light_hit.distance * light_hit.distance <= max_dist)
			return (true);
	} */
	return (false);
}

/**
 * @brief Determine if apoint is in shadow relative to a light source.
 *        without performing additional intersection tests.
 * 
 * This function uses dot product properties to "early exit" in 
 * cases where the point cannot be illuminated:
 * - For a sphere, if the ray toward the light points inside the sphere,
 *   the point is considered to be in shadow.
 * - For a plane, if the light source is on the same side of the plane
 *   as the camera, the point is considered in shadow (light is blocked
 *   by the plane itself).
 * 
 * Normals are oriented towards the incident ray (from the camera) after 
 * the intersection tests.
 * 
 * @param hit Pointer to the intersection information of the tested point.
 * @param ray Ray from the point toward the light source.
 * @return true if the point is considered to be in shadow without further tests.
 * @return false otherwise (more further intersection tests are required).
 */
bool	pre_shadow_calcul(t_hit_info *hit, t_ray ray)
{
	if (hit->type == SPHERE && dot(hit->normal, ray.direction) <= 0)
		return (true);
	if (hit->type == PLANE && ((dot(hit->normal, ray.direction) < 0 && dot(hit->normal, hit->incident_ray) < 0) || (dot(hit->normal, ray.direction) > 0 && dot(hit->normal, hit->incident_ray) > 0)))
		return (true);
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