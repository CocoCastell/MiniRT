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

int	ft_floor(float value)
{
	// if (value >= 0)
		return (value);
	// value = 1 - value + 1;
}

void	tiled_pattern(t_hit_info *hit, t_plane *plane)
{
	t_vec3	local_hit;
	float		tile_size;
	float		joint_size;

	tile_size = 1.0f;
	joint_size = 0.1f;
	if(hit->ent_index != 0)
		return ;
  local_hit = vector_from_to(hit->point, plane->point[hit->ent_index]);
	if (local_hit.x < 0)
		local_hit.x = fabsf(local_hit.x - joint_size / 2);
	if (local_hit.z < 0)
		local_hit.z = fabsf(local_hit.z - joint_size / 2);
	local_hit.x = fmodf(local_hit.x, tile_size + joint_size);
	local_hit.z = fmodf(local_hit.z, tile_size + joint_size);
	if (local_hit.x < joint_size || local_hit.z < joint_size)
    hit->material_color = create_color(1.0f, 1.0f, 1.0f);
}

/**
 * @brief Render a checkered pattern on the surface of spheres.
 *
 * Transforms the intersection point coordinates into the sphere's local space
 * relative to its center, then converts these Cartesian coordinates to spherical
 * coordinates:
 * - ro: the radius, distance from the sphere center to the intersection point.
 * - theta [0, 2π]: the azimuthal angle (longitude), horizontal xz-plane.
 * - phi [0, π]: the polar angle (latitude), vertical y-axis.
 *
 * The angles are scaled according to the number of desired stripes (STRIPE_NB)
 * to assign the colors. An n modulo can be applied on the sum of the integer 
 * parts of the scaled angles to select between n colors.
 *
 * The resulting color is assigned to hit->material_color.
 *
 * @param hit Pointer to the hit information of the intersection point.
 * @param scene Pointer to the scene data containing spheres and settings.
 */
void  checkered_pattern(t_hit_info *hit, t_scene *scene)
{
  t_vec3  local_hit;
  float   ro;
  float   theta;
  float   phi;

  if (hit->type == PLANE && scene->settings.checkered_on && !hit->in_shadow)
		tiled_pattern(hit, &scene->plane);
  if (hit->type != SPHERE || !scene->settings.checkered_on)
    return ;
  local_hit = vector_from_to(hit->point, scene->sphere.center[hit->ent_index]);
  // float   project_point;
  // project_point = sqrt(local_intersec.x * local_intersec.x + local_intersec.z * local_intersec.z);
  // ro = sqrt(project_point * project_point + local_intersec.y * local_intersec.y);
  // theta = acos(local_intersec.x / project_point);
  ro = sqrt(local_hit.x * local_hit.x + local_hit.y * local_hit.y + local_hit.z * local_hit.z);
  theta = atan2(local_hit.z, local_hit.x) / (2 * M_PI / STRIPE_NB); // const
  phi = acos(local_hit.y / ro) / (M_PI / STRIPE_NB); // const
  if (((int)theta + (int)phi) % 3 == 0)
    hit->material_color = create_color(1.0f, 1.0f, 1.0f);
  else if (((int)theta + (int)phi) % 3 == 1)
    hit->material_color = create_color(0.2f, 0.6f, 1.0f);
  else
    hit->material_color = create_color(0.6f, 0.2f, 0.5f);
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