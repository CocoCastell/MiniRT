/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/09/20 12:12:33 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/**
 * @brief Adds a cylinder at index i in a SoA structure.
 *
 * This function inserts the cylinder data (center, color, radius, etc.)
 * into the corresponding arrays of the `t_cylinder` structure at the given idx.
 * 
 * @param data Parsed cylinder data to insert (position, color, radius, etc.).
 * @param cylinder Structure holding SoA arrays of all cylinders.
 * @param i Index at which to insert the cylinder data in the `cylinder` struct.
 */
void	add_cylinder(t_parse_data data, t_cylinder cylinder, int i)
{
	cylinder.radius[i] = data.radius;
	cylinder.height[i] = data.height;
	cylinder.axis[i] = data.normal;
	cylinder.center[i] = data.center;
	cylinder.color[i] = data.color;
	cylinder.shininess[i] = data.shininess;
	cylinder.spec_force[i] = data.spec_force;
	cylinder.reflectivity[i] = data.reflectivity;
}

// void rotate_cylinder()
// {

// }
t_quad_eq tmp(t_ray ray, t_cylinder *cylinder, int i)
{
  t_ray p0_ray;
  t_quad_eq q;
  t_vec3 center;

  p0_ray.origin = vec3(ray.origin.x, 0, ray.origin.z);
  p0_ray.direction = vec3(ray.direction.x, 0, ray.direction.z);
  center = vec3(cylinder->center[i].x, 0, cylinder->center[i].z);
  q = compute_quadratic_data(p0_ray, center, cylinder->radius[i]);
  return (q);
}

void  disk_intersect(t_hit_info *hit, t_ray ray, t_cylinder *cylinder, int i)
{
  t_hit_info plane_hit;
  t_plane plane;

  plane.point = malloc(sizeof(t_vec3));
  if (plane.point == NULL)
    return ;
  plane.normal = malloc(sizeof(t_vec3));
  if (plane.normal == NULL)
  {
    free(plane.point);
    return ;
  }
  plane.point[0] = vec3(cylinder->center[i].x, cylinder->center[i].y + cylinder->height[i] / 2, cylinder->center[i].z);
  plane.normal[0] = cylinder->axis[i];
	init_ray(&plane_hit, vec3(999, 999, 999), false);
  plane_intersect(&plane_hit, ray, &plane, 0);

  t_vec3 inter = vec3((ray.origin.x + plane_hit.distance * ray.direction.x), (ray.origin.y + plane_hit.distance * ray.direction.y), (ray.origin.z + plane_hit.distance * ray.direction.z)); 
  t_vec3 tmp = vector_from_to(plane.point[0], inter);
  free(plane.point);
  free(plane.normal);
  if (vector_length(tmp) > cylinder->radius[i] || plane_hit.distance > hit->distance)
    return ;
  hit->distance = plane_hit.distance;
  hit->has_hit = true;
  hit->ent_index = i;
  hit->type = CYLINDER_CAP;
}

void  cylinder_intersect(t_hit_info *hit, t_ray ray, t_cylinder *cylinder, int i)
{
  t_quad_eq   q;
  float       sq_delta;
  float       intersection_height;
  float       t[3];

  q = tmp(ray, cylinder, i);
  if (q.delta < 0)
    return ;
  sq_delta = sqrt(q.delta);
	t[1] = (-q.h - sq_delta) / q.a;
	t[2] = (-q.h + sq_delta) / q.a;
	if (t[1] > 0)
		t[0] = t[1];
	else if (t[2] > 0)
		t[0] = t[2];
	else
		return ;
	if (t[0] > hit->distance)
    return ;
  intersection_height = fabsf((ray.origin.y + t[0] * ray.direction.y) - cylinder->center[i].y);
  if (intersection_height > cylinder->height[i] / 2)
    return (disk_intersect(hit, ray, cylinder, i));
  hit->has_hit = true;
  hit->distance = t[0];
  hit->ent_index = i;
  hit->type = CYLINDER;
}
