/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cochatel <cochatel@student.42barcelona     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:38:25 by cochatel          #+#    #+#             */
/*   Updated: 2025/06/23 16:29:07 by cochatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

/**
 * @brief Creates a sphere object.
 * 
 * @param	center Center of the sphere.
 * @param radius Radius of the sphere.
 * @param	color Color of the sphere.
 * @return the sphere created.
 */
t_sphere create_sphere(t_vec3 center, float radius, t_color color)
{
	t_sphere	sphere;

	sphere.center = center;
	sphere.radius = radius;
	sphere.color = color;
	return (sphere);
}

/**
 * @brief Compute the coefficients and discriminant of the ray-sphere intersection quadratic equation.
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
t_quad_data compute_quadratic_data(t_ray ray, t_sphere sph)
{
    t_quad_data q;
    t_vec3			m;
		
		m = sub_vector(sph.center, ray.origin);
    q.a = dot(ray.direction, ray.direction);
    q.h = dot(m, ray.direction);
    q.c = dot(m, m) - sph.radius * sph.radius;
    q.delta = q.h * q.h - q.a * q.c;
    return q;
}

/**
 * @brief Tests ray-sphere intersection and returns hit information.
 * 
 * @details Solves the quadratic equation: |P(t) - C|² = r²
 * Where P(t) = O + tD (ray equation)
 * Check if the sphere is behind the camera or not (t[]).
 * 
 * @param ray Incident ray.
 * @param sph Sphere to test against.
 * @return Hit information including point, normal, and color.
 */
t_hit_info hit_sphere(t_ray ray, t_sphere sph)
{
    t_hit_info	hit;
    t_quad_data	q;
		float				sq_delta;
		float				t[3];
		
		q = compute_quadratic_data(ray, sph);
    hit.has_hit = false;
		if (q.delta < 0) 
      return (hit);
		sq_delta = sqrt(q.delta);
    t[1] = (-q.h - sq_delta) / q.a;
    t[2] = (-q.h + sq_delta) / q.a;
		if (t[1] > 0)
			t[0] = t[1];
		else if (t[2] > 0)
			t[0] = t[2];
		else
      return (hit);
    hit.has_hit = true;
    hit.point = add_vector(ray.origin, scalar_mult(ray.direction, t[0]));
    hit.normal = normalise_vector(sub_vector(sph.center, hit.point));
		if (dot(ray.direction, hit.normal) < 0)
			hit.front_side = true;
		else
			hit.front_side = false;
    hit.color = linear_gradient(sph.color, create_color2(0.0f, 0.0f, 0.0f), 0.5 * (hit.normal.z + 1.0f));
    return (hit);
	}