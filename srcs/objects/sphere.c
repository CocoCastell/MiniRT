/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/09/20 11:43:16 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/**
 * @brief Adds a sphere at index i in a SoA structure.
 *
 * This function inserts the sphere data (position, color, radius, etc.)
 * into the corresponding arrays of the `t_sphere` structure at the given index.
 * 
 * @param data Parsed sphere data to insert (position, color, radius, etc.).
 * @param sphere Structure holding SoA arrays of all spheres.
 * @param i Index at which to insert the sphere data in the `sphere` structure.
 */
void	add_sphere(t_parse_data data, t_sphere sphere, int i)
{
	sphere.center[i] = data.center;
	sphere.radius[i] = data.radius;
	sphere.color[i] = data.color;
	sphere.shininess[i] = data.shininess;
	sphere.spec_force[i] = data.spec_force;
	sphere.reflectivity[i] = data.reflectivity;
}

/**
 * @brief Compute the coefficients and discriminant of the ray-sphere
 * intersection quadratic equation.
 * 
 * @details Delta determines the number of intersections based on its value:
 * - delta < 0: no intersection
 * - delta = 0: one intersection
 * - delta > 0: two intersections 
 *  
 * @param ray Incident ray.
 * @param sph Sphere to test against.
 * @return the quadratic coefficients (a, h, c) and discriminant (delta). 
 */
t_quad_eq	compute_quadratic_data(t_ray ray, t_vec3 center, float radius)
{
	t_quad_eq	q;
	t_vec3		m;

	m = vector_from_to(center, ray.origin);
	q.a = dot(ray.direction, ray.direction);
	q.h = dot(m, ray.direction);
	q.c = dot(m, m) - radius * radius;
	q.delta = q.h * q.h - q.a * q.c;
	return (q);
}

/**
 * @brief Computes the intersection between a ray and a sphere.
 *
 * This function checks if the input ray intersects the i-th sphere and, if so,
 * stores the intersec distance, type, and entity index in a t_hit_info struct.
 *
 * @param ray The incident ray.
 * @param plane Structure containing all spheres in a SoA.
 * @param i Index of the sphere to test against.
 * @return A t_hit_info struct describing the hit result.
 */
void	sphere_intersect(t_hit_info *hit, t_ray ray, t_sphere *sphere, int i)
{
	t_quad_eq	q;
	float		sq_delta;
	float		t[3];

	q = compute_quadratic_data(ray, sphere->center[i], sphere->radius[i]);
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
	hit->has_hit = true;
	hit->distance = t[0];
	hit->type = SPHERE;
	hit->ent_index = i;
}
